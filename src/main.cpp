#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "bus/Bus.hpp"
#include "../tests/test_rom.h"

#define FRAMERATE   60
#define WIDTH       256
#define HEIGHT      240
#define DEBUG       0

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SNESlite");
    window.setFramerateLimit(FRAMERATE);


    // Build rom
    std::string rom  = "build/romtest.nes";
    {
        std::ofstream output(rom, std::ios::binary);
        output.write(reinterpret_cast<const char*>(&ROM_TEST), sizeof(ROM_TEST));
    }

    // Write to debug file
    std::ofstream debug;
    if (DEBUG) debug.open("debug");

    // Create system
    sneslite::Bus nes;
    nes.initialize(rom);

    // Loop variables
    std::vector<uint8_t> frame_data;
    sf::Sprite sprite;
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);

    bool b_a, b_b, b_select, b_start, b_up, b_down, b_left, b_right = false;

    unsigned long frameCount = 0;

    while (window.isOpen()) {

        sf::Event event;

        // Clock system once
        nes.clock();

        if (DEBUG) debug << "Frame # " << frameCount << std::endl;

        // Handle Inputs

        // A
        b_a = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        nes.joypad.set_button_status(sneslite::JoyPadButton::BUTTON_A, b_a);

        // B
        b_b = sf::Keyboard::isKeyPressed(sf::Keyboard::LControl);
        nes.joypad.set_button_status(sneslite::JoyPadButton::BUTTON_B, b_b);

        // Select
        b_select = sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
        nes.joypad.set_button_status(sneslite::JoyPadButton::SELECT, b_select);

        // Start
        b_start = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        nes.joypad.set_button_status(sneslite::JoyPadButton::START, b_start);

        // Up and Down are mutually exclusive
        b_up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        b_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down) & !b_up;
        nes.joypad.set_button_status(sneslite::JoyPadButton::UP, b_up);
        nes.joypad.set_button_status(sneslite::JoyPadButton::DOWN, b_down);

        // Left and Right are mutually exclusive
        b_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        b_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Right) & !b_left;
        nes.joypad.set_button_status(sneslite::JoyPadButton::LEFT, b_left);
        nes.joypad.set_button_status(sneslite::JoyPadButton::RIGHT, b_right);
        
        // Prepare frame
        nes.ppu.render();
        const uint8_t* pixels = nes.ppu.get_frame_data().data();
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
        frameCount++;
    }
    return 0;
}