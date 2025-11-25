// WordCount.cpp

#include "WordCount.h"
#include <sstream>     
#include <locale>

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int total = 0;
	for (size_t i = 0; i < CAPACITY; i++) {
		for (size_t j = 0; j < table[i].size(); j++) {
			total += table[i][j].second;
		}
	}
	return total;
}

int WordCount::getNumUniqueWords() const {
	int unique = 0;
	for (size_t i = 0; i < CAPACITY; i++) {
		unique += table[i].size();
	}
	return unique;
}

int WordCount::getWordCount(std::string word) const {
	std::string validWord = makeValidWord(word);
	if (validWord.empty()) {
		return 0;
	}
	
	size_t index = hash(validWord);
	const std::vector<std::pair<std::string, int> >& bucket = table[index];
	
	for (size_t i = 0; i < bucket.size(); i++) {
		if (bucket[i].first == validWord) {
			return bucket[i].second;
		}
	}
	
	return 0;
}
	
int WordCount::incrWordCount(std::string word) {
	std::string validWord = makeValidWord(word);
	if (validWord.empty()) {
		return 0;
	}
	
	size_t index = hash(validWord);
	std::vector<std::pair<std::string, int> >& bucket = table[index];
	
	for (size_t i = 0; i < bucket.size(); i++) {
		if (bucket[i].first == validWord) {
			bucket[i].second++;
			return bucket[i].second;
		}
	}

	bucket.push_back(std::make_pair(validWord, 1));
	return 1;
}

int WordCount::decrWordCount(std::string word) {
	std::string validWord = makeValidWord(word);
	if (validWord.empty()) {
		return -1;
	}
	
	size_t index = hash(validWord);
	std::vector<std::pair<std::string, int> >& bucket = table[index];
	
	for (size_t i = 0; i < bucket.size(); i++) {
		if (bucket[i].first == validWord) {
			if (bucket[i].second > 1) {
				bucket[i].second--;
				return bucket[i].second;
			} else {
				bucket.erase(bucket.begin() + i);
				return 0;
			}
		}
	}
	
	return -1;
}

bool WordCount::isWordChar(char c) {
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}


std::string WordCount::makeValidWord(std::string word) {
	size_t first = word.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (first == std::string::npos) {
        return "";
    }
    size_t last = word.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
    if (last == std::string::npos) {
        return ""; 
    }
    
    string trimmed = word.substr(first, (last - first) + 1);

    string validWord = "";
    for (size_t i = 0; i < trimmed.length(); ++i) {
        char c = trimmed[i];
        
        if (isWordChar(c)) {
            
            validWord += std::tolower(c, std::locale());
        } else if (c == '-' || c == '\'') {
            if (i > 0 && i < trimmed.length() - 1) {
                if (!validWord.empty() && isWordChar(trimmed[i + 1])) {
                    validWord += c;
                }
            }
        }
    }
    
    while (!validWord.empty() && (validWord.back() == '-' || validWord.back() == '\'')) {
        validWord.pop_back();
    }
    
    return validWord;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
    std::vector<std::pair<std::string, int>> allWords;
    for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto& pair : table[i]) {
            allWords.push_back(pair);
        }
    }

    std::sort(allWords.begin(), allWords.end(), 
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.first > b.first;
        });

    for (const auto& pair : allWords) {
        out << pair.first << "," << pair.second << "\n";
    }
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
    std::vector<std::pair<std::string, int>> allWords;
    for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto& pair : table[i]) {
            allWords.push_back(pair);
        }
    }

    std::sort(allWords.begin(), allWords.end(), 
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            
            if (a.second != b.second) {
                return a.second < b.second;
            }
           
            return a.first < b.first;
        });

   
    for (const auto& pair : allWords) {
        out << pair.first << "," << pair.second << "\n";
    }
}

void WordCount::addAllWords(std::string text) {
    
    std::stringstream ss(text);
    std::string word;

    while (ss >> word) {
        
        incrWordCount(word);
    }
}