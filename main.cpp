#include <SFML/Graphics.hpp>
#include <chrono>
#include <cstring>
#include <functional>
#include <iostream>
#include <random>

#include "GameOfLife.h"

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define DIV (50)

#define FONT ("/usr/share/texmf/fonts/opentype/public/lm/lmsans17-regular.otf")

void draw_welcome_screen(sf::RenderWindow *window);
void draw_gol(sf::RenderWindow *window, GameOfLife *gol);
void draw_grid(sf::RenderWindow *window);

int main(int argc, char *argv[]) {
        sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                                "Game of Life");
        auto seed = std::chrono::high_resolution_clock::now()
                        .time_since_epoch()
                        .count();
        auto rand_gen = std::bind(
            std::uniform_int_distribution<int>(DIV / 5, DIV*DIV - (DIV / 5)),
            std::mt19937(seed));
        GameOfLife gol(rand_gen(), DIV, DIV);
        bool welcome_screen = true;
        sf::Clock clock;

        while (window.isOpen()) {

                sf::Time elapsed = clock.getElapsedTime();

                sf::Event event;
                while (window.pollEvent(event)) {
                        switch (event.type) {
                        case sf::Event::Closed:
                                window.close();
                                break;
                        case sf::Event::KeyPressed:
                                switch (event.key.code) {
                                case sf::Keyboard::Return:
                                        welcome_screen = false;
                                        break;
                                case sf::Keyboard::Escape:
                                        if (!welcome_screen) {
                                                welcome_screen = true;
                                        }
                                        break;
                                case sf::Keyboard::R:
                                        if (!welcome_screen) {
                                                gol = GameOfLife(rand_gen(),
                                                                 DIV, DIV);
                                        }
                                        break;
                                default:
                                        break;
                                }
                                break;
                        default:
                                break;
                        }
                }

                window.clear();

                if (welcome_screen) {
                        draw_welcome_screen(&window);
                        clock.restart();
                } else {
                        draw_gol(&window, &gol);
                        if (elapsed.asMilliseconds() > 233 &&
                            elapsed.asMilliseconds() < 275) {
                                gol.step();
                                clock.restart();
                        }
                }
                window.display();
        }

        return 0;
}

void draw_welcome_screen(sf::RenderWindow *window) {
        sf::Text text;
        sf::Font font;

        if (!font.loadFromFile(FONT)) {
                std::cerr << "Error: Could not load font file: "
                          << strerror(errno) << std::endl;
                exit(-1);
        }

        text.setFont(font);
        text.setString("Welcome to Conway's Game of Life");

        window->draw(text);
}

void draw_gol(sf::RenderWindow *window, GameOfLife *gol) {
        sf::Vector2u size = window->getSize();
        std::vector<std::vector<bool>> board = gol->get_board();

        draw_grid(window);

        for (int y = 0; y < DIV; y++) {
                for (int x = 0; x < DIV; x++) {
                        if (board[x][y]) {
                                int screen_x, screen_y;
                                sf::RectangleShape rect(
                                    sf::Vector2f(size.x / DIV, size.y / DIV));

                                screen_x = x * (size.x / DIV);
                                screen_y = y * (size.y / DIV);

                                rect.setFillColor(sf::Color::White);
                                rect.setPosition(
                                    sf::Vector2f(screen_x, screen_y));
                                window->draw(rect);
                        }
                }
        }
}

void draw_grid(sf::RenderWindow *window) {
        sf::Vector2u size = window->getSize();

        // Draw vertical lines in grid
        for (unsigned int col = size.x / DIV; col < size.x;
             col += size.x / DIV) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(col, 0)),
                    sf::Vertex(sf::Vector2f(col, size.y)),
                };
                window->draw(line, 2, sf::Lines);
        }

        // Draw horizontal lines in grid
        for (unsigned int row = size.y / DIV; row < size.y;
             row += size.y / DIV) {
                sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(0, row)),
                    sf::Vertex(sf::Vector2f(size.x, row)),
                };
                window->draw(line, 2, sf::Lines);
        }

        // Draw border
        sf::Vertex right[] = {
            sf::Vertex(sf::Vector2f(1, 0)), sf::Vertex(sf::Vector2f(1, size.y)),
        };

        sf::Vertex left[] = {
            sf::Vertex(sf::Vector2f(size.x, 0)),
            sf::Vertex(sf::Vector2f(size.x, size.y)),
        };

        sf::Vertex top[] = {
            sf::Vertex(sf::Vector2f(1, 1)), sf::Vertex(sf::Vector2f(size.x, 1)),
        };

        sf::Vertex bottom[] = {
            sf::Vertex(sf::Vector2f(1, size.y)),
            sf::Vertex(sf::Vector2f(size.x, size.y)),
        };

        window->draw(right, 2, sf::Lines);
        window->draw(left, 2, sf::Lines);
        window->draw(top, 2, sf::Lines);
        window->draw(bottom, 2, sf::Lines);
}
