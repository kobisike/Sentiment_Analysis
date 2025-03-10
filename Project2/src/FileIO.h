#ifndef FILEIO_H
#define FILEIO_H

#include <vector>
#include "DSString.h"

class FileIO {
public:
    // Reads the entire file and returns a vector of DSString, one per line.
    static std::vector<DSString> readLines(const char* filename);
};

#endif // FILEIO_H
