#include <iostream>
using namespace std;

class Vehicle {
public:
    string licensePlate;
    string vehicleType;

    Vehicle(string lp, string vt) {
        licensePlate = lp;
        vehicleType = vt;
    }

    void displayDetails() {
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "License Plate: " << licensePlate << endl;
    }
};

class ParkingSpot {
public:
    int spotNumber;
    bool isOccupied;

    ParkingSpot(int sn) {
        spotNumber = sn;
        isOccupied = false;
    }

    void occupySpot() {
        isOccupied = true;
        cout << "Spot " << spotNumber << " is now occupied." << endl;
    }

    void freeSpot() {
        isOccupied = false;
        cout << "Spot " << spotNumber << " is now free." << endl;
    }
};

int main() {
    Vehicle car("ABC123", "Car");
    ParkingSpot spot1(1);

    car.displayDetails();
    spot1.occupySpot();
    spot1.freeSpot();

    return 0;
}
