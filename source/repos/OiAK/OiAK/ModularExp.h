#pragma once
#include "BigInt.h"
namespace ModularExp{
	BigInt fastExp(BigInt a, BigInt b, BigInt c);
	BigInt toBinary(BigInt b);
	BigInt* fillValues(BigInt a, BigInt c, int size);
};

