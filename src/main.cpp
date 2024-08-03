#include <SFML/Graphics.hpp>
#include <iostream>
#include "engine.hpp"

using namespace std;

int main()
{
    // Create render window and set attributes
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Verlet Physics Engine 1.0");
    window.setFramerateLimit(60);

    vector<VerletObject> objects;
    objects.emplace_back(sf::Vector2f(740.0f, 360.0f), 20.0f, sf::Color::White);

    Engine engine;

    sf::Clock clock;
    float total_time = 0;
    // Enable window interactions
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) // Close window using window manager
            {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();
        engine.setGravity(sf::Vector2f{0.0f, 980.0f});
        engine.update(dt, objects);
        total_time += dt;

        for (VerletObject &obj : objects)
        {
            cout << objects.size() << " OBJECTS // "; 
            cout << "Delta Time: " << dt;
            cout << " // Total Time: " << total_time;
            cout << " // Current Pos: x - " << obj.current_position_.x << " y - " << obj.current_position_.y << endl;
        }
        // Render objects
        window.clear();
        for (VerletObject &obj : objects)
        {
            obj.drawObject(window);
        }
        window.display();
    }
}
