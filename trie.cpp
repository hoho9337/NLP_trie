#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Trie {
    bool is_word;
    Trie *children[55];
    Trie() : is_word(false) {
        memset(children, 0, sizeof(children));
    }
    ~Trie() {
        for (int i = 0; i < 55; i++) {
            if (children[i]) {
                delete children[i];
            }
        }
    }

    void insert(char *s) {
        if (*s == '\0') {
            is_word = true;
        }
        else {
            int index = *s - '&';
            if (children[index] == NULL) {
                children[index] = new Trie();
            }
            children[index]->insert(s + 1);
        }
    }
    Trie* find(const char* s) {
        if (*s == '\0') return this;
        int index = *s - '&';
        if (children[index] == NULL) return NULL;
        return children[index]->find(s + 1);
    }
};

int main() {
    Trie *root = new Trie();
    ifstream fin;
    string word;
    fin.open("words.txt");
    while (getline(fin, word)) {
        root->insert(&word[0]);
    }
    fin.close();

    string s;
    cin >> s;
    Trie* result = root->find(&s[0]);
    if (result == NULL) {
        cout << "False" << endl;
    }
    else {
        cout << "True" << endl;
    }
    delete root;
    return 0;
}