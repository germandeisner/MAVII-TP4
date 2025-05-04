#pragma once
#ifndef CANNON_H
#define CANNON_H
#include <Box2D/Box2D.h>
#include "Box2DHelper.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <stdlib.h>
#include "RagdollManager.h"
using namespace sf; // Espacio de nombres para la biblioteca SFML



class Cannon {
public:
    Cannon(b2World& world);
    void handleInput(RagdollManager& ragdollManager);
    void update(const sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

private:
    b2World& world_;
    sf::RectangleShape shape_;
    float angle_;
    float power_;
    const float maxPower_;
    const sf::Vector2f position_;
};

#endif // CANNON_H