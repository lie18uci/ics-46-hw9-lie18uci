#include "ladder.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

void error(string word1, string word2, string msg) {
    cerr << "Error for these words'" << word1 << "' and '" << word2 << "': " << msg << endl;
}

bool is_adjacent(const string& word1, const string& word2) {
    if (word1.size() > word2.size() + 1 || word2.size() > word1.size() + 1)
        return false;
    if (word1.size() == word2.size()) {
        int diffCount = 0;
        for (size_t i = 0; i < word1.size(); i++) {
            if (word1[i] != word2[i]) {
                diffCount++;
                if (diffCount > 1) return false;
            }
        }
        return (diffCount == 1);
    } else {
    const string* shorter;
    const string* longer;
    if (word1.size() < word2.size()) {
        shorter = &word1;
        longer = &word2;
    } else {
        shorter = &word2;
        longer = &word1;
    }
    int i = 0, j = 0;
    int diffCount = 0;
    while (i < (int)shorter->size() && j < (int)longer->size()) {
        if ((*shorter)[i] == (*longer)[j]) {
            i++;
            j++;
        } else {
            diffCount++;
            if (diffCount > 1) return false;
            j++;
        }
    }
    if (j < (int)longer->size()) diffCount++;
    return (diffCount == 1);
    }
}

// idk what the point of this func is
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    return false;
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
            if (visited.find(d_word) == visited.end() &&
                is_adjacent(last_word, d_word)) 
            {
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
        cout << "No ladder found." << endl;
        return;
    }
    for (size_t i = 0; i < l.size(); i++) {
        cout << l[i];
        if (i + 1 < l.size()) {
            cout << " -> ";
        }
    }
    cout << endl;
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

