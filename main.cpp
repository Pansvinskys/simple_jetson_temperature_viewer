#include <iostream>
#include <string>
#include "devices.h"

using namespace std;

int main(int argc, char[] *argv){
    Devices dev;
    Devices::DeviceVector devices;
    dev.getDevicesVector(devices);
    for(auto device : devices){
        cout << device.type << endl << device.temperature << endl << endl;
    }
    return 0;
}
