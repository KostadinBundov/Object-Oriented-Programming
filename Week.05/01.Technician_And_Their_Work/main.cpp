#include <iostream>
#include "Technic.h"
#include "Service.h"
#include "Client.h"
#include "BrokenAppliance.h"

int main() {
    // Създаване на майстори
    Technic technic1("Ivan Ivanov", "1234567890", (uint8_t)ApplianceCategory::Phone | (uint8_t)ApplianceCategory::Laptop, 1000, 5);
    Technic technic2("Georgi Georgiev", "9876543210", (uint8_t)ApplianceCategory::Camera, 1500, 8);

    // Създаване на сервиз и добавяне на майсторите
    Service service;
    service.hireTechnic(technic1);
    service.hireTechnic(technic2);

    // Създаване на клиент и повреден уред
    BrokenAppliance brokenPhone(ApplianceCategory::Camera, 200, false);
    Client client1("Maria Petrova", brokenPhone);

    // Търсене на майстор за ремонт на уреда
    Technic technicForRepair = service.findTechnic(client1);
    std::cout << "Technic: " << technicForRepair.getName() << std::endl;

    // Имитация на ремонт на уреда
    technicForRepair.repairBrokenAppliance(brokenPhone);

    // Премахване на майстор от сервиза
    service.fireTechnic("1234567890");

    // Запазване на данни за сервиза във файл
    service.saveServiceDataInFile("service_data.txt");

    return 0;
}
