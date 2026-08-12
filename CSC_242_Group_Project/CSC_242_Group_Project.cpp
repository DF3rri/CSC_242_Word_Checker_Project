#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iterator>

// Function to convert a string to lowercase
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
        [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

// Function to check if a word is in the dictionary
bool contains(const std::vector<std::string>& words, const std::string& target) {
    // Since the vector is unsorted, linear search
    for (const auto& word : words) {
        if (word == target) {
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<std::string> words; // vector of strings called words

    // Open the dictionary file
    std::ifstream dictFile("exclusion.dic");
    if (!dictFile) {
        std::cerr << "Error opening dictionary file." << std::endl;
        return 1;
    }

    // For each word in the dictionary file, append to words vector
    std::string line;
    while (std::getline(dictFile, line)) {
        // Remove whitespace
        line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
        // Convert to lowercase
        words.push_back(toLower(line));
    }
    dictFile.close();

    // Open the file to be checked
    std::ifstream checkFile("Checker.txt");
    if (!checkFile) {
        std::cerr << "Error opening input file." << std::endl;
        return 1;
    }

    // Read entire content of the input file
    std::string content((std::istreambuf_iterator<char>(checkFile)), std::istreambuf_iterator<char>());
    checkFile.close();

    // Replace punctuation with spaces
    for (char& c : content) {
        if (ispunct(c)) {
            c = ' ';
        }
    }

    // Split into words
    std::istringstream iss(content);
    std::string word;
    while (iss >> word) {
        // Convert to lowercase
        std::string lowerWord = toLower(word);
        // If not contained in the dictionary, print it
        if (!contains(words, lowerWord)) {
            std::cout << word << std::endl;
        }
    }

    return 0;
}
