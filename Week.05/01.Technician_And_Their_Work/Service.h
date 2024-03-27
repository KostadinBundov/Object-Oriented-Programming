#pragma once

#include "Technic.h";
#include "Client.h";

const size_t MAX_COUNT_TECHNICIANS = 30;

class Service
{
private:
	Technic technicians[MAX_COUNT_TECHNICIANS];
	size_t count = 0;
	void freeTechnic(Technic& technic);

public:
	Service() = default;
	Service(const Technic* arr, size_t count);

	const Technic* getTechnices() const;
	size_t getTechnicesCount() const;

	void setTechices(const Technic* technices);
	void setCount(size_t count);

	Technic findTechnic(const Client& client) const;
	void hireTechnic(const Technic& technic);
	void fireTechnic(const char* UCN);
	void saveServiceDataInFile(const char* fileName) const;
};
