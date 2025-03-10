#include "SentimentClassifier.h"       // Include the header file for the SentimentClassifier class
#include "FileIO.h"                    // Include the header file for file I/O functions
#include "Tokenizer.h"                 // Include the header file for tokenizing DSString objects
#include "TextProcessor.h"             // Include the header file for text processing functions (toLower, remove punctuation, stop words, stemming)
#include <fstream>                     // Include fstream for file reading and writing
#include <sstream>                     // Include sstream for string stream operations (if needed)
#include <iostream>                    // Include iostream for console I/O (e.g., std::cout, std::cerr)
#include <iomanip>                     // Include iomanip for output formatting (e.g., std::setprecision)
#include <cmath>                       // Include cmath for mathematical functions (e.g., log)
#include <set>                         // Include set for storing unique tokens

// Constructor: Initialize all counters and variables to 0.
SentimentClassifier::SentimentClassifier() 
    : positiveTweetCount(0), negativeTweetCount(0),
      totalPositiveWords(0), totalNegativeWords(0), vocabularySize(0) {
    // Constructor body is empty since initialization is done in the initializer list.
}

// Helper function: Preprocess and tokenize a tweet.
// This function takes a DSString containing tweet text, cleans it, tokenizes it, removes stop words, and stems each token.
std::vector<DSString> SentimentClassifier::tokenizeTweet(const DSString& tweetText) {
    // Convert the tweet text to lowercase and remove punctuation.
    DSString cleaned = TextProcessor::removePunctuation(TextProcessor::toLower(tweetText));
    // Tokenize the cleaned text into tokens based on spaces.
    std::vector<DSString> tokens = Tokenizer::tokenize(cleaned, ' ');
    // Remove common stop words from the tokens.
    tokens = TextProcessor::removeStopWords(tokens);
    // Create a vector to hold the stemmed tokens.
    std::vector<DSString> stemmedTokens;
    // For each token in the vector...
    for (size_t i = 0; i < tokens.size(); i++) {
        // Apply stemming to the token and add the result to the stemmedTokens vector.
        stemmedTokens.push_back(TextProcessor::stem(tokens[i]));
    }
    // Return the final vector of processed tokens.
    return stemmedTokens;
}

// Process a single training tweet.
// The expected CSV format is: sentiment, tweetID, date, query, username, tweet_text.
void SentimentClassifier::processTrainingTweet(const DSString& tweetLine) {
    // Tokenize the CSV line using a comma as the delimiter.
    std::vector<DSString> tokens = Tokenizer::tokenize(tweetLine, ',');
    // If there are fewer than 6 tokens, the line is invalid; skip processing.
    if (tokens.size() < 6) {
        return;  // Not enough tokens; skip this line.
    }
    
    // Determine sentiment: if the first token is "4", treat the tweet as positive; otherwise, treat it as negative.
    int sentiment = (tokens[0] == DSString("4")) ? 4 : 0;
    // Extract the tweet text from the sixth token.
    DSString tweetText = tokens[5];
    
    // Tokenize the tweet text using the helper function.
    std::vector<DSString> words = tokenizeTweet(tweetText);
    
    // If the tweet is positive, update the positive tweet count and word frequencies.
    if (sentiment == 4) {
        positiveTweetCount++;  // Increment positive tweet counter.
        for (size_t i = 0; i < words.size(); i++) {
            positiveWords[words[i]]++;  // Increment frequency for each token in positive tweets.
        }
    } else { // Otherwise, the tweet is negative.
        negativeTweetCount++;  // Increment negative tweet counter.
        for (size_t i = 0; i < words.size(); i++) {
            negativeWords[words[i]]++;  // Increment frequency for each token in negative tweets.
        }
    }
}

// Train the classifier using the training data file.
void SentimentClassifier::train(const char* trainingFile) {
    // Read all lines from the training file into a vector of DSString objects.
    std::vector<DSString> lines = FileIO::readLines(trainingFile);
    // Process each line (i.e., each tweet) from the training data.
    for (size_t i = 0; i < lines.size(); i++) {
        processTrainingTweet(lines[i]);
    }
    
    // Calculate the total number of words in positive tweets.
    for (auto &entry : positiveWords) {
        totalPositiveWords += entry.second;
    }
    // Calculate the total number of words in negative tweets.
    for (auto &entry : negativeWords) {
        totalNegativeWords += entry.second;
    }
    
    // Build the vocabulary as a set of unique words from both positive and negative tweets.
    std::set<DSString> vocab;
    // Insert each unique word from positive tweets.
    for (auto &entry : positiveWords) {
        vocab.insert(entry.first);
    }
    // Insert each unique word from negative tweets.
    for (auto &entry : negativeWords) {
        vocab.insert(entry.first);
    }
    // Set the vocabulary size to the number of unique words.
    vocabularySize = vocab.size();
}

// Predict sentiment using a Naive Bayes approach.
// The function returns 4 for positive sentiment and 0 for negative sentiment.
int SentimentClassifier::predict(const DSString& tweetText) {
    // Tokenize and process the tweet text.
    std::vector<DSString> words = tokenizeTweet(tweetText);
    
    // Compute the total number of training tweets.
    int totalTweets = positiveTweetCount + negativeTweetCount;
    // Calculate the log prior probability for the positive class.
    double logPriorPositive = log((double)positiveTweetCount / totalTweets);
    // Calculate the log prior probability for the negative class.
    double logPriorNegative = log((double)negativeTweetCount / totalTweets);
    
    // Initialize the log probabilities with the log prior probabilities.
    double logProbPositive = logPriorPositive;
    double logProbNegative = logPriorNegative;
    
    // For each token in the processed tweet...
    for (size_t i = 0; i < words.size(); i++) {
        DSString word = words[i];  // Get the current token.
        // Retrieve the frequency of the token in positive tweets.
        int countPositive = positiveWords[word];
        // Retrieve the frequency of the token in negative tweets.
        int countNegative = negativeWords[word];
        
        double alpha = 1.0; // Use Laplace smoothing with alpha = 1.0.
        // Compute the smoothed probability of the token in the positive class.
        double wordProbPositive = (countPositive + alpha) / (totalPositiveWords + alpha * vocabularySize);
        // Compute the smoothed probability of the token in the negative class.
        double wordProbNegative = (countNegative + alpha) / (totalNegativeWords + alpha * vocabularySize);
        
        // Update the log probability for the positive class by adding the log of the token's probability.
        logProbPositive += log(wordProbPositive);
        // Update the log probability for the negative class by adding the log of the token's probability.
        logProbNegative += log(wordProbNegative);
    }
    
    // Compare the log probabilities:
    // If the positive log probability is greater than or equal to the negative, return 4 (positive sentiment).
    // Otherwise, return 0 (negative sentiment).
    return (logProbPositive >= logProbNegative) ? 4 : 0;
}

// Evaluate the classifier on the test data.
// This function reads test tweets and ground truth, writes predictions to a results file,
// writes accuracy and error details to an accuracy file, and returns the accuracy.
float SentimentClassifier::evaluate(const char* testTweetsFile, const char* testSentimentFile, 
                                      const char* resultsFile, const char* accuracyFile) {
    // Read all lines from the test tweets file.
    std::vector<DSString> tweetLines = FileIO::readLines(testTweetsFile);
    // Read all lines from the ground truth (test sentiment) file.
    std::vector<DSString> groundTruthLines = FileIO::readLines(testSentimentFile);
    
    // Build a mapping from tweet ID to the actual sentiment using the ground truth file.
    std::map<DSString, int> groundTruth;
    // For each line in the ground truth file...
    for (size_t i = 0; i < groundTruthLines.size(); i++) {
        // Tokenize the line using a comma as the delimiter.
        std::vector<DSString> tokens = Tokenizer::tokenize(groundTruthLines[i], ',');
        // If there are fewer than 2 tokens, skip this line.
        if (tokens.size() < 2)
            continue;
        // Determine the actual sentiment: "4" means positive; otherwise, negative.
        int sentiment = (tokens[0] == DSString("4")) ? 4 : 0;
        // Extract the tweet ID from the second token.
        DSString tweetID = tokens[1];
        // Map the tweet ID to its corresponding sentiment.
        groundTruth[tweetID] = sentiment;
    }
    
    // Open the results output file for writing predictions.
    std::ofstream resultsOut(resultsFile);
    // Open the accuracy output file for writing overall accuracy and error details.
    std::ofstream accuracyOut(accuracyFile);
    // If either file fails to open, print an error and return 0.0 accuracy.
    if (!resultsOut || !accuracyOut) {
        std::cerr << "Error: Unable to open results or accuracy output files." << std::endl;
        return 0.0f;
    }
    
    int totalTweetsCount = 0;           // Counter for the number of tweets with available ground truth.
    int correct = 0;                    // Counter for correctly classified tweets.
    std::vector<DSString> errorLines;   // Vector to store error lines for misclassified tweets.
    
    // Process each test tweet.
    for (size_t i = 0; i < tweetLines.size(); i++) {
        // Tokenize the test tweet line using a comma.
        // Expected format: tweetID, date, query, username, tweet_text.
        std::vector<DSString> tokens = Tokenizer::tokenize(tweetLines[i], ',');
        // If the line doesn't have at least 5 tokens, skip it.
        if (tokens.size() < 5)
            continue;
        // Extract the tweet ID (first token).
        DSString tweetID = tokens[0];
        // Extract the tweet text (fifth token).
        DSString tweetText = tokens[4];
        
        // Predict the sentiment for the tweet text.
        int predicted = predict(tweetText);
        // Write the predicted sentiment and tweet ID to the results file in the format: predicted, tweetID.
        resultsOut << predicted << ", " << tweetID << std::endl;
        
        // If ground truth exists for this tweet...
        if (groundTruth.find(tweetID) != groundTruth.end()) {
            totalTweetsCount++;       // Increment the counter of tweets with ground truth.
            int actual = groundTruth[tweetID]; // Retrieve the actual sentiment from the ground truth map.
            if (predicted == actual) {
                correct++;            // If the prediction matches the actual sentiment, increment the correct counter.
            } else {
                // If the prediction is incorrect, create an error line in the format: actual, predicted, tweetID.
                DSString errorLine((std::to_string(actual) + ", " +
                                    std::to_string(predicted) + ", " +
                                    tweetID.c_str()).c_str());
                // Add the error line to the vector of error lines.
                errorLines.push_back(errorLine);
            }
        }
    }
    
    // Calculate the overall accuracy as the ratio of correct predictions to the total tweets with ground truth.
    float accuracy = (totalTweetsCount > 0) ? (float)correct / totalTweetsCount : 0.0f;
    // Write the accuracy (formatted with exactly three decimal places) on the first line of the accuracy file.
    accuracyOut << std::fixed << std::setprecision(3) << accuracy << std::endl;
    // Write each error line (misclassified tweet details) to the accuracy file.
    for (size_t i = 0; i < errorLines.size(); i++) {
        accuracyOut << errorLines[i] << std::endl;
    }
    
    // Close the results and accuracy output files.
    resultsOut.close();
    accuracyOut.close();
    
    // Return the calculated accuracy.
    return accuracy;
}
