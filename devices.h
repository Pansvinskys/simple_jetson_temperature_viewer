#ifndef DEVICES
#define DEVICES

#include <vector>
#include <string>
#include <experimental/filesystem>


class Devices{
    public:
        struct Device{ 
	    std::string type, temperature;
	};
        typedef std::vector<Devices::Device> DeviceVector;
	
	Devices();
	void getDevicesVector(DeviceVector &devicesExtRef);
    private:
	typedef std::vector<std::experimental::filesystem::path> DevicePaths;
        DeviceVector devices;
	DevicePaths devicePaths;
	std::string getStem(const std::experimental::filesystem::path &p);
	void getDevices(DevicePaths &devicePaths);
	void getTemperatureFromDevices(const DevicePaths &devicePaths, DeviceVector &devices);
};

#endif
