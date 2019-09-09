#include <iostream>
#include <matrix.h>

void mult() {
	std::cout << "Matrix Multiplication\n";
	std::cout << "____________________________________________________\n\n";

	size_t number;
	size_t rows, cols;
	std::cout << "Enter the number to multiply: ";
	std::cin >> number;

	std::cout << "Enter first matrix size (N x K): ";
	std::cin >> rows >> cols;

	Matrix* result = new Matrix(rows, cols);
	std::cout << "Enter " << result->Size() << " values: ";
	std::cin >> *result;

	for (size_t i = 1; i < number; i++) {
		std::cout << "Enter matrix #" << i + 1 << " columns: ";
		std::cin >> cols;
		Matrix temp(result->Columns(), cols);
		std::cout << "Enter " << temp.Size() << " values for matrix #" << i + 1 << ": ";
		std::cin >> temp;

		result = (*result * temp).Clone();
	}

	std::cout << "The result is\n" << *result << "\n";
}

void determinant() {
	std::cout << "Matrix Determinant Calculator\n";
	std::cout << "____________________________________________________\n\n";

	size_t rows;

	std::cout << "Enter matrix size (N x N): ";
	std::cin >> rows;

	Matrix result(rows, rows);
	std::cout << "Enter " << result.Size() << " values: ";
	std::cin >> result;
	
	std::cout << "The determinant of the matrix:\n" << result << "\nis: " << result.Determinant() << "\n";
}

void sum() {
	std::cout << "Matrix Summerize\n";
	std::cout << "____________________________________________________\n\n";

	size_t number;
	size_t rows, cols;
	std::cout << "Enter the number to sum: ";
	std::cin >> number;

	std::cout << "Enter first matrix size (N x K): ";
	std::cin >> rows >> cols;

	Matrix result(rows, cols);
	std::cout << "Enter " << result.Size() << " values: ";
	std::cin >> result;

	for (size_t i = 1; i < number; i++) {
		Matrix temp(rows, cols);
		std::cout << "Enter " << temp.Size() << " values for matrix #" << i + 1 << ": ";
		std::cin >> temp;

		result += temp;
	}

	std::cout << "The result is\n" << result << "\n";
}

void scalar() {
	std::cout << "Matrix Scalar Multiplication\n";
	std::cout << "____________________________________________________\n\n";

	size_t rows, cols;
	double value;

	std::cout << "Enter first matrix size (N x K): ";
	std::cin >> rows >> cols;

	Matrix result(rows, cols);
	std::cout << "Enter " << result.Size() << " values: ";
	std::cin >> result;

	std::cout << "Enter a scalar value to multiply with: ";
	std::cin >> value;

	std::cout << "The reslut of the matrix:\n" << result << "\n times " << value << " is\n" << result * value << "\n";
}

int main() {
	unsigned int op = 10;

	std::cout << "Welcome to Matrix V4 - by David Delarosa\n";
	std::cout << "____________________________________________________\n\n";
	
	do {
		std::cout << "Select from the following:";

		std::cout << R"(
    1 - Multiply matrix
    2 - Calculete matrix determinant
    3 - Sum matrix together
    4 - Multiply matrix in scalar
    0 - Exit
Select: )";

		std::cin >> op;
		system("cls");

		switch (op) {
		case 0:
			continue;
		case 1:
			mult();
			break;
		case 2:
			determinant();
			break;
		case 3:
			sum();
			break;
		case 4:
			scalar();
			break;
		default:			
			break;
		}
		
		system("pause");
		system("cls");
	} while (op != 0);

	return 0;
}