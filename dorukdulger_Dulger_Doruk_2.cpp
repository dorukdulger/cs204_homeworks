/*
   Doruk Dulger 28842
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "sparse_matrix_2d_linked_list.h"

using namespace std;

row_node* read_matrix(const string& filename, int& num_rows, int& num_columns){
    ifstream input;
    string line;
    int temp,cnt=0;
    
    input.open(filename.c_str()); //opening file
    
    //initiliazing number of rows and columns
    input >> temp;
    num_rows = temp;
    input >> temp;
    num_columns = temp;
    
    row_node* head = new row_node(); //head node
    row_node* node = head; //node for creating and traversing 2d linked list
    
    for (int i = 0; i < num_rows; ++i) {
        //if its not the first row_node, create another row_node to go down until all rows are created
        if(i>0){
            node->down = new row_node(); //header node
            node = node->down;
        }
        cell_node* tail = new cell_node(); //tail node to connect cell nodes' left and right
        cnt=0;
        for (int j = 0; j < num_columns; ++j) {
                input >> temp; //read data
                if(temp != 0){ //if its 0 do not add cell to linked list
                    cnt++;
                    cell_node* tempc = new cell_node();
                    tempc->value = temp;
                    tempc->column = j;
                    if(cnt==1){ //if its the first cell do not need to connect left
                        node->cell=tempc;
                        tail = tempc;
                    }else{ //since its not the first cell connect left with previous cell
                        tempc->left = tail;
                        tail->right = tempc;
                        tail = tempc;
                    }
                }          
            }
        }
    input.close();
    
    return head;
}

void print_matrix(row_node* head, int num_rows, int num_columns){
    //creating node for traversing
    row_node* rowtraverse;
    cell_node* celltraverse;
    //val for printing
    int val;
    rowtraverse = head;
    
    for (int i = 0; i < num_rows; ++i){
        celltraverse = rowtraverse->cell;
        
        for (int j = 0; j < num_columns; ++j){
            if(celltraverse==nullptr){
                for(int a = 0; a < num_columns-1 ;a++){
                    cout << "0" << " ";
                }
                cout << "0";
                break;
            }
            //creating a temporary cell node to print 0's
            if(celltraverse->column != j){
                cell_node* tempnode = new cell_node();
                tempnode->value = 0;
                tempnode->right = celltraverse;
                celltraverse = tempnode;
            }
            //printing value
            val = celltraverse->value;
            cout << val << " ";
            //if there are still columns without values print 0 until all columns are filled
            if(j+1 != num_columns){
                if(celltraverse->right == nullptr){
                    while(j != num_columns-2){
                        cout << "0" << " ";
                        j++;
                    }
                    cout << "0";
                    break;
                }
                celltraverse = celltraverse->right;
            }
        }
        //update row
        rowtraverse = rowtraverse->down;
        cout << endl;
    }
}

void delete_matrix(row_node* head){
    row_node* temprow;
    cell_node* tempcell;

    while (head) {
        temprow = head->down;
        //deleting all cells
        while(head->cell){
            tempcell = head->cell->right;
            delete head->cell;
            head->cell = tempcell;
        }
        delete head;
        //update row
        head = temprow;
       }
    }

row_node* add_matrices(row_node* left, row_node* right, int num_rows, int num_columns){
    
    row_node* newhead = new row_node();
    row_node* node = newhead;//for creating m3
    row_node* rowtraverse_left = left;
    row_node* rowtraverse_right = right;
    cell_node* celltraverse_left, *celltraverse_right;
    int templeft,tempright,cnt;
    bool checker;
    
    for (int i = 0; i < num_rows; ++i) {
    //if its not the first row_node, create another row_node to go down until all rows are created
        if(i>0){
            node->down = new row_node();
            node = node->down;
            rowtraverse_left = rowtraverse_left->down;
            rowtraverse_right = rowtraverse_right->down;
        }
        
        cell_node* tail = new cell_node();
        //cells to traverse cells of left and right matrix
        celltraverse_right = rowtraverse_right->cell;
        celltraverse_left = rowtraverse_left->cell;
        cnt=0;
        
        for (int j = 0; j < num_columns; ++j) {
            cell_node* tempc = new cell_node();
            checker = false;
            //if its nullptr assign 0 value to add nothing while sum process
            if(celltraverse_left == nullptr){
                cell_node* dummy = new cell_node();
                dummy->value = 0;
                dummy->column = 0;
                celltraverse_left = dummy;
            }
            if(celltraverse_right == nullptr){
                cell_node* dummy = new cell_node();
                dummy->value = 0;
                dummy->column = 0;
                celltraverse_right = dummy;
            }
            //if left and right matrices' columns are same add their values to create m3
            if(celltraverse_left->column == j && celltraverse_right->column == j){
                tempright = celltraverse_right->value;
                templeft = celltraverse_left->value;
                tempc->value = templeft + tempright;
                tempc->column = j;
                //if there is still values different than 0, go to them
                if(celltraverse_left->right != nullptr){
                    celltraverse_left = celltraverse_left->right;
                }
                if(celltraverse_right->right != nullptr){
                    celltraverse_right = celltraverse_right->right;
                }
                //checker to understand if program adds values to m3
                checker = true;
            }else if(celltraverse_left->column == j){
                templeft = celltraverse_left->value;
                tempc->value = templeft;
                tempc->column = j;
                if(celltraverse_left->right != nullptr){
                    celltraverse_left = celltraverse_left->right;
                }
                checker = true;
            }else if(celltraverse_right->column == j){
                tempright = celltraverse_right->value;
                tempc->value = tempright;
                tempc->column = j;
                if(celltraverse_right->right != nullptr){
                    celltraverse_right = celltraverse_right->right;
                }
                checker = true;
            }
            //if value is added, connect the cells
            if(checker){
                cnt++;//counter to check if its first cell
                if(cnt==1){
                    node->cell = tempc;
                    tail = tempc;
                }else{
                    tempc->left = tail;
                    tail->right = tempc;
                    tail = tempc;
                }
            }
        }
    }
    return newhead;
}

//function to get value from matrices
int getValue(row_node* head, int row, int col){
    row_node* ptr = head; //head pointer
    int rowIdx = 0; //row index
    //while head is not empty
    while(ptr!=nullptr){
        if(rowIdx == row){
            cell_node* cell = ptr->cell;
            //if there is no cell then return 0 since its value must be 0
            if(cell==nullptr){
                return 0;
            }
            while(cell!=nullptr){
                int colIdx = cell->column;
                //check if values' columns are correct
                if(colIdx == col){
                    return cell->value;
                }
                else if(colIdx>col){
                    return 0;
                }
                cell = cell->right;
            }
        }
        ptr = ptr->down;
        rowIdx++;
    }

    return 0;
}


bool is_symmetric(row_node* head, int num_rows, int num_columns){

    if(num_rows != num_columns)
        return false;
    
    row_node* ptr = head;
    int rowIdx = 0;
    while(ptr!=nullptr){
        cell_node* cell = ptr->cell;
        while(cell!=nullptr){
            int val = cell->value;
            int sym_row = cell->column;
            int sym_col = rowIdx;
            int sym_val = getValue(head,sym_row,sym_col); //getting value from symmetric location
            if(val != sym_val){ //checking if symmetric locations' values are equal
                return false;
            }
            cell = cell->right; //next cell
        }
        ptr = ptr->down; //next row
        rowIdx++;
    }
    return true;
}
//function to insert values into new transposed matrix
row_node* inserter(row_node* head, int rowIdx, int colcnt, cell_node* insert){
    row_node* rowptr = head;
    cell_node* cellptr;
 
    for(int i=0; i < rowIdx ;i++){
        rowptr = rowptr->down;
    }
    
    if(colcnt>0){
        cellptr = rowptr->cell;
        //until reaching the wanted cell
        for(int i=0; i<colcnt-1 ;i++){
            cellptr = cellptr->right;
        }
        //insert cell after reaching
        cellptr->right = insert;
        insert->left = cellptr;
    }else{
        rowptr->cell = insert; //if its first cell of row, insert cell as row pointer -> cell
    }
    
    return head;
}

row_node* transpose(row_node* head, int num_rows, int num_columns){
    
    row_node* transpose = nullptr;
    int colcnt;

    for(int i = 0; i < num_columns; i++){
        row_node* newrow = new row_node;
        //assign transpose a row_node
        if(transpose == nullptr){
            transpose = newrow;
        }
        else{
            row_node* ptr = transpose;
            while(ptr->down != nullptr){
                ptr = ptr->down;
                 }
              ptr->down = newrow;
            }
        }
    
    for (int i = 0; i < num_columns; i++){
        colcnt=0;
        for (int j = 0; j < num_rows; j++){
            int val = getValue(head,j,i);
            //if value is not 0, insert it to new linked list
            if(val!=0){
                cell_node* newcell = new cell_node;
                newcell->value = val;
                newcell->column = j;
                transpose = inserter(transpose, i, colcnt, newcell);
                colcnt++; //update after a cell been inserted
                }
            }
        }
        
    return transpose;
    }
    

