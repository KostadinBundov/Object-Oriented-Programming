#include <iostream>
#include "Car.h"

int main() 
{
    try
    {
        FuelTank firstTank(50);
        FuelTank secondTank(60);

        Engine firstEngine(1, "Toyota", "V6 Engine", 250);
        Engine secondEngine(2, "Honda", "I4 Turbo", 220);

        Tire t1(1, "Michelin", "Performance Tire", 205, 55, 16);
        Tire t2(5, "Goodyear", "All Season Tire", 215, 60, 17);

        Tire firstTires[4];
        for (int i = 0; i < 4; i++)
        {
            firstTires[i] = t1;
        }

        Tire secondTires[4];
        for (int i = 0; i < 4; i++)
        {
            secondTires[i] = t2;
        }

        Accumulator firstAccumulator(3, "Bosch", "High Capacity", 75, "123ABC");
        Accumulator secondAccumulator(4, "Exide", "Standard", 65, "456DEF");

        Car car1(firstTank, firstEngine, firstTires, firstAccumulator, 1500);
        Car car2(secondTank, secondEngine, secondTires, secondAccumulator, 1400);

        std::cout << "Before driving:" << std::endl;
        std::cout << car1.getFuelTank().getLeftOver() << std::endl;
        std::cout << car2.getFuelTank().getLeftOver() << std::endl;

        car1.drive(10);
        car2.drive(20);

        std::cout << "After driving:" << std::endl;
        std::cout << car1.getFuelTank().getLeftOver() << std::endl;
        std::cout << car2.getFuelTank().getLeftOver() << std::endl;

        Car* winner = dragRace(&car1, &car2);
        if (winner != nullptr) {
            std::cout << "The winner of the drag race has ID: " << winner->getFuelTank().getCapacity();
        }
        else {
            std::cout << "No winner, both cars lack sufficient fuel." << std::endl;
        }
    }
    catch (const std::logic_error& ex)
    {
        std::cout << ex.what();
    }
    catch (const std::invalid_argument& ex)
    {
        std::cout << ex.what();
    }
    catch (const std::bad_alloc& ex)
    {
        std::cout << ex.what();
    }
    catch (...)
    {
        std::cout << "Unknown exception!";
    }
}
