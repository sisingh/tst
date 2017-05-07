//
//  main.cpp
//  TernaraySearchTree
//
//  Created by Siddhartha Singh on 04/05/17.
//  Copyright © 2017 Siddhartha Singh. All rights reserved.
//

#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;
using std::tolower;
using std::string;

typedef struct TST {
    char c;
    TST *left;
    TST *mid;
    TST *right;
    bool isWord;
    TST() : isWord(false), left(nullptr), right(nullptr), mid(nullptr) {}
} TST;

TST * insert (TST * head, const char * word) {
    if (head == nullptr) {
        if (word && *word) {
            head = new TST();
            head->c = *word;
            head->mid = insert(head->mid, ++word);
            if (head->mid == nullptr) {
                head->isWord = true;
            }
        }
    } else if (tolower(*word) == tolower(head->c)) {
        head->mid = insert(head->mid, ++word);
    } else if (tolower(*word) < tolower(head->c)) {
        head->left = insert(head->left, word);
    } else {
        head->right = insert(head->right, word);
    }
    return head;
}

/* <TODO> Take outstream as parameter to print to any device */

void sortedOut(TST * head, const char * prefix) {
    static string s;
    if (head != nullptr) {
        sortedOut(head->left, prefix);
        s += head->c;
        if (head->isWord) {
            cout << ((prefix) ? prefix : (char*)("") ) << " " <<  s << endl;
        }
        sortedOut(head->mid, prefix);
        s.pop_back();
        sortedOut(head->right, prefix);
    }
}

/* TODO with prefix */
TST * getHeadForPrefix (TST * head, const char * prefix) {
    if (prefix && *prefix) {
        if (tolower(*prefix) < tolower(head->c)) {
            head->left = getHeadForPrefix(head->left, prefix);
        } else if (tolower(*prefix) > tolower(head->c)) {
            head->right = getHeadForPrefix(head->right, prefix);
        } else {
            head->mid = getHeadForPrefix(head->mid, ++prefix);
        }
    }
    return head;
}

TST * sortedOutWithPrefix(TST * head, const char * prefix) {
    TST * temp = getHeadForPrefix(head, prefix);
    if (temp != nullptr) {
        sortedOut(temp->mid, prefix);
    }
    return temp;
}

/* TODO with wild card */

int main(int argc, const char * argv[], const char ** arge) try {
    cout << "Hello, World!\n";
    TST * head = nullptr;
    head = insert(head, (char*)(""));
    head = insert(head, (char*)("how"));
    head = insert(head, (char*)("Hello"));
    head = insert(head, (char*)("Sid"));
    head = insert(head, (char*)("Hem"));
    sortedOut(head, nullptr);
    string prefix("H");
    cout << endl << "Search with a prefix '" << prefix << "' now " << endl << endl;
    sortedOutWithPrefix(head, "H");
    return 0;
    } catch(...) {
        cerr << "Uncaught exception..." << endl;
        return 1;
    }
