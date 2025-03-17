#include <iostream>
#include "ladder.h"

int main() {
    set<string> words;
    load_words(words, "src/words.txt");
    string start, end;
    cout << "Enter start word: ";
    cin >> start;
    cout << "Enter end word: ";
    cin >> end;
    vector<string> ladder = generate_word_ladder(start, end, words);
    print_word_ladder(ladder);
    return 0;
}
