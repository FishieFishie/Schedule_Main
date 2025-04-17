#include <iostream> // for cout and cin
#include <fstream> // for reading files
#include <string> // for using strings
#include "Schedule.h" // include our Schedule class

int main() {
    Schedule schedule;  // Create a schedule object
    std::ifstream inFile("STEM - Summer 2022 Schedule of Classes as of 05-02-22.csv");

    // Check if the file was opened successfully
    if (!inFile) {
        std::cerr << "Error: Could not open the CSV file." << std::endl;
        return 1; // return 1 to signal error
    }

    // Load all the data from the CSV file into the schedule map
    schedule.inSchedule(inFile);
    inFile.close(); // we're done with the file

    int choice;
    do {
        // Display menu options to the user
        std::cout << "\n===== Course Schedule Menu =====" << std::endl;
        std::cout << "1. Display all schedule items" << std::endl;
        std::cout << "2. Search by Subject" << std::endl;
        std::cout << "3. Search by Subject and Catalog Number" << std::endl;
        std::cout << "4. Search by Instructor Last Name" << std::endl;
        std::cout << "0. EXIT" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        std::cin.ignore(); // clear leftover newline after user input

        // Handle menu selection
        if (choice == 1) {
            schedule.print();
        }
        else if (choice == 2) {
            std::string subject;
            std::cout << "Enter Subject (e.g., BIO): ";
            std::getline(std::cin, subject);
            schedule.findBYsubject(subject);
        }
        else if (choice == 3) {
            std::string subject, catalog;
            std::cout << "Enter Subject (e.g., BIO): ";
            std::getline(std::cin, subject);
            std::cout << "Enter Catalog Number (e.g., 101): ";
            std::getline(std::cin, catalog);
            schedule.findBYsubCat(subject, catalog);
        }
        else if (choice == 4) {
            std::string lastName;
            std::cout << "Enter Instructor Last Name (e.g, Martin): ";
            std::getline(std::cin, lastName);
            schedule.findBYintroLN(lastName);
        }
        else if (choice == 0) {
            std::cout << "Exiting program. Goodbye!" << std::endl;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

    } while (choice != 0); // Repeat menu until user chooses to exit

    return 0; // end of main program
}