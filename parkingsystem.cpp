#include <iostream>
using namespace std;

class Vehicle {
public:
    string licensePlate;
    string vehicleType;

    Vehicle(string lp, string vt) : licensePlate(lp), vehicleType(vt) {}

    void displayDetails() {
        cout << "Vehicle Type: " << vehicleType << endl;
        cout << "License Plate: " << licensePlate << endl;
    }
};

class ParkingSpot {
public:
    int spotNumber;
    bool isOccupied;
    Vehicle* parkedVehicle;

    ParkingSpot(int sn) : spotNumber(sn), isOccupied(false), parkedVehicle(nullptr) {}

    void occupySpot(Vehicle* vehicle) {
        if (!isOccupied) {
            isOccupied = true;
            parkedVehicle = vehicle;
            cout << "Spot " << spotNumber << " is now occupied by " << vehicle->licensePlate << "." << endl;
        } else {
            cout << "Spot " << spotNumber << " is already occupied." << endl;
        }
    }

    void freeSpot() {
        if (isOccupied) {
            int hours;
            cout << "Enter the number of hours the vehicle was parked: ";
            cin >> hours;
            int amount = hours * 50;
            cout << "Total amount to be paid: Rs " << amount << endl;

            cout << "Spot " << spotNumber << " is now free." << endl;
            parkedVehicle = nullptr;
            isOccupied = false;
        } else {
            cout << "Spot " << spotNumber << " is already free." << endl;
        }
    }

    void displayStatus() {
        if (isOccupied) {
            cout << "Spot " << spotNumber << " is occupied by " << parkedVehicle->licensePlate << endl;
        } else {
            cout << "Spot " << spotNumber << " is free." << endl;
        }
    }
};

int main() {
    const int totalSpots = 5;
    ParkingSpot parkingSpots[totalSpots] = {ParkingSpot(1), ParkingSpot(2), ParkingSpot(3), ParkingSpot(4), ParkingSpot(5)};

    Vehicle car1("ABC123", "Car");
    Vehicle car2("XYZ789", "Car");

    parkingSpots[0].occupySpot(&car1);
    parkingSpots[1].occupySpot(&car2);

    parkingSpots[0].displayStatus();
    parkingSpots[1].displayStatus();

    parkingSpots[0].freeSpot();
    parkingSpots[1].freeSpot();

    return 0;
}
