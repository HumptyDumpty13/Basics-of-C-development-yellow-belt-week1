#include<iostream>
#include<map>
#include<fstream>
#include<string>
#include<exception>
#include<vector>
#include<iomanip>
#include<sstream>
#include<set>
// Реализуйте функции и методы классов и при необходимости добавьте свои

class Matrix {
public:
	Matrix() {
		rows = 0;
		cols = 0;
		//matrix();
	}
	Matrix(int num_rows, int num_cols) {
		//matrix(num_rows, std::vector<int>(num_cols));
		Reset(num_rows, num_cols);
	}
	void Reset(int new_rows, int new_cols) {
		if (new_rows < 0 || new_cols < 0) {
			throw std::out_of_range("");
		}
		if (new_rows == 0 || new_cols == 0) {
			new_rows = new_cols = 0;
		}
		rows = new_rows;
		cols = new_cols;
		matrix.assign(new_rows, std::vector<int>(new_cols));
	}
	int At(int row, int col) const {
		if (row > rows || col > cols) {
			throw std::out_of_range("");
		}
		return matrix.at(row).at(col);
	}
	int& At(int row, int col) {
		if (row > rows || col > cols) {
			throw std::out_of_range("");
		}
		return matrix.at(row).at(col);
	}
	int GetNumRows() const {
		return rows;
	}
	int GetNumColumns() const {
		return cols;
	}

private:
	int rows;
	int cols;
	std::vector<std::vector<int>> matrix;
};

std::istream& operator>>(std::istream& stream, Matrix& matrix) {
	int rows, cols;
	if (stream) {
		stream >> rows >> cols;
		if (stream) {
			matrix.Reset(rows, cols);
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					stream >> matrix.At(i,j);
				}
			}
		}
	}
	return stream;
}
std::ostream& operator << (std::ostream& os, const Matrix& m) {
	 os << m.GetNumRows() << " " << m.GetNumColumns() << std::endl;
	 for (int i = 0; i < m.GetNumRows(); ++i) {
		 for (int j = 0; j < m.GetNumColumns(); ++j) {
			 os<< m.At(i, j)<<" ";
		 }
		 os << std::endl;
	 }
	 return os;
}

bool operator==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
		for (int i = 0; i < lhs.GetNumRows(); ++i) {
			for (int j = 0; j < lhs.GetNumColumns(); ++j) {
				if (lhs.At(i, j) != rhs.At(i, j)) { return false; }
			}
		}
	}
	return lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns();
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)  {
	if (lhs.GetNumRows()  != rhs.GetNumRows() || lhs.GetNumColumns() != rhs.GetNumColumns()) {
		throw std::invalid_argument("Invalid argument");
	}
		Matrix m(lhs.GetNumRows(), lhs.GetNumColumns());
		for (int i = 0; i < lhs.GetNumRows(); ++i) {
			for (int j = 0; j < lhs.GetNumColumns(); ++j) {
				m.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
			}
		}
		return m;
}

int main() {
	try {
			Matrix one;
			Matrix two;

			std::cin >> one >> two;
			if (one == two) {
				std::cout << one + two << std::endl;
			}

	}
	catch (std::out_of_range& out) {
		std::cout << out.what() << std::endl;
	}
	catch(std::invalid_argument & ia) {
		std::cout << ia.what() << std::endl;
	}
}