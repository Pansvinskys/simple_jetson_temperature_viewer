#include <regex>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "devices.h"

Devices::Devices(){
    getDevices(devicePaths);
    getTemperatureFromDevices(devicePaths, devices);
}

std::string Devices::getStem(const std::experimental::filesystem::path &p){
    return p.stem().string();
}

void Devices::getDevicesVector(DeviceVector &devicesExtRef){
    devicesExtRef = devices;
}

void Devices::getDevices(DevicePaths &devicePaths){
    std::string text;
    const std::experimental::filesystem::path dir_path{"/sys/devices/virtual/thermal"};
    std::regex thermal_regex("^thermal_zone\\d$");

    for(auto const& dir_entry: std::experimental::filesystem::directory_iterator{dir_path}){
        std::string file_name = getStem(dir_entry);
        auto word_begin = std::sregex_iterator(file_name.begin(), file_name.end(), thermal_regex);
        auto word_end = std::sregex_iterator();

        if (std::distance(word_begin, word_end) > 0){
            devicePaths.push_back(dir_entry);
        }
    }
}

void Devices::getTemperatureFromDevices(const DevicePaths &devicePaths, DeviceVector &devices){
    for(auto device: devicePaths){
        std::ifstream temperature_file(device.string() + "/temp");
        std::ifstream type_file(device.string() + "/type");
        std::string s;
	std::string temp_string("");

        while(std::getline(type_file, s)){
            devices.push_back(Device{s, std::string()});
        }

        while(getline(temperature_file, s)){
    	std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << (stoi(s)/1000.0);
	    temp_string = temp_string + stream.str();
        }
        devices.back().temperature = temp_string + " °C";
    }
}

