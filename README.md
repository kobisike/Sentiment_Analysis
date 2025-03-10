# Don't Be Sentimental! - Sentiment Analysis Project

## Overview

"Don't Be Sentimental!" is a C++ project that builds a simple sentiment classifier for tweets. It utilizes a custom string class (`DSString`) and implements several core modules for text processing and classification. The classifier uses a Naive Bayes approach to determine whether a tweet expresses positive or negative sentiment. It reads training and testing data from CSV files, processes the tweets, and then outputs both the predicted sentiment for each tweet and an accuracy report with error details.

## Project Structure

The project is organized as follows:

- **DSString**  
  A custom string class implemented without using the STL string. It provides dynamic memory management (using the rule-of-three: constructor, destructor, and copy assignment operator), and supports operations like concatenation, equality, and ordering.  
  Files:  
  - `src/DSString.h`  
  - `src/DSString.cpp`

- **FileIO**  
  Contains functions for file reading. The module reads files line by line and converts each line into a `DSString`.  
  Files:  
  - `src/FileIO.h`  
  - `src/FileIO.cpp`

- **Tokenizer**  
  Splits a `DSString` into tokens based on a specified delimiter (used both for CSV parsing and splitting tweet text into words).  
  Files:  
  - `src/Tokenizer.h`  
  - `src/Tokenizer.cpp`

- **TextProcessor**  
  Implements text preprocessing functions such as converting to lowercase, removing punctuation, filtering out stop words, and performing simple stemming (removing common suffixes like "ing", "ed", and trailing "s").  
  Files:  
  - `src/TextProcessor.h`  
  - `src/TextProcessor.cpp`

- **SentimentClassifier**  
  This is the core component that handles training and predicting tweet sentiment. It reads the training dataset, processes each tweet, and updates frequency counts for positive and negative words. For prediction, it applies the same text preprocessing and uses a Naive Bayes classifier with Laplace smoothing to calculate probabilities. The classifier also evaluates its performance on a testing dataset, outputting both a results file and an accuracy report (including details on misclassified tweets).  
  Files:  
  - `src/SentimentClassifier.h`  
  - `src/SentimentClassifier.cpp`

- **Main Driver**  
  Contains the `main()` function which processes command-line arguments, initiates training and testing, and outputs the results.  
  File:  
  - `src/main.cpp`

## How It Works

1. **Training Phase:**  
   - The program reads a CSV training file containing tweets with labels (positive or negative).
   - For each tweet, it extracts the tweet text and applies text preprocessing (lowercasing, punctuation removal, tokenization, stop word removal, and stemming).
   - It then updates frequency counts for each token, separately for positive and negative tweets, and calculates totals (e.g., total number of words and vocabulary size).

2. **Prediction Phase:**  
   - The program reads a separate testing dataset (tweets without labels) and a ground truth sentiment file.
   - It processes each test tweet with the same preprocessing steps.
   - Using a Naive Bayes classifier with Laplace smoothing, it computes the log probability of the tweet belonging to the positive and negative classes.
   - The predicted sentiment (4 for positive and 0 for negative) is written to a results file, and overall accuracy along with details of misclassified tweets is written to an accuracy file.

## Building and Running the Project

This project uses CMake as the build system. 

**References:**

ChatGPT
