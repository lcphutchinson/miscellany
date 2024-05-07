#include <string>
#include "matrix.h"
#include "row.cpp"
#include "../fraction/fraction.cpp"

Matrix::Matrix(int m, int n, Fraction *in_data[])
{
	cols = m;
	rows = n;
	int data_length = cols * rows * sizeof(Fraction);
	int col_offset = cols * sizeof(Fraction);
	buf = new alignas (Fraction) unsigned char[data_length];
	data = new Row*[rows];
	for(int i = 0; i < rows; i++)
	{
		void *addr = buf + i * col_offset;
		Fraction **row_i = &in_data[i * cols];
		data[i] = new Row(cols, row_i, addr);
	}
}

Matrix::Matrix(int m, int n, Row *in_rows[])
{
	cols = m;
	rows = n;
	int data_length = cols * rows * sizeof(Fraction);
	int col_offset = cols * sizeof(Fraction);
	buf = new alignas (Fraction) unsigned char[data_length];
	data = new Row*[rows];
	for(int i = 0; i < rows; i++)
	{
		void *addr = buf + i * col_offset;
		Row &rr = *in_rows[i];
		data[i] = new Row(rr, addr);
	}	
}

Matrix::Matrix(int m, int n, int in_data[])
{
	cols = m;
	rows = n;
	int data_length = cols * rows * sizeof(Fraction);
	int col_offset = cols * sizeof(Fraction);
	buf = new alignas (Fraction) unsigned char[data_length];
	data = new Row*[rows];
	for(int i = 0; i < rows; i++)
	{
		void *addr = buf + i * col_offset;
		int *row_i = &in_data[cols * i];
		data[i] = new Row(cols, row_i, addr); 
	}
}

Matrix::Matrix(Matrix &m)
{
	cols = m.getM();
	rows = m.getN();
	int data_length = cols * rows * sizeof(Fraction);
	int col_offset = cols * sizeof(Fraction);
	buf = new alignas (Fraction) unsigned char[data_length];
	data = new Row*[rows];
	for(int i = 0; i < rows; i++)
	{
		void *addr = buf + i * col_offset;
		Row &rr = *m.getRow(i);
		data[i] = new Row(rr, addr);
	}
}

Matrix::~Matrix()
{
	for(int i = 0; i < rows; i++)
	{
		data[i]->~Row();
	}
	delete[] data;
	delete[] buf;
}

int Matrix::getM()
{
	return cols;
}

int Matrix::getN()
{
	return rows;
}

Fraction* Matrix::getItem(int n, int m) 
{
	return data[n]->getItem(m);
}

Row* Matrix::getRow(int n)
{
	return data[n];
}

std::string Matrix::toString()
{
	std::string output = "";
	
	for(int i = 0; i < rows; i++)
	{
		output.append(data[i]->toString() + "\n");
	}
	return output;
}

void Matrix::swapRows(int r1, int r2)
{
	void *r1_addr = (void*)data[r1];
	Row &rr1 = *data[r1];
	Row *r = new Row(rr1);
	data[r1]->~Row();

	void *r2_addr = (void*)data[r2];
	Row &rr2 = *data[r2];
	data[r1] = new Row(rr2, r1_addr);
	data[r2]->~Row();

	Row &rr = *r;
	data[r2] = new Row(rr2, r2_addr);
	r->~Row();
}

void Matrix::addScaledRow(int r1, int r2, Fraction *s)
{
	Row *r2_scaled = getScaledRow(data[r2], s);
	Row *row_sum = getRowSum(data[r1], r2_scaled);
	r2_scaled->~Row();

	void *r1_addr = (void*)data[r1];
	data[r1]->~Row();
	Row &sumr = *row_sum;
	data[r1] = new Row(sumr, r1_addr);
	row_sum->~Row();
}

void Matrix::scaleRow(int r, Fraction *s)
{
	Row *r_scaled = getScaledRow(data[r], s);
	Row &scaledr = *r_scaled;
	
	void *r_addr = (void*)data[r];
	data[r]->~Row();
	data[r] = new Row(scaledr, r_addr);
	r_scaled->~Row();
}

Matrix *sumMatrix(Matrix *m1, Matrix *m2)
{
	int cols = m1->getM();
	int rows = m1->getN();
	Row **base = new Row*[rows];
	for(int i = 0; i < rows; i++)
	{
		base[i] = getRowSum(m1->getRow(i), m2->getRow(i));
	}
	Matrix *output = new Matrix(cols, rows, base);
	delete[] base;
	return output;
}

Matrix *difMatrix(Matrix *m1, Matrix *m2)
{
	int cols = m1->getM();
	int rows = m1->getN();
	Row **base = new Row*[rows];
	for(int i = 0; i < rows; i++)
	{
		base[i] = getRowDiff(m1->getRow(i), m2->getRow(i));
	}
	Matrix *output = new Matrix(cols, rows, base);
	delete[] base;
	return output;
}

Matrix *productMatrix(Matrix *m1, Matrix *m2)
{
	int m1_cols = m1->getM();
	int m1_rows = m1->getN();
	int m2_cols = m2->getM();
	int m2_rows = m2->getN();
	Fraction **base = new Fraction*[m2_cols * m1_rows];
	int write_index = 0;
	for(int i = 0; i < m1_rows; i++)
	{
		for(int j = 0; j < m2_cols; j++)
		{
			Fraction *dot_prod = new Fraction(0);
			for(int k = 0; k < m2_rows; k++)
			{
				Fraction *f = product(m1->getRow(i)->getItem(k), m2->getRow(k)->getItem(j)); 
				dot_prod = sum(dot_prod, f);
			}
			Fraction &fr = *dot_prod;
			base[write_index] = new Fraction(fr);
			write_index++;
		}
	}
	Matrix *output = new Matrix(m2_cols, m1_rows, base);
	delete[] base;
	return output;
}

Matrix *getTranspose(Matrix *m)
{
	int m_cols = m->getM();
	int m_rows = m->getN();
	Fraction **base = new Fraction*[m_cols * m_rows];
	int write_index = 0;
	for(int i = 0; i < m_cols; i++)
	{
		for(int j = 0; j < m_rows; j++)
		{
			base[write_index] = m->getRow(j)->getItem(i);
			write_index++;
		}
	}
	Matrix *output = new Matrix(m_rows, m_cols, base);
	delete[] base;
	return output;
}
