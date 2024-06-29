#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <iostream>
#include <thread> // For std::this_thread::sleep_for
#include <chrono> // For std::chrono::seconds
#include "ProgressBar.cpp"

int waitTime = 4;

// Helper function to wait a few seconds.
void wait(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// Helper function to clear the screen.
void clearScreen()
{
    std::cout << "\033[2J\033[1;1H";
}

// Driving result
struct driveResult
{
    int distance;     // The distance covered by the car
    int fuelConsumed; // The amount of fuel consumed by the car
    bool carDamaged;  // Whether the car is damaged after being used.
};

class Person
{
public:
    double money = 10000; // amount of money they got.
    std::string name;     // Name of the person
    Person(std::string nameOfPerson)
    {
        name = nameOfPerson;
    }
};

class Car
{
public:
    std::string name;        // Name of the car
    int speed;               // The speed of the car
    int maxSped = 10000000;  // The maximum speed of the car
    double price;            // Price of the car
    int fuelEfficiency = 10; // The fuel efficiency of the car (l/km)
    int fuelTank = 100;      // The fuel capacity of the car
    int fuelTankMax = 100;
    double upgradePrice;          // The upgrade price of the car
    int totalDistanceCovered = 0; // The total distance covered by the car
    int fuelPrice;                // The price of the car that is fuel
    double fixPrice;              // The price of the car that
    bool isDamaged = false;       // Whether the car is damaged after being used.
    Car(std::string carName, int carSpeed, double priceOfCar = 100)
    {
        name = carName;
        speed = carSpeed;
        price = priceOfCar;
        upgradePrice = price * 0.1;
        fuelPrice = price * 0.05; // Price of fuel per unit distance
        fixPrice = price * 0.01;  // Price of fixing the car
    }

    double upgradeCar(int money)
    {
        auto handleUpgrade = []() -> char
        {
            std::cout
                << "What would you like to upgrade?" << std::endl;
            std::cout << "(s) " << 5 << " Speed" << std::endl;
            std::cout << "(e) " << 5 << "Fuel efficiency" << std::endl;
            std::cout << "(t) " << 5 << "Fuel tank capacity" << std::endl;
            std::cout << "(anything) Cancel" << std::endl;
            char choice;
            std::cin >> choice;
            return choice;
        };

        if (money < upgradePrice)
        {
            std::cout << "Not enough money to upgrade the car." << std::endl;
            return -1;
        }

        money -= upgradePrice;
        upgradePrice *= 1.1;
        fuelTankMax += 10;
        std::cout << name << " upgraded to a more fuel-efficient car. Fuel tank capacity increased by 10." << std::endl;
        return upgradePrice;
    }

    driveResult drive()
    {
        clearScreen();
        if (isDamaged)
        {
            std::cout << "Your car is damaged bro. You cannot drive." << std::endl;
            return {0, fuelTank, true};
        }
        int distance = 0;
        while (fuelTank != 0)
        {
            clearScreen();
            fuelTank -= fuelEfficiency;
            distance += speed;
            std::cout << "Distance covered: " << distance << ", Fuel remaining: " << fuelTank << std::endl;
            wait(1);
        }

        clearScreen();

        bool carDamaged = rand() % 2 ? true : false;
        std::cout << "Not enough fuel to cover the remaining distance." << std::endl;
        std::cout << (carDamaged ? "Damn ur car damaged" : "ur car aint damaged.") << std::endl;
        isDamaged = carDamaged;
        return {distance, fuelTank, carDamaged};
    }

    void carInfo()
    {
        std::cout << "Car name: " << name << std::endl;
        std::cout << "Speed: " << speed << " km/h" << std::endl;
        std::cout << "Price: R" << price << std::endl;
        std::cout << "Fuel efficiency: " << fuelEfficiency << " l/s" << std::endl;
        std::cout << "Fuel tank capacity: " << fuelTank << "/" << fuelTankMax << std::endl;
        std::cout << "Upgrade price: R" << upgradePrice << std::endl;
        std::cout << "Total distance covered so far: " << totalDistanceCovered << " km" << std::endl;
    }

    int buyFuel(int money)
    {
        if (fuelTank >= fuelTankMax)
        {
            std::cout << "Fuel tank is already full." << std::endl;
            return -1;
        }

        if (money < fuelPrice)
        {
            std::cout << "Not enough money to buy fuel." << std::endl;
            return -1;
        }

        money -= fuelPrice;
        fuelTank = std::min(fuelTank + 100, fuelTankMax);
        std::cout << "You bought fuel. Fuel tank capacity increased by 100." << std::endl;

        return fuelPrice;
    }

    int fixCar(int money)
    {
        if (!isDamaged)
        {
            std::cout << "Your car isn't damaged." << std::endl;
            return -1;
        }
        if (money < fixPrice)
        {
            std::cout << "Not enough money to fix the car." << std::endl;

            return -1;
        }

        money -= fixPrice;
        std::cout << "Car fixed successfully." << std::endl;
        isDamaged = false;

        return fixPrice;
    }
};

void showCommands(double money)
{
    std::cout << "Type any one of these to do it! You have R" << money << std::endl
              << std::endl;
    std::cout << "(d) - Drive you bad boy" << std::endl;
    std::cout << "(i) - Information on your car" << std::endl;
    std::cout << "(u) - Upgrade the car" << std::endl;
    std::cout << "(b) - Buy fuel" << std::endl;
    std::cout << "(f) - Fix your car if it's damaged" << std::endl;
    std::cout << "(c) - Show available commands" << std::endl;
    std::cout << "(e) - Exit the game" << std::endl;
}

int main()
{

    clearScreen();
    std::cout << "Your name?" << std::endl;
    std::string name;
    std::cin >> name;
    Person person(name);
    clearScreen();
    std::cout << "Ight cool " << person.name << "! You start the game with R" << person.money << std::endl;

    std::cout << std::endl;

    std::cout << "Let's create your car now!" << std::endl;
    std::string carName;
    int carSpeed;
    std::cout << "Car name: ";
    std::cin >> carName;
    std::cout << "Car speed (km/s): ";
    std::cin >> carSpeed;
    Car car(carName, carSpeed);

    clearScreen();

    std::cout << "Okay, that's an odd car." << std::endl;
    car.carInfo();
    wait(4);
    std::cout << "Anyways, game starts now.";

    clearScreen();

    bool exit = false;

    while (!exit)
    {
        clearScreen();
        showCommands(person.money);
        char command;
        std::cin >> command;
        switch (command)
        {
        case 'd':
        {
            driveResult result = car.drive();
            person.money += result.distance * car.fuelPrice;
            car.totalDistanceCovered += result.distance;
            if (result.carDamaged)
            {
                person.money -= car.price * 0.1;
            };
            break;
        }
        case 'i':
        {
            car.carInfo();
            break;
        }
        case 'u':
        {
            double upgradePrice = car.upgradeCar(person.money);
            if (upgradePrice > 0)
            {
                person.money -= upgradePrice;
            }
            break;
        }
        case 'b':
        {
            int fuelPrice = car.buyFuel(person.money);
            if (fuelPrice > 0)
            {
                person.money -= fuelPrice;
            }
            break;
        }
        case 'c':
        {
            showCommands(person.money);
            break;
        }
        case 'f':
        {
            int fixPrice = car.fixCar(person.money);
            if (fixPrice > 0)
            {
                person.money -= fixPrice;
            }
            break;
        }
        case 'e':
        {
            std::cout << "Thanks for playing! Your final money is R" << person.money;
            exit = true;
        }
        };

        wait(waitTime);
    }
    return 0;
};