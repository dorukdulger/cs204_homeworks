/*
  Doruk Dulger 28842
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
using namespace std;

#include "SparseMatrix.h"

SparseMatrix::SparseMatrix(const string &file_name) {
    ifstream fin(file_name);
    if (fin.fail()) {
        throw "File couldn't be opened";
    }
    // actual head_
    head_ = nullptr;
    // head_ of current row
    row_node *curr_head = nullptr;
    // row counter for error checking
    int row = 0;
    fin >> num_rows_ >> num_columns_;
    if (fin.fail()){
        throw "Invalid number of rows or number of columns";
    }
    string line;
    getline(fin, line);
    while (getline(fin, line)) {
        int col = 0, val;
        stringstream ss(line);
        // if this is the first row
        if (head_ == nullptr) {
            head_ = curr_head = new row_node;
        } else {
            curr_head->down = new row_node;
            curr_head = curr_head->down;
        }
        // pointer at last cell added in this row
        cell_node *curr_cell = nullptr;
        while (ss >> val) {
            if (val != 0) {
                cell_node *new_cell = new cell_node;
                new_cell->value = val;
                new_cell->column = col;
                // if first cell in this row
                if (curr_cell == nullptr)
                    curr_head->cell = curr_cell = new_cell;
                else {
                    curr_cell->right = new_cell;
                    curr_cell->right->left = curr_cell;
                    curr_cell = curr_cell->right;
                }
            }
            col++;
            if (col > num_columns_) {
                throw "Too many columns in row " + to_string(row);
            }
        }
        row++;
        if (row > num_rows_) {
            throw "Too many rows";
        }
        if (col < num_columns_) {
            throw "Not enough columns in row " + to_string(row);
        }
    }
    if (row < num_rows_) {
        throw "Not enough rows";
    }
}

SparseMatrix::~SparseMatrix() {
    while (head_ != nullptr) {
        cell_node *cell = head_->cell;
        while (cell != nullptr) {
            cell_node *t = cell->right;
            delete cell;
            cell = t;
        }
        row_node *t = head_->down;
        delete head_;
        head_ = t;
    }
}

ostream &operator<<(ostream &out, const SparseMatrix & rhs) {
    int rows = 0;
    row_node * head = rhs.head_;
    while (head != nullptr) {
        // To know how many zeros to print between cells
        int col = -1;
        cell_node *cell = head->cell;
        while (cell != nullptr) {
            col++;
            // until we get to this cell's column, print zeros
            while (col < cell->column) {
                out << "0 ";
                col++;
            }
            out << cell->value << " ";
            col = cell->column;
            cell = cell->right;
        }
        // If there are more zeros after the last cell in the row,
        // print them
        while (col < rhs.num_columns_ - 1) {
            out << "0 ";
            col++;
        }
        out << endl;
        head = head->down;
        rows++;
    }
    // If there are rows with no cells at all, print zeros for them
    while (rows < rhs.num_rows_) {
        for (int i = 0; i < rhs.num_columns_; i++) {
            out << "0 ";
        }
        out << endl;
        rows++;
    }
    return out;
}

SparseMatrix::SparseMatrix(SparseMatrix&& rhs) {
    head_ = rhs.head_;
    rhs.head_ = nullptr;
    num_rows_ = rhs.num_rows_;
    num_columns_ = rhs.num_columns_;
}

SparseMatrix::SparseMatrix(row_node *head, int num_rows, int num_columns): head_(head), num_rows_(num_rows), num_columns_(num_columns) {}

SparseMatrix::SparseMatrix(const SparseMatrix &rhs): head_(nullptr), num_columns_(rhs.num_columns_), num_rows_(rhs.num_rows_) {
    copy(rhs, head_, num_rows_, num_columns_);
}

SparseMatrix &SparseMatrix::operator=(const SparseMatrix & rhs) {
    if (&rhs != this)
        copy(rhs, head_, num_rows_, num_columns_);
    return *this;
}

void SparseMatrix::copy(const SparseMatrix& rhs, row_node *&head, int &num_rows, int &num_columns) {
    num_rows = rhs.num_rows_;
    num_columns = rhs.num_columns_;
    if (rhs.num_rows_ == 0 || rhs.num_columns_ == 0) return;
    row_node* curr = head = new row_node;
    row_node* other_head = rhs.head_;
    while(other_head!= nullptr){
        cell_node* rhs_cell = other_head->cell;
        cell_node* my_cell = nullptr;
        while (rhs_cell!=nullptr){
            cell_node * new_cell = new cell_node(rhs_cell->column, rhs_cell->value);
            if (my_cell == nullptr) my_cell = curr->cell = new_cell;
            else{
                my_cell->right = new_cell;
                my_cell->right->left = my_cell;
                my_cell = my_cell->right;
            }
            rhs_cell = rhs_cell->right;
        }
        if (other_head->down!=nullptr){
            curr->down = new row_node;
            curr = curr->down;
        }
        other_head = other_head->down;
    }
}


int SparseMatrix::get(int row, int col) const {
    row_node *r_ptr = getRow(row);
    cell_node *c_ptr = r_ptr->cell;
    while (c_ptr != nullptr && c_ptr->column < col) {
        c_ptr = c_ptr->right;
    }
    if (c_ptr == nullptr || c_ptr->column > col) {
        return 0;
    } else {
        return c_ptr->value;
    }
}

row_node *SparseMatrix::getRow(int row) const {
    row_node *r_ptr = head_;
    for (int i = 0; i < row; i++) {
        r_ptr = r_ptr->down;
    }
    return r_ptr;
}

void SparseMatrix::set(int row, int col, int val) {
    row_node* rowptr = head_;
    if (rowptr == nullptr) {
        head_ = new row_node;
        rowptr = head_;
    }
    cell_node* cellptr;
    cell_node *insert = new cell_node;
    insert->column = col;
    insert->value = val;
    
    
    for(int i=0; i < row ;i++){
        if(rowptr->down == nullptr){
            rowptr->down = new row_node;
        }
        rowptr = rowptr->down;
    }
    
    if(col>0 && rowptr->cell != nullptr){
        cellptr = rowptr->cell;
        //until reaching the wanted cell
        for(int i=0; i<col-1 ;i++){
            cellptr = cellptr->right;
        }
        //insert cell after reaching
        cellptr->right = insert;
        insert->left = cellptr;
    }else{
        rowptr->cell = new cell_node;
        rowptr->cell = insert; //if its first cell of row, insert cell as row pointer -> cell
    }
    
}

void SparseMatrix::multiplyRow(const SparseMatrix& rhs, SparseMatrix& result, int row) const{
    // Iterate over the columns of the right matrix
    for (int col = 0; col < rhs.num_columns_; col++) {
        int sum = 0;
        // Calculate dot product of row and column and add to sum
        for (int i = 0; i < num_columns_; i++) {
            sum += get(row, i) * rhs.get(i, col);
        }
        // Add sum to result matrix
        if(sum != 0)
         result.set(row, col, sum);
    }
}

SparseMatrix SparseMatrix::mat_mul(const SparseMatrix& rhs) const {
    // Check that the matrices are compatible for multiplication
    if (num_columns_ != rhs.num_rows_) {
        throw invalid_argument("matrices are not compatible for multiplication");
    }
    
    // Initializing result matrix with appropriate number of rows and columns
    SparseMatrix result(nullptr, num_rows_, rhs.num_columns_);
    
    // Creating a thread for each row of the lhs
    vector<thread> threads;
    for (int i = 0; i < num_rows_; i++) {
        threads.emplace_back(&SparseMatrix::multiplyRow, this, ref(rhs), ref(result), i);
    }
    
    // Join all threads
    for (auto& thread : threads) {
        thread.join();
    }

    return result;
}
