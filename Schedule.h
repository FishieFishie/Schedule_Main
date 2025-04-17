#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <iostream> // for cout and endl
#include <fstream>  // for ifstream (file input)
#include <sstream>  // for stringstream (to split lines)
#include <map>      // for std::map
#include <string>   // for std::string
#include <vector>   // for vector
#include "Schedule_item.h" // include our struct from before

// This class manages all course schedule entries
class Schedule {
private:
    // This map holds all courses using a unique key like "BIO_101_01H"
    std::map<std::string, ScheduleItem> scheduleMap;

public:
    // Loads course data from the CSV file
    void inSchedule(std::ifstream& inFile) {
        std::string line;
        std::getline(inFile, line); // Skip header

        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            std::string cell;
            std::vector<std::string> columns;

            // Split line into individual comma-separated columns
            while (std::getline(ss, cell, ',')) {
                columns.push_back(cell);
            }

            // Defensive: skip if not enough columns
            if (columns.size() < 12) continue;

            ScheduleItem course;

            // Assign only the columns we care about (by index)
            course.subject = columns[0];   // Subject
            course.catalog = columns[1];   // Catalog
            course.section = columns[2];   // Section
            course.component = columns[3];   // Component
            course.session = columns[4];   // Session
            course.units = std::stoi(columns[6]);  // Units (column 7)
            course.totEnrolled = std::stoi(columns[7]);  // TotEnrl (column 8)
            course.capEnrolled = std::stoi(columns[8]);  // CapEnrl (column 9)
            course.instructor = columns[10];            // Instructor (column 11)

            addEntry(course); // Add to map
        }
    }
    // Adds one ScheduleItem to the map
    void addEntry(const ScheduleItem& item) {
        std::string key = item.getKey(); // get the key like "BIO_101_01H"
        scheduleMap[key] = item; // insert into the map
    }

    // Prints the column headers
    void printHeader() const {
        std::cout << std::left
            << std::setw(8) << "Subject"
            << std::setw(10) << "Catalog"
            << std::setw(10) << "Section"
            << std::setw(10) << "Component"
            << std::setw(8) << "Session"
            << std::setw(6) << "Units"
            << std::setw(10) << "TotEnrl"
            << std::setw(10) << "CapEnrl"
            << "Instructor" << std::endl;
    }

    // Prints all entries in the map
    void print() const {
        printHeader();
        for (const auto& pair : scheduleMap) {
            pair.second.print(); // call print() on each ScheduleItem
        }
    }

    // Finds and prints courses that match a subject
    void findBYsubject(const std::string& subject) const {
        printHeader();
        for (const auto& pair : scheduleMap) {
            if (pair.second.subject == subject) {
                pair.second.print();
            }
        }
    }

    // Find and prints courses that match a subject and catalog
    void findBYsubCat(const std::string& subject, const std::string& catalog) const {
        printHeader();
        for (const auto& pair : scheduleMap) {
            if (pair.second.subject == subject && pair.second.catalog == catalog) {
                pair.second.print();
            }
        }
    }

    // Finds and prints courses that match an instructor's last name
    void findBYintroLN(const std::string& lastName) const {
        printHeader();
        for (const auto& pair : scheduleMap) {
            // Find position of comma in name to extract last name
            std::string instructor = pair.second.instructor;
            size_t commaPos = instructor.find(',');
            std::string actualLast = (commaPos != std::string::npos) ? instructor.substr(0, commaPos) : instructor;

            if (actualLast == lastName) {
                pair.second.print();
            }
        }
    }
};

#endif // SCHEDULE_H