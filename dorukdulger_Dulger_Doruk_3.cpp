
//Doruk Dulger 28842

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include "activity_bst.h"

using namespace std;

int cnt = 0;

string fill_with_zeros(int num_zeros, const string& input){
    unsigned long zeros_to_add = num_zeros - input.length();
    if (zeros_to_add < 0) zeros_to_add = 0;
    return string(zeros_to_add, '0') + input;
}

string number_to_time(int number){
    return fill_with_zeros(2, to_string(number/100))+":"+ fill_with_zeros(2,
                                                                          to_string(number%100));
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

void delete_tree(tree_node *root){
    if (root == NULL) return;
    delete_tree(root->left);
    delete_tree(root->right);
    delete root;
}

// Add an activity with name 'activity' and time 'time'
void add_activity(tree_node *&root, int time, const string &activity){
    
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

// Print the name of the activity occurring at time 'time'
void print_activity(tree_node *root, int time){
    string stime = number_to_time(time);
    bool checker = time_check(time);
    string temp_time = stime.substr(0,2) + ":00";
    
    //checks if root exist
    if(checker && root){
        if(root->time == 0000 && root->right == nullptr && root->left == nullptr ){
            cout << "Time: " << stime << ", Activity : " << root->activity << endl;
            return;
        }
        if(number_to_time(root->time) == temp_time){
            cout << "Time: " << stime << ", Activity : " << root->activity << endl;
            return;
        }
        if(root->left && root->time > time)
            print_activity(root->left, time);
        else if(root->right && root->time < time)
            print_activity(root->right, time);
        else{
            cout << "Time: " << stime << ", Activity : free" << endl;
            return;
        }
    }else if(checker){
        cout << "Time: " << stime << ", Activity : free" << endl;
        return;
    }else if(!checker){
        cout << "ERROR! Could not print activity at specific time due to illegal time" << endl;
    }
}


// Print the duration of the activity occurring at time 'time'
void print_activity_and_duration(tree_node *root, int time){
    string stime = number_to_time(time);
    bool checker = time_check(time);
    string temp_time = stime.substr(0,2) + ":00";
    
    if(checker && root){
        if(root->time == 0000 && root->right == nullptr && root->left == nullptr ){
            cout << "Time period: [00:00 - 00:00]: " << root->activity << endl;
            return;
        }
        if(number_to_time(root->time) == temp_time){
            if(root->right){
                cout << "Time period: [" << temp_time << " - "<< number_to_time(root->right->time) << "]: " << root->activity << endl;
                return;
            }else if(root->parent && root->parent->time > root->time){
                cout << "Time period: [" << temp_time << " - "<< number_to_time(root->parent->time) << "]: " << root->activity << endl;
                return;
            }else{
                cout << "Time period: [" << temp_time << " - "<< "00:00]: " << root->activity << endl;
                return;
            }
        }if(root->left && root->time > time)
            print_activity_and_duration(root->left, time);
        else if(root->right && root->time < time)
            print_activity_and_duration(root->right, time);
        else if(root->time < time){
            cout << "Time period: [" << number_to_time(root->time) << " - "  << "00:00]: "<< root->activity << endl;
            return;
        }else{
            cout << "Time period: [00:00" << " - " << number_to_time(root->time) << "]: free" << endl;
            return;
        }
    }else if(!checker){
        cout << "ERROR! Could not print activity at specific time due to illegal time" << endl;
    }else if(checker && !root){
        cout << "Time period: [00:00 - 00:00]: free" << endl;
        return;
    }
}


// Print the duration of every occurrence of activity 'activity'
void print_single_activity(tree_node *root, const string &activity){
    while(root != nullptr){
        if(activity == "free" && cnt == 0 && root != nullptr && root->time == 0000){
            return;
        }
        print_single_activity(root->left,activity);
        if(root->parent == nullptr){
            if(root->right == nullptr){
                cout << "Time period: ["<< number_to_time(root->time) <<  " - " << "00:00]: " << activity << endl;
                cnt++;
                break;
            }
        }
        if(root->activity == activity){
            if(root->right){
                cout << "Time period: ["<< number_to_time(root->time) << " - " << number_to_time(root->right->time) << "]: "<< activity << endl;
            }else if(root->parent->left == root){
                cout << "Time period: [" << number_to_time(root->time) << " - " << number_to_time(root->parent->time) << "]: "<< activity << endl;
            }else if(root->parent->right == root){
                while(root->parent){
                    if(root->parent->parent != NULL){
                        if(root->time < root->parent->parent->time){
                            cout << "Time period: [" << number_to_time(root->time) << " - " << number_to_time(root->parent->parent->time) << "]: "<< activity << endl;
                            break;
                        }else{
                            root->parent = root->parent->parent;
                        }
                    }else{
                        cout << "Time period: [" << number_to_time(root->time) << " - " << "00:00]: "<< activity << endl;
                        break;
                    }
                }
            }else{
                cout << "Time period: [" << number_to_time(root->time) << " - " << "00:00]: "<< activity << endl;
            }
        }
        print_single_activity(root->right,activity);
        break;
    }
    if(activity == "free" && cnt == 0 && root != nullptr){
        cout << "Time period: [00:00" <<  " - " << number_to_time(root->time) << "]: free" << endl;
    }else if(activity == "free" && cnt == 0){
        cout << "Time period: [00:00 - 00:00]: free" << endl;
        return;
    }
}


void print_all_activities(tree_node* root){
    if (root != nullptr) {
        print_all_activities(root->left);
        cout << "[" << number_to_time(root->time) << "] - " << root->activity << endl;
        print_all_activities(root->right);
    }
}
