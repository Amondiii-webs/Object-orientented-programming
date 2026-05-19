#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

// ==================== CLASS DEFINITIONS ====================

class Patient {
private:
    int id;
    string name;
    int age;
    string disease;
    string contact;

public:
    // Constructor
    Patient(int i = 0, string n = "", int a = 0, string d = "", string c = "")
        : id(i), name(n), age(a), disease(d), contact(c) {}

    // Getter methods
    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getDisease() const { return disease; }
    string getContact() const { return contact; }

    // Setter methods
    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setDisease(string d) { disease = d; }
    void setContact(string c) { contact = c; }

    // Display patient details
    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(8) << age
             << setw(20) << disease
             << setw(15) << contact << endl;
    }
};

class Doctor {
private:
    int id;
    string name;
    string specialization;
    double fee;

public:
    Doctor(int i = 0, string n = "", string s = "", double f = 0.0)
        : id(i), name(n), specialization(s), fee(f) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getSpecialization() const { return specialization; }
    double getFee() const { return fee; }

    void setName(string n) { name = n; }
    void setSpecialization(string s) { specialization = s; }
    void setFee(double f) { fee = f; }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(20) << specialization
             << "$" << setw(10) << fee << endl;
    }
};

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    string date;
    string time;

public:
    Appointment(int appId = 0, int pId = 0, int dId = 0, string dt = "", string tm = "")
        : appointmentId(appId), patientId(pId), doctorId(dId), date(dt), time(tm) {}

    int getAppointmentId() const { return appointmentId; }
    int getPatientId() const { return patientId; }
    int getDoctorId() const { return doctorId; }
    string getDate() const { return date; }
    string getTime() const { return time; }

    void display() const {
        cout << left << setw(12) << appointmentId
             << setw(12) << patientId
             << setw(12) << doctorId
             << setw(15) << date
             << setw(10) << time << endl;
    }
};

// ==================== HOSPITAL MANAGEMENT SYSTEM CLASS ====================

class HospitalSystem {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
    int nextPatientId;
    int nextDoctorId;
    int nextAppointmentId;

public:
    HospitalSystem() : nextPatientId(100), nextDoctorId(200), nextAppointmentId(1000) {
        // Add some sample data
        addSampleData();
    }
//
    void addSampleData() {
        // Sample doctors
        doctors.push_back(Doctor(nextDoctorId++, "Dr. Singh", "Cardiology", 500.0));
        doctors.push_back(Doctor(nextDoctorId++, "Dr. Johnson", "Neurology", 600.0));
        doctors.push_back(Doctor(nextDoctorId++, "Dr. Milele", "Pediatrics", 400.0));
        doctors.push_back(Doctor(nextDoctorId++, "Dr. Mathenge", "Orthopedics", 550.0));

        // Sample patients
        patients.push_back(Patient(nextPatientId++, "Scarlet Amondi", 30, "Fever", "123-456-7890"));
        patients.push_back(Patient(nextPatientId++, "Michael Mwangi", 45, "Back Pain", "234-567-8901"));
        patients.push_back(Patient(nextPatientId++, "Lucy Kimani", 12, "Cold", "345-678-9012"));
    }

    // ---------- PATIENT MANAGEMENT ----------
    void addPatient() {
        string name, disease, contact;
        int age;

        cout << "\n--- Add New Patient ---\n";
        cout << "Enter Patient Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Disease: ";
        cin.ignore();
        getline(cin, disease);
        cout << "Enter Contact Number: ";
        getline(cin, contact);

        patients.push_back(Patient(nextPatientId++, name, age, disease, contact));
        cout << "\n Patient added successfully! Patient ID: " << (nextPatientId - 1) << endl;
    }

    void viewAllPatients() const {
        if (patients.empty()) {
            cout << "\nNo patients found.\n";
            return;
        }

        cout << "\n--- All Patients ---\n";
        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(8) << "Age"
             << setw(20) << "Disease"
             << setw(15) << "Contact" << endl;
        cout << string(73, '-') << endl;

        for (const auto& patient : patients) {
            patient.display();
        }
    }

    void searchPatientById() {
        int id;
        cout << "\nEnter Patient ID to search: ";
        cin >> id;

        for (const auto& patient : patients) {
            if (patient.getId() == id) {
                cout << "\n--- Patient Found ---\n";
                cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(8) << "Age"
                     << setw(20) << "Disease" << setw(15) << "Contact" << endl;
                cout << string(73, '-') << endl;
                patient.display();
                return;
            }
        }
        cout << "\n Patient with ID " << id << " not found.\n";
    }

    void searchPatientByName() {
        string name;
        cout << "\nEnter Patient Name to search: ";
        cin.ignore();
        getline(cin, name);

        bool found = false;
        cout << "\n--- Search Results ---\n";
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(8) << "Age"
             << setw(20) << "Disease" << setw(15) << "Contact" << endl;
        cout << string(73, '-') << endl;

        for (const auto& patient : patients) {
            if (patient.getName().find(name) != string::npos) {
                patient.display();
                found = true;
            }
        }

        if (!found) {
            cout << "\n No patient found with name containing '" << name << "'\n";
        }
    }

    void updatePatient() {
        int id;
        cout << "\nEnter Patient ID to update: ";
        cin >> id;

        for (auto& patient : patients) {
            if (patient.getId() == id) {
                string name, disease, contact;
                int age;

                cout << "\n--- Updating Patient (ID: " << id << ") ---\n";
                cout << "Enter New Name (current: " << patient.getName() << "): ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter New Age (current: " << patient.getAge() << "): ";
                cin >> age;
                cout << "Enter New Disease (current: " << patient.getDisease() << "): ";
                cin.ignore();
                getline(cin, disease);
                cout << "Enter New Contact (current: " << patient.getContact() << "): ";
                getline(cin, contact);

                patient.setName(name);
                patient.setAge(age);
                patient.setDisease(disease);
                patient.setContact(contact);

                cout << "\n Patient updated successfully!\n";
                return;
            }
        }
        cout << "\n Patient with ID " << id << " not found.\n";
    }

    void deletePatient() {
        int id;
        cout << "\nEnter Patient ID to delete: ";
        cin >> id;

        auto it = remove_if(patients.begin(), patients.end(),
                           [id](const Patient& p) { return p.getId() == id; });

        if (it != patients.end()) {
            patients.erase(it, patients.end());
            cout << "\n Patient deleted successfully!\n";
        } else {
            cout << "\n Patient with ID " << id << " not found.\n";
        }
    }

    // ---------- DOCTOR MANAGEMENT ----------
    void addDoctor() {
        string name, specialization;
        double fee;

        cout << "\n--- Add New Doctor ---\n";
        cout << "Enter Doctor Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Specialization: ";
        getline(cin, specialization);
        cout << "Enter Consultation Fee: $";
        cin >> fee;

        doctors.push_back(Doctor(nextDoctorId++, name, specialization, fee));
        cout << "\n Doctor added successfully! Doctor ID: " << (nextDoctorId - 1) << endl;
    }

    void viewAllDoctors() const {
        if (doctors.empty()) {
            cout << "\nNo doctors found.\n";
            return;
        }

        cout << "\n--- All Doctors ---\n";
        cout << left << setw(10) << "ID"
             << setw(20) << "Name"
             << setw(20) << "Specialization"
             << setw(10) << "Fee" << endl;
        cout << string(60, '-') << endl;

        for (const auto& doctor : doctors) {
            doctor.display();
        }
    }

    // ---------- APPOINTMENT MANAGEMENT ----------
    void bookAppointment() {
        viewAllPatients();
        viewAllDoctors();

        int patientId, doctorId;
        string date, time;

        cout << "\n--- Book Appointment ---\n";
        cout << "Enter Patient ID: ";
        cin >> patientId;
        cout << "Enter Doctor ID: ";
        cin >> doctorId;
        cout << "Enter Date (DD/MM/YYYY): ";
        cin >> date;
        cout << "Enter Time (HH:MM): ";
        cin >> time;

        // Verify patient and doctor exist
        bool patientExists = false, doctorExists = false;

        for (const auto& p : patients) {
            if (p.getId() == patientId) patientExists = true;
        }

        for (const auto& d : doctors) {
            if (d.getId() == doctorId) doctorExists = true;
        }

        if (!patientExists) {
            cout << "\n Patient ID not found!\n";
            return;
        }

        if (!doctorExists) {
            cout << "\n Doctor ID not found!\n";
            return;
        }

        appointments.push_back(Appointment(nextAppointmentId++, patientId, doctorId, date, time));
        cout << "\n Appointment booked successfully! Appointment ID: " << (nextAppointmentId - 1) << endl;
    }

    void viewAllAppointments() const {
        if (appointments.empty()) {
            cout << "\nNo appointments found.\n";
            return;
        }

        cout << "\n--- All Appointments ---\n";
        cout << left << setw(12) << "Appt ID"
             << setw(12) << "Patient ID"
             << setw(12) << "Doctor ID"
             << setw(15) << "Date"
             << setw(10) << "Time" << endl;
        cout << string(61, '-') << endl;

        for (const auto& appt : appointments) {
            appt.display();
        }
    }

    // ---------- BILLING ----------
    void generateBill() {
        int patientId;
        cout << "\nEnter Patient ID for billing: ";
        cin >> patientId;

        string patientName;
        double consultationFee = 0;
        bool patientFound = false;

        // Find patient and their doctor from appointments
        for (const auto& p : patients) {
            if (p.getId() == patientId) {
                patientName = p.getName();
                patientFound = true;
                break;
            }
        }

        if (!patientFound) {
            cout << "\n Patient not found!\n";
            return;
        }

        // Get latest appointment for this patient
        for (const auto& appt : appointments) {
            if (appt.getPatientId() == patientId) {
                for (const auto& d : doctors) {
                    if (d.getId() == appt.getDoctorId()) {
                        consultationFee = d.getFee();
                        break;
                    }
                }
                break;
            }
        }

        double medicineCost, otherCharges;
        cout << "\n--- Bill Generation for " << patientName << " ---\n";
        cout << "Enter Medicine Cost: $";
        cin >> medicineCost;
        cout << "Enter Other Charges (Room, Tests, etc.): $";
        cin >> otherCharges;

        double total = consultationFee + medicineCost + otherCharges;

        cout << "\n========== INVOICE ==========\n";
        cout << "Patient ID: " << patientId << endl;
        cout << "Patient Name: " << patientName << endl;
        cout << "Consultation Fee: $" << consultationFee << endl;
        cout << "Medicine Cost: $" << medicineCost << endl;
        cout << "Other Charges: $" << otherCharges << endl;
        cout << "-----------------------------\n";
        cout << "TOTAL AMOUNT: $" << total << endl;
        cout << "=============================\n";

        double paid;
        cout << "\nEnter amount paid: $";
        cin >> paid;

        if (paid >= total) {
            cout << "\n Bill paid successfully! Change: $" << (paid - total) << endl;
        } else {
            cout << "\n Balance due: $" << (total - paid) << endl;
        }
    }

    // ---------- MAIN MENU ----------
    void showMenu() {
        int choice;

        do {
            cout << "\n========================================\n";
            cout << "    HOSPITAL MANAGEMENT SYSTEM\n";
            cout << "========================================\n";
            cout << "1. Patient Management\n";
            cout << "2. Doctor Management\n";
            cout << "3. Appointment Management\n";
            cout << "4. Billing\n";
            cout << "5. Exit\n";
            cout << "========================================\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch(choice) {
                case 1:
                    patientMenu();
                    break;
                case 2:
                    doctorMenu();
                    break;
                case 3:
                    appointmentMenu();
                    break;
                case 4:
                    generateBill();
                    break;
                case 5:
                    cout << "\nThank you for using Hospital Management System!\n";
                    break;
                default:
                    cout << "\n Invalid choice! Please try again.\n";
            }
        } while(choice != 5);
    }

    void patientMenu() {
        int choice;
        do {
            cout << "\n--- Patient Management ---\n";
            cout << "1. Add Patient\n";
            cout << "2. View All Patients\n";
            cout << "3. Search Patient by ID\n";
            cout << "4. Search Patient by Name\n";
            cout << "5. Update Patient\n";
            cout << "6. Delete Patient\n";
            cout << "7. Back to Main Menu\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice) {
                case 1: addPatient(); break;
                case 2: viewAllPatients(); break;
                case 3: searchPatientById(); break;
                case 4: searchPatientByName(); break;
                case 5: updatePatient(); break;
                case 6: deletePatient(); break;
                case 7: break;
                default: cout << "\n Invalid choice!\n";
            }
        } while(choice != 7);
    }

    void doctorMenu() {
        int choice;
        do {
            cout << "\n--- Doctor Management ---\n";
            cout << "1. Add Doctor\n";
            cout << "2. View All Doctors\n";
            cout << "3. Back to Main Menu\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice) {
                case 1: addDoctor(); break;
                case 2: viewAllDoctors(); break;
                case 3: break;
                default: cout << "\n Invalid choice!\n";
            }
        } while(choice != 3);
    }

    void appointmentMenu() {
        int choice;
        do {
            cout << "\n--- Appointment Management ---\n";
            cout << "1. Book Appointment\n";
            cout << "2. View All Appointments\n";
            cout << "3. Back to Main Menu\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch(choice) {
                case 1: bookAppointment(); break;
                case 2: viewAllAppointments(); break;
                case 3: break;
                default: cout << "\n Invalid choice!\n";
            }
        } while(choice != 3);
    }
};

// ==================== MAIN FUNCTION ====================

int main() {
    HospitalSystem system;
    system.showMenu();

    return 0;
}
