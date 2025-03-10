#include "TextProcessor.h"        // Include the header file for the TextProcessor class
#include <cctype>                 // Include cctype for character classification and conversion functions (e.g., std::tolower, std::isalnum, std::isspace)

// Convert the input DSString to all lowercase letters.
DSString TextProcessor::toLower(const DSString& input) {
    DSString result;              // Create an empty DSString to store the lowercase result
    const char* data = input.c_str(); // Get the C-string representation of the input DSString
    for (size_t i = 0; i < input.length(); i++) { // Loop through each character in the input DSString
        // Append the lowercase version of the current character to the result DSString
        result.append(std::tolower(data[i]));  
    }
    return result;                // Return the resulting DSString that is now all lowercase
}

// Remove punctuation characters from the DSString (keeping only alphanumerics and spaces).
DSString TextProcessor::removePunctuation(const DSString& input) {
    DSString result;              // Create an empty DSString to store the result without punctuation
    const char* data = input.c_str(); // Get the C-string representation of the input DSString
    for (size_t i = 0; i < input.length(); i++) { // Loop through each character in the input
        char c = data[i];         // Get the current character
        // If the character is alphanumeric or a whitespace, then append it to the result
        if (std::isalnum(c) || std::isspace(c)) {
            result.append(c);
        }
    }
    return result;                // Return the DSString that contains only alphanumeric characters and spaces
}

// Remove common stop words from the list of tokens.
std::vector<DSString> TextProcessor::removeStopWords(const std::vector<DSString>& tokens) {
    // Define a fixed list of common stop words that were effective (~72% accuracy version).
    const char* stopWordsArray[] = {"the", "and", "is", "in", "at", "of", "a", "an", "to"};
    const int stopWordsCount = 9; // Total number of stop words in the array
    
    std::vector<DSString> filtered;  // Create a vector to store tokens that are not stop words
    // Iterate through each token in the provided list.
    for (size_t i = 0; i < tokens.size(); i++) {
        DSString lowerToken = toLower(tokens[i]); // Convert the token to lowercase for case-insensitive comparison
        bool isStopWord = false;   // Flag to indicate if the current token is a stop word
        // Check against each stop word in the list.
        for (int j = 0; j < stopWordsCount; j++) {
            DSString stopWord(stopWordsArray[j]); // Create a DSString for the current stop word
            if (lowerToken == stopWord) { // Compare the lowercase token to the stop word
                isStopWord = true;  // Mark as a stop word if they match
                break;              // No need to check further stop words, so exit the loop
            }
        }
        // If the token is not a stop word and is not empty, add it to the filtered vector.
        if (!isStopWord && lowerToken.length() > 0) {
            filtered.push_back(tokens[i]);
        }
    }
    return filtered;  // Return the vector of tokens with stop words removed
}

// Simple stemming function: removes common suffixes ("ing", "ed", and trailing "s").
DSString TextProcessor::stem(const DSString& input) {
    DSString lowerWord = toLower(input); // Convert the input token to lowercase
    size_t len = lowerWord.length();       // Get the length of the lowercase token
    const char* word = lowerWord.c_str();    // Get the C-string representation of the lowercase token
    
    // If the word ends with "ing" and is long enough (length > 4 to ensure some stem remains)
    if (len > 4 && word[len - 3] == 'i' && word[len - 2] == 'n' && word[len - 1] == 'g') {
        char* buffer = new char[len - 3 + 1]; // Allocate memory for the stem (original length minus "ing" plus null terminator)
        for (size_t i = 0; i < len - 3; i++) {  // Copy characters excluding the last three
            buffer[i] = word[i];
        }
        buffer[len - 3] = '\0';    // Append the null terminator to the new string
        DSString stemmed(buffer);  // Create a DSString from the stemmed C-string
        delete[] buffer;           // Free the allocated memory
        return stemmed;            // Return the stemmed token
    }
    // If the word ends with "ed" and is long enough (length > 3 to ensure some stem remains)
    if (len > 3 && word[len - 2] == 'e' && word[len - 1] == 'd') {
        char* buffer = new char[len - 2 + 1]; // Allocate memory for the stem (original length minus "ed" plus null terminator)
        for (size_t i = 0; i < len - 2; i++) {  // Copy characters excluding the last two
            buffer[i] = word[i];
        }
        buffer[len - 2] = '\0';    // Append the null terminator
        DSString stemmed(buffer);  // Create a DSString from the stemmed C-string
        delete[] buffer;           // Free the allocated memory
        return stemmed;            // Return the stemmed token
    }
    // If the word ends with "s" (and is not very short, to avoid removing 's' from words that are only one letter)
    if (len > 3 && word[len - 1] == 's') {
        char* buffer = new char[len - 1 + 1]; // Allocate memory for the stem (original length minus 1 plus null terminator)
        for (size_t i = 0; i < len - 1; i++) {  // Copy all characters except the last one
            buffer[i] = word[i];
        }
        buffer[len - 1] = '\0';    // Append the null terminator
        DSString stemmed(buffer);  // Create a DSString from the stemmed C-string
        delete[] buffer;           // Free the allocated memory
        return stemmed;            // Return the stemmed token
    }
    
    // If none of the conditions above apply, return the lowercase token unchanged.
    return lowerWord;
}
