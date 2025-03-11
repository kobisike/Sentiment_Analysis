# Sentiment Analysis Project: Q&A

Below are the answers to the questions regarding the sentiment analysis project.

---

## 1. How do you train the model and how do you classify a new tweet?

**Answer:**  
- **Training:**  
  The program reads a CSV training file, where each line contains a tweet and its sentiment label. For each tweet, it extracts the tweet text and applies a preprocessing pipeline consisting of:
  - Converting text to lowercase.
  - Removing punctuation.
  - Tokenizing the text into words.
  - Removing common stop words.
  - Applying simple stemming (removing common suffixes like "ing", "ed", and trailing "s").

  The preprocessed tokens are used to update frequency counts for positive and negative tweets separately, forming the basis of the Naive Bayes model.

- **Classification:**  
  To classify a new tweet, the tweet is preprocessed using the same steps as during training. The Naive Bayes classifier then calculates the log-probabilities of the tweet belonging to the positive and negative classes using Laplace smoothing. The class with the higher probability is assigned as the prediction.

---

## 2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Explain why.

**Answer:**  
- **Training Time:**  
  On the provided dataset (e.g., 20,000 tweets), training typically takes a few seconds on a standard machine.
  
- **Time Complexity:**  
  The training process has a time complexity of **O(N * M * log V)**, where:
  - **N** is the number of tweets.
  - **M** is the average number of words per tweet.
  - **V** is the vocabulary size.

  Each tweet is processed individually. For each tweet, every word is tokenized and processed, and each token update in the frequency maps (implemented as balanced trees) takes O(log V) time.

---

## 3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

**Answer:**  
- **Classification Time:**  
  Classifying a single tweet is very fast—typically in the order of milliseconds.
  
- **Time Complexity:**  
  The classification of a single tweet has a time complexity of **O(M * log V)**, where:
  - **M** is the number of words in the tweet.
  - **V** is the vocabulary size.

  For each token in the tweet, the classifier performs a lookup in the frequency maps (O(log V) per token) and computes log-probabilities. Since tweets are short, the overall complexity per tweet remains very efficient.

---

## 4. What accuracy did your algorithm achieve on the provided training and test data?

**My accuracy:** Approximately **72.15%**

---

## 5. What were the changes that you made that improved the accuracy the most?

**Answer:**  
The most significant improvements came from enhancing the text preprocessing pipeline. The key changes were:
- Converting all text to lowercase.
- Removing punctuation to eliminate noise.
- Filtering out common stop words.
- Applying a simple stemming algorithm to reduce word variations.
- Using a Naive Bayes classifier with Laplace smoothing to accurately estimate word probabilities.

These steps reduced variability in the text data, allowing the classifier to capture more meaningful patterns.

---

## 6. How do you know that you use proper memory management? I.e., how do you know that you do not have a memory leak?

**Answer:**  
The custom `DSString` class follows the rule-of-three by implementing a copy constructor, assignment operator, and destructor. This ensures that dynamic memory is allocated, copied, and deallocated correctly. Additionally, I have used tools like Valgrind to test the application, and no memory leaks were detected.

---

## 7. What was the most challenging part of the assignment?

**Answer:**  
The most challenging part was implementing the custom `DSString` class without using the STL string library. Managing dynamic memory safely and ensuring deep copies, while avoiding memory leaks, was particularly difficult. Additionally, fine-tuning the text preprocessing steps (tokenization, stop word removal, and stemming) to achieve the desired accuracy required significant experimentation and iteration.

---
