#include "DSString.h"  // Include the header file for the DSString class

// Default constructor: creates an empty string
DSString::DSString() : data(nullptr), len(0) {  // Initialize data pointer to nullptr and length to 0
    data = new char[1];             // Allocate memory for one character (for the null terminator)
    data[0] = '\0';                 // Set the first (and only) character to the null terminator, representing an empty string
}

// Parameterized constructor: creates a DSString from a C-string
DSString::DSString(const char* s) { // Constructor that initializes DSString with a C-string
    size_t i = 0;                   // Initialize index counter i to 0
    while (s[i] != '\0') {          // Loop until the end of the C-string is reached
        i++;                      // Increment i to count the number of characters
    }
    len = i;                      // Set the DSString length to the number of characters found
    data = new char[len + 1];     // Allocate memory for the characters plus one extra for the null terminator
    for (size_t j = 0; j < len; j++) { // Loop over each character index j from 0 to len-1
        data[j] = s[j];           // Copy the j-th character from the input C-string to the DSString data array
    }
    data[len] = '\0';             // Append a null terminator at the end of the DSString
}

// Copy constructor: deep copy
DSString::DSString(const DSString& other) { // Copy constructor that creates a new DSString as a deep copy of another
    len = other.len;              // Copy the length from the other DSString
    data = new char[len + 1];     // Allocate new memory for the copied string (including null terminator)
    for (size_t i = 0; i < len; i++) { // Loop over each character in the other DSString
        data[i] = other.data[i];  // Copy each character from the other DSString's data array
    }
    data[len] = '\0';             // Set the last element to the null terminator
}

// Destructor: free allocated memory
DSString::~DSString() {           // Destructor for DSString, called when an object is destroyed
    delete[] data;              // Free the dynamically allocated memory for the data array
}

// Assignment operator: ensure proper deep copy and self-assignment check
DSString& DSString::operator=(const DSString& other) { // Overloaded assignment operator for DSString
    if (this == &other)          // Check for self-assignment (i.e., assigning the object to itself)
        return *this;           // If self-assignment, return the current object without doing anything

    delete[] data;              // Delete the current data to free memory and avoid a memory leak
    len = other.len;            // Copy the length from the other DSString
    data = new char[len + 1];   // Allocate new memory for the data array based on the new length
    for (size_t i = 0; i < len; i++) { // Loop over each character index
        data[i] = other.data[i]; // Copy each character from the other DSString
    }
    data[len] = '\0';           // Set the last character to the null terminator
    return *this;               // Return the current object by reference
}

// Return the length of the string
size_t DSString::length() const { // Function to return the length of the DSString
    return len;               // Return the stored length (number of characters)
}

// Return the C-string (null-terminated character array)
const char* DSString::c_str() const { // Function to return the internal C-string representation of DSString
    return data;              // Return the pointer to the data array containing the characters
}

// Append a single character to the string
void DSString::append(char c) { // Function to append one character to the end of the DSString
    char* newData = new char[len + 2]; // Allocate new memory for current length + 1 new char + 1 for null terminator
    for (size_t i = 0; i < len; i++) { // Loop through each character of the existing string
        newData[i] = data[i];   // Copy the existing characters into the new array
    }
    newData[len] = c;           // Append the new character at the position equal to the current length
    newData[len + 1] = '\0';    // Append a null terminator at the end of the new array
    delete[] data;              // Delete the old data array to free memory
    data = newData;             // Update the data pointer to the new array
    len++;                      // Increment the length to account for the new character
}

// Equality operator
bool DSString::operator==(const DSString& other) const { // Overloaded equality operator to compare two DSString objects
    if (len != other.len)       // If lengths differ, the strings cannot be equal
        return false;           // Return false if lengths are not the same
    for (size_t i = 0; i < len; i++) { // Loop over each character index
        if (data[i] != other.data[i]) // Compare corresponding characters in the two strings
            return false;       // If any character differs, return false
    }
    return true;                // If all characters match, return true
}

// Less-than operator: used for ordering DSString objects (e.g., in STL containers)
bool DSString::operator<(const DSString& other) const { // Overloaded operator to compare DSString objects lexicographically
    size_t minLen = (len < other.len) ? len : other.len; // Determine the minimum length between the two strings
    for (size_t i = 0; i < minLen; i++) { // Iterate over each character up to the minimum length
        if (data[i] < other.data[i]) // If the character in this string is less than that in the other string,
            return true;         // return true because this string is lexicographically smaller
        if (data[i] > other.data[i]) // If the character in this string is greater than that in the other,
            return false;        // return false because this string is not smaller
    }
    return len < other.len;      // If all compared characters are equal, the shorter string is considered less
}

// Concatenation operator: returns a new DSString that is the concatenation of the two strings
DSString DSString::operator+(const DSString& other) const { // Overloaded '+' operator for concatenating DSString objects
    size_t newLen = len + other.len; // Calculate the length of the concatenated string
    char* newData = new char[newLen + 1]; // Allocate memory for the new concatenated string (+1 for null terminator)
    for (size_t i = 0; i < len; i++) { // Copy the characters from the current string to the new array
        newData[i] = data[i];     // Copy each character from the original DSString
    }
    for (size_t i = 0; i < other.len; i++) { // Copy the characters from the other string
        newData[len + i] = other.data[i]; // Append each character from the other DSString after the current string's characters
    }
    newData[newLen] = '\0';       // Set the null terminator at the end of the new concatenated string
    DSString result(newData);     // Create a new DSString object using the concatenated C-string
    delete[] newData;             // Free the temporary memory allocated for newData
    return result;                // Return the new DSString object representing the concatenated string
}

// Overloaded stream insertion operator for printing DSString
std::ostream& operator<<(std::ostream& os, const DSString& str) { // Overloaded '<<' operator for outputting DSString objects
    os << str.c_str();            // Insert the C-string representation of the DSString into the output stream
    return os;                    // Return the output stream to allow chaining of the operator
}
