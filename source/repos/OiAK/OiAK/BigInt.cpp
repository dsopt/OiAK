#include "BigInt.h"
#include <iostream>

void BigInt::setSize(long size){
	this->size = size;
	value = new int[size];
}

void BigInt::setValue(int* value){
	this->value = value;
}

void BigInt::relocate(long size){
	//wypelniane tablicy zerami w celu wyrownania liczby bitow
	int* newValue = new int[size];
	for (int i = 0; i < this->getSize(); i++) {
		newValue[i] = this->value[i];
	}
	for (int j = this->getSize(); j < size; j++) {
		newValue[j] = 0;
	}
	this->setSize(size);
	this->setValue(newValue);
}

void BigInt::relocate(){
	//usuwanie niepotrzebnych wiodacych zer
	int* newValue;
	long i = this->getSize() - 1;
	while (this->value[i] == 0) {
		i--;
	}
	newValue = new int[i + 1];
	for (int j = i; j > -1; j--) {
		newValue[j] = this->value[j];
	}
	this->setSize(i + 1);
	this->setValue(newValue);
}

int BigInt::isValueBiggerThan(BigInt& b){
	//return 1 - yes
	//return 0 - even values
	//return -1 - no
	if (this->size > b.size) {
		return 1;
	}
	else if (this->size < b.size) {
		return -1;
	}
	else {
		for (long i = this->size - 1; i > -1; i--) {
			if (this->value[i] > b.value[i]) return 1;
			else if (this->value[i] < b.value[i]) return -1;
		}
		return 0;
	}
}

BigInt::BigInt(std::string input) {
	if (input[0] == '-') {
		negative = true;
		input = input.substr(1, input.size());
	}
	else if (input[0] == '+') {
		input = input.substr(1, input.size());
	}
	this->setSize(input.size());
	for (int i = 0; i < this->size; i++) {
		value[i] = input.at(this->size - i - 1) - '0';
	}
	this->relocate();
}

BigInt BigInt::operator=(BigInt& b){
	this->negative = b.negative;
	this->size = b.size;
	this->value = b.value;
	return *this;
}

BigInt BigInt::operator-(BigInt& b){
	if (*this == b && (this->negative != b.negative)) return BigInt("0");
	else if ((!this->negative && b.negative) || (this->negative && !b.negative)) {
		b.negative = !b.negative;
		return *this + b;
	}
	else {
		long max, min, c = 0, i = 0;
		BigInt res = *this;
		res.relocate();
		if (this->isValueBiggerThan(b) == 1) {
			max = this->size;
			min = b.size;
			b.relocate(max);
			for (i; i < min; i++) {
				res.value[i] = this->value[i] - b.value[i] - c;
				c = 0;
				while (res.value[i] < 0) {
					res.value[i] += B;
					c++;
				}
			}
			for (i; i < max; i++) {
				res.value[i] -= c;
				c = 0;
				while (res.value[i] < 0) {
					res.value[i] += B;
					c++;
				}
			}
			b.relocate();
			res.relocate();
			return res;
		}
		else {
			res.negative = !res.negative;
			b.negative = !b.negative;
			return b - res;
		}
	}
}

BigInt BigInt::operator+(BigInt& b){
	if (this->negative == b.negative) {
		long max, min, c = 0, i = 0;
		BigInt res = *this;

		if (*this > b) {
			max = this->size;
			min = b.size;
			b.relocate(this->size);
		}
		else {
			max = b.size;
			min = this->size;
			this->relocate(b.size);
		}
		res.relocate(2 * max);

		for (i; i < max; i++) {
			res.value[i] = this->value[i] + b.value[i] + c;
			c = 0;
			while (res.value[i] >= B) {
				res.value[i] = res.value[i] - B;
				c++;
			}
		}
		while (c > 0) {
			res.value[i] = c;
			c = 0;
			while (res.value[i] > B) {
				res.value[i] = res.value[i] - B;
				c++;
			}
		}

		b.relocate();
		res.relocate();
		return res;
	}
	else {
		b.negative = !b.negative;
		return *this - b;
	}
}

bool BigInt::operator==(BigInt& b){
	if (this->size == b.size) {
		if (this->isValueBiggerThan(b) == 0 && this->negative == b.negative) return true;
	}
	return false;
}

bool BigInt::operator<(BigInt& b){
	if (!this->negative && b.negative) {
		return false;
	}
	else if (this->negative && !b.negative) {
		return true;
	}
	else {
		if (this->negative) {
			switch (this->isValueBiggerThan(b)) {
			case -1:
				return false;
			case 0:
				return false;
			case 1:
				return true;
			}
		}
		else {
			switch (this->isValueBiggerThan(b)) {
			case -1:
				return true;
			case 0:
				return false;
			case 1:
				return false;
			}
		}
	}
}

bool BigInt::operator>(BigInt& b)
{
	return b < *this;
}

bool BigInt::operator<=(BigInt& b)
{
	return *this < b || *this == b;
}

bool BigInt::operator>=(BigInt& b)
{
	return *this > b || *this == b;
}

bool BigInt::operator!=(BigInt& b)
{
	return !(*this == b);
}

bool BigInt::isNegative(){
	return this->negative;
}

long BigInt::getSize(){
	return this->size;
}

int* BigInt::getValue(){
	return this->value;
}

void BigInt::print(){
	if (negative) std::cout << "-";
	for (int i = this->size - 1; i > -1; i--) {
		std::cout << value[i];
	}
	std::cout << std::endl;
}
