#include "BigInt.h"
#include <iostream>

void BigInt::setSize(int size){
	this->size = size;
	value = new int32_t[size];
}

void BigInt::setValue(std::int32_t* value){
	this->value = value;
}

BigInt::BigInt(){
	negative = false;
	size = 1;
	setSize(1);
	value[0] = 0;
}

void BigInt::relocate(int size){
	//wypelniane tablicy zerami w celu rozszerzenia tablicy
	int32_t* newValue = new int32_t[size];
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
	int32_t* newValue;
	int i = this->getSize() - 1;
	while (this->value[i] == 0) {
		i--;
	}
	newValue = new int32_t[i + 1];
	for (int j = i; j > -1; j--) {
		newValue[j] = this->value[j];
	}
	this->setSize(i + 1);
	this->setValue(newValue);
}

int BigInt::isValueBiggerThan(BigInt& b){
	//return 1 - tak
	//return 0 - wartosci rowne
	//return -1 - nie
	if (this->size > b.size) {
		return 1;
	}
	else if (this->size < b.size) {
		return -1;
	}
	else {
		for (int i = this->size - 1; i > -1; i--) {
			if (this->value[i] > b.value[i]) return 1;
			else if (this->value[i] < b.value[i]) return -1;
		}
		return 0;
	}
}

BigInt::BigInt(std::string input) {
	int i = 0, size = 0;
	if (input[0] == '-') {
		negative = true;
		input = input.substr(1, input.size());
	}
	else if (input[0] == '+') {
		input = input.substr(1, input.size());
	}
	if ((float)input.size() / digits > input.size() / digits) size = input.size() / digits + 1;
	else size = input.size() / digits;

	this->setSize(size);
	for (int i = 0; i < this->size; i++) {
		if (input.size() >= digits) {
			this->value[i] = std::stoi(input.substr(input.size() - digits, input.size()));
			input = input.substr(0, input.size() - digits);
		}
		else {
			this->value[i] = std::stoi(input);
			input = "";
		}
	}
	this->relocate();
}

BigInt::BigInt(std::int32_t num){
	if (num < 0) negative = true;
	size = 1;
	setSize(1);
	value[0] = num;
}

BigInt::BigInt(std::int64_t num){
	if (num < 0) negative = true;
	size = 2;
	setSize(2);
	value[0] = num % B;
	value[1] = num / B;
	relocate();
}

BigInt BigInt::operator=(BigInt b){
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
		int max, min, c = 0, i = 0;
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
		int max, min, c = 0, i = 0;
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
			if (res.value[i] >= B) {
				c = res.value[i] / B;
				res.value[i] -= c * B;
			}
		}
		while (c > 0) {
			res.value[i] = c;
			c = 0;
			if (res.value[i] >= B) {
				c = res.value[i] / B;
				res.value[i] -= c * B;
			}
		}

		this->relocate();
		b.relocate();
		res.relocate();
		return res;
	}
	else {
		b.negative = !b.negative;
		return *this - b;
	}
}

BigInt BigInt::operator*(BigInt& b)
{
	if (this->size < b.size) return b * (*this);
	else {
		int min, max, i = 0, j = 0;
		int64_t c = 0;
		BigInt res = *this;
		res.relocate(this->size * 2);
		int64_t* temp = new int64_t[2 * this->size];

		min = b.size;
		max = this->size;
		for (int k = 0; k < 2 * max; k++) {
			temp[k] = 0;
		}

		for (i; i < min; i++) {
			if (b.value[i] == 0) i++;
			for (j; j < max; j++) {
				if (this->value[j] == 0) j++;
				temp[j + i] += static_cast<std::uint64_t>(this->value[j]) * static_cast<std::uint64_t>(b.value[i]) + c;
				c = 0;
				if (temp[j + i] >= B) {
					c = temp[j + i] / B;
					temp[j + i] = temp[j + i] - c * B;
				}
			}
			while (c != 0) {
				temp[j + i] += c;
				c = 0;
				if (temp[j + i] >= B) {
					c = temp[j + i] / B;
					temp[j + i] -= c * B;
				}
				j++;
			}
			j = 0;
		}
		for (int m = 0; m < res.size; m++) {
			res.value[m] = static_cast<std::uint32_t>(temp[m]);
		}
		if (this->negative != b.negative) {
			res.negative = true;
		}
		res.relocate();
		return res;
	}
}

BigInt BigInt::operator/(BigInt& b) {
	BigInt zero = BigInt(0);
	if (b > * this) return zero;
	else if (b == *this) return BigInt(1);

	BigInt res = *this;
	BigInt part = BigInt(0);
	BigInt p = BigInt(0);
	BigInt baseInt = BigInt(this->B);
	BigInt divHelper = BigInt(0);
	int64_t helper = 0, top = 0, btm = 0;
	bool found = false;
	res.relocate();

	for (int i = this->getSize() - 1; i > this->getSize() - b.getSize(); i--) {
		if (!(part == zero)) part = part * baseInt;
		p = BigInt(this->value[i]);
		part = part + p;
		res.value[i] = 0;
	}

	for (int i = this->getSize() - b.getSize(); i > -1; i--) {
		if (!(part == zero)) part = part * baseInt;
		p = BigInt(this->value[i]);
		part = part + p;
		if (part == b) {
			res.value[i] = 1;
			part = zero;
		}
		else if (part < b) {
			res.value[i] = 0;
		}
		else {
			found = false;
			if (part.size > b.size) helper = ((int64_t)part.value[part.size - 1] * (int64_t)this->B + part.value[part.size - 2]) / b.value[b.size - 1];
			else helper = part.value[part.size - 1] / b.value[b.size - 1];
			divHelper = BigInt(helper);
			divHelper = divHelper * b;

			top = helper;
			btm = 0;
			if (divHelper > part) {
				while (!found) {
					helper = (top + btm) / 2;
					divHelper = BigInt(helper);
					divHelper = divHelper * b;
					if (((divHelper < part) && (divHelper + b > part)) || divHelper == part) {
						found = true;
					}
					else if (divHelper < part) {
						btm = helper;
					}
					else if (divHelper > part) {
						top = helper;
					}
				}
			}
			part = part - divHelper;
			res.value[i] = helper;
		}
	}
	res.relocate();
	return res;
}

bool BigInt::operator==(BigInt b){
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
			default:
				return false;
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
			default:
				return false;
			}
		}
	}
}

bool BigInt::operator>(BigInt& b){
	return b < *this;
}

bool BigInt::operator<=(BigInt& b){
	return *this < b || *this == b;
}

bool BigInt::operator>=(BigInt& b){
	return *this > b || *this == b;
}

bool BigInt::operator!=(BigInt& b){
	return !(*this == b);
}

BigInt BigInt::pow(std::int32_t b){
	BigInt res = *this;
	res.relocate();
	for (int i = 1; i < b; i++) {
		res = res * *this;
	}
	return res;
}

BigInt BigInt::mod(BigInt& m){
	BigInt zero = BigInt(0);
	if (m > * this) return *this;
	else if (m == *this) return zero;

	BigInt part = BigInt(0);
	BigInt p = BigInt(0);
	BigInt baseInt = BigInt(this->B);
	BigInt divHelper = BigInt(0);
	int64_t helper = 0, top = 0, btm = 0;
	bool found = false;

	for (int i = this->getSize() - 1; i > this->getSize() - m.getSize(); i--) {
		if (!(part == zero)) part = part * baseInt;
		p = BigInt(this->value[i]);
		part = part + p;
	}

	for (int i = this->getSize() - m.getSize(); i > -1; i--) {
		if (!(part == zero)) part = part * baseInt;
		p = BigInt(this->value[i]);
		part = part + p; 
		if (part == m) {
			part = zero;
		}
		else {
			found = false;
			if (part.size > m.size) helper = ((int64_t)part.value[part.size - 1] * (int64_t)this->B + part.value[part.size - 2]) / m.value[m.size - 1];
			else helper = part.value[part.size - 1] / m.value[m.size - 1];
			divHelper = BigInt(helper);
			divHelper = divHelper * m;
			top = helper;
			btm = 0;
			if (divHelper > part) {
				while (!found) {
					helper = (top + btm) / 2;
					divHelper = BigInt(helper);
					divHelper = divHelper * m;
					if (((divHelper < part) && (divHelper + m > part)) || divHelper == part) {
						found = true;
					}
					else if (divHelper < part) {
						btm = helper; 
					}
					else if (divHelper > part){
						top = helper;
					}
				}
			}
			part = part - divHelper;
		}
	}
	part.relocate();
	return part;
}

bool BigInt::isNegative(){
	return this->negative;
}

int BigInt::getSize(){
	return this->size;
}

std::int32_t* BigInt::getValue(){
	return this->value;
}

void BigInt::print(){
	std::cout << this->toString() << std::endl;
}

std::string BigInt::toString(){
	std::string number = "", part = "";
	if (this->size == 0) return "0";
	if (negative) number += "-";
	for (int i = this->size - 1; i > -1; i--) {
		part = std::to_string(value[i]);
		while (i != this->size - 1 && part.size() != this->digits) {
			part = "0" + part;
		}
		number += part;
		number += " ";
	}
	return number;
}

int BigInt::getB(){
	return B;
}

