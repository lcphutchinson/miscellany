#pragma once
#include <string>
#include "row.h"
#include "../fraction/fraction.cpp"

Row::Row(int m, Fraction *in_data[], void *addr = NULL)
{
	len = m;
	int data_length = sizeof(Fraction) * len;
	buf = (addr == NULL) ? new alignas(Fraction) unsigned char[data_length]
		: new(addr) alignas(Fraction) unsigned char[data_length];
	data = new Fraction*[len];
	for(int i = 0; i < len; i++)
	{
		int offset = i * sizeof(Fraction);
		const Fraction &fr = *in_data[i];
		data[i] = new(buf + offset) Fraction(fr);
	}
}

Row::Row(int m, int in_data[], void *addr = NULL)
{
	len = m;
	int data_length = sizeof(Fraction) * len;
	buf = (addr == NULL) ? new alignas(Fraction) unsigned char[data_length]
		: new(addr) alignas(Fraction) unsigned char[data_length];
	data = new Fraction*[len];
	for(int i = 0; i < len; i++)
	{
		int offset = i * sizeof(Fraction);
		data[i] = new(buf + offset) Fraction(in_data[i]);
	}
}

Row::Row(Row &r, void *addr = NULL)
{
	len = r.getLength();
	int data_length = sizeof(Fraction) * len;
	buf = (addr == NULL) ? new alignas(Fraction) unsigned char[data_length]
		: new(addr) alignas(Fraction) unsigned char[data_length];
	data = new Fraction*[len];
	for(int i = 0; i < len; i++)
	{
		int offset = i * sizeof(Fraction);
		const Fraction &fr = *r.getItem(i);
		data[i] = new(buf + offset) Fraction(fr);
	}
}

Row::~Row()
{
	delete[] data;
	delete[] buf;
}

Fraction *Row::getItem(int i)
{
	return data[i];
}

int Row::getLength()
{
	return len;
}

std::string Row::toString()
{
	std::string output = "";
	for(int i = 0; i < len; i++)
	{
		output.append("\t" + data[i]->toString());
	}
	return output + "\n";
}

Row *getScaledRow(Row *r, Fraction *f)
{
	int m = r->getLength();
	Fraction **fracs = new Fraction*[m]; 
	for(int i = 0; i < m; i++)
	{
		fracs[i] = product(r->getItem(i), f);
	}
	Row *output = new Row(m, fracs);
	delete[] fracs;
	return output;
}

Row *getRowSum(Row *r1, Row *r2)
{
	int m = r1->getLength();
	Fraction **fracs = new Fraction*[m];
	for(int i = 0; i < m; i++)
	{
		fracs[i] = sum(r1->getItem(i), r2->getItem(i));
	}
	Row *output = new Row(m, fracs);
	delete[] fracs;
	return output;
}

Row *getRowDiff(Row *r1, Row *r2)
{
	int m = r1->getLength();
	Fraction **fracs = new Fraction*[m];
	for(int i = 0; i < m; i++)
	{
		fracs[i] = difference(r1->getItem(i), r2->getItem(i));
	}
	Row *output = new Row(m, fracs);
	delete[] fracs;
	return output;
}

