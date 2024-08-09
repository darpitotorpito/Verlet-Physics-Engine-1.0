#include "render.hpp"

using namespace std;

const float update_rate = 0.0001f;

int main()
{
    // Create render window and set attributes
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Verlet Physics Engine 1.0");
    window.setFramerateLimit(60);

    vector<VerletObject> objects;
    objects.emplace_back(sf::Vector2f(740.0f, 360.0f), 20.0f, sf::Color::White, 1.0f);

    Engine engine;
    Render render;

    sf::Clock clock;
    float accumulator = 0.0f;
    float total_time = 0;
    bool blue_circle = false;

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
        if (!freeze_frame)
        {
            total_time += dt;
            accumulator += dt;

            if (total_time >= 5.0f && !blue_circle)
            {
                blue_circle = true;
                objects.emplace_back(sf::Vector2f(740.0f, 360.0f), 20.0f, sf::Color::Blue, 1.0f);
            }

            if (accumulator >= update_rate)
            {
                engine.setGravity(sf::Vector2f{0.0f, 98.0f});
                engine.update(dt, objects);
                accumulator -= update_rate;
            }

            // for (VerletObject &obj : objects)
            // {
            //     cout << objects.size() << " OBJECTS // ";
            //     cout << "Delta Time: " << dt;
            //     cout << " // Total Time: " << total_time;
            //     cout << " // Current Pos: x - " << obj.current_position_.x << " y - " << obj.current_position_.y << endl;
            // }

            if (blue_circle)
            {
                const float dx = objects.at(0).current_position_.x - objects.at(1).current_position_.x;
                const float dy = objects.at(0).current_position_.y - objects.at(1).current_position_.y;
                const float abs_distance = sqrt(dx * dx + dy * dy);
                cout << "CURRENT TIME: " << total_time << " // CURRENT ABSOLUTE DISTANCE: " << abs_distance << "\n";
            }
        }

        // Render objects
        window.clear();
        render.renderConstraint(window);
        for (VerletObject &obj : objects)
        {
            obj.drawObject(window);
        }
        window.display();
    }
}
