#include <iostream>
#include "SmartHome.h"
#include "DeviceFactory.h"

int main() 
{
    SmartHome home;
    char continueInput = 'y';

    while (continueInput == 'y' || continueInput == 'Y') 
    {
        std::cout << "Add a new device? (Y/N): ";
        std::cin >> continueInput;

        if (continueInput == 'y' || continueInput == 'Y') 
        {
            Device* newDevice = deviceFactory();

            if (newDevice) 
            {
                home.addDevice(std::move(*newDevice));
                std::cout << "Device added successfully.\n";
            }
        }
    }

    //std::cout << "\nDevices in system:\n";

    /*for (int i = 0; i < home.getDevicesCount(); ++i) 
    {
        const Device* dev = home.getDevice(i);

        if (dev != nullptr) 
        {
            dev->turnOn();
            dev->printDetails();
            dev->turnOff();
        }
    }*/

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    home.removeDevice();

    SmartHome newHome = home;

    for (int i = 0; i < newHome.getDevicesCount(); i++)
    {
        const Device* dev = home.getDevice(i);

        if (dev != nullptr)
        {
            dev->turnOn();
            dev->printDetails();
            dev->turnOff();
        }
    }
}