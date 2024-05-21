#include <iostream>
#include "SmartLight.h"
#include "SmartSpeaker.h"
#include "SmartThermostat.h"

Device* deviceFactory() 
{
    int figureType;
    std::cout << "Enter device type (1=SmartLight, 2=SmartSpeaker, 3=SmartThermostat): ";
    std::cin >> figureType;
    std::cin.ignore();

    char name[100], manufacturer[100];

    switch (figureType) 
    {
    case 1: 
    {
        std::cout << "Enter light name: ";
        std::cin.getline(name, 100);
        std::cout << "Enter manufacturer: ";
        std::cin.getline(manufacturer, 100);
        unsigned brightnessLevel;
        std::cout << "Enter brightness level: ";
        std::cin >> brightnessLevel;
        std::cin.ignore();

        return new SmartLight(name, manufacturer, brightnessLevel);
    }
    case 2: 
    {
        std::cout << "Enter speaker name: ";
        std::cin.getline(name, 100);
        std::cout << "Enter manufacturer: ";
        std::cin.getline(manufacturer, 100);
        unsigned volumeLevel;
        std::cout << "Enter volume level: ";
        std::cin >> volumeLevel;
        std::cin.ignore();

        return new SmartSpeaker(name, manufacturer, volumeLevel);
    }
    case 3: 
    {
        std::cout << "Enter thermostat name: ";
        std::cin.getline(name, 100);
        std::cout << "Enter manufacturer: ";
        std::cin.getline(manufacturer, 100);
        int currentTemperature, wantedTemperature;
        std::cout << "Enter current temperature: ";
        std::cin >> currentTemperature;
        std::cout << "Enter wanted temperature: ";
        std::cin >> wantedTemperature;
        std::cin.ignore();

        return new SmartThermostat(name, manufacturer, currentTemperature, wantedTemperature);
    }
    default:
        std::cout << "Invalid device type." << std::endl;
        return nullptr;
    }
}
