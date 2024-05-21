#pragma once
#include "Device.h"

class SmartThermostat : public Device
{
private:
	int currentTemperature = 0;
	int wantedTemperature = 0;

	void copyFrom(const SmartThermostat& other);

public:
	SmartThermostat(const char* name, const char* manufacturer, int currTemperature, int wantedTemperature);

	SmartThermostat(const SmartThermostat& other);
	SmartThermostat(SmartThermostat&& other);

	SmartThermostat& operator=(const SmartThermostat& other);
	SmartThermostat& operator=(SmartThermostat&& other);

	void turnOff() const override;
	void turnOn() const override;
	void printDetails() const override;

	Device* clone() const override;
};