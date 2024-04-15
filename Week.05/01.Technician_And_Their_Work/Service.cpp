#include "Service.h";
#include <string.h>;
#include <fstream>;
#include <iostream>;

Service::Service(const Technic* arr, size_t count)
{
	this->setCount(count);
	this->setTechices(arr);
}

const Technic* Service::getTechnices() const
{
	return this->technicians;
}

size_t Service::getTechnicesCount() const
{
	return this->count;
}

void Service::setTechices(const Technic* technices)
{
	for (int i = 0; i < this->count; i++)
	{
		this->technicians[i] = technices[i];
	}
}
void Service::setCount(size_t count)
{
	if (this->count > MAX_COUNT_TECHNICIANS)
	{
		return;
	}

	this->count = count;
}

Technic Service::findTechnic(const Client& client) const
{
	for (int i = 0; i < this->count; i++)
	{
		if (this->technicians[i].canRepairAppliance(client.getAppliance()))
		{
			return this->technicians[i];
		}
	}

	return {};
}
void Service::hireTechnic(const Technic& technic)
{
	if (this->count >= MAX_COUNT_TECHNICIANS)
	{
		return;
	}

	this->technicians[this->count] = technic;
	this->count++;
}

void Service::fireTechnic(const char* UCN)
{
	for (int i = 0; i < this->count; i++)
	{
		if (strcmp(this->technicians[i].getUCN(), UCN) == 0)
		{
			this->freeTechnic(this->technicians[i]);
		}
	}
}

void Service::saveServiceDataInFile(const char* fileName) const
{
	std::ofstream ofs(fileName, std::ios::out);

	if (!ofs.is_open())
	{
		return;
	}

	for (int i = 0; i < this->count; i++)
	{
		double average = this->technicians[i].getExperience() == 0 ? 0 : this->technicians[i].getSalary() / this->technicians[i].getExperience();

		ofs << this->technicians[i].getName() << ":" << this->technicians[i].getUCN() << ": " << average << std::endl;

	}
	ofs.close();
}

void Service::freeTechnic(Technic& technic)
{
	technic.setName("Fired");
	technic.setUCN("Fired");
}