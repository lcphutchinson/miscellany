#pragma once
#include <string>
#include "row.cpp"
#include "../fraction/fraction.cpp"

class Matrix
{
	public:
		/**
		 * Primary Constructor for in-operation constructions
		 *
		 * @param m Collumn count for this Matrix
		 * @param n Row count for this Matrix
		 * @param in_rows Row Reference Array for data input. 
		 *
		 */
		Matrix(int m, int n, Fraction *in_data[]);

		/**
		 * Shortcut Constructor for Matrices from console input.
		 *
		 * @param m Collumn count for this Matrix
		 * @param n Row Count for this Matrix
		 * @param in_data int array source data.
		 *
		 */
		Matrix(int m, int n, int in_data[]);

		Matrix(Matrix &m);
		~Matrix();

		// Getter for Collumns
		int getM();
		// and for Rows
		int getN();

		// Getter for individual member Fractions
		Fraction *getItem(int n, int m);
		// and for whole Rows
		Row *getRow(int n);

		// toString for console display
		std::string toString();

		/**
		 * Swaps two rows by reassigning internal references. Does not write data.
		 *
		 * @param r1 First target row
		 * @param r2 Second target row
		 *
		 */
		void swapRows(int r1, int r2);

		/**
		 * Writes new data into a Row based on the result of a compound row operation.
		 *
		 * Scaled Row addition and subtraction are handled by this method, to emulate the
		 * standard operation model Ra: Ra +- xRb. Use scaleRow instead to scale Ra directly.
		 *
		 * @param r1 Target row for writing (Ra)
		 * @param r2 Operand row to be scaled (Rb)
		 * @param s Scalar for r2, passed in a Fraction. Use negative values for subtraction
		 *
		 */
		void addScaledRow(int r1, int r2, Fraction *s);

		/**
		 * Writes new data into a Row after applying a scalar value to that same row
		 *
		 * @param r Row to be scaled
		 * @param s Scalar to apply, passed in a Fraction
		 *
		 */
		void scaleRow(int r, int s);

	private:
		// Matrix dimensions
		int cols;
		int rows;
		
		// Data Pointer
		Row **data;
		// Data Buffer
		unsigned char *buf;
};

/**
 * Produces a new Matrix representing the sum of two input Matrices.
 * 
 * Input Matrices must have equal order (M and N values) to be added.
 *
 * @param m1 First Matrix operand
 * @param m2 Second Matrix operand
 * @return pointer to a new Matrix m1 + m2
 *
 */
Matrix* sumMatrix(Matrix *m1, Matrix *m2);

/**
 * Produces a new Matrix representing the difference of two input Matrices.
 *
 * Input Matrices must have equal order (M and N values) to be subtracted.
 *
 * @param m1 First Matrix operand
 * @param m2 Second Matrix operand
 * @return pointer to a new Matrix m1 - m2
 *
 */
Matrix *difMatrix(Matrix *m1, Matrix *m2);

/**
 * Produces a new Matrix representing the product of two input Matrices.
 *
 * Input Matrices must have complementary M and N values (M1 = N2, M2 = N1) to be multiplied.
 *
 * @param m1 First Matrix operand
 * @param m2 Second Matrix operand
 * @return pointer to a new Matrix m1 * m2
 *
 */
Matrix *productMatrix(Matrix *m1, Matrix *m2);

/**
 * Produces a new Matrix representing the transpose of an input matrix
 *
 * @param m Matrix to be transposed
 * @return pointer to a new Matrix containing the same values as the input matrix, transposed.
 *
 */
Matrix *getTranspose(Matrix *m);
