#include <iostream>
#include <vector>
using namespace std;

// Abstract class Vehicle
class Vehicle {
protected:
    string licensePlate;
    string vehicleType;

public:
    // Constructor
    Vehicle(string lp, string vt) : licensePlate(lp), vehicleType(vt) {}

    // Pure virtual function to be implemented in derived classes
    virtual void displayDetails() = 0;

    string getLicensePlate() {
        return this->licensePlate;
    }
};

// Derived class Car
class Car : public Vehicle {
public:
    Car(string lp) : Vehicle(lp, "Car") {}

    void displayDetails() override {
        cout << "Vehicle Type: Car" << endl;
        cout << "License Plate: " << this->licensePlate << endl;
    }
};

// Derived class Bike
class Bike : public Vehicle {
public:
    Bike(string lp) : Vehicle(lp, "Bike") {}

    void displayDetails() override {
        cout << "Vehicle Type: Bike" << endl;
        cout << "License Plate: " << this->licensePlate << endl;
    }
};

// Derived class ElectricCar
class ElectricCar : public Vehicle {
public:
    ElectricCar(string lp) : Vehicle(lp, "Electric Car") {}

    void displayDetails() override {
        cout << "Vehicle Type: Electric Car" << endl;
        cout << "License Plate: " << this->licensePlate << endl;
    }
};

// Derived class Truck
class Truck : public Vehicle {
public:
    Truck(string lp) : Vehicle(lp, "Truck") {}

    void displayDetails() override {
        cout << "Vehicle Type: Truck" << endl;
        cout << "License Plate: " << this->licensePlate << endl;
    }
};

// ParkingSpot class
class ParkingSpot {
private:
    int spotNumber;
    bool isOccupied;
    Vehicle* parkedVehicle;

public:
    ParkingSpot(int sn) : spotNumber(sn), isOccupied(false), parkedVehicle(nullptr) {}

    int getSpotNumber() {
        return this->spotNumber;
    }

    bool getIsOccupied() {
        return this->isOccupied;
    }

    Vehicle* getParkedVehicle() {
        return this->parkedVehicle;
    }

    void occupySpot(Vehicle* vehicle) {
        if (!this->isOccupied) {
            this->isOccupied = true;
            this->parkedVehicle = vehicle;
            cout << "Spot " << this->spotNumber << " is now occupied by vehicle with license plate: " << vehicle->getLicensePlate() << endl;
        } else {
            cout << "Spot " << this->spotNumber << " is already occupied." << endl;
        }
    }

    void freeSpot() {
        if (this->isOccupied) {
            cout << "Spot " << this->spotNumber << " is now free. Vehicle with license plate " << this->parkedVehicle->getLicensePlate() << " has checked out." << endl;
            this->isOccupied = false;
            this->parkedVehicle = nullptr;
        } else {
            cout << "Spot " << this->spotNumber << " is already free." << endl;
        }
    }
};

// ParkingSystem class
class ParkingSystem {
protected:
    ParkingSpot* spots[5];
    static int totalVehiclesParked;
    static int totalRevenue;

public:
    ParkingSystem() {
        for (int i = 0; i < 5; i++) {
            spots[i] = new ParkingSpot(i + 1);
        }
    }

    void parkVehicle(Vehicle* vehicle) {
        for (int i = 0; i < 5; i++) {
            if (!spots[i]->getIsOccupied()) {
                spots[i]->occupySpot(vehicle);
                vehicle->displayDetails(); // Calls displayDetails() based on vehicle type
                totalVehiclesParked++;
                return;
            }
        }
        cout << "No available parking spots for vehicle with license plate: " << vehicle->getLicensePlate() << endl;
    }

    void checkoutVehicle(int spotNumber) {
        if (spotNumber > 0 && spotNumber <= 5) {
            if (spots[spotNumber - 1]->getIsOccupied()) {
                int hours;
                cout << "How many hours was the vehicle parked? ";
                cin >> hours;
                int fee = hours * 50;
                spots[spotNumber - 1]->freeSpot();
                totalRevenue += fee;
                cout << "Parking fee: Rs " << fee << endl;
                cout << "Thank you! Have a nice day!\n";
            } else {
                cout << "Spot " << spotNumber << " is already free." << endl;
            }
        } else {
            cout << "Invalid spot number." << endl;
        }
    }

    void listAvailableSpots() {
        cout << "\nAvailable Spots:\n";
        for (int i = 0; i < 5; i++) {
            if (!spots[i]->getIsOccupied()) {
                cout << "Spot " << spots[i]->getSpotNumber() << " is available." << endl;
            }
        }
    }

    void listParkedVehicles() {
        cout << "\nParked Vehicles:\n";
        for (int i = 0; i < 5; i++) {
            if (spots[i]->getIsOccupied()) {
                cout << "Spot " << spots[i]->getSpotNumber() << ": ";
                spots[i]->getParkedVehicle()->displayDetails();
            }
        }
    }

    static void displayStatistics() {
        cout << "\n--- Parking Statistics ---\n";
        cout << "Total Vehicles Parked: " << totalVehiclesParked << endl;
        cout << "Total Revenue Generated: Rs " << totalRevenue << endl;
    }

    ~ParkingSystem() {
        for (int i = 0; i < 5; i++) {
            delete spots[i];
        }
    }
};

int ParkingSystem::totalVehiclesParked = 0;
int ParkingSystem::totalRevenue = 0;

int main() {
    ParkingSystem* parkingSystem = new ParkingSystem();

    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Park a Vehicle\n";
        cout << "2. Checkout a Vehicle\n";
        cout << "3. List Available Spots\n";
        cout << "4. List Parked Vehicles\n";
        cout << "5. Display Parking Statistics\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string licensePlate, vehicleType;
            cout << "Enter Vehicle License Plate: ";
            cin >> licensePlate;
            cout << "Enter Vehicle Type (Car/Bike/ElectricCar/Truck): ";
            cin >> vehicleType;
            Vehicle* vehicle;
            if (vehicleType == "Car") {
                vehicle = new Car(licensePlate);
            } else if (vehicleType == "Bike") {
                vehicle = new Bike(licensePlate);
            } else if (vehicleType == "ElectricCar") {
                vehicle = new ElectricCar(licensePlate);
            } else if (vehicleType == "Truck") {
                vehicle = new Truck(licensePlate);
            } else {
                cout << "Invalid vehicle type!" << endl;
                continue;
            }
            parkingSystem->parkVehicle(vehicle);

        } else if (choice == 2) {
            int spotNumber;
            cout << "Enter the spot number to checkout: ";
            cin >> spotNumber;
            parkingSystem->checkoutVehicle(spotNumber);

        } else if (choice == 3) {
            parkingSystem->listAvailableSpots();

        } else if (choice == 4) {
            parkingSystem->listParkedVehicles();

        } else if (choice == 5) {
            ParkingSystem::displayStatistics();

        } else if (choice == 6) {
            cout << "Exiting the simulation." << endl;
            break;

        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    delete parkingSystem;
    return 0;
}
