#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "ActivityBST.h"

using namespace std;

void delete_tree(tree_node *root){
    if (root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

string fill_with_zeros(int num_zeros, const string& input){
    unsigned long zeros_to_add = num_zeros - input.length();
    if (zeros_to_add < 0) zeros_to_add = 0;
    return string(zeros_to_add, '0') + input;
}

string number_to_time(int number){
    return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2,to_string(number%100));
}

bool time_check(int time){
    string temp_time = number_to_time(time);
    bool checker = true;
    
    //checking time if its written in correct numbers to state a time
    if(stoi(temp_time.substr(0,2)) < 0 || stoi(temp_time.substr(0,2)) > 23)
        checker = false;
    if(stoi(temp_time.substr(3,4)) < 0 || stoi(temp_time.substr(3,4)) > 59)
        checker = false;
    
    return checker;
}

ActivityBST::~ActivityBST(){
    delete_tree(root);
}

ActivityBST::ActivityBST (const ActivityBST & copy)
{
    root = copy.root;
}

void add_activity(tree_node *&root){
    
    bool checker = time_check(time);
    
    //if its the first node and the time is okay to add
    if (root == nullptr && checker) {
        root = new tree_node(time, activity);
        cout << "Added activity '" << root->activity << "' at " << number_to_time(root->time) << endl;
    }
    //if time is wrong
    else if(!checker){
        cout << "ERROR! Could not add activity '" << activity << "' due to illegal time value" << endl;
    }
    //determining if time is bigger or lesser than the root->time to understand which side to add
    else if (time < root->time) {
        add_activity(root->left, time, activity);
        root->left->parent = root;
    }
    else if (time > root->time) {
        add_activity(root->right, time, activity);
        root->right->parent = root;
    }
}

void ActivityBST::add(int time, const string& activity){
    
    if(time_check(time)){
        ActivityBST addBst = ActivityBST(root, time, activity);
        add_activity(addBst);
        return;
    }
}
