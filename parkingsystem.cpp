#include <iostream>
#include <vector>
using namespace std;

class Vehicle {
private:
    string licensePlate;
    string vehicleType;

public:
    Vehicle(string lp, string vt) {
        this->licensePlate = lp;
        this->vehicleType = vt;
    }

    // Accessors
    string getLicensePlate() {
        return licensePlate;
    }

    string getVehicleType() {
        return vehicleType;
    }

    // Mutators
    void setLicensePlate(string lp) {
        licensePlate = lp;
    }

    void setVehicleType(string vt) {
        vehicleType = vt;
    }

    void displayDetails() {
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "License Plate: " << licensePlate << endl;
    }
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

    // Accessors
    int getSpotNumber() {
        return spotNumber;
    }

    bool getIsOccupied() {
        return isOccupied;
    }

    Vehicle* getParkedVehicle() {
        return parkedVehicle;
    }

    // Mutators
    void setIsOccupied(bool occupied) {
        isOccupied = occupied;
    }

    void setParkedVehicle(Vehicle* vehicle) {
        parkedVehicle = vehicle;
    }

    void occupySpot(Vehicle* vehicle) {
        if (!isOccupied) {
            setIsOccupied(true);
            setParkedVehicle(vehicle);
            cout << "Spot " << spotNumber << " is now occupied by vehicle with license plate: " << vehicle->getLicensePlate() << endl;
        } else {
            cout << "Spot " << spotNumber << " is already occupied." << endl;
        }
    }

    void freeSpot() {
        if (isOccupied) {
            cout << "Spot " << spotNumber << " is now free. Vehicle with license plate " << parkedVehicle->getLicensePlate() << " has checked out." << endl;
            setIsOccupied(false);
            setParkedVehicle(nullptr);
        } else {
            cout << "Spot " << spotNumber << " is already free." << endl;
        }
    }
};

class ParkingSystem {
public:
    ParkingSpot* spots[5];  // Array of parking spots

    static int totalVehiclesParked;
    static int totalRevenue;

    ParkingSystem() {
        for (int i = 0; i < 5; i++) {
            spots[i] = new ParkingSpot(i + 1);
        }
    }

    void parkVehicle(Vehicle* vehicle) {
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
                totalRevenue += fee;  // Add the fee to total revenue
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
    ParkingSystem* parkingSystem = new ParkingSystem();  // 5 spots by default

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
