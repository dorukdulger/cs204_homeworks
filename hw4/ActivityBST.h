#include <string>

using namespace std;
#ifndef ACTIVITY_BST_H
#define ACTIVITY_BST_H

struct tree_node {
    int time;
    string activity;
    tree_node *right;
    tree_node *left;
    tree_node *parent;
    tree_node(int t, const string &a) : time(t), activity(a),
    right(nullptr), left(nullptr),
    parent(nullptr) {}
};

class ActivityBST{
private:
    tree_node* root; // the root of the BST
public:
    ActivityBST();
    ActivityBST(const ActivityBST &);
    ~ActivityBST();
    void add(int time, const string& activity);
    static string fill_with_zeros(int num_zeros, const string& input);
    static string number_to_time(int number);
    static  bool is_number(const std::string& s);
    static  bool timeOk(string s);
};

#endif //ACTIVITY_BST_H
