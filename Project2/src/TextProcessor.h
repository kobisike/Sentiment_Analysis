#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <vector>
#include "DSString.h"

class TextProcessor {
public:
    // Converts the given DSString to all lowercase letters.
    static DSString toLower(const DSString& input);
    
    // Removes punctuation characters from the DSString (keeps alphanumerics and spaces).
    static DSString removePunctuation(const DSString& input);
    
    // Filters out common stop words from the list of tokens.
    static std::vector<DSString> removeStopWords(const std::vector<DSString>& tokens);

    // Reduces a token to its stem (a simple implementation).
    static DSString stem(const DSString& input);

};

#endif // TEXTPROCESSOR_H
