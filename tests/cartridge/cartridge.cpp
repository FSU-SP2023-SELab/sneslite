#include "../../src/cartridge/cartridge.hpp"

#include<iostream>
#include<string>

int main()
{
    std::cout << "Testing cartridge read..." << std::endl;
    sneslite::cartridge test_cart;
    std::string file;

    std::cout << "Enter local file ROM name: ";
    std::cin >> file;

    if(!test_cart.load_dump_file(file))
    {
        std::cerr << "CARTRIDGE TEST: FAIL" << std::endl;
    }
    else
    {
        std::cerr << "CARTRIDGE TEST: PASS" << std::endl;
    }
}