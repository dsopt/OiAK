#pragma once
#include <string>
class BigInt{
private:
	bool negative = false;
	long size;
	int *value;
	int B = 10;
	void setSize(long size);
	void setValue(int* value);
	void relocate(long size);
	void relocate();
	int isValueBiggerThan(BigInt& b);
public:
	BigInt(std::string input);
	BigInt operator=(BigInt& b);
	BigInt operator-(BigInt& b);
	BigInt operator+(BigInt& b);
	BigInt operator*(BigInt& b);
	bool operator==(BigInt& b);
	bool operator<(BigInt& b);
	bool operator>(BigInt& b);
	bool operator<=(BigInt& b);
	bool operator>=(BigInt& b);
	bool operator!=(BigInt& b);
	bool isNegative();
	long getSize();
	int* getValue();
	void print();
};

