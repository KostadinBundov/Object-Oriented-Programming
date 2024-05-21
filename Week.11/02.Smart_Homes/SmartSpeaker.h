#pragma once
#include "Device.h"

class SmartSpeaker : public Device
{
private:
	unsigned volumeLevel = 0;

public:
	SmartSpeaker(const char* name, const char* manufacturer, unsigned volumeLevel);

	SmartSpeaker(const SmartSpeaker& other);
	SmartSpeaker(SmartSpeaker&& other);

	SmartSpeaker& operator=(const SmartSpeaker& other);
	SmartSpeaker& operator=(SmartSpeaker&& other);

	void turnOff() const override;
	void turnOn() const override;
	void printDetails() const override;

	Device* clone() const override;
};