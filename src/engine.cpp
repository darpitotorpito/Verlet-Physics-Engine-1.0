#include "engine.hpp"


bool freeze_frame = false;

// ===== VECTOR - 2D DOUBLE ===== //
Vector2d::Vector2d()
{
    x = 0.0;
    y = 0.0;
}

// ===== VERLET OBJECT ===== //
VerletObject::VerletObject() // Default Constructor
{
    current_position_ = sf::Vector2f(0.0f, 0.0f);
    previous_position_ = sf::Vector2f(0.0f, 0.0f);
    acceleration_ = sf::Vector2f(0.0f, 0.0f);
    object_.setRadius(10.0f);
    radius_ = 10.0f;
    object_.setFillColor(sf::Color::White);
    object_.setOrigin(10.0f, 10.0f);
}
VerletObject::VerletObject(sf::Vector2f initial_position, float radius, sf::Color color, float mass) // Parameterized constructor
{
    current_position_ = initial_position;
    previous_position_ = initial_position;
    acceleration_ = sf::Vector2f(0.0f, 0.0f);
    object_.setRadius(radius);
    radius_ = radius;
    object_.setFillColor(color);
    object_.setOrigin(radius, radius);
    mass_ = mass;
}
void VerletObject::drawObject(sf::RenderWindow &window) // Draw the object to be rendered onto the screen
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
    // cout << "CURRENT VELOCITY - " << sqrt(velocity.x * velocity.x + velocity.y * velocity.y) << endl;
}
void VerletObject::accelerate(sf::Vector2f acceleration)
{
    acceleration_ += acceleration;
}

// ===== ENGINE ===== //
void Engine::update(float dt, vector<VerletObject> &objects) // Update the engine for the next frame
{
    for (VerletObject &obj : objects)
    {
        applyGravity(obj);
        applyElasticConstraints(obj);
        updatePositions(dt, obj);
    }
    applyCollisions(dt, objects);
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
void Engine::applyInelasticConstraints(VerletObject &obj) // Constrain each Verlet Object
{
    const sf::Vector2f constraint_position = {640.0f, 360.0f};
    const float constraint_radius = 300.0f;

    const sf::Vector2f to_obj_distance = obj.current_position_ - constraint_position;
    const float dx = constraint_position.x - obj.current_position_.x;
    const float dy = constraint_position.y - obj.current_position_.y;
    const float abs_distance = sqrt(dx * dx + dy * dy);

    if (abs_distance > constraint_radius - obj.radius_)
    {
        // Calculate normal position and constraint limits
        const sf::Vector2f normalize = to_obj_distance / abs_distance;
        obj.current_position_ = constraint_position + normalize * (constraint_radius - obj.radius_);
    }
}
void Engine::applyElasticConstraints(VerletObject &obj)
{
    const sf::Vector2f constraint_position = {640.0f, 360.0f};
    const float constraint_radius = 300.0f;

    const sf::Vector2f to_obj_distance = obj.current_position_ - constraint_position;
    const float dx = constraint_position.x - obj.current_position_.x;
    const float dy = constraint_position.y - obj.current_position_.y;
    const float abs_distance = sqrt(dx * dx + dy * dy);

    if (abs_distance > constraint_radius - obj.radius_)
    {
        // Calculate normal position and constraint limits
        const sf::Vector2f normalize = to_obj_distance / abs_distance;
        obj.current_position_ = constraint_position + normalize * (constraint_radius - obj.radius_);

        // Reflect velocity for elastic collision
        sf::Vector2f velocity = obj.current_position_ - obj.previous_position_;
        float dot_product = velocity.x * normalize.x + velocity.y * normalize.y;
        sf::Vector2f reflection = velocity - 2.0f * dot_product * normalize;
        obj.previous_position_ = obj.current_position_ - reflection;
    }
}
void Engine::applyCollisions(float dt, vector<VerletObject> &objects)
{
    for (VerletObject &obj1 : objects)
    {
        for (VerletObject &obj2 : objects)
        {
            if (&obj1 != &obj2)
            {
                const sf::Vector2f distance = obj1.current_position_ - obj2.current_position_;
                const float dx = obj1.current_position_.x - obj2.current_position_.x;
                const float dy = obj1.current_position_.y - obj2.current_position_.y;
                const float abs_distance = sqrt(dx * dx + dy * dy);

                if (abs_distance < obj1.radius_ + obj2.radius_)
                {
                    cout << "ABS DISTANCE: " << abs_distance << " // OBJ RADIUS: " << obj1.radius_ << " // COLLISSION DETECTED PROGRAM WILL TERMINATE \n";
                    freeze_frame = true;
                }

                if (freeze_frame == true)
                {
                    char input;
                    cout << "Enter 'y' to continue \n";
                    cin >> input;
                    if (input == 'y')
                    {
                        freeze_frame = false;
                    }            
                }

                const sf::Vector2f velocity_1 = obj1.current_position_ - obj2.previous_position_;
                const sf::Vector2f velocity_2 = obj2.current_position_ - obj2.previous_position_;

                const float velocity_x = velocity_1.x + velocity_2.x;
                const float velocity_y = velocity_1.y + velocity_2.y;

                
            }
        }
    }
}