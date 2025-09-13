#include "dserial.h"

Napi::Value Serial(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

   if(info.Length() != 1) {
      Napi::TypeError::New(env, "Missing device path").ThrowAsJavaScriptException();
      return env.Null();
  }

  if(!info[0].IsString()) {
      Napi::TypeError::New(env, "Wrong type argument").ThrowAsJavaScriptException();
      return env.Null();
  }

  // Convert the JavaScript string to wide character string
  std::string devicePath = info[0].As<Napi::String>().Utf8Value();
  std::wstring wideDevicePath(devicePath.begin(), devicePath.end());
  
  HANDLE hDevice = CreateFileW(
      wideDevicePath.c_str(),   // file or device name to be opened (from info[0])
      0,                        // '0' - query device attributres without accessing it
      FILE_SHARE_READ,          // shared move of 'read'
      NULL,                     // cannot be inherited by any child process
      OPEN_EXISTING,            // opens the drive
      0,                        // device has not attributes nor flags 
      NULL                      // handle to a template file with GENERIC_READ access right
  );
  
  // STORAGE_PROPERTY_QUERY - indicates the properties of a storage device to retrieve
  //                          as the input buffer passd to the IOCTL_STORAGE_QUERY_PROPERTY
  //                          control code.
  STORAGE_PROPERTY_QUERY query;
  memset(&query, 0, sizeof(query)); // fills a block of memory with 0's to vaoid garbage values
  query.PropertyId = StorageDeviceProperty; 
  query.QueryType = PropertyStandardQuery; 

  BYTE buffer[1024] = {0}; // common 1024 sized buffer, with all intialized to '0'
  DWORD bytesReturned = 0;

  Napi::Value result = env.Null(); // default return value

  // DeviceIoControl - sends a control code to a specified device driver, causing the 
  //                   corresponding device to perform the corresponding operation
  if(DeviceIoControl(
      hDevice,
      IOCTL_STORAGE_QUERY_PROPERTY, // used to return the properties of a storage device
      &query,                       // pointer to the input buffer that contains the data required
      sizeof(query),                // size of the input buffer, in bytes
      &buffer,                      // pointer to the output buffer that is to receive the data returned
      sizeof(buffer),               // size of the output buffer, in bytes
      &bytesReturned,               // pointer to a variable that recieves the size of the data stored in output buffer, in bytes
      NULL                          // pointer to an OVERLAPPED structure
  )) {
      // Used to retrieve the storage device descriptor data for a device
      STORAGE_DEVICE_DESCRIPTOR* descriptor = (STORAGE_DEVICE_DESCRIPTOR*)buffer;

      if(descriptor->SerialNumberOffset != 0) {
          string serial = (char *)(buffer + descriptor->SerialNumberOffset);
          result = Napi::String::New(env, serial);
      }
  } 

  CloseHandle(hDevice);

  return result;
}

