#include <iostream>
using namespace std;

// Class representing a vehicle
class Vehicle {
public:
    string licensePlate;
    string vehicleType;

    // Constructor to initialize vehicle
    Vehicle(string lp, string vt) {
        licensePlate = lp;
        vehicleType = vt;
    }

    // Method to display vehicle details
    void displayDetails() {
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "License Plate: " << licensePlate << endl;
    }
};

// Class representing a parking spot
class ParkingSpot {
public:
    int spotNumber;
    bool isOccupied;

    // Constructor to initialize parking spot
    ParkingSpot(int sn) {
        spotNumber = sn;
        isOccupied = false;
    }

    // Method to occupy the spot
    void occupySpot() {
        isOccupied = true;
        cout << "Spot " << spotNumber << " is now occupied." << endl;
    }

    // Method to free the spot
    void freeSpot() {
        isOccupied = false;
        cout << "Spot " << spotNumber << " is now free." << endl;
    }
};

int main() {
    // Creating an object of Vehicle class
    Vehicle car("ABC123", "Car");

    // Creating an object of ParkingSpot class
    ParkingSpot spot1(1);

    // Display vehicle details
    car.displayDetails();

    // Occupying and freeing the parking spot
    spot1.occupySpot();
    spot1.freeSpot();

    return 0;
}
