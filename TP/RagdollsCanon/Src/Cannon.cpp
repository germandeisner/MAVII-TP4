#include "Cannon.h"
#include <cmath>

Cannon::Cannon(b2World& world)
    : world_(world),
    angle_(0.0f),
    power_(0.0f),
    maxPower_(250.0f),
    position_(0.0f, 95.0f) {
    shape_.setSize(sf::Vector2f(30.0f, 10.0f));
    shape_.setFillColor(sf::Color::Red);
    shape_.setOrigin(0.0f, 5.0f);
    shape_.setPosition(position_);
}

void Cannon::handleInput(RagdollManager& ragdollManager) {

    b2Vec2 cannonPos(position_.x+(cos(angle_)*30.0f), (position_.y)-(sin(angle_)*30.0f));
    ragdollManager.createRagdoll(cannonPos, b2Vec2(power_ * (cos(angle_)*30.0f), power_ * -(sin(angle_)*30.0f)));
    
}

void Cannon::update(const sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    float dx = mousePos.x - position_.x;
    float dy = position_.y - mousePos.y+600;
    angle_ = std::atan2(dy, dx);
    float distance = std::sqrt(dx * dx + dy * dy);
    power_ = std::min(distance / 500.0f * maxPower_, maxPower_);
    shape_.setRotation(-angle_ * 180.0f / b2_pi);
}

void Cannon::render(sf::RenderWindow& window) {
    window.draw(shape_);
}