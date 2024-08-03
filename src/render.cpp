#include "render.hpp"

void Render::renderConstraint(sf::RenderWindow &window)
{
    sf::CircleShape constraint;
    constraint.setRadius(300.0f);
    constraint.setOrigin(constraint.getRadius(), constraint.getRadius());
    constraint.setOutlineColor(sf::Color::Red);
    constraint.setFillColor(sf::Color::Black);
    constraint.setOutlineThickness(5);
    constraint.setPosition(640.0f, 360.0f);
    window.draw(constraint);
}