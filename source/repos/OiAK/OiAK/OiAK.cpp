#include <iostream>
#include "BigInt.h"

int main(){
    BigInt b = BigInt("7");
    BigInt c = BigInt("200");
    BigInt d = b - c;
    b.print();
    c.print();
    d.print();
}
