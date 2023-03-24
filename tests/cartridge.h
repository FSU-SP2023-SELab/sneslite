#include "../src/cartridge/Cartridge.hpp"

#include<iostream>
#include<string>

bool test_cartridge(std::string file)
{
    std::cout << "Testing cartridge read..." << std::endl;

    sneslite::Cartridge test_cart;
    return test_cart.load_dump_file(file);
}