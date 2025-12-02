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
void recurse(std::string& current, size_t position, string floating, const string& in, const std::set<string>& dict, set<string>& results);

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
    // Recurse
    recurse(current, 0, floating, in, dict, results);

    return results;

}

// Recurse function
void recurse(std::string& current, size_t position, string floating, const string& in, const std::set<string>& dict, set<string>& results){
    // Base case
    if(position == current.length()){
        // Check if there are floating letters and if word exists in dictionary
        if(floating.empty() && dict.find(current) != dict.end()){
            results.insert(current);
        }
        return;
    }

    // Check if letter is fixed and recurse
    if(in[position] != '-'){
        // Insert the set letter to current
        current[position] = in[position];
        recurse(current, position+1, floating, in, dict, results);
        return;
    }

    // Update the positions left based on word length and positions filled
    size_t positionsRemaining = current.length() - position - 1;

    // Loop through the floating letters
    for(size_t i=0; i < floating.length(); i++){
        // Check for remaining position space
        if(floating.length() - 1 <= positionsRemaining){
            current[position] = floating[i];

            // Remove floating[i] from floating and store in a new string
            std::string newFloating = floating.substr(0, i) + floating.substr(i+1);

            // Recurse
            recurse(current, position + 1, newFloating, in, dict, results);
        }
    }

    // Substitute in other letters and see if they make valid words
    if(positionsRemaining >= floating.length()){
        for(char c = 'a'; c <= 'z'; c++){
            // Check if this letter is not in floating
            bool inFloating = false;
            // Loop through and compare each letter with floating
            for(char d : floating){
                if(d == c){
                    inFloating = true;
                    break;
                }
            }
            if(!inFloating){
                current[position] = c;
                // Recurse
                recurse(current, position + 1, floating, in, dict, results);
            }
        }
    }
}


// Define any helper functions here