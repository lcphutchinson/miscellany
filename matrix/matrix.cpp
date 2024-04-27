#include <iostream> // for preliminary testing
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
	Row row_sum = getRowSum(data[r1], r2_scaled);
	r2_scaled->~Row();

	void *r1_addr = (void*)data[r1];
	data[r1]->~Row();
	Row &sumr = *row_sum;
	data[r1] = new Row(sumr, r1_addr);
	row_sum->~Row();
}

// from here down is WIP
void scaleRow(int r, int s)
{
	int nothing = 0;
}

Matrix *sumMatrix(Matrix *m1, Matrix *m2)
{
	return m1;
}

Matrix *difMatrix(Matrix *m1, Matrix *m2)
{
	return m2;
}

Matrix *productMatrix(Matrix *m1, Matrix *m2)
{
	return m1;
}

Matrix *getTranspose(Matrix *m)
{
	return m;
}

int main(){
	int data_base[4] = { 1, 2, 2, 1 };
	Matrix *m1 = new Matrix(2, 2, data_base);
	std::cout << "Matrix 1: \n" << m1->toString();

	Fraction **m2_base = new Fraction*[4];
	m2_base[0] = new Fraction(1, 4);
	m2_base[1] = new Fraction(1, 2);
	m2_base[2] = new Fraction(1, 2);
	m2_base[3] = new Fraction(1, 4);
	Matrix *m2 = new Matrix(2, 2, m2_base);
	delete[] m2_base;

	std::cout << "Matrix 2: \n" << m2->toString();
}
