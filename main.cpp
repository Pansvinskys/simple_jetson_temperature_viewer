#include <iostream>
#include <fstream>
#include <string>
#include <experimental/filesystem>
#include <regex>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;
namespace fs = std::experimental::filesystem;
typedef vector<fs::path> Devices;
typedef vector<string> Temps_per_Device;

string get_stem(const fs::path &p){
    return p.stem().string();
}

void get_thermal_devices(Devices &devices){
    string text;
    const fs::path dir_path{"/sys/devices/virtual/thermal"};
    regex thermal_regex("^thermal_zone\\d$");

    for(auto const& dir_entry: fs::directory_iterator{dir_path}){
	string file_name = get_stem(dir_entry);
        auto word_begin = sregex_iterator(file_name.begin(), file_name.end(), thermal_regex);
	auto word_end = std::sregex_iterator();

	if (distance(word_begin, word_end) > 0){
	    devices.push_back(dir_entry);
	}
    }
}

void get_devices_temp(const Devices &devices, Temps_per_Device &temps){
    for(auto device: devices){
        ifstream temperature_file(device.string() + "/temp");
	ifstream type_file(device.string() + "/type");
	string s;

	while(getline(type_file, s)){
            temps.push_back(s);
	}

	while(getline(temperature_file, s)){
	    stringstream stream;
	    stream << fixed << setprecision(2) << (stoi(s)/1000.0); 
            temps.back() = temps.back() + "\n" + stream.str() + " °C";
	}
    }
}

int main(){
    Devices devices;
    Temps_per_Device devices_temps;

    get_thermal_devices(devices);
    get_devices_temp(devices, devices_temps);
    for(auto temp : devices_temps){
        cout << temp << endl << endl;
    }
    return 0;
}
