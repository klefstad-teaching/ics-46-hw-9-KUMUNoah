#include "ladder.h"

int main() {
    set<string> word_list;
    load_words(word_list, "words.txt");
    string start_word, end_word;
    cout << "Enter Starting Word" << endl;
    cin >> start_word;
    cout << "Enter End Word" << endl;
    cin >> end_word;
    vector<string> ladder = generate_word_ladder(start_word, end_word, word_list);
    print_word_ladder(ladder);
    verify_word_ladder();
    return 0;
}