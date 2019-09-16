#pragma once
#include <iostream>
#include <iomanip>
#include <cmath>

class Matrix {
private:
	unsigned int _rows;
	unsigned int _columns;

	double* _content;

public:
	Matrix(unsigned int size);
	Matrix(unsigned int rows, unsigned columns);
	Matrix(const Matrix& matrix);
	~Matrix();

	/*
	Get the size of matrix (rows times the columns).
	*/
	unsigned int Size() const;
	/*
	Get the number of rows in a matrix.
	*/
	unsigned int Rows() const;
	/*
	Get the number of columns in a matrix.
	*/
	unsigned int Columns() const;
	
	/*
	Get a value of a matrix at a linear index.
	*/
	double GetAt(unsigned int index) const;
	/*
	Get a value of a matrix at a specific row and column.
	*/
	double GetAt(unsigned int row, unsigned int col) const;

	/*
	Get the linear index of a row and column in a matrix.
	*/
	unsigned int GetIndex(unsigned int row, unsigned int col) const;

	/*
	Set a value in a matrix at a linear index.
	*/
	void SetAt(unsigned int index, double value);

	/*
	Set a value in a matrix at a specific row and column.
	*/
	void SetAt(unsigned int row, unsigned int col, double value);

	// operators
	Matrix operator= (const Matrix& other) const;
	Matrix operator+ (const Matrix& other) const;
	Matrix operator+= (const Matrix& other) const;
	Matrix operator* (const Matrix& other) const;
	Matrix operator*= (const Matrix& other) const;
	Matrix operator* (double value) const;

	/*
	Calculate the determinant of a square matrix.
	*/
	double Determinant() const;

	/*
	Clones a matrix and return a pointer to the created matrix.
	*/
	Matrix* Clone() const;

	/*
	Implement std::cout for the Matrix class
	*/
	friend std::ostream& operator << (std::ostream& os, const Matrix& matrix);
	/*
	Implement std::cin for the Matrix class
	*/
	friend std::istream& operator >> (std::istream& input, Matrix& matrix);

};
