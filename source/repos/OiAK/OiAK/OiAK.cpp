#include <iostream>
#include "BigInt.h"

int main(){
    BigInt b = BigInt("233459214899875352");
    BigInt c = BigInt("12576543456787654");
    BigInt d = b * c;
    std::cout << "Wartosci: " << std::endl;
    b.print();
    c.print();
    d.print();
}
