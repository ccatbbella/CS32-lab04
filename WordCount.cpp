#include "WordCount.h"
#include <algorithm>
#include <map>
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
  for(size_t arrIndex = 0; arrIndex < CAPACITY; arrIndex++){
    for(size_t vectorIndex = 0; vectorIndex < table[arrIndex].size(); vectorIndex++){
      total += table[arrIndex][vectorIndex].second;
    }
  }
  return total;
}

int WordCount::getNumUniqueWords() const {
  int numUnique = 0;
  for(size_t arrIndex = 0; arrIndex < CAPACITY; arrIndex++){
    for(size_t vectorIndex = 0; vectorIndex < table[arrIndex].size(); vectorIndex++){
	    numUnique++;
    }
  }
  return numUnique;
}

int WordCount::getWordCount(std::string word) const {
	std::string strippedWord = stripWord(word);
  for(size_t i = 0; i < strippedWord.length(); i++)
   strippedWord[i]= toupper(strippedWord[i]);
  size_t arrIndex = hash(strippedWord);
  for(size_t vectorIndex = 0; vectorIndex < table[arrIndex].size(); vectorIndex++){
    if(table[arrIndex][vectorIndex].first == strippedWord)
      return table[arrIndex][vectorIndex].second;
  }
  return 0;
}
	

int WordCount::incrWordCount(std::string word) {
  std::string strippedWord = stripWord(word);
  for(size_t i = 0; i < strippedWord.length(); i++)
    strippedWord[i]= toupper(strippedWord[i]);
  
  if(strippedWord == "") return 0;             //word strip to empty string
  
  size_t arrIndex = hash(strippedWord);
  if(getWordCount(strippedWord) == 0){         //the upperWord not in table
    std::pair<std::string, size_t> newWord(strippedWord, 1);
    table[arrIndex].push_back(newWord);
    return 1;
  }
  for(size_t vectorIndex = 0; vectorIndex < table[arrIndex].size(); vectorIndex++){
    if(table[arrIndex][vectorIndex].first == strippedWord){
      table[arrIndex][vectorIndex].second++;
      return static_cast<int>(table[arrIndex][vectorIndex].second);
    }
  }
}


bool WordCount::isWordChar(char c) {
	if( (c >= 65 && c <= 90) || (c >= 97 && c <= 122) )
    return true;
  else
    return false;
}


std::string WordCount::stripWord(std::string word) {
  std::string::iterator pFront = word.begin();
  while(!isWordChar(*pFront) && word.length() > 0){      //erase every thing in front of first alpha char
    word.erase(pFront);//after erase, an iterator is returned that point to the updated first character of the updated string, so no pFront++ is needed here
  }
  
  if(pFront == word.end())      //This is for when word strip to empty!!! without these two lines of code you get scary seg fault!!!
    return "";
    
  std::string::iterator pBack = word.begin() + (word.length() - 1);
  while(!isWordChar(*pBack) && pBack != word.begin()){     //erase every thing behind the last  alpha char
    word.erase(pBack);
    pBack--; //this pBack-- has to be here because if erase is called on last character of the string, it doesn't return an iterator to the updated last character, it returns an iterator that dereferenced to empty string!!!
  }
  for(std::string::iterator p = word.begin(); p != word.end(); p++){
    if(!(isWordChar(*p) || *p == 45 || *p == 39))
      word.erase(p--);            //the p-- code is important for makeing sure that no character get skipped after a character is erased!!!
  }
  return word;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	// method 1
   //copy every unique word without their occurrance in the table into some linear container and sort the temporary container based on ASCII code of the first character
   //iterate through the container, find the element in hash table according to word, then write the element out in certain format
 //method 2
   //(put everything into a stack)
   //write getNexTBiggestOccurance function which return a pair
   //every iteration, call the above function and write the result to out
     
 //a wild thought about how to sort a hashtable
 //it is already subvector of array, can I do a merge sort?
 
 
 
 
  if(getTotalWords() == 0) return;  //empty table return nothing
  map<string,size_t> mapOfWordCount;
  for(size_t arrIndex = 0; arrIndex < CAPACITY; arrIndex++){
    for(size_t vectorIndex = 0; vectorIndex < table[arrIndex].size(); vectorIndex++){
      mapOfWordCount.insert(table[arrIndex][vectorIndex]);
    }
  }
  for(map<string,size_t>::iterator p = mapOfWordCount.begin(); p != mapOfWordCount.end(); p++){
    out << p -> first << ',' << p -> second << '\n';
  }
  
  
  
	return;
}




  bool customCompare(pair<string,size_t> p1, pair<string,size_t> p2){
    if(p1.second != p2.second)
      return p1.second > p2.second;  //pay attention to this code if(p1.second > p2.second) return true is WRONG!!!
      
    if(p1.second == p2.second){
      return p1.first < p2.first;
      
    }
    
  }



void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	// method 1
   //copy every unique word with their occurrance in the table into some linear container and sort the temporary container
   //iterate through the container and write each element to out in certain format
 //method 2
   //(put everything into a stack)
   //write getNexTBiggestOccurance function which return a pair
   //every iteration, call the above function and write the result to out
   
   if(getTotalWords() == 0) return;
 
   vector<pair<string,size_t>> v;
   for(size_t arrIndex = 0; arrIndex < CAPACITY; arrIndex++){
     for(size_t vectorIndex = 0; vectorIndex < table[arrIndex].size(); vectorIndex++){
       v.push_back(table[arrIndex][vectorIndex]);
     }
   }
   sort(v.begin(), v.end(), customCompare);
   for(auto item : v){
     out << item.first << ',' << item.second << '\n';
   }
   
   return;
}

void WordCount::addAllWords(std::string text) {
  vector<string> tokens;

	// split string into tokens using multiple occurrance of space or newline
  while(text.length() > 0){
 
    string::iterator pFront = text.begin();

    while(!isWordChar(*pFront) && text.length() > 0){    //erase every thing in front of first alpha char
      text.erase(pFront);
    }
    if(pFront == text.end())      //This is for when word strip to empty!!! without these two lines of code you get scary seg fault!!!
      break;
    
    size_t index1 = text.find(' ');
    size_t index2 = text.find('\n');
    size_t index;
    if(index1 < index2) index = index1;
    else index = index2;
    
    tokens.push_back(text.substr(0,index));
    text.erase(0,index);
  }
    
  //add each word to the hash table
  for(size_t i = 0; i < tokens.size(); i++)
    incrWordCount(tokens[i]);
 
	return;
}

