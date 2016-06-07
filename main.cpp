#include<iostream>
#include<cmath>
#include<list>
#include<vector>
#include<string>
#include<cstdint>

#include<SFML/Audio.hpp>
#include<SFML/Graphics.hpp>

static const uint32_t xres = 800;
static const uint32_t yres = 600;
static const uint32_t fps  = 30;

bool key_states[sf::Keyboard::KeyCount] = {false};

sf::Font font;
sf::Texture bbuffer_t;
sf::Sprite bbuffer_s;
sf::Image bbuffer_i;

std::vector<sf::Music> music;
std::vector<sf::SoundBuffer> snd_buf;
std::vector<sf::Sound> snd;
std::vector<sf::Text> txt;
sf::RenderWindow window;

void game_init();
void game_main();
void buffer_flip();
void pset(const uint32_t, const uint32_t, const sf::Color&);

int main(int argc, char **argv) {
    std::cout<<"Hello World"<<std::endl;
    window.create(sf::VideoMode(xres,yres), "Engine Base");

    if(window.isOpen()) {
        game_init();
    }

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::KeyPressed) {
                key_states[event.key.code] = true;
            }
            else if(event.type == sf::Event::KeyReleased) {
                key_states[event.key.code] = true;
            }
            //Closed,                 ///< The window requested to be closed (no data)
            //Resized,                ///< The window was resized (data in event.size)
            //LostFocus,              ///< The window lost the focus (no data)
            //GainedFocus,            ///< The window gained the focus (no data)
            //KeyPressed,             ///< A key was pressed (data in event.key)
            //KeyReleased,            ///< A key was released (data in event.key)
            //MouseWheelScrolled,     ///< The mouse wheel was scrolled (data in event.mouseWheelScroll)
            //MouseButtonPressed,     ///< A mouse button was pressed (data in event.mouseButton)
            //MouseButtonReleased,    ///< A mouse button was released (data in event.mouseButton)
            //MouseMoved,             ///< The mouse cursor moved (data in event.mouseMove)
            //MouseEntered,           ///< The mouse cursor entered the area of the window (no data)
            //MouseLeft,              ///< The mouse cursor left the area of the window (no data)
        }

        window.clear();
        game_main();
        window.display();

    }
}

uint8_t color_shift;

void game_init() {
    //window.setVerticalSyncEnabled(true); //This option is included in the default context, apparently
    window.setKeyRepeatEnabled(false);
    window.setFramerateLimit(30);
    bbuffer_t.create(xres,yres);
    bbuffer_s.setTexture(bbuffer_t);
    bbuffer_i.create(xres,yres);
    color_shift = 0;
    font.loadFromFile("hack-r.ttf");
}

void game_main() {
    for(int x=0;x<xres;++x) {
        for(int y=0;y<yres;++y) {
            //pset(x,y,sf::Color(x+color_shift,y+color_shift,0));
            bbuffer_i.setPixel(x,y,sf::Color(x+color_shift,y+color_shift,0));
        }
    }
    color_shift++;
    color_shift %= 255;
    buffer_flip();
}

void buffer_flip() {
    //bbuffer_t.update(reinterpret_cast<uint8_t *>(&buffer_raw[0]));
    bbuffer_t.loadFromImage(bbuffer_i);
    window.draw(bbuffer_s);
}
