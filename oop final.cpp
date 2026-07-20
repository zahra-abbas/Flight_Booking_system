#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_SEATS = 100;  // Maximum number of seats per flight
const int MAX_FLIGHTS = 10; // Maximum number of flights

class Admin {
    string name;
    string password;

public:
    Admin() : name(""), password("") {}

//    void setCredentials(string n, string p) {
//        name = n;
//        password = p;
//    }

    bool authenticate(string uname, string pwd) {
        return ((uname == "noor" && pwd == "1234") ||
            (uname == "nimrah" && pwd == "2345") ||
            (uname == "zahra" && pwd == "3456") ||
            (uname == "alamdar" && pwd == "4567"));
    }
};
class Payment {
    string paymentMethod;     // e.g., Credit Card, Debit Card, Cash
    double amount;            // Amount to be paid
    string paymentStatus;     // e.g., "Pending", "Completed", "Failed"
    string accountNumber;     // Account or Card Number (last 4 digits for security)
    string paymentProcessor;  // Payment processor (e.g., PayPal, Stripe)

public:
    Payment(double amt, string method, string status, string account, string processor = "") {
        amount = amt;
        paymentMethod = method;
        paymentStatus = status;
        accountNumber = account;
        paymentProcessor = processor;
    }

    void processPayment() {
        // Simulate payment processing
        cout << "Processing " << paymentMethod << " payment of $" << amount << " using " << paymentProcessor << "..." << endl;
        paymentStatus = "Completed";
        cout << "Payment completed successfully!" << endl;
    }

    string getPaymentStatus() { return paymentStatus; }
};
class Seat {
    int seatNumber;
    bool isAvailable;
    string seatClass;
    double price;

public:
    Seat() : seatNumber(0), isAvailable(true), seatClass(""), price(0.0) {}

    Seat(int number, string cls, double pr)
        : seatNumber(number), isAvailable(true), seatClass(cls), price(pr) {}

    void displaySeat() {
        cout << "Seat " << seatNumber << " (" << seatClass << ", $" << price << ") - "
            << (isAvailable ? "Available" : "Booked") << endl;
    }

    bool bookSeat() {
        if (isAvailable) {
            isAvailable = false;
            return true;
        }
        return false;
    }

    bool cancelBooking() {
        if (!isAvailable) {
            isAvailable = true;
            return true;
        }
        return false;
    }

    bool getAvailability() { return isAvailable; }
    string getClass() { return seatClass; }
    int getSeatNumber() { return seatNumber; }
    double getPrice() { return price; }
};

class Flight {
    string flightNumber;
    string departureTime;
    string arrivalTime;
    string destination;
    string departureLocation;
    string date;
    Seat seats[MAX_SEATS];
    int totalSeats;

public:
    Flight() : totalSeats(0) {}

    void setFlight(string fn, string dept, string arr, string dest, string depLoc, string dt, int econSeats, int busSeats, double econPrice, double busPrice) {
        flightNumber = fn;
        departureTime = dept;
        arrivalTime = arr;
        destination = dest;
        departureLocation = depLoc;
        date = dt;

        totalSeats = econSeats + busSeats;
        for (int i = 0; i < econSeats; i++) {
            seats[i] = Seat(i + 1, "Economy", econPrice);
        }
        for (int i = econSeats; i < totalSeats; i++) {
            seats[i] = Seat(i + 1, "Business", busPrice);
        }
    }

    void displayFlightDetails() {
        cout << "\nFlight Number: " << flightNumber << endl;
        cout << "Date: " << date << endl;
        cout << "Departure Location: " << departureLocation << endl;
        cout << "Destination: " << destination << endl;
        cout << "Departure Time: " << departureTime << endl;
        cout << "Arrival Time: " << arrivalTime << endl;
        cout << "Available Seats: " << endl;
        for (int i = 0; i < totalSeats; i++) {
            seats[i].displaySeat();
        }
        cout << "---------Luggage limit---------\nEconomy class: 20kg\nBusiness class: 40kg\n" << endl;
    }

    bool bookSeat(int seatNumber, string customerName, string paymentMethod, string account, string processor) {
        if (seatNumber > 0 && seatNumber <= totalSeats) {
            if (seats[seatNumber - 1].bookSeat()) {
                double amount = seats[seatNumber - 1].getPrice();
                cout << "Seat " << seatNumber << " booked successfully!" << endl;
                cout << "Customer Name: " << customerName << endl;

                // Create a Payment object
                Payment payment(amount, paymentMethod, "Pending", account, processor);
                payment.processPayment();

                if (payment.getPaymentStatus() == "Completed") {
                    printTicket(customerName, seatNumber, seats[seatNumber - 1].getClass(), amount);
                    return true;
                } else {
                    cout << "Payment failed. Booking cannot be completed." << endl;
                    return false;
                }
            } else {
                cout << "Seat " << seatNumber << " is already booked." << endl;
                return false;
            }
        }
        cout << "Invalid seat number." << endl;
        return false;
    }

    bool cancelSeat(int seatNumber) {
        if (seatNumber > 0 && seatNumber <= totalSeats) {
            if (seats[seatNumber - 1].cancelBooking()) {
                cout << "Seat " << seatNumber << " canceled successfully!" << endl;
                return true;
            }
            else {
                cout << "Seat " << seatNumber << " is not currently booked." << endl;
            }
        }
        else {
            cout << "Invalid seat number." << endl;
        }
        return false;
    }


    void printTicket(string customerName, int seatNumber, string seatClass, double price) {
        cout << "\n--------- Ticket Details ---------\n";
        cout << "Customer Name: " << customerName << endl;
        cout << "Flight Number: " << flightNumber << endl;
        cout << "Date: " << date << endl;
        cout << "Departure Location: " << departureLocation << endl;
        cout << "Destination: " << destination << endl;
        cout << "Departure Time: " << departureTime << endl;
        cout << "Arrival Time: " << arrivalTime << endl;
        cout << "Seat Number: " << seatNumber << endl;
        cout << "Class: " << seatClass << endl;
        cout << "Price: $" << price << endl;
        cout << "----------------------------------\n";
    }

    string getFlightNumber() { return flightNumber; }
};

class AirlineSystem {
    Flight flights[MAX_FLIGHTS];
    int flightCount;

public:
    AirlineSystem() : flightCount(0) {}

    void addFlight(string flightNumber, string departureTime, string arrivalTime, string destination, string departureLocation, string date, int econSeats, int busSeats, double econPrice, double busPrice) {
        if (flightCount < MAX_FLIGHTS) {
            flights[flightCount].setFlight(flightNumber, departureTime, arrivalTime, destination, departureLocation, date, econSeats, busSeats, econPrice, busPrice);
            flightCount++;
        }
        else {
            cout << "Cannot add more flights. Maximum limit reached." << endl;
        }
    }

    void displayFlights() {
        for (int i = 0; i < flightCount; i++) {
            flights[i].displayFlightDetails();
        }
    }

    void bookFlightSeat(string flightNumber, int seatNumber, string customerName, string paymentMethod, string account, string processor) {
        for (int i = 0; i < flightCount; i++) {
            if (flightNumber == flights[i].getFlightNumber()) {
                flights[i].bookSeat(seatNumber, customerName, paymentMethod, account, processor);
                return;
            }
        }
        cout << "Flight not found." << endl;
    }

    void cancelFlightSeat(string flightNumber, int seatNumber) {
        for (int i = 0; i < flightCount; i++) {
            if (flightNumber == flights[i].getFlightNumber()) {
                flights[i].cancelSeat(seatNumber);
                return;
            }
        }
        cout << "Flight not found." << endl;
    }

    void cancelFlight(string flightNumber, Admin& admin) {

        string username, password;
        cout << "Enter Admin Username: ";
        cin >> username;
        cout << "Enter Admin Password: ";
        cin >> password;

        if (admin.authenticate(username, password)) {
            for (int i = 0; i < flightCount; i++) {
                if (flights[i].getFlightNumber() == flightNumber) {
                    for (int j = i; j < flightCount - 1; j++) {
                        flights[j] = flights[j + 1];
                    }
                    flightCount--;
                    cout << "Flight " << flightNumber << " canceled successfully by admin." << endl;
                    return;
                }
            }
            cout << "Flight not found." << endl;
        }
        else {
            cout << "Invalid admin credentials. Access denied." << endl;
        }
    }
};

int main() {
    AirlineSystem airline;
    Admin admin;

    airline.addFlight("AI123", "10:00 AM", "2:00 PM", "New York", "Los Angeles", "2025-01-15", 10, 5, 100.0, 200.0);
    airline.addFlight("AI456", "3:00 PM", "7:00 PM", "London", "Paris", "2025-01-16", 15, 8, 120.0, 250.0);

    cout << "========================                                           ================================" << endl;
    cout << "                           Welcome to Airline Reservation System                                   " << endl;
    cout << "========================                                           ================================" << endl;

    int choice;
    while (true) {
        cout << "\n1. Display Flights\n2. Book a Seat\n3. Cancel a Seat\n4. Cancel a Flight\n5. Exit\nChoose an option: ";
        cin >> choice;

        if (choice == 1) {
            airline.displayFlights();
        }
        else if (choice == 2) {
            string flightNumber;
            int seatNumber;
            string customerName;
            string paymentMethod, account, paymentDate, paymentProcessor;

            cout << "Enter Flight Number: ";
            cin >> flightNumber;
            cout << "Enter Seat Number to Book: ";
            cin >> seatNumber;
            cout << "Enter Customer Name: ";
            cin.ignore();
            getline(cin, customerName);

            // Get payment details
            while (true) {
            cout << "Enter Payment Method (Credit Card / Debit Card): ";
            getline(cin, paymentMethod);
 
    // Convert input to uppercase for case-insensitive comparison
    transform(paymentMethod.begin(), paymentMethod.end(), paymentMethod.begin(), ::toupper);

    // Check if the input is either "CREDIT CARD" or "DEBIT CARD"
    if (paymentMethod == "CREDIT CARD" || paymentMethod == "DEBIT CARD" || paymentMethod == "CREDIT" || paymentMethod == "DEBIT") {
        break;  // Valid payment method, exit the loop
    } else {
        cout << "Invalid Payment Method. Please enter either 'Credit Card' or 'Debit Card'." << endl;
    }
}
           while (true) {
           cout << "Enter Account Number (Last 4 digits): ";
            getline(cin, account);
            if (account.length() == 4){
            	break;
			} else {
        cout << "Invalid Account Number. Please enter exactly 4 digits." << endl;
    }}
            cout << "Enter Payment Processor (e.g., PayPal, Stripe): ";
            getline(cin, paymentProcessor);
             airline.bookFlightSeat(flightNumber, seatNumber, customerName, paymentMethod, account, paymentProcessor);
        }
		 else if (choice == 3) {
            string flightNumber;
            int seatNumber;
            cout << "Enter Flight Number: ";
            cin >> flightNumber;
            cout << "Enter Seat Number to Cancel: ";
            cin >> seatNumber;
            airline.cancelFlightSeat(flightNumber, seatNumber);
        } 
        else if (choice == 3) {
            string flightNumber;
            int seatNumber;
            cout << "Enter Flight Number: ";
            cin >> flightNumber;
            cout << "Enter Seat Number: ";
            cin >> seatNumber;
            airline.cancelFlightSeat(flightNumber, seatNumber);
        }
        else if (choice == 4) {
            string flightNumber;
            cout << "Enter Flight Number to Cancel: ";
            cin >> flightNumber;
            airline.cancelFlight(flightNumber, admin);
        }
        else if (choice == 5) {
        	cout << "========================                                           ================================" << endl;
            cout << "                   Thank you for using the Airline Reservation System!" << endl;
            cout << "========================                                           ================================" << endl;
            break;
        }
        else {
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
