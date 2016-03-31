#include <iostream>
#include <string>
#include <bitset>

int main (){
  std::bitset<8> test(std::string("10101010"));
  std::cout << test.count() << std::endl;
}
