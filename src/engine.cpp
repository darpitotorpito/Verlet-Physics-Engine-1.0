#include "engine.hpp"

// ===== VERLET OBJECT ===== //
VerletObject::VerletObject() // Default Constructor
{
    current_position_ = sf::Vector2f(0.0f, 0.0f);
    previous_position_ = sf::Vector2f(0.0f, 0.0f);
    acceleration_ = sf::Vector2f(0.0f, 0.0f);
    object_.setRadius(10.0f);
    object_.setFillColor(sf::Color::White);
    object_.setOrigin(10.0f, 10.0f);
}
VerletObject::VerletObject(sf::Vector2f initial_position, float radius, sf::Color color) // Parameterized constructor
{
    current_position_ = initial_position;
    previous_position_ = initial_position;
    acceleration_ = sf::Vector2f(0.0f, 0.0f);
    object_.setRadius(radius);
    object_.setFillColor(color);
    object_.setOrigin(radius, radius);
}
void VerletObject::drawObject(sf::RenderWindow& window) // Draw the object to be rendered onto the screen
{
    object_.setPosition(current_position_);
    window.draw(object_);
}
void VerletObject::setPosition(sf::Vector2f set_position)
{
    current_position_ = set_position;
    previous_position_ = set_position;
}
void VerletObject::updatePosition(float dt)
{
    const sf::Vector2f velocity = current_position_ - previous_position_; // Determine current velocity
    previous_position_ = current_position_;
    current_position_ = previous_position_ + velocity + acceleration_ * dt * dt;
    acceleration_ = {};
    cout << "CURRENT VELOCITY - " << sqrt(velocity.x * velocity.x + velocity.y * velocity.y) << endl;
}
void VerletObject::accelerate(sf::Vector2f acceleration)
{
    acceleration_ += acceleration;
}

// ===== ENGINE ===== //
void Engine::update(float dt, vector<VerletObject> &objects) // Update the engine for the next frame
{
    for (VerletObject &obj: objects)
    {
        applyGravity(obj);
        updatePositions(dt, obj);
    }
}
void Engine::updatePositions(float dt, VerletObject &obj) // Update the position of each Verlet Object
{
    obj.updatePosition(dt);
}
void Engine::applyGravity(VerletObject &obj) // Update the gravity of each Verlet Object
{
    obj.accelerate(gravity);
}
void Engine::setGravity(sf::Vector2f set_gravity)
{
    gravity = set_gravity;
}
// void Engine::applyConstraints(VerletObject obj) // Constrain each Verlet Object
// {

// }