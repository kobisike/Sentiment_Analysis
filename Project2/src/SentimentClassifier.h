#ifndef SENTIMENTCLASSIFIER_H
#define SENTIMENTCLASSIFIER_H

#include <vector>
#include <map>
#include "DSString.h"

class SentimentClassifier {
private:
    // Word frequency maps for positive and negative tweets.
    std::map<DSString, int> positiveWords;
    std::map<DSString, int> negativeWords;
    
    // Count of tweets in each class.
    int positiveTweetCount;
    int negativeTweetCount;
    
    // New members for Naive Bayes calculations.
    int totalPositiveWords;
    int totalNegativeWords;
    int vocabularySize;
    
    // New: document frequency for tokens.
    std::map<DSString, int> tokenDocFrequency;

    // Helper functions.
    void processTrainingTweet(const DSString& tweetLine);
    std::vector<DSString> tokenizeTweet(const DSString& tweetText);
    
public:
    SentimentClassifier();
    
    // Train using the training file.
    void train(const char* trainingFile);
    
    // Predict the sentiment (4 for positive, 0 for negative) using Naive Bayes.
    int predict(const DSString& tweetText);
    
    // Evaluate the classifier on the test files.
    float evaluate(const char* testTweetsFile, const char* testSentimentFile, 
                   const char* resultsFile, const char* accuracyFile);
};

#endif // SENTIMENTCLASSIFIER_H
