#include <iostream>
#include <vector>
using namespace std;

class Vehicle {
public:
    string licensePlate;
    string vehicleType;

    Vehicle(string lp, string vt) {
        // Using 'this' pointer to reference current object
        this->licensePlate = lp;
        this->vehicleType = vt;
    }

    void displayDetails() {
        cout << "Vehicle Type: " << this->vehicleType << endl;
        cout << "License Plate: " << this->licensePlate << endl;
    }
};

class ParkingSpot {
public:
    int spotNumber;
    bool isOccupied;
    Vehicle* parkedVehicle;

    ParkingSpot(int sn) {
        // Using 'this' pointer to reference current object
        this->spotNumber = sn;
        this->isOccupied = false;
        this->parkedVehicle = nullptr;
    }

    void occupySpot(Vehicle* vehicle) {
        if (!this->isOccupied) {
            this->isOccupied = true;
            this->parkedVehicle = vehicle;
            cout << "Spot " << this->spotNumber << " is now occupied by vehicle with license plate: " << vehicle->licensePlate << endl;
        } else {
            cout << "Spot " << this->spotNumber << " is already occupied." << endl;
        }
    }

    void freeSpot() {
        if (this->isOccupied) {
            cout << "Spot " << this->spotNumber << " is now free. Vehicle with license plate " << this->parkedVehicle->licensePlate << " has checked out." << endl;
            this->isOccupied = false;
            this->parkedVehicle = nullptr;
        } else {
            cout << "Spot " << this->spotNumber << " is already free." << endl;
        }
    }
};

class ParkingSystem {
public:
    vector<ParkingSpot*> spots;

    ParkingSystem(int numSpots = 5) {  // Default number of spots is set to 5
        for (int i = 1; i <= numSpots; i++) {
            spots.push_back(new ParkingSpot(i));
        }
    }

    void parkVehicle(Vehicle* vehicle) {
        for (auto spot : spots) {
            if (!spot->isOccupied) {
                spot->occupySpot(vehicle);
                return;
            }
        }
        cout << "No available parking spots for vehicle with license plate: " << vehicle->licensePlate << endl;
    }

    void checkoutVehicle(int spotNumber) {
        if (spotNumber > 0 && spotNumber <= spots.size()) {
            spots[spotNumber - 1]->freeSpot();
        } else {
            cout << "Invalid spot number." << endl;
        }
    }

    void listAvailableSpots() {
        cout << "\nAvailable Spots:\n";
        for (auto spot : spots) {
            if (!spot->isOccupied) {
                cout << "Spot " << spot->spotNumber << " is available." << endl;
            }
        }
    }

    void listParkedVehicles() {
        cout << "\nParked Vehicles:\n";
        for (auto spot : spots) {
            if (spot->isOccupied) {
                cout << "Spot " << spot->spotNumber << ": ";
                spot->parkedVehicle->displayDetails();
            }
        }
    }

    ~ParkingSystem() {
        for (auto spot : spots) {
            delete spot;
        }
    }
};

int main() {
    ParkingSystem* parkingSystem = new ParkingSystem();  // Default to 5 spots

    int choice;
    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Park a Vehicle\n";
        cout << "2. Checkout a Vehicle\n";
        cout << "3. List Available Spots\n";
        cout << "4. List Parked Vehicles\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string licensePlate, vehicleType;
            cout << "Enter Vehicle License Plate: ";
            cin >> licensePlate;
            cout << "Enter Vehicle Type (Car/Bike): ";
            cin >> vehicleType;
            Vehicle* vehicle = new Vehicle(licensePlate, vehicleType);
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
            cout << "Exiting the simulation." << endl;
            break;

        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    delete parkingSystem;
    return 0;
}
