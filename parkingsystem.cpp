#include <iostream>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string licensePlate;
    string vehicleType;

public:
    Vehicle(string lp, string vt) : licensePlate(lp), vehicleType(vt) {}

    virtual void displayDetails() {
        cout << "Vehicle Type: " << this->vehicleType << endl;
        cout << "License Plate: " << this->licensePlate << endl;
    }

    string getLicensePlate() {
        return this->licensePlate;
    }
};

class Car : public Vehicle {
public:
    Car(string lp) : Vehicle(lp, "Car") {}
};

class Bike : public Vehicle {
public:
    Bike(string lp) : Vehicle(lp, "Bike") {}
};

class ParkingSpot {
private:
    int spotNumber;
    bool isOccupied;
    Vehicle* parkedVehicle;

public:
    ParkingSpot(int sn) {
        this->spotNumber = sn;
        this->isOccupied = false;
        this->parkedVehicle = nullptr;
    }

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

    virtual void parkVehicle(Vehicle* vehicle) {
        for (int i = 0; i < 5; i++) {
            if (!spots[i]->getIsOccupied()) {
                spots[i]->occupySpot(vehicle);
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

    virtual ~ParkingSystem() {
        for (int i = 0; i < 5; i++) {
            delete spots[i];
        }
    }
};

class AdvancedParkingSystem : public ParkingSystem {
public:
    void parkVehicle(Vehicle* vehicle) override {
        // This method can be extended to add additional checks or new behavior for advanced systems
        ParkingSystem::parkVehicle(vehicle);
    }

    void offerPremiumParking() {
        cout << "Premium parking options available for Cars and Bikes.\n";
    }
};

int ParkingSystem::totalVehiclesParked = 0;
int ParkingSystem::totalRevenue = 0;

int main() {
    AdvancedParkingSystem* parkingSystem = new AdvancedParkingSystem();

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
            cout << "Enter Vehicle Type (Car/Bike): ";
            cin >> vehicleType;
            Vehicle* vehicle = (vehicleType == "Car") ? new Car(licensePlate) : new Bike(licensePlate);
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
