#ifndef DSSTRING_H
#define DSSTRING_H

#include <iostream>

class DSString {
private:
    char* data;   // dynamically allocated character array
    size_t len;   // cached length of the string
public:
    // Constructors
    DSString();                       // default constructor
    DSString(const char* s);          // parameterized constructor
    DSString(const DSString& other);  // copy constructor

    // Destructor
    ~DSString();

    // Assignment operator
    DSString& operator=(const DSString& other);

    // Member functions
    size_t length() const;
    const char* c_str() const;
    
    // Append a single character to the string (used in tokenization)
    void append(char c);

    // Overloaded operators
    bool operator==(const DSString& other) const;

    // Comparison operator for STL containers (lexicographical comparison)
    bool operator<(const DSString& other) const;
    
    DSString operator+(const DSString& other) const;

    // Friend function for stream output
    friend std::ostream& operator<<(std::ostream& os, const DSString& str);
};

#endif // DSSTRING_H
