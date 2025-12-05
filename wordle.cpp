#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void recurse(std::string& current, size_t position, int floatCount[26], const std::string& pattern, const std::set<string>& dict, set<string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here

    // Create set results
    std::set<std::string> results;

    // Initialize current to in
    std::string current = in;

    int floatCount[26] = {0};
    for(char c : floating){
        floatCount[c-'a']++;
    }


    // Recurse
    recurse(current, 0, floatCount, in, dict, results);

    return results;

}

// Recurse function
void recurse(std::string& current, size_t position, int floatCount[26], const std::string& pattern, const std::set<string>& dict, set<string>& results){
    // Base case
    if(position == current.length()){

        // Check if count is 0 and all floating letters are used
        bool isUsed = true;
        for(int i=0; i<26; i++){
            if(floatCount[i] > 0){
                isUsed = false;
                break;
            }
        }

        // Check if there are floating letters and if word exists in dictionary
        if(isUsed && dict.find(current) != dict.end()){
            results.insert(current);
        }
        return;
    }

    // Check if letter is fixed and recurse
    if(pattern[position] != '-'){
        char fixedChar = pattern[position];
        current[position] = fixedChar;

        recurse(current, position+1, floatCount, pattern, dict, results);
        
        return;
    }

    // Test out all letters for the dash
    for(int i=0; i<26; i++){
        if(floatCount[i]>0){
            current[position] = 'a' + i;
            floatCount[i]--;
            recurse(current, position+1, floatCount, pattern, dict, results);
            floatCount[i]++;
            current[position] = '-';
        }
    }

    // Determine the number of floating letters needed to be put into a spot
    int floatingRemaining = 0;
    for(int i=0; i<26; i++){
        floatingRemaining += floatCount[i];
    }

    // Check if there are enough positons for the number of floating letters left and test letters
    if(floatingRemaining <= static_cast<int>(current.length()-position)-1){
        for(char c='a'; c<='z'; c++){
            if(floatCount[c-'a'] == 0){
                current[position] = c;
                recurse(current, position+1, floatCount, pattern, dict, results);
                current[position] = '-';
            }
        }
    }

}


// Define any helper functions here