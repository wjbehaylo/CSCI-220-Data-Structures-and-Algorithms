/*
 * trie.h
 *
 * Declaration of the trie class.
 * 
 * Author: <your name here>
 */

#ifndef _TRIE_H
#define _TRIE_H

#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class trie {
public:
    void insert(const string &s);
    bool contains(const string &s);
    bool is_prefix(const string &s);
    void extend(const string &prefix, vector<string> &result);
    trie(){root = new trie_node;}
    ~trie(){
        delete root;
    }
private:
    //this is, to be fair, only used in local functions (extend)
    
    class trie_node{
        public:
        trie_node(){
            stopping_point = false;
            children = new trie_node*[26];
            for (int i = 0; i<26; i++){
                children[i] = nullptr;
            }
        }
        ~trie_node(){
            for (int i = 0; i<26; i++){
                delete children[i];
            }
        }

        bool stopping_point;
        trie_node** children; //children will be a pointer to a dynamically allocated array of trie_node pointers
    };
    void prefix_children(const string& prefix, trie_node* start, vector<string>& result);
    trie_node* root;
};


#endif
