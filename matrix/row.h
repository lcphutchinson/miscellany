#pragma once
#include <string>
#include "../fraction/fraction.cpp"

/**
 * Object Implementation of a single matrix row, or horizontal vector.
 *
 * The Row is the site of several important Matrix operations, and building a Matrix
 * from Rows allows for a safer memory structure, as well as a more reader-friendly organization of methods..
 */
class Row
{
	public:
		/**
		 * Default Constructor
		 *
		 * Allocates memory for its data if no pre-allocated address is supplied
		 *
		 * @param m Length of the Row, in Fractions
		 * @param in_data Source data pointer
		 * @param addr Optional destination address for data buffer
		 *
		 */
		Row(int m, Fraction *in_data[], void *addr);

		/**
		 * Express Constructor for building from user input
		 *
		 * Allocates memory for its data if no pre-allocated address is supplied
		 *
		 * @param m Length of the Row, in Fractions
		 * @param in_data Source data array
		 * @param addr Optional destination address for data buffer
		 *
		 */
		Row(int m, int in_data[], void *addr);

		/**
		 * Copy Constructor with address specifier
		 *
		 * Allocates memory for its data if no pre-allocated address is supplied
		 *
		 * @param r Const Row Reference data source
		 * @param addr Optional destination address for data buffer
		 *
		 */
		Row(Row &r, void *addr);

		// Destructor
		~Row();

		// Getters
		Fraction *getItem(int i);
		int getLength();

		// toString
		std::string toString();
		
	private:
		// Row Length
		int len;
		
		// Internal Data Reference
		Fraction **data;

		// Data Container
		unsigned char *buf;
};

/**
 * Create a new Row by scaling each Fraction in the input Row by a fixed rational value.
 *
 * @param r Source row for the operation
 * @param f Scalar value, as a Fraction
 * @return a new Row object where each data value is equal to r[i] * f
 * 
 */
Row *getScaledRow(Row *r, Fraction *n);

/**
 * Create a new Row from the sums of aligned values from two input Rows
 *
 * @param r1 First row for addition
 * @param r2 Second row for addition
 * @return a new Row with each value equal to r1[i] + r2[i]
 *
 */
Row *getRowSum(Row *r1, Row *r2);
