#pragma once
#include <string>
#include <cstdint>
class BigInt{
private:
	bool negative = false;
	int size;
	std::int32_t *value;
	//int B = 10000;
	//int digits = 4;
	int B = 1000000000;
	int digits = 9;
	void setSize(int size);
	void setValue(std::int32_t* value);
	void relocate(int size);
	void relocate();
	int isValueBiggerThan(BigInt& b);
public:
	BigInt(std::string input);
	BigInt operator=(BigInt& b);
	BigInt operator-(BigInt& b);
	BigInt operator+(BigInt& b);
	BigInt operator*(BigInt& b);
	BigInt operator/(BigInt& b);
	bool operator==(BigInt& b);
	bool operator<(BigInt& b);
	bool operator>(BigInt& b);
	bool operator<=(BigInt& b);
	bool operator>=(BigInt& b);
	bool operator!=(BigInt& b);
	BigInt pow(BigInt& b);
	BigInt toBinary();
	bool isNegative();
	int getSize();
	std::int32_t* getValue();
	void print();
	std::string toString();
};

