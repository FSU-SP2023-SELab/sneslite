#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "cpu/Bus.h"
#include "tests/test_rom.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SNESlite");

    // Create system
    sneslite::Bus nes;

    // Build rom
    std::string rom  = "./build/romtest.nes";
    {
        std::ofstream output(rom, std::ios::binary);
        output.write(reinterpret_cast<const char*>(&ROM_TEST), sizeof(ROM_TEST));
    }


    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
    return 0;
}