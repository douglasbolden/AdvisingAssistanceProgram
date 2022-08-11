// The include statements are for all the different functions.
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// So that "std::" is assumed before cout and endl.
// This is not a good practice, but okay to have for a non-official code set.
using namespace std;

/* Define the general structure of a course that will be
   stored in the courses vector. */
struct Course{
    string courseID;
    string courseName;
    string coursePrerequisite1;
    string coursePrerequisite2;
    /* This is a constructor that assumes that some courses can have
       zero prerequisites. */
    Course() {
        coursePrerequisite1 = "";
        coursePrerequisite2 = "";
    }
};

/**
* Prints course information for passed course.
* Average performance O(1).
* Worst case performance O(1).
* 
* @param course to display the information of.
*/
void printCourseInformation(Course course) {
    cout << course.courseID << ", " << course.courseName << endl;
    // Check if course has only one prerequisite.
    if ((course.coursePrerequisite1 != "") &&
        (course.coursePrerequisite2 == "")) {
        cout << "Prerequisites:" << course.coursePrerequisite1 << endl;
    }
    // Check if course has two prerequisite.
    else if ((course.coursePrerequisite1 != "") && 
        (course.coursePrerequisite2 != "")) {
        cout << "Prerequisites:" << course.coursePrerequisite1
             << ", " << course.coursePrerequisite2 << endl;
    }
    // If course has zero prerequisites.
    else {
        cout << "Prerequisites: None" << endl;
    }
}

/**
 * Partition the vector of courses into two parts, low and high.
 *
 * @param courses Address of the vector<Course> instance to be partitioned.
 * @param begin Beginning index to partition.
 * @param end Ending index to partition.
 */
int partition(vector<Course>& courses, int begin, int end) {
    // Set low and high equal to begin and end.
    int low = begin;
    int high = end;
    // Pick the middle element as pivot point.
    int pivot = low + (high - low) / 2;

    // While not done.
    bool done = false;
    while (!done) {

        // Keep incrementing low index while courses[low] < courses[pivot].
        while (courses[low].courseID.compare(courses[pivot].courseID) < 0) {
            low += 1;
        }
        // Keep decrementing high index while courses[pivot] < courses[high].
        while (courses[pivot].courseID.compare(courses[high].courseID) < 0) {
            high -= 1;
        }
        /* If there are zero or one elements remaining,
           all courses are partitioned. Return high. */
        if (low >= high) {
            done = true;
        }
        // Else swap the low and high courses (built in vector method).
        else {
            // Move low and high closer ++low, --high.
            swap(courses[low], courses[high]);
            low += 1;
            high -= 1;
        }
    }
    // Return high.
    return high;
}

/**
 * Perform a quick sort on courseID.
 * Average performance: O(n log(n)).
 * Worst case performance O(n^2)).
 *
 * @param courses address of the vector<Course> instance to be sorted.
 * @param begin the beginning index to sort on.
 * @param end the ending index to sort on.
 */
void quickSort(vector<Course>& courses, int begin, int end) {
    // Set mid equal to 0.
    int mid = 0;
    /* Base case: If there are 1 or zero courses to sort,
       partition is already sorted otherwise if begin is greater
       than or equal to end then return. */
    if (begin >= end) {
        return;
    }
    /* Partition courses into low and high such that
     midpoint is location of last element in low. */
    mid = partition(courses, begin, end);
    // Recursively sort low partition (begin to mid).
    quickSort(courses, begin, mid);
    // Recursively sort high partition (mid+1 to end).
    quickSort(courses, mid + 1, end);
}

/**
* Display sorted courses.
* Average performance O(n).
* Worst case performance O(n).
* 
* @param vector containing courses to display.
*/
void createSampleSchedule(Course courses) {
    // Display each course in the newly sorted vector.
    cout << courses.courseID << ", " << courses.courseName << endl;
}

/**
* Opens the file that contains courses and places them in the courses vector.
*/
vector<Course> loadCourses() {
    // Define a vector data structure to hold a collection of courses.
    vector<Course> courses;
    // Declare input file stream.
    ifstream file;
    // Open the file.
    file.open("Advising-Assistance-Inputs.txt");
    // Make sure fule is open, and iterate the lines for information placement.
    if (file.is_open()) {
        // While NOT the last line of the file.
        while (!file.eof()) {
            Course course;
            stringstream delimitedInfo;
            string info;
            getline(file, info);

            delimitedInfo << info;
            int frequency = count(info.begin(), info.end(), ',');

            /* Calculate how many commas are in the line.
            * Calculate accordingly.
            */

            if (frequency == 1) {
                getline(delimitedInfo, course.courseID, ',');
                getline(delimitedInfo, course.courseName, ',');
            }

            else if (frequency == 2) {
                getline(delimitedInfo, course.courseID, ',');
                getline(delimitedInfo, course.courseName, ',');
                getline(delimitedInfo, course.coursePrerequisite1, ',');
            }

            else if (frequency == 3) {
                getline(delimitedInfo, course.courseID, ',');
                getline(delimitedInfo, course.courseName, ',');
                getline(delimitedInfo, course.coursePrerequisite1, ',');
                getline(delimitedInfo, course.coursePrerequisite2, ',');
            }
            else {
                cout << "Software only accepts a maximum of two prerequisites!" << endl;
            }

            // Push this course to the end of the Course vector.
            courses.push_back(course);
        }
        cout << "Loaded courses into the course list!" << endl;
    }
    // If the file can't be found.
    else {
        cout << "File Not Found." << endl;
    }
    // Close the file for use by other applications.
    file.close();
    // Load the vector with courses.
    return courses;
}

/**
* Main Driver
*/
int main() {
    // Held courses vector.
    vector<Course> courses;

    // For verification of course information.
    bool found = false;
    // For user selection of Menu.
    int choice = 0;
    // For course information selection.
    string course = "";
    cout << "Welcome to the course planner." << endl;
    
    // User menu display.
    while (choice != 9) {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        // Get user's choice for menu.
        cin >> choice;

        // Check user input for menu selection.
        switch (choice) {
        case 1:
            // Function Call.
            courses = loadCourses();
            cout << endl << "What would you like to do?" << endl;
            // Go back to menu.
            break;

        case 2:
            // Display sample schedule.
            cout << "Here is a sample schedule:" << endl << endl;
            // Iterate the courses vector.
            for (int i = 0; i < courses.size(); ++i) {
                // Function Call.
                quickSort(courses, 0, courses.size() - 1);
                // Function Call.
                createSampleSchedule(courses[i]);
            }
            cout << endl << "What would you like to do?" << endl;
            // Go back to menu.
            break;

        case 3:
            cout << "What course do you want to know about?" << endl;
            // Gather the course that user wants information for.
            cin >> course;
            /* This capitalizes the user's input,
               so that they can put either case */
            transform(course.begin(), course.end(), course.begin(), ::toupper);
            // Iterate courses vector.
            for (int i = 0; i < courses.size(); ++i) {
                // Compare currently iterated course with user-input course.
                if (course.compare(courses[i].courseID) == 0) {
                    // Function Call.
                    printCourseInformation(courses[i]);
                    cout << endl << "What would you like to do?" << endl;
                    /* Set the bool to true, so that we
                       can skip the next if statement. */
                    found = true;
                }

            }
            if (found == false) {
                cout << "Course Information not available." << endl;
                cout << "What would you like to do?" << endl;
                // Go back to the menu.
                break;
            }
            else {
                // Reset for future use.
                found = false;
                // Go back to the menu.
                break;
            }
            

        case 9:
            // Exit application.
            break;

        default:
            // In case input is something that isn't an int.
            if (cin.fail()) {
                cout << "Please enter a valid number." << endl;
                cout << "What would you like to do?" << endl;
                // Get rid of failure state.
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Tell user that their choice is invalid.
            else {
                cout << choice << " is not a valid option." << endl << endl;
                cout << "What would you like to do?" << endl;
            }
        }
    }
    cout << "Thank you for using the course planner!" << endl;
    // To confirm good application exit.
    return 0;
}
