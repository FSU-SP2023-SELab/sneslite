#include "../src/ppu/Ppu.hpp"
#include "../src/cpu/Bus.h"

#include <string>
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

bool test_ppu(std::string file, sneslite::Bus bus)
{
    // initialize SFML and create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "TestROM");

    sf::Texture texture;
    sf::Sprite sprite;

    auto& ppu_frame = bus.ppu.p_f;
    auto tile_frame = ppu_frame->show_tile(bus.cartridge.get_char_rom(), 1, 0);

    texture.create(8, 8);
    texture.update(tile_frame.data(), 8, 8, 0, 0);

    sprite.setTexture(texture);
    sprite.setPosition(0, 0);

    while (window.isOpen())
    {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            else if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }

        // clear the window and draw the sprite
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return true;
}