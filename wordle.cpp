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


void wordleHelper(
    size_t pos,
    string& current,
    const string& remainingFloating,
    const string& in,
    size_t blanksRemaining,
    const set<string>& dict,
    set<string>& results);


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> results;
    if (in.empty()) {
        return results;
    }

    size_t blanksRemaining = 0;
    for (size_t i = 0; i < in.length(); i++) {
        if (in[i] == '-') {
            blanksRemaining++;
        }
    }

    string current(in.length(), 'a');
    wordleHelper(0, current, floating, in, blanksRemaining, dict, results);
    return results;
}

void wordleHelper(
    size_t pos,
    string& current,
    const string& remainingFloating,
    const string& in,
    size_t blanksRemaining,
    const set<string>& dict,
    set<string>& results)
{
    if (remainingFloating.length() > blanksRemaining) {
        return;
    }

    if (pos == in.length()) {
        if (remainingFloating.empty() && dict.find(current) != dict.end()) {
            results.insert(current);
        }
        return;
    }

    if (in[pos] != '-') {
        current[pos] = in[pos];
        string nextFloating = remainingFloating;
        size_t idx = nextFloating.find(in[pos]);
        if (idx != string::npos) {
            nextFloating.erase(idx, 1);
        }
        wordleHelper(pos + 1, current, nextFloating, in, blanksRemaining, dict, results);
        return;
    }

    if (blanksRemaining == remainingFloating.length()) {
        for (size_t i = 0; i < remainingFloating.length(); i++) {
            char c = remainingFloating[i];
            current[pos] = c;
            string nextFloating = remainingFloating;
            nextFloating.erase(i, 1);
            wordleHelper(pos + 1, current, nextFloating, in, blanksRemaining - 1, dict, results);
        }
        return;
    }

    for (char c = 'a'; c <= 'z'; c++) {
        current[pos] = c;
        string nextFloating = remainingFloating;
        size_t idx = nextFloating.find(c);
        if (idx != string::npos) {
            nextFloating.erase(idx, 1);
        }
        if (nextFloating.length() <= blanksRemaining - 1) {
            wordleHelper(pos + 1, current, nextFloating, in, blanksRemaining - 1, dict, results);
        }
    }
}
