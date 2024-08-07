#pragma once
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <SFML/Graphics.hpp>

extern bool freeze_frame;

using namespace std;

struct Vector2d
{
    double x;
    double y;

    Vector2d();
};

struct VerletObject
{
    sf::Vector2f current_position_; // The current position of the object
    sf::Vector2f previous_position_;     // The most recent previous position of the object
    sf::Vector2f acceleration_;     // The acceleration of the object
    sf::CircleShape object_;        // The shape of the object
    sf::Color color_;               // The color of the object
    float radius_; // The radius of the object

    VerletObject();                                                             // Default constructor
    VerletObject(sf::Vector2f initial_position, float radius, sf::Color color); // Parameterized constructor
    void drawObject(sf::RenderWindow &window);                                  // Draw the object to be rendered onto the screen
    void setPosition(sf::Vector2f set_position);                                // Set the current position of the object
    void updatePosition(float dt);                                              // Update position of the object based on frame time
    void accelerate(sf::Vector2f acceleration);                                 // Add acceleration to the object
};

class Engine
{
public:
    // Engine(); // Default constructor

    void update(float dt, vector<VerletObject> &objects); // Update the engine for the next frame
    void updatePositions(float dt, VerletObject &obj); // Update the position of each Verlet Object
    void applyGravity(VerletObject &obj); // Update the gravity of each Verlet Object
    void setGravity(sf::Vector2f set_gravity);
    void applyInelasticConstraints(VerletObject &obj);
    void applyElasticConstraints(VerletObject &obj);
    void applyCollisions(float dt, vector<VerletObject> &objects);

private:
    sf::Vector2f gravity = {0.0f, 0.0f};
};