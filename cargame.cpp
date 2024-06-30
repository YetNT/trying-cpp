#include <array>
#include <chrono> // For std::chrono::seconds
#include <cmath>
#include <iostream>
#include <string>
#include <thread> // For std::this_thread::sleep_for

int waitTime = 4;

// Helper function to wait a few seconds.
void wait(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

// Helper function to clear the screen.
void clearScreen() { std::cout << "\033[2J\033[1;1H"; }

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
    Person(std::string nameOfPerson) { name = nameOfPerson; }
};

class Car
{
public:
    std::string name;        // Name of the car
    int speed = 1;               // The speed of the car
    int maxSpeed = 10000000; // The maximum speed of the car
    double price;            // Price of the car
    int fuelEfficiency = 20; // The fuel efficiency of the car (l/km)
    int defaultFuelEfficiency =
        fuelEfficiency;            // The default fuel efficiency of the car
    int fuelTank = 100;            // The fuel capacity of the car
    int fuelTankMax = 100;         // Fuel tank's maximum capacity
    double tankUpgradePrice;       // The upgrade price of the car
    double speedUpgradePrice;      // The speed upgrade price of the car
    double efficiencyUpgradePrice; // The efficiency upgrade price of the car
    int totalDistanceCovered = 0;  // The total distance covered by the car
    int fuelPrice;                 // The price of the car that is fuel
    double fixPrice;               // The price of the car that
    bool isDamaged = false;        // Whether the car is damaged after being used.
    Car(std::string carName, double priceOfCar = 100)
    {
        name = carName;
        price = priceOfCar;
        tankUpgradePrice = price * 0.1;
        speedUpgradePrice = price * 0.05;
        efficiencyUpgradePrice =
            price * 0.02;         // Price of efficiency upgrade per unit distance
        fuelPrice = price * 0.05; // Price of fuel per unit distance
        fixPrice = price * 0.01;  // Price of fixing the car
    }

    double upgradeCar(int money)
    {
        clearScreen();
        char choice = 's';
        // Holy crap this shi is getting crazy for a terminal game where im learning
        auto handleUpgrade = [this]() -> char
            {
                std::cout << "Type a letter to upgrade that:" << std::endl
                    << std::endl;

                std::cout << "(s) [R" << speedUpgradePrice << "] Speed\t\t\t" << speed << "km\\s"
                    << (speed >= maxSpeed ? "[MAX REACHED]\n" : "\n");

                std::cout << "(e) [R" << efficiencyUpgradePrice
                    << "] Fuel efficiency\t" << fuelEfficiency << " litres per kilometre"
                    << (fuelEfficiency >= 2 ? "[MAX REACHED]\n" : "\n");

                std::cout << "(t) [R" << tankUpgradePrice
                    << "] Fuel tank capacity\t" << fuelTank << "\\" << fuelTankMax << std::endl;

                std::cout << "(anything) Cancel" << std::endl
                    << std::endl;
                char choice;
                std::cin >> choice;
                return choice;
            };
        double finalPrice = 0;

        while (choice == 's' || choice == 'e' || choice == 't')
        {
            clearScreen();
            choice = handleUpgrade();
            switch (choice)
            {
                case 's':
                    {
                        if (money < speedUpgradePrice) {
                            std::cout << "Not enough money to upgrade the speed of the car." << std::endl;
                            break;
                        }
                        speed += 10;
                        finalPrice = speedUpgradePrice;
                        money -= speedUpgradePrice;
                        speedUpgradePrice += (speedUpgradePrice * 0.5);
                        break;
                    }
                case 'e':
                    {
                        if (money < efficiencyUpgradePrice) {
                            std::cout << "Not enough money to upgrade the fuel efficiency of the car." << std::endl;
                            break;
                        }
                        if (fuelEfficiency == 2) {
                            std::cout << "The car's fuel efficiency cannot be lowered even more." << std::endl;
                            break;
                        }
                        fuelEfficiency -= 1;
                        finalPrice = efficiencyUpgradePrice;
                        money -= efficiencyUpgradePrice;
                        efficiencyUpgradePrice += (efficiencyUpgradePrice * 0.7);
                        break;
                    }
                case 't':
                    {
                        if (money < tankUpgradePrice) {
                            std::cout << "Not enough money to upgrade the fuel tank capacity of the car." << std::endl;
                            break;
                        }
                        if (fuelTank >= fuelTankMax) {
                            std::cout << "The car's fuel tank cannot be increased even more." << std::endl;
                            break;
                        }
                        fuelTankMax += 10;
                        finalPrice = tankUpgradePrice;
                        money -= tankUpgradePrice;
                        tankUpgradePrice += (tankUpgradePrice * 0.4);
                        break;
                    }
                default:
                    {
                        std::cout << "Okay so you're broke-" << std::endl;
                        break;
                    }
            }
        }

        return finalPrice;
    }

    driveResult drive()
    {
        clearScreen();
        if (isDamaged)
        {
            std::cout << "Your car is damaged bro. You cannot drive." << std::endl;
            return { 0, fuelTank, true };
        }
        int distance = 0;
        while (fuelTank > 0)
        {
            clearScreen();
            fuelTank -= fuelEfficiency;
            distance += speed;
            std::cout << "Distance covered: " << distance
                << ", Fuel remaining: " << fuelTank << std::endl;
            wait(1);
        }

        clearScreen();

        bool carDamaged = rand() % 2 ? true : false;
        std::cout << "Not enough fuel to cover the remaining distance."
            << std::endl;
        std::cout << (carDamaged ? "Damn ur car damaged" : "ur car aint damaged.")
            << std::endl;
        isDamaged = carDamaged;
        return { distance, fuelTank, carDamaged };
    }

    void carInfo()
    {
        std::cout << "Car name: " << name << std::endl;
        std::cout << "Speed: " << speed << " km/h" << std::endl;
        std::cout << "Price: R" << price << std::endl;
        std::cout << "Fuel efficiency: " << fuelEfficiency << " l/s" << std::endl;
        std::cout << "Fuel tank capacity: " << fuelTank << "/" << fuelTankMax
            << std::endl;
        std::cout << "Total distance covered so far: " << totalDistanceCovered
            << " km" << std::endl;
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
        std::cout << "You bought fuel. Fuel tank capacity increased by 100."
            << std::endl;

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
    std::cout << "Type any one of these to do it! You have R" << money
        << std::endl
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
    std::cout << "Ight cool " << person.name << "! You start the game with R"
        << person.money << std::endl;

    std::cout << std::endl;

    std::cout << "Let's create your car now!" << std::endl;
    std::string carName;
    std::cout << "Car name: ";
    std::cin >> carName;
    Car car(carName);

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