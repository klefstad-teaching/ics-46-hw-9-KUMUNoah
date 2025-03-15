#include "ladder.h"

void error(string word1, string word2, string msg) {
    cout << word1 << word2 << msg << endl;
}
bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int size1 = str1.size();
    int size2 = str2.size();
    if (abs(size1 - size2) > d) return false;
    int i = 0, j = 0, edits = 0;
    while (i < size1 && j < size2) {
        if (str1[i] != str2[j]) {
            if (++edits > d) return false;
            if (size1 > size2) i++;
            else if (size1 < size2) j++;
            else { i++; j++; }
        } else {
            i++;
            j++;
        }
    }
    
    return edits + (size1 - i) + (size2 - j) <= d; // Account for remaining chars
}
bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}
vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    queue<vector<string>> ladder_queue;
    vector<string> begin_list;
    begin_list.push_back(begin_word);
    ladder_queue.push(begin_list);
    map<string, string> wordMap;
    set<string> visited;
    visited.insert(begin_word);
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder[ladder.size() - 1];
        for (string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (!(visited.find(word) != visited.end())) {
                    visited.insert(word);
                    vector<string> new_ladder = std::move(ladder);
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    } else {
                        ladder_queue.push(new_ladder);
                    }
                }
            }
        }
    }
    error(begin_word, end_word, "No word ladder found");
    vector<string> empty;
    return empty;
}
void load_words(set<string> & word_list, const string& file_name) {
    ifstream infile(file_name);
    string line;
    while (getline(infile, line)) {
        word_list.insert(line);
    }
}
void print_word_ladder(const vector<string>& ladder) {
    if (ladder.empty()) {
        cout << "No word ladder found." << endl;
        return;
    }
    cout << "Word ladder found: ";
    for (string s : ladder) {
        cout << s << " ";
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