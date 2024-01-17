/*
 * sorter.h
 *
 * Declares a template function:
 *    
 *   sorter() : k-way merge sort.
 * 
 * 
 * You may add other functions if you wish, but this template function
 * is the only one that need to be exposed for the testing code.
 * 
 * Authors: C. Painter-Wakefield & Tolga Can
 */

#ifndef _SORTER_H
#define _SORTER_H

#include <string>
#include <cstddef>
#include <vector>

using namespace std;
`
template <class T>
void sorter(vector<T> &vec, int k) {  
	// write your solution for k-way merge sort below	
	//because the function is based in recursion, we need to establish a base case.
	if( vec.size() <=1) return;

	//this is the large vector that the smaller vectors will be stored within
	vector<vector<T>> big_vector;
	
	//now we go through k and add a vector (sublist) to big vector k times 
	for (int i = 0; i<k; i++){
		vector<T> new_vector;
		big_vector.push_back(new_vector);
	}
	//next step is to take values from the input vector into these smaller vectors within big_vector
	for(int i = 0; i<vec.size(); i++){
		big_vector.at(i % k).push_back(vec.at(i));
	}
	//next step is to merge sort these smaller vectors, now that the input vector is within them
	for(int i = 0; i<k; i++){
		sorter(big_vector.at(i), k);
	}

	//the challenge now is to merge these small sorted vectors together, which is where all the work really comes from
	//because it is less bookkeeping, we will try approach 2 initially
	for(int i = vec.size()-1; i>=0; i--){ //going backwards through the initial vector
		T max;
		bool first = true;
		int current_max_location;
		for(int j = 0; j<k; j++){ //and looking through each small vector to find their maxes
			if (big_vector.at(j).size() == 0){ //if we are currently looking at an empty vector, we skip this vector
				continue; //goes to next iteration of loop. We need to make sure vector isn't empty otherwise findMax will break
			}
			if(first){//if this is the first non-empty vector in big_vector, it's maximum will be the initial maximum.
				max = big_vector.at(j).back(); //the vectors should be sorted, so this should be the largest element of this vector
				current_max_location = j;
				first = false; //we are no longer setting the first
			}
			else{
				if(big_vector.at(j).back() > max){
					max = big_vector.at(j).back();
					current_max_location = j;
				}
			}
		}
		//at this point, the next largest element has been determined, so that needs to be reflected in vec
		vec.at(i) = big_vector.at(current_max_location).back();
		big_vector.at(current_max_location).pop_back();
	}
}
#endif
