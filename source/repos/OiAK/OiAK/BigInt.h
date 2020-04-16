#pragma once
#include <string>
#include <cstdint>
class BigInt{
private:
	bool negative = false;
	int size;
	std::int32_t *value;
	int B = 1000000000;
	int digits = 9;
	int isValueBiggerThan(BigInt& b);
public:
	void relocate(int size);
	void relocate();
	void setSize(int size);
	void setValue(std::int32_t* value);
	BigInt();
	BigInt(std::string input);
	BigInt(std::int32_t num);
	BigInt(std::int64_t num);
	BigInt operator=(BigInt b);
	BigInt operator-(BigInt& b);
	BigInt operator+(BigInt& b);
	BigInt operator*(BigInt& b);
	BigInt operator/(BigInt& b);
	bool operator==(BigInt b);
	bool operator<(BigInt& b);
	bool operator>(BigInt& b);
	bool operator<=(BigInt& b);
	bool operator>=(BigInt& b);
	bool operator!=(BigInt& b);
	BigInt pow(std::int32_t b);
	BigInt mod(BigInt& m);
	bool isNegative();
	int getSize();
	std::int32_t* getValue();
	void print();
	std::string toString();
	int getB();

};

