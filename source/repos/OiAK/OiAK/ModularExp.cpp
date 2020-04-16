#include "ModularExp.h"
#include <iostream>
#include <cmath>

namespace ModularExp{
	static const int BASE = 134217728;	//2^27
	static const int POWER = 27;
	int* pwrs = new int[POWER];

	BigInt ModularExp::fastExp(BigInt a, BigInt b, BigInt c) {
		if (a == BigInt("0")) return BigInt("0");
		else if (b == BigInt("0")) return BigInt("1");
		else if (b.isNegative()) return BigInt("0");
		else if (a == c) return BigInt("0");
		else if (c == BigInt(1)) return BigInt(0);
		else if (c == BigInt(0)) return BigInt(0);
		else if ((c == BigInt(2)) && (a.getValue()[0] % 2 == 0)) return BigInt(0);
		else if ((c == BigInt(2)) && (a.getValue()[0] % 2 == 1)) return BigInt(1);
		else if (a - c == BigInt(1)) return BigInt("1");
		else if (c - a == BigInt(1) && b.getValue()[0] % 2 == 0) return BigInt("1");
		else if (c - a == BigInt(1) && b.getValue()[0] % 2 == 1) return BigInt("-1");
		else{
			BigInt exp = toBinary(b);
			a = a.mod(c);
			BigInt* values = new BigInt[exp.getSize()*9];
			BigInt res = BigInt(1);
			BigInt part = BigInt("0");
			bool first = false;
			int max = 100000000;
			int m = max;
			std::string current = "";
			int val = 0;

			for (int i = exp.getSize() - 1; i > - 1; i--) {
				current = std::to_string(exp.getValue()[i]);
				current = std::string(9 - current.length(), '0').append(current);
				int j = 8;
				int index = 0;
				while (current.length() > 0) {
					val = current.at(0) - '0';
					current.erase(0, 1);
					if (val == 1) {
						index = i * 9 + j;
						if (!first) {
							values = fillValues(a, c, index);
							first = true;
						}
						part = values[index];
						res = res * part;
						res = res.mod(c);
					}
					j--;
				}
			}
			return res;
		}
	}

	BigInt toBinary(BigInt b) {
		BigInt res = BigInt(0);
		BigInt h = BigInt(0);
		int bSize = b.getSize() + 1;
		int32_t* helper = new int32_t[bSize];
		BigInt* pwrBase = new BigInt[bSize];
		BigInt bigBase = BigInt(BASE);
		int64_t value = 0;
		int64_t newValue = 0;
		pwrBase[0] = 1;
		helper[0] = 0;
		for (int i = 1; i < bSize; i++) {
			helper[i] = 0;
			pwrBase[i] = pwrBase[i - 1] * bigBase;
		}

		for (int i = b.getSize(); i > 0; i--) {
			if (b >= pwrBase[i]) {
				h = b / pwrBase[i];
				helper[i] = h.getValue()[0];
				b = b.mod(pwrBase[i]);
			}
			else {
				helper[i] = 0;
			}
		}
		helper[0] = b.getValue()[0];

		int* pwrHelper = new int[POWER];
		pwrs[0] = 1;
		pwrHelper[0] = 0;
		for (int i = 1; i < POWER; i++) {
			pwrs[i] = pwrs[i - 1] * 2;
			pwrHelper[i] = 0;
		}

		int32_t* binHelper = new int32_t[bSize * 3];
		int j = 0;
		newValue = 0;
		int k = POWER - 1;
		for (int i = 0; i < bSize; i++) {
			value = helper[i];
			if (value == 0) {
				for (int l = 0; l < 3; l++) {
					binHelper[j] = 0;
					j++;
				}
			}
			else {
				k = POWER - 1;
				while (value >= 0 && k > -1) {
					if (value >= pwrs[k]) {
						pwrHelper[k] = 1;
						value = value - pwrs[k];
					}
					else {
						pwrHelper[k] = 0;
					}
					k--;
				}
				for (int l = 0; l < 3; l++) {
					for (int m = 8; m > -1; m--) {
						newValue *= 10;
						newValue += pwrHelper[l * 9 + m];
					}
					binHelper[j] = newValue;
					j++;
					newValue = 0;
				}
			}
		}
		res.setSize(bSize * 3);
		res.setValue(binHelper);
		res.relocate();
		return res;
	}
	BigInt* fillValues(BigInt a, BigInt c, int size){
		BigInt* res = new BigInt[size + 1];
		BigInt base = a;
		base.relocate();
		base = base.mod(c);
		res[0] = base ;	//a^2^0

		for (int i = 1; i < size + 1; i++) {
			res[i] = res[i - 1] * res[i - 1];
			res[i] = res[i].mod(c); 
		}
		return res;
	}
}
