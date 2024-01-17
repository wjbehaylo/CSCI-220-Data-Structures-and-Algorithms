/*
 * trie.cpp
 *
 * Method definitions for the trie class.
 *
 * Author: <your name here>
 */

#include "trie.h"

void trie::insert(const string&s){
    //if the string is present, do nothing
    //otherwise, we need to go through each letter of the string in order
    //we are inserting starting at the root
    trie_node* current = root;
    for(auto letter: s){
        //we then need to access the child corresponding to the letter of the current trie_node
        int child = int(letter)-97;
        //if the child is still a nullptr, we need to make a new trie_node at that child's index in children
        if(current->children[child] == nullptr) current->children[child] = new trie_node;
        //now we make the current node we're at be the child corresponding to the edge from the letter
        current = current->children[child];
    }
    //at this point we have gone through all the letters and gotten to the last, so we will now say that that child is a stopping point for a string
    current->stopping_point = true;
}

bool trie::contains(const string&s){
    trie_node* current = root;
    for(auto letter: s){
        int child = int(letter) - 97;
        if(current->children[child] == nullptr) return false; //if the node isn't there yet, then that prefix is not in the trie
        current = current->children[child];
    }
    return current->stopping_point; //if this is false, then the node is not a stopping point which means we don't have a string ending there, if true, the opposite
}

bool trie::is_prefix(const string& s){
    trie_node* current = root;
    for(auto letter: s){
        int child = int(letter) -97;
        if(current->children[child] == nullptr) return false;
        current = current->children[child];
    }
    //if we have gotten to this point without running into a nullptr, that means that some word at some point has the current path as a prefix
    return true;
}

void trie::extend(const string& prefix, vector<string> &result){
    if(!is_prefix(prefix)) return; //if it isn't a prefix, then its over

    //the plan is to get down to the node where the prefix ends, and then recursively (or if possible iteratively?) print all stopping-point trie nodes after that
    trie_node* current = root;
    for(auto letter: prefix){
        int child = int(letter) - 97;
        current = current->children[child];
    }
    prefix_children(prefix, current, result);
}

//this is going to be a helper function that returns a vector of all suffixes with the included prefix.
void trie::prefix_children(const string& prefix, trie_node* start, vector<string>& result){
    if(start->stopping_point) result.push_back(prefix); //if the beginning is terminal , add it to the vector of suffixes
    trie_node* child;
    //now for each child, will try and add to the prefix that child if it exists, and 
    for(int i = 0; i<26; i++){
        child = start->children[i]; //child will be the first of children
        if(child != nullptr){ //if the child isn't a nullptr, we want all the suffixes of it to be added to a different suffix string
            string new_prefix = prefix + char(i + 97); 
            prefix_children(new_prefix, child, result); //now we will get all the children of that, added into suffixes
        }
    }
}


