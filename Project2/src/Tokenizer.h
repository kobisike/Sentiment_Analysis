#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <vector>
#include "DSString.h"

class Tokenizer {
public:
    // Splits the given DSString by the delimiter and returns a vector of tokens.
    static std::vector<DSString> tokenize(const DSString& str, char delimiter);
};

#endif // TOKENIZER_H
