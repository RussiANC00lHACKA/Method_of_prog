/**
 * @file main.cpp
 * @brief Example code for sorting students and measuring sorting times.
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;
/**
 * @brief Class for representing a student.
 */
class Student {
public:
    string fullname;/**< Full name of the student. */
    string faculty;/**< Faculty of the student. */
    int avg_grade;/**< Average grade of the student. */
    /**
     * @brief Constructor of the Student class.
     * @param fullname Full name of the student.
     * @param faculty Faculty of the student.
     * @param avg_grade Average grade of the student.
     */
    Student(const string& fullname, const string& faculty, int avg_grade)
        : fullname(fullname), faculty(faculty), avg_grade(avg_grade) {}
    /**
     * @brief Overloading '<' operator for comparing students.
     * @param other Another student to compare.
     * @return Comparison result.
     */
    bool operator <(const Student& other) const {
        if (fullname != other.fullname)
            return fullname < other.fullname;
        if (faculty != other.faculty)
            return faculty < other.faculty;
        return avg_grade < other.avg_grade;
    }
    /**
     * @brief Overloading '>' operator for comparing students.
     * @param other Another student to compare.
     * @return Comparison result.
     */
    bool operator >(const Student& other) const {
        if (fullname != other.fullname)
            return fullname > other.fullname;
        if (faculty != other.faculty)
            return faculty > other.faculty;
        return avg_grade > other.avg_grade;
    }
    /**
     * @brief Overloading '<=' operator for comparing students.
     * @param other Another student to compare.
     * @return Comparison result.
     */
    bool operator <=(const Student& other) const {
        return !(other < *this);
    }
    /**
     * @brief Overloading '>=' operator for comparing students.
     * @param other Another student to compare.
     * @return Comparison result.
     */
    bool operator >=(const Student& other) const {
        return !(*this < other);
    }
};
/**
 * @brief Function for reading data from a CSV file and creating a vector of students.
 * @param filename File name.
 * @param n Number of students to read.
 * @return Vector of students.
 */
vector<Student> read_csv(const string& filename, int n) {
    vector<Student> students;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        getline(file, line);
        for (int i = 0; i < n && getline(file, line); i++) {
            stringstream ss(line);
            string fullname, faculty;
            int avg_grade;
            getline(ss, fullname, ',');
            getline(ss, faculty, ',');
            ss >> avg_grade;
            students.emplace_back(fullname, faculty, avg_grade);
        }
        file.close();
    }
    return students;
}
/**
 * @brief Function for selection sort.
 * @tparam T Type of elements to sort.
 * @param arr Vector to sort.
 */
template<typename T>
void selectionSort(vector<T>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}
/**
 * @brief Function for bubble sort.
 * @tparam T Type of elements to sort.
 * @param arr Vector to sort.
 */
template<typename T>
void bubbleSort(vector<T>& arr) {
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = 0; j < arr.size() - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}
/**
 * @brief Function for cocktail shaker sort.
 * @tparam T Type of elements to sort.
 * @param arr Vector to sort.
 */
template<typename T>
void cocktailSort(vector<T>& arr) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;
        --end;

        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        ++start;
    }
}
/**
 * @brief Function for printing sorting results.
 * @tparam T Type of elements.
 * @param data Data to print.
 * @param sort_type Type of sorting.
 * @param size Size of data.
 * @param data_type Type of data.
 * @param duration Sorting duration in microseconds.
 */
template<typename T>
void printResults(const vector<T>& data, const string& sort_type, int size, const string& data_type, long long duration) {
    cout << sort_type << " Sorting: " << size << " students by " << data_type << " took " << duration << " microseconds." << endl;
}
/**
 * @brief Main entry point of the program.
 * @return Return code.
 */
int main() {
    string filename = "C:\\Users\\79276\\OneDrive\\Documents\\Jupyter_Work_Study\\students_data.csv";
    vector<int> data_sizes = { 75000, 85000, 100000, 120000 }; //500, 1000, 3000, 10000, 30000, 50000

    for (int n : data_sizes) {
        vector<Student> students = read_csv(filename, n);

        // Selection Sort
        auto start = high_resolution_clock::now();
        selectionSort(students);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        printResults(students, "Selection", n, "name, faculty, average grade", duration.count());

        // Bubble Sort
        vector<Student> studentsBubble = students;
        start = high_resolution_clock::now();
        bubbleSort(studentsBubble);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        printResults(studentsBubble, "Bubble", n, "name, faculty, average grade", duration.count());

        // Cocktail Shaker Sort
        vector<Student> studentsCocktail = students;
        start = high_resolution_clock::now();
        cocktailSort(studentsCocktail);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);
        printResults(studentsCocktail, "Cocktail Shaker", n, "name, faculty, average grade", duration.count());
    }

    return 0;
}
