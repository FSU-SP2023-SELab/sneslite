#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "cpu/Bus.h"
#include "tests/test_rom.hpp"

#define FRAMERATE   60
#define WIDTH       256
#define HEIGHT      240

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SNESlite");
    window.setFramerateLimit(FRAMERATE);


    // Build rom
    std::string rom  = "./build/romtest.nes";
    {
        std::ofstream output(rom, std::ios::binary);
        output.write(reinterpret_cast<const char*>(&ROM_TEST), sizeof(ROM_TEST));
    }

    // Create system
    sneslite::Bus nes;
    nes.initialize(rom);

    // Frame variables
    std::vector<uint8_t> frame_data;
    uint8_t* pixels;
    sf::Sprite sprite;
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);

    while (window.isOpen()) {

        sf::Event event;

        // Clock system once
        nes.clock();

        // Prepare frame
        const uint8_t* pixels = nes.ppu.p_f->get_frame_data().data();
        texture.update(pixels, WIDTH, HEIGHT, 0, 0);
        sprite.setTexture(texture);
        sprite.setPosition(0, 0);

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite);
        window.display();
        delete pixels;
    }
    return 0;
}