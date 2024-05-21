#pragma once
#include "Device.h"

class SmartLight : public Device
{
private:
	unsigned brightnessLevel = 0;

public:
	SmartLight(const char* name, const char* manufacturer, unsigned brightnessLevel);

	SmartLight(const SmartLight& other);
	SmartLight(SmartLight&& other);

	SmartLight& operator=(const SmartLight& other);
	SmartLight& operator=(SmartLight&& other);

	void turnOff() const override;
	void turnOn() const override;
	void printDetails() const override;

	Device* clone() const override;
};