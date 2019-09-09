#include "../headers/matrix.h"

Matrix::Matrix(unsigned int size) : Matrix(size, size) {}

Matrix::Matrix(unsigned int rows, unsigned columns) : 
	_rows(rows), 
	_columns(columns), 
	_content(nullptr) {
	
	_content = new double[_rows * _columns];

	for (size_t i = 0; i < _rows * _columns; i++) {
		_content[i] = 0;
	}
}

Matrix::Matrix(const Matrix& matrix) : 
	_rows(matrix.Rows()), 
	_columns(matrix.Columns()), 
	_content(nullptr) {

	_content = new double[_rows * _columns];

	for (size_t i = 0; i < _rows * _columns; i++) {
		_content[i] = matrix.GetAt(i);
	}
}

Matrix::~Matrix() {
	if (_content != nullptr) {
		delete _content;
	}
}

unsigned int Matrix::Size() const {
	return this->_rows* this->_columns;
}

unsigned int Matrix::Rows() const {
	return this->_rows;
}
unsigned int Matrix::Columns() const {
	return this->_columns;
}

double Matrix::GetAt(unsigned int index) const {
	return this->_content[index];
}

double Matrix::GetAt(unsigned int row, unsigned int col) const {
	return this->GetAt(this->GetIndex(row, col));
}

void Matrix::SetAt(unsigned int index, double value) {
	this->_content[index] = value;
}
void Matrix::SetAt(unsigned int row, unsigned int col, double value) {
	this->SetAt(GetIndex(row, col), value);
}

unsigned int Matrix::GetIndex(unsigned int row, unsigned int col) const {
	// row * columns + column
	return row * this->_columns + col;
}

Matrix Matrix::operator= (const Matrix& other) const {
	if (this->_rows == other.Rows() && this->_columns == other.Columns()) {
		for (size_t i = 0; i < this->Size(); i++) {
			this->_content[i] = other.GetAt(i);
		}
	}

	return *this;
}

Matrix Matrix::operator+ (const Matrix& other) const {
	Matrix result(*this);

	if (this->_rows == other.Rows() && this->_columns == other.Columns()) {
		for (size_t i = 0; i < this->Size(); i++) {
			result.SetAt(i, other.GetAt(i) + this->_content[i]);
		}
	}
	
	return result;
}

Matrix Matrix::operator+= (const Matrix& other) const {
	if (this->_rows == other.Rows() && this->_columns == other.Columns()) {
		for (size_t i = 0; i < this->Size(); i++) {
			this->_content[i] += other.GetAt(i);
		}
	}

	return *this;
}

Matrix Matrix::operator* (const Matrix& other) const {
	if (this->_columns != other.Rows()) {
		throw "Can only multiply (N x K) with (K x N)";
	}

	Matrix result(this->_rows, other.Columns());

	for (size_t i = 0; i < this->_rows; i++)
	{
		for (size_t j = 0; j < other.Columns(); j++)
		{
			double value = 0;
			for (size_t x = 0; x < this->_columns; x++)
			{
				value += this->GetAt(i, x) * other.GetAt(x, j);
			}
			result.SetAt(i, j, value);
		}
	}

	return result;
}

Matrix Matrix::operator*= (const Matrix& other) const {
	*this = (*this * other);
	return *this;
}

Matrix Matrix::operator* (double value) const {
	Matrix result(*this);

	for (size_t i = 0; i < this->Size(); i++) {
		result.SetAt(i, this->_content[i] * value);
	}

	return result;
}

double Matrix::Determinant() const {
	if (this->_rows != this->_columns) {
		throw "Determinant exist only for (N x N) matrix";
	}

	if (2 == this->_rows) {
		// ad - bc
		return (this->_content[0] * this->_content[3]) - (this->_content[1] * this->_content[2]);
	}
	else {
		double det = 0;
		Matrix submatrix(this->_rows - 1, this->_columns - 1);
		for (size_t x = 0; x < this->_rows; x++) {
			int subi = 0;
			for (size_t i = 1; i < this->_rows; i++) {
				int subj = 0;
				for (size_t j = 0; j < this->_rows; j++) {
					if (j != x) {
						submatrix.SetAt(subi, subj,this->GetAt(i, j));
						subj++;
					}
				}
				subi++;
			}
			det = det + (pow(-1, x) * this->GetAt(0, x) * submatrix.Determinant());
		}
		
		return det;
	}
}

Matrix* Matrix::Clone() const {
	Matrix* matrix = new Matrix(this->_rows, this->_columns);
	for (size_t i = 0; i < this->Size(); i++) {
		matrix->SetAt(i, this->GetAt(i));
	}

	return matrix;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
	for (size_t row = 0; row < matrix.Rows(); row++) {
		for (size_t col = 0; col < matrix.Columns(); col++) {
			os << std::left << std::setw(6) << matrix.GetAt(row, col) << " ";
		}
		os << "\n";
		
	}
	
	return os;
}

std::istream& operator >> (std::istream& input, Matrix& matrix) {
	double value;

	for (size_t row = 0; row < matrix.Rows(); row++) {
		for (size_t col = 0; col < matrix.Columns(); col++) {
			input >> value;
			matrix.SetAt(row, col, value);
		}
	}

	return input;
}