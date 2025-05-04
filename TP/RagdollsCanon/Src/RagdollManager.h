#pragma once
#ifndef RAGDOLL_MANAGER_H
#define RAGDOLL_MANAGER_H

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <vector>
#include <memory>
#include "Ragdoll.h"

class RagdollManager {
public:
    RagdollManager(b2World& world);
    void createRagdoll(const b2Vec2& position, const b2Vec2& impulse);
    void render(sf::RenderWindow& window);

private:
    b2World& world_;
    std::vector<std::unique_ptr<Ragdoll>> ragdolls_;
};

#endif // RAGDOLL_MANAGER_H