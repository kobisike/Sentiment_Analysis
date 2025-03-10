#include <iostream>                     // Include the standard input/output stream library for console I/O
#include <vector>                       // Include the vector library to use the std::vector container
#include "DSString.h"                   // Include the header file for the custom DSString class
#include "FileIO.h"                     // Include the header file for file input/output operations
#include "Tokenizer.h"                  // Include the header file for the Tokenizer class
#include "SentimentClassifier.h"        // Include the header file for the SentimentClassifier class

using namespace std;                    // Use the standard namespace to avoid prefixing std:: everywhere

// Main function: the entry point of the program.
// It receives command-line arguments, which are used for file paths.
int main(int argc, char* argv[]) {
    // Check that the number of command-line arguments is exactly 6:
    // argv[0] is the program name, and argv[1] to argv[5] are the required arguments.
    // Expected arguments:
    // 1. Training data file
    // 2. Testing tweets file
    // 3. Testing sentiment file (ground truth)
    // 4. Results output file
    // 5. Accuracy output file
    if (argc != 6) {                 
        // If the number of arguments is incorrect, display the correct usage information.
        cout << "Usage: " << argv[0] 
             << " <training_data> <testing_data> <testing_sentiment> <results_file> <accuracy_file>" 
             << endl;
        return 1;                    // Exit the program with an error code of 1
    }
    
    // Display a message indicating the start of the sentiment analysis process.
    cout << "Starting Sentiment Analysis..." << endl;
    // Output the training data file path provided as the first argument.
    cout << "Training data file: " << argv[1] << endl;
    // Output the testing data file path provided as the second argument.
    cout << "Testing data file: " << argv[2] << endl;
    // Output the testing sentiment (ground truth) file path provided as the third argument.
    cout << "Testing sentiment file: " << argv[3] << endl;
    // Output the results output file path provided as the fourth argument.
    cout << "Results output file: " << argv[4] << endl;
    // Output the accuracy output file path provided as the fifth argument.
    cout << "Accuracy output file: " << argv[5] << endl;
    
    // Create an instance of the SentimentClassifier class.
    SentimentClassifier classifier;
    // Train the classifier using the training data file (provided as argv[1]).
    classifier.train(argv[1]);
    
    // Evaluate the classifier using the testing tweets file, testing sentiment file,
    // results output file, and accuracy output file (provided as argv[2] to argv[5]).
    float accuracy = classifier.evaluate(argv[2], argv[3], argv[4], argv[5]);
    // Output the classifier's accuracy to the console.
    cout << "Classifier Accuracy: " << accuracy << endl;
    
    return 0;                         // Return 0 to indicate successful execution of the program.
}
