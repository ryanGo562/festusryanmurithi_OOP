#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ============================================================
//  ABSTRACT BASE CLASS — User
//  Pillar: Abstraction + Encapsulation
// ============================================================
class User {
private:
    string userID;
    string name;
    string email;

public:
    User(string id, string nm, string em) {
        userID = id;
        name   = nm;
        email  = em;
    }

    string getUserID() const { return userID; }
    string getName()   const { return name; }
    string getEmail()  const { return email; }

    // Pure virtual — Abstraction (User cannot be created directly)
    virtual string getRole() const = 0;

    virtual void getDetails() const {
        cout << "Name:  " << name   << endl;
        cout << "Email: " << email  << endl;
        cout << "Role:  " << getRole() << endl;
    }

    virtual ~User() {}
};


// ============================================================
//  DERIVED CLASS — Driver
//  Pillar: Inheritance + Polymorphism
// ============================================================
class Driver : public User {
private:
    string licenseNumber;
    string licenseExpiry;
    string assignedVehiclePlate;
    string route;

public:
    Driver(string id, string nm, string em, string lic, string exp)
        : User(id, nm, em) {
        licenseNumber        = lic;
        licenseExpiry        = exp;
        assignedVehiclePlate = "Not Assigned";
        route                = "Not Assigned";
    }

    void assignVehicle(string plate) { assignedVehiclePlate = plate; }
    void assignRoute(string r)       { route = r; }

    string getRole() const override { return "Driver"; }

    void getDetails() const override {
        cout << "\n--- Driver Profile ---" << endl;
        User::getDetails();
        cout << "License No:  " << licenseNumber        << endl;
        cout << "Expiry:      " << licenseExpiry         << endl;
        cout << "Vehicle:     " << assignedVehiclePlate  << endl;
        cout << "Route:       " << route                 << endl;
    }
};


// ============================================================
//  DERIVED CLASS — VehicleOwner
//  Pillar: Inheritance + Polymorphism
// ============================================================
class VehicleOwner : public User {
private:
    string ownerID;
    string saccoName;
    vector<string> plates;

public:
    VehicleOwner(string id, string nm, string em, string oid)
        : User(id, nm, em) {
        ownerID   = oid;
        saccoName = "Not Assigned";
    }

    void joinSACCO(string sacco) { saccoName = sacco; }

    void registerVehicle(string plate) {
        plates.push_back(plate);
    }

    string getRole() const override { return "Vehicle Owner"; }

    void getDetails() const override {
        cout << "\n--- Vehicle Owner Profile ---" << endl;
        User::getDetails();
        cout << "Owner ID: " << ownerID   << endl;
        cout << "SACCO:    " << saccoName << endl;
        cout << "Registered Vehicles:" << endl;
        if (plates.empty()) {
            cout << "  None." << endl;
        } else {
            for (int i = 0; i < (int)plates.size(); i++)
                cout << "  " << i+1 << ". " << plates[i] << endl;
        }
    }
};


// ============================================================
//  DERIVED CLASS — PoliceOfficer
//  Pillar: Inheritance + Polymorphism
// ============================================================
class PoliceOfficer : public User {
private:
    string badgeNumber;
    string station;

public:
    PoliceOfficer(string id, string nm, string em, string badge, string sta)
        : User(id, nm, em) {
        badgeNumber = badge;
        station     = sta;
    }

    string getBadgeNumber() const { return badgeNumber; }
    string getStation()     const { return station; }

    void flagVehicle(string plate, string violationType, string reason) const {
        cout << "\n--- FLAG RECORD ---" << endl;
        cout << "Officer:    " << getName()     << endl;
        cout << "Badge No:   " << badgeNumber   << endl;
        cout << "Station:    " << station       << endl;
        cout << "Vehicle:    " << plate         << endl;
        cout << "Violation:  " << violationType << endl;
        cout << "Reason:     " << reason        << endl;
        cout << "[SYSTEM] Vehicle " << plate << " has been flagged successfully." << endl;
    }

    string getRole() const override { return "Police Officer"; }

    void getDetails() const override {
        cout << "\n--- Police Officer Profile ---" << endl;
        User::getDetails();
        cout << "Badge No: " << badgeNumber << endl;
        cout << "Station:  " << station     << endl;
    }
};


// ============================================================
//  DERIVED CLASS — Whistleblower
//  Pillar: Inheritance + Polymorphism + Encapsulation
// ============================================================
class Whistleblower : public User {
private:
    bool   isAnonymous;
    string contactInfo;

public:
    Whistleblower(string id, string nm, string em, bool anon, string contact)
        : User(id, nm, em) {
        isAnonymous = anon;
        contactInfo = contact;
    }

    // Encapsulation — contact hidden if anonymous
    string getContactInfo() const {
        if (isAnonymous) return "Anonymous";
        return contactInfo;
    }

    void submitReport(string plate, string description) const {
        cout << "\n--- WHISTLEBLOWER REPORT ---" << endl;
        cout << "Reporter:   " << getContactInfo() << endl;
        cout << "Vehicle:    " << plate            << endl;
        cout << "Report:     " << description      << endl;
        cout << "[SYSTEM] Report submitted successfully." << endl;
    }

    string getRole() const override { return "Whistleblower"; }

    void getDetails() const override {
        cout << "\n--- Whistleblower Profile ---" << endl;
        User::getDetails();
        cout << "Anonymous:  " << (isAnonymous ? "Yes" : "No") << endl;
        cout << "Contact:    " << getContactInfo()              << endl;
    }
};


// ============================================================
//  DERIVED CLASS — NTSAOfficer
//  Pillar: Inheritance + Polymorphism
// ============================================================
class NTSAOfficer : public User {
private:
    string officerID;
    string department;

public:
    NTSAOfficer(string id, string nm, string em, string oid, string dept)
        : User(id, nm, em) {
        officerID  = oid;
        department = dept;
    }

    void approveVehicle(string plate) const {
        cout << "[NTSA] Vehicle " << plate << " has been APPROVED." << endl;
    }
    void rejectVehicle(string plate, string reason) const {
        cout << "[NTSA] Vehicle " << plate << " REJECTED. Reason: " << reason << endl;
    }
    void suspendVehicle(string plate) const {
        cout << "[NTSA] Vehicle " << plate << " has been SUSPENDED." << endl;
    }

    string getRole() const override { return "NTSA Officer"; }

    void getDetails() const override {
        cout << "\n--- NTSA Officer Profile ---" << endl;
        User::getDetails();
        cout << "Officer ID:  " << officerID  << endl;
        cout << "Department:  " << department << endl;
    }
};


// ============================================================
//  SUPPORTING CLASS — Vehicle
//  Pillar: Encapsulation
// ============================================================
class Vehicle {
private:
    string plateNumber;
    string make;
    string model;
    int    year;
    string ownerName;
    string saccoName;
    string route;
    string vehicleType; // Matatu, Country Bus, Nganya
    bool   isApproved;

public:
    Vehicle(string plt, string mk, string mdl, int yr,
            string ownr, string sac, string rte, string vtype) {
        plateNumber = plt;
        make        = mk;
        model       = mdl;
        year        = yr;
        ownerName   = ownr;
        saccoName   = sac;
        route       = rte;
        vehicleType = vtype;
        isApproved  = false;
    }

    string getPlate() const { return plateNumber; }
    void   setApproved(bool status) { isApproved = status; }

    void getDetails() const {
        cout << "\n--- Vehicle Details ---"                          << endl;
        cout << "Plate:    " << plateNumber                         << endl;
        cout << "Type:     " << vehicleType                         << endl;
        cout << "Vehicle:  " << make << " " << model                << endl;
        cout << "Year:     " << year                                 << endl;
        cout << "Owner:    " << ownerName                           << endl;
        cout << "SACCO:    " << saccoName                           << endl;
        cout << "Route:    " << route                               << endl;
        cout << "Status:   " << (isApproved ? "Approved" : "Pending Approval") << endl;
    }
};


// ============================================================
//  HELPERS
// ============================================================
void divider() {
    cout << "\n========================================" << endl;
}

void showSACCOs() {
    cout << "\nSelect your SACCO:" << endl;
    cout << "  1. Super Metro"       << endl;
    cout << "  2. Nico Movers"       << endl;
    cout << "  3. Forward Travellers"<< endl;
    cout << "  4. Double M"          << endl;
    cout << "  5. Githurai Shuttle"  << endl;
    cout << "  6. City Hoppa"        << endl;
    cout << "  7. Other (type yours)"<< endl;
}

string pickSACCO() {
    showSACCOs();
    int choice;
    cout << "Enter choice: ";
    cin >> choice;
    cin.ignore();
    switch (choice) {
        case 1: return "Super Metro";
        case 2: return "Nico Movers";
        case 3: return "Forward Travellers";
        case 4: return "Double M";
        case 5: return "Githurai Shuttle";
        case 6: return "City Hoppa";
        default:
            string other;
            cout << "Type your SACCO name: ";
            getline(cin, other);
            return other;
    }
}

void showRoutes() {
    cout << "\nKnown Nairobi Routes (for reference):" << endl;
    cout << "  Ngong Road | Langata Road | Westlands | Kilimani" << endl;
    cout << "  Hurlingham | Eastleigh | Umoja | Donholm"         << endl;
    cout << "  Embassava | Membley | Tatu City | Ruiru"          << endl;
    cout << "  Kimbo | Matangi | Pipeline | Eastern Bypass"      << endl;
}


// ============================================================
//  ROLE HANDLERS
// ============================================================

void handleOwner() {
    divider();
    cout << "  VEHICLE OWNER REGISTRATION" << endl;
    divider();

    string name, email, plate, make, model, route, vtype;
    int year, typeChoice;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "\nEnter vehicle plate number (e.g. KDA 123B): ";
    getline(cin, plate);

    cout << "Enter vehicle make (e.g. Toyota): ";
    getline(cin, make);

    cout << "Enter vehicle model (e.g. HiAce): ";
    getline(cin, model);

    cout << "Enter vehicle year: ";
    cin >> year;
    cin.ignore();

    cout << "\nSelect vehicle type:"  << endl;
    cout << "  1. Standard Matatu"   << endl;
    cout << "  2. Country Bus"       << endl;
    cout << "  3. Nganya"            << endl;
    cout << "Enter choice: ";
    cin >> typeChoice;
    cin.ignore();

    switch (typeChoice) {
        case 1: vtype = "Standard Matatu"; break;
        case 2: vtype = "Country Bus";     break;
        case 3: vtype = "Nganya";          break;
        default: vtype = "Standard Matatu";
    }

    string sacco = pickSACCO();

    showRoutes();
    cout << "\nType your route: ";
    getline(cin, route);

    VehicleOwner owner("OWN001", name, email, "OWN001");
    owner.joinSACCO(sacco);
    owner.registerVehicle(plate);

    Vehicle vehicle(plate, make, model, year, name, sacco, route, vtype);

    owner.getDetails();
    vehicle.getDetails();

    cout << "\n[SYSTEM] Vehicle registered successfully. Awaiting NTSA approval." << endl;
}


void handleDriver() {
    divider();
    cout << "  DRIVER REGISTRATION" << endl;
    divider();

    string name, email, license, expiry, plate, route;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter your license number: ";
    getline(cin, license);

    cout << "Enter license expiry date (e.g. 2026-12-01): ";
    getline(cin, expiry);

    cout << "Enter plate number of your vehicle: ";
    getline(cin, plate);

    showRoutes();
    cout << "\nType your route: ";
    getline(cin, route);

    // Create object
    Driver driver("DRV001", name, email, license, expiry);
    driver.assignVehicle(plate);
    driver.assignRoute(route);

    // Show results
    driver.getDetails();

    cout << "\n[SYSTEM] Driver profile created successfully." << endl;
}


void handlePolice() {
    divider();
    cout << "  POLICE OFFICER — FLAG A VEHICLE" << endl;
    divider();

    string name, email, badge, station, plate, reason;
    int violationChoice;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter your badge number: ";
    getline(cin, badge);

    cout << "Enter your station: ";
    getline(cin, station);

    cout << "\nEnter plate number of vehicle to flag: ";
    getline(cin, plate);

    cout << "\nSelect violation type:" << endl;
    cout << "  1. Overloading"                  << endl;
    cout << "  2. No Insurance"                 << endl;
    cout << "  3. Operating on wrong route"     << endl;
    cout << "  4. Reckless driving"             << endl;
    cout << "  5. Expired roadworthiness"       << endl;
    cout << "  6. Other"                        << endl;
    cout << "Enter choice: ";
    cin >> violationChoice;
    cin.ignore();

    string violationType;
    switch (violationChoice) {
        case 1: violationType = "Overloading";               break;
        case 2: violationType = "No Insurance";              break;
        case 3: violationType = "Operating on wrong route";  break;
        case 4: violationType = "Reckless driving";          break;
        case 5: violationType = "Expired roadworthiness";    break;
        default: violationType = "Other";                    break;
    }

    cout << "State your reason / description: ";
    getline(cin, reason);

    // Create object and flag
    PoliceOfficer officer("POL001", name, email, badge, station);
    officer.flagVehicle(plate, violationType, reason);
}


void handleWhistleblower() {
    divider();
    cout << "  WHISTLEBLOWER REPORT" << endl;
    divider();

    string name = "Anonymous";
    string email = "anonymous@gmail.com";
    string contact, plate, description;
    int anonChoice;
    bool isAnon;

    cout << "Do you want to remain anonymous?" << endl;
    cout << "  1. Yes — stay anonymous"        << endl;
    cout << "  2. No  — include my name"       << endl;
    cout << "Enter choice: ";
    cin >> anonChoice;
    cin.ignore();

    if (anonChoice == 2) {
        isAnon = false;
        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your phone number: ";
        getline(cin, contact);
    } else {
        isAnon  = true;
        contact = "Anonymous";
    }

    cout << "\nEnter plate number of vehicle you are reporting: ";
    getline(cin, plate);

    cout << "Describe what you witnessed: ";
    getline(cin, description);

    // Create object and submit
    Whistleblower wb("WB001", name, email, isAnon, contact);
    wb.submitReport(plate, description);
}


void handleNTSA() {
    divider();
    cout << "  NTSA OFFICER — VEHICLE ACTION" << endl;
    divider();

    string name, email, officerID, department, plate, reason;
    int actionChoice;

    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter your email: ";
    getline(cin, email);

    cout << "Enter your officer ID: ";
    getline(cin, officerID);

    cout << "Enter your department: ";
    getline(cin, department);

    cout << "\nEnter plate number of vehicle to act on: ";
    getline(cin, plate);

    cout << "\nSelect action:" << endl;
    cout << "  1. Approve vehicle"  << endl;
    cout << "  2. Reject vehicle"   << endl;
    cout << "  3. Suspend vehicle"  << endl;
    cout << "Enter choice: ";
    cin >> actionChoice;
    cin.ignore();

    NTSAOfficer ntsa("NTSA001", name, email, officerID, department);
    ntsa.getDetails();

    switch (actionChoice) {
        case 1:
            ntsa.approveVehicle(plate);
            break;
        case 2:
            cout << "Enter reason for rejection: ";
            getline(cin, reason);
            ntsa.rejectVehicle(plate, reason);
            break;
        case 3:
            ntsa.suspendVehicle(plate);
            break;
        default:
            cout << "Invalid action." << endl;
    }
}


// ============================================================
//  MAIN
// ============================================================
int main() {
    int choice;

    do {
        cout << "\n========================================" << endl;
        cout << "   KENYA MATATU MANAGEMENT SYSTEM"       << endl;
        cout << "========================================" << endl;
        cout << "\nWELCOME to NTSA Services\n Kindly follow the guidelines and answer accordingly" << endl;
        cout << "  1. Vehicle Owner"   << endl;
        cout << "  2. Driver"          << endl;
        cout << "  3. Police Officer"  << endl;
        cout << "  4. Whistleblower"   << endl;
        cout << "  5. NTSA Officer"    << endl;
        cout << "\nEnter choice: ";

        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: handleOwner();         break;
            case 2: handleDriver();        break;
            case 3: handlePolice();        break;
            case 4: handleWhistleblower(); break;
            case 5: handleNTSA();          break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }

        int back;
        cout << "\n========================================" << endl;
        cout << "  Go back to main menu?"                   << endl;
        cout << "  1. Yes"                                  << endl;
        cout << "  2. No (Exit)"                            << endl;
        cout << "Enter choice: ";
        cin >> back;
        cin.ignore();

        if (back != 1) break;

    } while (true);

    cout << "\n========================================" << endl;
    cout << "   GOODBYE. SYSTEM CLOSED.WE VALUE YOU FEEDBACK"               << endl;
    cout << "========================================" << endl;

    return 0;
}
