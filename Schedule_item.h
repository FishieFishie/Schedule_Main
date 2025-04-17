#ifndef SCHEDULE_ITEM_H
#define SCHEDULE_ITEM_H

#include <iostream> // for std::cout and std::endl
#include <iomanip> // for formatting output with setw
#include <string> // for using std::string

// This struct represents one course in the schedule
struct ScheduleItem {
    // Data fields - these hold the info for each course
    std::string subject;
    std::string catalog;
    std::string section;
    std::string component;
    std::string session;
    int units;
    int totEnrolled; // tot. = total
    int capEnrolled; // cap. = capacity
    std::string instructor;

    // This function returns a key to uniquely identify a course
    std::string getKey() const {
        return subject + "_" + catalog + "_" + section;
    }

    // This function prints one row of course data formatted in columns
    void print() const {
        std::cout << std::left
            << std::setw(8) << subject
            << std::setw(10) << catalog
            << std::setw(10) << section
            << std::setw(10) << component
            << std::setw(8) << session
            << std::setw(6) << units
            << std::setw(10) << totEnrolled
            << std::setw(10) << capEnrolled
            << instructor << std::endl;
    }

    // Comparision operators based on the key
    bool operator==(const ScheduleItem& other) const {
        return getKey() == other.getKey();
    }

    bool operator!=(const ScheduleItem& other) const {
        return !(*this == other);
    }

    bool operator>=(const ScheduleItem& other) const {
        return getKey() >= other.getKey();
    }

};

#endif // SCHEDULE_ITEM_H
