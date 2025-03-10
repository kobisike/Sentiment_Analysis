#include "Tokenizer.h"  // Include the header file for the Tokenizer class

// The tokenize function splits the given DSString 'str' into tokens separated by the specified 'delimiter' character.
std::vector<DSString> Tokenizer::tokenize(const DSString& str, char delimiter) {
    std::vector<DSString> tokens;        // Create an empty vector to hold the resulting tokens
    const char* cstr = str.c_str();        // Get the C-string (null-terminated char array) representation of the input DSString
    size_t length = str.length();          // Determine the length of the input DSString
    
    DSString currentToken;  // Initialize an empty DSString to accumulate characters for the current token
    // Loop through each character in the C-string representation of the input
    for (size_t i = 0; i < length; i++) {
        if (cstr[i] == delimiter) {        // Check if the current character is the delimiter
            // When the delimiter is encountered, add the current token to the tokens vector
            tokens.push_back(currentToken);
            // Reset currentToken to an empty DSString for the next token
            currentToken = DSString();
        } else {
            // If the character is not the delimiter, append it to the current token
            currentToken.append(cstr[i]);
        }
    }
    // After the loop, push the final token into the vector (even if it is empty)
    tokens.push_back(currentToken);
    
    return tokens;  // Return the vector containing all the tokens
}
