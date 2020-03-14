#include <iostream>
#include "BigInt.h"

int main(){
    BigInt b = BigInt("92468952");
    BigInt c = BigInt("221");
    BigInt d = b * c;
    std::cout << "Wartosci: " << std::endl;
    b.print();
    c.print();
    d.print();
}
