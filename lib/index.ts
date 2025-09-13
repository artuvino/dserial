import bindings = require('bindings');
const dserialBindings = bindings('dserial');

export async function serial(physicalDevicePath: string): Promise<string | null> {
	return await dserialBindings.serial(physicalDevicePath);
}

const api = { serial };
export default api;
