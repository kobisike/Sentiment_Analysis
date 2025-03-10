#include "FileIO.h"               // Include the header file for the FileIO class
#include <fstream>                // Include fstream for file input/output operations
#include <iostream>               // Include iostream for console input/output (e.g., std::cerr)
#include <string>                 // Include string to use std::string for temporary storage

// Definition of the static method readLines in the FileIO class.
// This method reads all lines from the given file and returns a vector of DSString objects.
std::vector<DSString> FileIO::readLines(const char* filename) {
    std::vector<DSString> lines;  // Create an empty vector to store each line as a DSString
    
    std::ifstream infile(filename); // Open the file using an ifstream, with the filename provided as an argument
    if (!infile) {                // Check if the file was successfully opened
        std::cerr << "Error: Unable to open file " << filename << std::endl; // Output an error message to the standard error stream
        return lines;           // Return the empty vector if the file could not be opened
    }
    
    std::string line;           // Declare a std::string variable to temporarily store each line read from the file
    while (std::getline(infile, line)) { // Read each line from the file into the variable 'line'
        // Convert std::string to DSString:
        // Create a DSString object using the C-string (null-terminated char array) version of the std::string.
        DSString dsLine(line.c_str());
        lines.push_back(dsLine); // Append the DSString object to the vector of lines
    }
    
    infile.close();             // Close the file after reading all lines
    return lines;               // Return the vector containing all the lines as DSString objects
}
