// Jacob Port 
// CPS 222
// HW Part 2 

#include "bdc.h"
#include<iostream> 
#include<sstream> 
#include<vector> 
#include<cassert> 
#include<algorithm>

using namespace std; 


/*
-------------------------------------Explanation----------------------------------------

I start by sorting the input in ascending order and creating a vector of venter<int>s (called DP) to store my dynamic results. 

I then deal with the base case––in tthis case the smallest number, so input[0]–––and push back a vector with just the smallest element in it. 

Then, the code moves to the next smallest vector, and detirmines if any of the element of the list that are smaller than it are also divisors of
the element. If so, it will save the element(s), check DP to see which one has the largest conglomerate (because they are smaller, they will already have
been calculated), and combined the current element with the DP[index] such that the length of the sum is greatest. 

The code then repeats this process until the largest int is reached. (Example Below)

-----------------------------------Time Complexity-x-------------------------------------
The time complexity of this Dynamic Approach is O(n) at worst, because it will only need to do max one calculation for each 
element in the list. It will never have to do repeat calculations. 

In the previous recursive problem, the time complexity would be O(2^n), because each recursive call would output two more recursive calls
which would do computations that have already been computed, which at worst, will go for the entire length fo the list which is size n. 

--------------------------------------Example: -----------------------------------------

[28, 22, 7, 2, 8, 14, 24, 56] -> [2, 7, 8, 14, 22, 24, 28, 56]

2 is base case: DP becomes 
   DP =  { {2} }

Move on to 7: (seven has no lower divisors): 
   DP =  { {2}, {7} }

Move onto 8: 
   DP = { {2}, {7}, {8, 2} }

Move onto 14. 7 Divides 14, code will reference index 2 which calculate conglomerate of 7: 
    DP = { {2}, {7}, {8, 2}, {14,7} }

Move onto 22: 
    DP = { {2}, {7}, {8, 2}, {14,7}, {22, 2} }

Move onto 24: 
    DP = { {2}, {7}, {8, 2}, {14,7}, {22, 2}, {24, 8, 2} }

Move onto 28 (24 will reference the conglomerate from 14 at index 3 ): 

    DP = { {2}, {7}, {8, 2}, {14,7}, {22, 2}, {24, 8, 2}, {28,14,7},  }
            0    1    2     3         4        5           6

Move onto 56––code will reference 28 at DP[6]: 

    DP = { {2}, {7}, {8, 2}, {14,7}, {22, 2}, {24, 8, 2}, {28,14,7},  {56, 28, 14, 7]} }
            0    1      2       3       4        5           6               7

*/

vector<int> combine(vector<int> left, vector<int> right){
    vector<int> combined; 

    for(int i = 0; i < left.size(); i++){
        combined.push_back(left[i]);
    }
    for(int i = 0; i < right.size(); i++){
        combined.push_back(right[i]);
    }
    return combined;
};

string vec_to_string(vector<int> v){
    //if vector is empty output []
    if(v.size() == 0){
        return "[ ]";
    }

    ostringstream oSS;
    oSS << "["; //start output here 

    //iterates throug the vector an outputs the element with a comma and space 
    for(int i = 0; i < v.size(); i++){
        if(i < v.size()-1){
            oSS << v.at(i) << ", ";
        }else{
            oSS << v.at(i) << "]"; //end output here 
        }
    }
    return oSS.str(); //return the to string version of oSS
};

vector<int> biggest_divisible_conglomerate(vector<int> input){

    //sort input in ascending order 
    sort(input.begin(),input.end()); 

    vector<vector<int>> DP; //creates the table that will be used for dynamic programming 

    //I'm using the smallest element as the base case, because it can never have a conglomerate thats smaller than itself 
    vector<int> baseCase = {input[0]};
    DP.push_back(baseCase);

    //iterates through the input, ignoring the base case 
    for(size_t i = 1; i < input.size(); i++){

        vector<int> divisorsIndexes; //I will store the indexes of divisors in here 
        for(size_t j = 0; j < i; j++){ //may get issues here, check here first for debugging 
            if(input[i] % input[j] == 0){
                divisorsIndexes.push_back(j);
            }
        }
        //if there are no divisors, I will just push back the single vector: 
        int vecSize; //initalizes these two vars here so that I can acess them outside the scope later on...
        int idx; 

        if(divisorsIndexes.size() == 0){
            vector<int> temp = {input[i]}; 
            DP.push_back(temp); 
        }else{
            //Here I will iterate through the list of divisors, and test which one is the longest, then use that to create the larger conglomerate 
             vecSize = 1; //sets to smallest possivle
             idx = divisorsIndexes.at(0);  //arbitrary

            for(size_t index : divisorsIndexes){

                if(DP[index].size() > vecSize){
                vecSize = DP[index].size(); 
                idx = index;
                }
            }    
            vector<int> left = {input[i]};
            vector<int> combined = combine(left,DP[idx]);
            DP.push_back(combined);
        }
    }

    //find the largest conglomerate in DP: -------------------

    int currVecSize = 0;
    int currIndex = 0;
    for(int i = 0; i < DP.size(); i++){
        if(DP[i].size() > currVecSize){
            currVecSize = DP[i].size();
            currIndex = i;
        }
    }
    //returns smallest or emtpy list if the vector is 1 or 0
    if(currVecSize == 0){
        vector<int> emptyVec = {};
        return emptyVec;
    }
    if(currVecSize == 1){
        vector<int> smallest = {input[0]};
        return smallest;
    }

    //otherwise, returns the longest element. 
    return DP[currIndex];
    //--------------------------------------------------------

}

void test(){
    //was called in int main() but I removed main from this file to test with the main.cpp

    cout << "Starting Testing: " << endl; 

    vector<int> test = {1, 2, 4, 8}; 
    cout << vec_to_string(test) << endl << vec_to_string(biggest_divisible_conglomerate(test)); 
    cout << endl << endl;

    vector<int> test2 = {2, 3, 6, 9, 18}; 
    cout << vec_to_string(test2) << endl << vec_to_string(biggest_divisible_conglomerate(test2)); 
    cout << endl << endl;

    vector<int> test3 = {7, 11, 13, 17}; 
    cout << vec_to_string(test3) << endl << vec_to_string(biggest_divisible_conglomerate(test3)); 
    cout << endl << endl;

    vector<int> test4 = {2, 4, 6, 9, 12, 18, 20}; 
    cout << vec_to_string(test4) << endl << vec_to_string(biggest_divisible_conglomerate(test4)); 
    cout << endl << endl;

    vector<int> test5 = {}; 
    cout << vec_to_string(test5) << endl << vec_to_string(biggest_divisible_conglomerate(test5)); 
    cout << endl << endl;

    cout << "Testing Done. " << endl;


}
