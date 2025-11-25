#include "WordCount.h"
#include "tddFuncs.h"
#include <iostream>
#include <sstream>

using namespace std;

WordCount setupWordCount() {
    WordCount wc;
    string text = "The dog, a good-natured friend, chased the Cat. The dog likes milk.";
    wc.addAllWords(text);
    return wc;
}


void testMakeValidWord() {
    cout << "--- Testing makeValidWord ---\n";
    ASSERT_EQUALS("can't", WordCount::makeValidWord("can't"));
    ASSERT_EQUALS("good-hearted", WordCount::makeValidWord("good-hearted"));
    ASSERT_EQUALS("monkeys", WordCount::makeValidWord("12mOnkEYs-$"));
    ASSERT_EQUALS("paive", WordCount::makeValidWord("Pa55ive"));
    ASSERT_EQUALS("money", WordCount::makeValidWord("$money!"));
    ASSERT_EQUALS("c", WordCount::makeValidWord("C++"));
    ASSERT_EQUALS("word", WordCount::makeValidWord("$1wo,rd-%#"));
    ASSERT_EQUALS("nuff-said", WordCount::makeValidWord("'nuff-said-"));
   
    ASSERT_EQUALS("", WordCount::makeValidWord("123"));
    ASSERT_EQUALS("", WordCount::makeValidWord("---"));
    ASSERT_EQUALS("a", WordCount::makeValidWord("a'")); // Should strip trailing apostrophe
    ASSERT_EQUALS("b", WordCount::makeValidWord("-b")); // Should strip leading hyphen
    ASSERT_EQUALS("test", WordCount::makeValidWord("t'e-s-t.")); // Complex inner symbols
}


void testBasicCounters() {
    cout << "\n--- Testing Basic Counters (Lab 06) ---\n";
    WordCount wc = setupWordCount();
    
    ASSERT_EQUALS(9, wc.getNumUniqueWords());
  
    ASSERT_EQUALS(11, wc.getTotalWords()); 

    ASSERT_EQUALS(3, wc.getWordCount("the"));
    ASSERT_EQUALS(2, wc.getWordCount("dog"));
    ASSERT_EQUALS(1, wc.getWordCount("cat"));
    ASSERT_EQUALS(0, wc.getWordCount("notfound"));
}


void testAddAllWords() {
    cout << "\n--- Testing addAllWords ---\n";
    WordCount wc;
   
    string text = "This is\n a multi-line\t test.";
    wc.addAllWords(text);
    
    ASSERT_EQUALS(5, wc.getNumUniqueWords());
    ASSERT_EQUALS(5, wc.getTotalWords());
    ASSERT_EQUALS(1, wc.getWordCount("this"));
    ASSERT_EQUALS(1, wc.getWordCount("multi-line"));
}


void testDumpWordsSortedByWord() {
    cout << "\n--- Testing dumpWordsSortedByWord ---\n";
    WordCount wc = setupWordCount();
    std::stringstream ss;

   
    wc.dumpWordsSortedByWord(ss);

    const char* expected = 
        "the,3\n"
        "milk,1\n"
        "likes,1\n"
        "good-natured,1\n"
        "friend,1\n"
        "dog,2\n"
        "chased,1\n"
        "cat,1\n"
        "a,1\n";

    ASSERT_EQUALS(expected, ss.str());
}


void testDumpWordsSortedByOccurence() {
    cout << "\n--- Testing dumpWordsSortedByOccurence ---\n";
    WordCount wc;
    wc.incrWordCount("apple");
    wc.incrWordCount("orange");
    wc.incrWordCount("banana");
    wc.incrWordCount("pear");
    wc.incrWordCount("orange");
    wc.incrWordCount("banana");

    std::stringstream ss;
    wc.dumpWordsSortedByOccurence(ss);

    const char* expected = 
        "apple,1\n"
        "pear,1\n"
        "banana,2\n"
        "orange,2\n";

    ASSERT_EQUALS(expected, ss.str());
}


int main() {
    testMakeValidWord();
    testBasicCounters();
    testAddAllWords();
    testDumpWordsSortedByWord();
    testDumpWordsSortedByOccurence();
    
    return 0;
}