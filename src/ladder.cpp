#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error for these words'" << word1 << "' and '" << word2 << "': " << msg << endl;
}

bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int ls = str1.size(), lt = str2.size();
    if (ls > lt + d || lt > ls + d)
        return false;
    if (ls == lt) {
        int diff = 0;
        for (int i = 0; i < ls; i++) {
            if (str1[i] != str2[i]) {
                diff++;
                if (diff > d) return false;
            }
        }
        return true;
    } else {
        const string& shorter = (ls < lt ? str1 : str2);
        const string& longer  = (ls < lt ? str2 : str1);
        int i = 0, j = 0;
        int diff = 0;
        while (i < shorter.size() && j < longer.size()) {
            if (shorter[i] == longer[j]) {
                i++;
                j++;
            } else {
                diff++;
                if (diff > d) 
                    return false;
                j++;
            }
        }
        if (j < longer.size()) diff++;
        return diff <= d;
    }
}

void load_words(set<string>& word_list, const string& file_name) {
    ifstream in(file_name);
    string word;
    while (in >> word) {
        word_list.insert(word);}
    in.close();
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (begin_word == end_word) {
        return vector<string>();
    }
    if (word_list.find(end_word) == word_list.end()) {
        return vector<string>();
    }
    queue<vector<string>> paths;
    paths.push({begin_word});
    set<string> visited;
    visited.insert(begin_word);
    while (!paths.empty()) {
        vector<string> path = paths.front();
        paths.pop();
        string last_word = path.back();
        for (auto& d_word : word_list) {
            if (d_word.size() > last_word.size() + 1 || last_word.size() > d_word.size() + 1)
                continue;
            if (visited.find(d_word) == visited.end() && is_adjacent(last_word, d_word)) {
                vector<string> newPath = path;
                newPath.push_back(d_word);
                visited.insert(d_word);
                if (d_word == end_word) {
                    return newPath;
                }
                paths.push(newPath);
            }
        }
    }
    return {};
}

void print_word_ladder(const vector<string>& l) {
    if (l.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (size_t i = 0; i < l.size(); i++) {
        cout << l[i];
        if (i + 1 < l.size()) {
            cout << " ";
        }
    }
    cout << "\n";
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);

}

