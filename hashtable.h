/*
 * hashtable.h
 *
 * A basic hashtable implementation.
 * 
 * Author: <your name here>
 */

#ifndef _HASHTABLE_PROJECT_H
#define _HASHTABLE_PROJECT_H

#include <functional>   // for std::hash
#include <vector>
using namespace std;

template <class T, class H = std::hash<T>>
class hashtable {
public:
    // constructor
    hashtable(){
        table = vector<vector<T>>(4);
        num_elements = 0;
    }

    // basic hashset operations
    void insert(const T& key){
        if(contains(key)) return; //checks if key is in table already

        //now we need to check if adding it would cause the load factor to surpass 0.75
        num_elements ++;
        if(load_factor() > 0.75){
            //double table size by creating a new table of double the size, then rehashing current table values
            vector<vector<T>> new_table(size()*2);
            
            // now we will go through each chain in the table, and each element in the chain, and hash them into the new table
            for (const auto& chain : table){
                for (const auto& element : chain){
                    int element_location = hash(element)%(new_table.size()); //we need to get the new hash for each element, 
                    new_table.at(element_location).push_back(element); //and then put them into the new table
                }
            }
            //finally, we make the old table a copy of the new table
            table = new_table;
        }
        //the above copying only occurs if the load factor restriction would be violated, and ends with setting table to be new_table, so the below function should execute regardless of load factor satisfaction
        
        int location = hash(key)%table.size();
        table.at(location).push_back(key);
    }

    void remove(const T& key){
        if(!contains(key)) return; //if the key is not in the table, nothing happens
        else{
            num_elements--; //we are removing an element, so we need to decrease the number of elements
            //otherwise, we need to find where the element would be, and remove it from it's former location
            int location = hash(key)%table.size();
            if(table.at(location).size() == 1){ //if that chain only has one element in it, it must be our element, so we just remove the only item in the chain
                table.at(location).pop_back();
                return;
            }
            else{ //the table must have at least two elements in it, so we will find the index of our element, swap it with the element at the last index, and remove the last index
                int chain_size = table.at(location).size();
                for(int i = 0; i<chain_size; i++){
                    if(table.at(location).at(i) == key){ //if the element we are looking at is the one we're looking for, we will remove it
                        //if it is the last element, we can just remove the last element
                        if(i == chain_size -1) table.at(location).pop_back();
                        
                        else{ //we will put the last element into the location of our key, then remove the last element, essentially removing our key
                             table.at(location).at(i) = table.at(location).at(chain_size-1);
                             table.at(location).pop_back(); //we have now removed the key from the chain at the location of the key's hash 
                        }
                        return;
                    }

                }
            }
        }
    }

    bool contains(const T& key){
        int location = hash(key)%table.size();
        if(table.at(location).size() == 0) return false; //if the vector at that key is empty, then the key is not in the table
        else{
            for(const auto& element : table.at(location)){ //for each element in the chain, we check if it is our key
                if(element == key) return true;
            }
            return false;

        }
    }

    size_t size(){
        return num_elements;
    }

    // diagnostic functions
    double load_factor(){
        double loadFactor = ((num_elements*1.0)/table.size());
        return loadFactor;
    }

    // convenience method, invokes the "hash" template parameter
    // function object to get a hash code
    static size_t hash(const T &key) {
        H h;
        return h(key);
    }

private:
    vector<vector<T>> table;
    size_t num_elements;
};

#endif
