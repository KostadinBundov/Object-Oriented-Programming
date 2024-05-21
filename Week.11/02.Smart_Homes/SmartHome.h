#pragma once
#include "Device.h"

constexpr size_t capacity = 10;

class SmartHome
{
private:
	size_t size = 0;
	Device* devices[capacity]{ nullptr };

	void copyFrom(const SmartHome& other);
	void moveFrom(SmartHome&& other);
	void free();

public:
	SmartHome() = default;

	SmartHome(const SmartHome& other);
	SmartHome(SmartHome&& other);

	SmartHome& operator=(const SmartHome& other);
	SmartHome& operator=(SmartHome&& other);

	~SmartHome();

	size_t getDevicesCount() const;
	const Device* getDevice(size_t index) const;

	void addDevice(const Device& device);
	void addDevice(Device* device);

	void removeDevice();
};