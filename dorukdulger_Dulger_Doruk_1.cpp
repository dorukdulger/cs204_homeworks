#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

bool checkfile(string file) {
	ifstream input;
	input.open(file.c_str());
	if (input.fail()) {
		return true;
	}
	return false;
}

bool checkforall(string textFile, int& num_rows, int& num_columns) {
	ifstream input;
	int j = 0, rows = -1, length = 0, spaceind, cols = 0;
	string line, item;
	input.open(textFile.c_str());
	while (getline(input, line)) {
		rows++;
		if (rows == 0) {
			length = line.length();
			spaceind = line.find(" ");
			num_rows = stoi(line.substr(0, spaceind));
			num_columns = stoi(line.substr(spaceind, length - 1));
		}
		if (rows > 0) {
			stringstream ss(line);
			while (ss >> item) cols++;
		}
	}
	input.close();

	if (rows != num_rows)
		return true;
	if (cols != num_columns)
		return true;

	return false;
}

void creatingvect(string textFile, int num_rows, int num_columns, vector<vector<int>>& matrix) {
	ifstream input;
	input.open(textFile.c_str());
	string dummyLine;
	getline(input, dummyLine);

	for (int i = 0; i < num_rows; ++i) {
		for (int j = 0; j < num_columns; ++j) {
			input >> matrix[i][j];
		}
	}

	input.close();
}

//until onlyforres function put ! before functions in if conditions
bool matrixvalchecklhs(vector<vector<int>> matrix, int row, int column) {

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (!((matrix[i][j] <= 9 && matrix[i][j] >= 1) || (matrix[i][j] == -1))) {
				return false;
			}
		}
	}
	return true;
}

bool onlyforrhs(vector<vector<int>> matrix, int row, int column) {
	if (column != 1)
		return true;

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (!((matrix[i][j] <= 9 && matrix[i][j] >= 1)))
				return false;
		}
	}
	return true;
}

bool onlyforres(vector<vector<int>> matrix, int row, int column) {
	if (column != 1)
		return true;

	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < column; ++j) {
			if (!(matrix[i][j] >= 1))
				return false;
		}
	}
	return true;
}

void savinglocations(vector<vector<int>> matrix, vector<int>& locs) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			if ((matrix[i][j] == -1)) {
				locs.push_back(i);
				locs.push_back(j);
			}	
		}
	}

}

vector<int> multiplyMatricesCell(vector<int> firstMatrixRow, vector<vector<int>> secondMatrix, int col, int sum) {
	int sumLocal = sum;
	for (int i = 0; i < secondMatrix.size(); i++) {
		int cell = firstMatrixRow[i];
		if (i == secondMatrix.size() - 1) {
			if (cell == -1) {
				int division = sumLocal / secondMatrix[i][col];
				if (division > 9 || division * secondMatrix[i][col] != sumLocal) {
					return vector<int>();
				} else {
					firstMatrixRow[i] = division;
					return firstMatrixRow;
				}
			}
			else {
				sumLocal -= firstMatrixRow[i] * secondMatrix[i][col];
				if (sumLocal != 0) {
					return vector<int>();
				} else {
					return firstMatrixRow;
				}
			}
		} else if (cell != -1) {
			sumLocal -= firstMatrixRow[i] * secondMatrix[i][col];
		} else {
			for (int j = 1; j < 10; j++) {
				vector<int> copy;
				for (int i = 0; i < firstMatrixRow.size(); i++) {
					copy.push_back(firstMatrixRow[i]);
				}
				copy[i] = j;
				vector<int> result = multiplyMatricesCell(copy, secondMatrix, col, sum);
				if (result != vector<int>()) {
					return result;
				}
			}
		}
	}
	return firstMatrixRow;
}

vector<vector<int>> multiplyMatrices(vector<vector<int>> firstMatrix, vector<vector<int>> secondMatrix, vector<vector<int>> resultMatrix) {
	for (int row = 0; row < resultMatrix.size(); row++) {
		for (int col = 0; col < 1; col++) {
			firstMatrix[row] = multiplyMatricesCell(firstMatrix[row], secondMatrix, col, resultMatrix[row][col]);
		}
	}
	return firstMatrix;
}

int main() {
	string LHStxt, RHStxt, REStxt, ofilename;
	int LHSr = 0, LHSc = 0, RHSr = 0, RHSc = 0, RESr = 0, RESc = 0;

	cout << "Enter LHS matrix filename: ";
	cin >> LHStxt;

	cout << "Enter RHS matrix filename: ";
	cin >> RHStxt;

	cout << "Enter RES filename: ";
	cin >> REStxt;

	cout << "Enter output filename: ";
	cin >> ofilename;

	ofstream outputfile(ofilename);

	if (checkfile(LHStxt)) {
		outputfile << "Error" << endl;
		outputfile.close();
		return 0;
	}
	if (checkfile(RHStxt)) {
		outputfile << "Error" << endl;
		outputfile.close();
		return 0;
	}
	if (checkfile(REStxt)) {
		outputfile << "Error" << endl;
		outputfile.close();
		return 0;
	}
	if (!checkforall(LHStxt, LHSr, LHSc)) {
		outputfile << "Error" << endl;
		outputfile.close();
		return 0;
	}
	if (!checkforall(RHStxt, RHSr, RHSc))
	{
		outputfile << "Error" << endl;
		outputfile.close();
		return 0;
	}
	if (!checkforall(REStxt, RESr, RESc))
	{
		outputfile << "Error" << endl;
		outputfile.close();
		return 0;
	}

	vector<vector<int>> LHSmatrix(LHSr, vector<int>(LHSc));
	creatingvect(LHStxt, LHSr, LHSc, LHSmatrix);

	vector<vector<int>> RHSmatrix(RHSr, vector<int>(RHSc));
	creatingvect(RHStxt, RHSr, RHSc, RHSmatrix);

	vector<vector<int>> RESmatrix(RESr, vector<int>(RESc));
	creatingvect(REStxt, RESr, RESc, RESmatrix);

	if (!matrixvalchecklhs(LHSmatrix, LHSr, LHSc)) {
		outputfile << "Error" << endl;
		outputfile.close();
		return 0;
	}
	if (!onlyforrhs(RHSmatrix, RHSr, RHSc)) {
			outputfile << "Error" << endl;
			outputfile.close();
			return 0;
	}
	if (!onlyforres(RESmatrix, RESr, RESc)) {
			outputfile << "Error" << endl;
			outputfile.close();
			return 0;
	}

	vector<int> locs;
	savinglocations(LHSmatrix, locs);
	LHSmatrix = multiplyMatrices(LHSmatrix, RHSmatrix, RESmatrix);

	for (int i = 0; i < locs.size(); i=i+2) {
		outputfile << locs[i] << " " << locs[i + 1] << " " << LHSmatrix[locs[i]][locs[i + 1]] << endl;
	}

	return 0;
}