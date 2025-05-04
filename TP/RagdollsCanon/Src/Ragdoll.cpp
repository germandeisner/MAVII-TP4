#include "Ragdoll.h"
#include <iostream>

Ragdoll::Ragdoll() : m_Body(nullptr), m_Head(nullptr), m_RightArm(nullptr), m_LeftArm(nullptr),
m_RightLeg(nullptr), m_LeftLeg(nullptr), m_NeckJoint(nullptr),
m_RightShoulderJoint(nullptr), m_LeftShoulderJoint(nullptr),
m_RightHipJoint(nullptr), m_LeftHipJoint(nullptr), m_World(nullptr)
{
}

void Ragdoll::Crear(b2World* world, const b2Vec2& position)
{
    // Definicion cuerpo
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = false;

    // Seteado inicial de posiciones
    // Torso   
    m_Body = world->CreateBody(&bodyDef);
    m_Body->SetTransform(position,0.0f);
    
    // Cabeza
    m_Head = world->CreateBody(&bodyDef);
    m_Head->SetTransform(position+b2Vec2(0.0f,7.0F), 0.0f);

    // Brazo derecho
    m_RightArm = world->CreateBody(&bodyDef);
    m_RightArm->SetTransform(position + b2Vec2(-4.5f, 0.0F), 0.0f);

    // Brazo izquierdo
    m_LeftArm = world->CreateBody(&bodyDef);
    m_LeftArm->SetTransform(position + b2Vec2(4.5f, 0.0F), 0.0f);

    // Pierna derecha
    m_RightLeg = world->CreateBody(&bodyDef);
    m_RightLeg->SetTransform(position + b2Vec2(-1.5f, 10.0F), 0.0f);

    // Pierna izquierda
    m_LeftLeg = world->CreateBody(&bodyDef);
    m_LeftLeg->SetTransform(position + b2Vec2(1.5f, 10.0F), 0.0f);

    // Fixture
    b2PolygonShape bodyShape;
    b2PolygonShape limbShape;
    b2CircleShape headShape;

    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f; 
    fixtureDef.restitution = 0.2f;

    // Torso
    bodyShape.SetAsBox(3.0f, 5.0f);
    fixtureDef.shape = &bodyShape;
    m_Body->CreateFixture(&fixtureDef);

    // Cabeza
    headShape.m_radius = 2.0f;
    fixtureDef.shape = &headShape;
    m_Head->CreateFixture(&fixtureDef);

    // Brazos
    limbShape.SetAsBox(1.5f, 4.0f);
    fixtureDef.shape = &limbShape;
    m_RightArm->CreateFixture(&fixtureDef);
    m_LeftArm->CreateFixture(&fixtureDef);

    // Piernas
    limbShape.SetAsBox(1.5f, 5.0f);
    fixtureDef.shape = &limbShape;
    m_RightLeg->CreateFixture(&fixtureDef);
    m_LeftLeg->CreateFixture(&fixtureDef);

    // Joints 
    b2RevoluteJointDef jointDef;
    jointDef.lowerAngle = -0.4f * b2_pi;
    jointDef.upperAngle = 0.4f * b2_pi;
    jointDef.enableLimit = true;

    // Cuello
    jointDef.bodyA = m_Body;
    jointDef.bodyB = m_Head;
    jointDef.localAnchorA.Set(0.0f, 5.0f);
    jointDef.localAnchorB.Set(0.0f, -2.0f);
    m_NeckJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Hombro derecho
    jointDef.bodyA = m_Body;
    jointDef.bodyB = m_RightArm;
    jointDef.localAnchorA.Set(3.0f, 4.0f);
    jointDef.localAnchorB.Set(0.0f, 4.0f);
    m_RightShoulderJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Hombro izquierdo
    jointDef.bodyA = m_Body;
    jointDef.bodyB = m_LeftArm;
    jointDef.localAnchorA.Set(-3.0f, 4.0f);
    jointDef.localAnchorB.Set(0.0f, 4.0f);
    m_LeftShoulderJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Cadera derecha
    jointDef.bodyA = m_Body;
    jointDef.bodyB = m_RightLeg;
    jointDef.localAnchorA.Set(1.5f, -5.0f);
    jointDef.localAnchorB.Set(0.0f, 5.0f);
    m_RightHipJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Cadera izquierda
    jointDef.bodyA = m_Body;
    jointDef.bodyB = m_LeftLeg;
    jointDef.localAnchorA.Set(-1.5f, -5.0f);
    jointDef.localAnchorB.Set(0.0f, 5.0f);
    m_LeftHipJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Formas
    m_BodyShape.setSize(sf::Vector2f(6.0f, 10.0f));
    m_HeadShape.setRadius(2.0f);
    m_RightArmShape.setSize(sf::Vector2f(3.0f, 8.0f));
    m_LeftArmShape.setSize(sf::Vector2f(3.0f, 8.0f));
    m_RightLegShape.setSize(sf::Vector2f(3.0f, 10.0f));
    m_LeftLegShape.setSize(sf::Vector2f(3.0f, 10.0f));

    // Seteo origins
    m_BodyShape.setOrigin(3.0f, 5.0f);
    m_HeadShape.setOrigin(2.0f, 2.0f);
    m_RightArmShape.setOrigin(1.5f, 4.0f);
    m_LeftArmShape.setOrigin(1.5f, 4.0f);
    m_RightLegShape.setOrigin(1.5f, 5.0f);
    m_LeftLegShape.setOrigin(1.5f, 5.0f);

    // Seteo Colores
    m_BodyShape.setFillColor(sf::Color::Blue);
    m_HeadShape.setFillColor(sf::Color::Red);
    m_RightArmShape.setFillColor(sf::Color::Green);
    m_LeftArmShape.setFillColor(sf::Color::Green);
    m_RightLegShape.setFillColor(sf::Color::Yellow);
    m_LeftLegShape.setFillColor(sf::Color::Yellow);
}

Ragdoll::~Ragdoll()
{
    if (m_World) {
        if (m_NeckJoint) m_World->DestroyJoint(m_NeckJoint);
        if (m_RightShoulderJoint) m_World->DestroyJoint(m_RightShoulderJoint);
        if (m_LeftShoulderJoint) m_World->DestroyJoint(m_LeftShoulderJoint);
        if (m_RightHipJoint) m_World->DestroyJoint(m_RightHipJoint);
        if (m_LeftHipJoint) m_World->DestroyJoint(m_LeftHipJoint);
        if (m_Body) m_World->DestroyBody(m_Body);
        if (m_Head) m_World->DestroyBody(m_Head);
        if (m_RightArm) m_World->DestroyBody(m_RightArm);
        if (m_LeftArm) m_World->DestroyBody(m_LeftArm);
        if (m_RightLeg) m_World->DestroyBody(m_RightLeg);
        if (m_LeftLeg) m_World->DestroyBody(m_LeftLeg);
    }
}

void Ragdoll::AplicarImpulso(const b2Vec2& impulso)
{
    if (m_Body)
    {
        m_Body->ApplyLinearImpulseToCenter(impulso, true);
    }
}

void Ragdoll::Actualizar()
{    
    m_BodyShape.setPosition((m_Body->GetPosition().x), (m_Body->GetPosition().y));
    m_BodyShape.setRotation(m_Body->GetAngle() * 180.0f / b2_pi);

    m_HeadShape.setPosition((m_Head->GetPosition().x), (m_Head->GetPosition().y));
    m_HeadShape.setRotation(m_Head->GetAngle() * 180.0f / b2_pi);

    m_RightArmShape.setPosition((m_RightArm->GetPosition().x), (m_RightArm->GetPosition().y));
    m_RightArmShape.setRotation(m_RightArm->GetAngle() * 180.0f / b2_pi);

    m_LeftArmShape.setPosition((m_LeftArm->GetPosition().x), (m_LeftArm->GetPosition().y));
    m_LeftArmShape.setRotation(m_LeftArm->GetAngle() * 180.0f / b2_pi);

    m_RightLegShape.setPosition((m_RightLeg->GetPosition().x), (m_RightLeg->GetPosition().y));
    m_RightLegShape.setRotation(m_RightLeg->GetAngle() * 180.0f / b2_pi);

    m_LeftLegShape.setPosition((m_LeftLeg->GetPosition().x), (m_LeftLeg->GetPosition().y));
    m_LeftLegShape.setRotation(m_LeftLeg->GetAngle() * 180.0f / b2_pi);
}

void Ragdoll::Dibujar(sf::RenderWindow& window)
{
    Actualizar();
    window.draw(m_BodyShape);
    window.draw(m_HeadShape);
    window.draw(m_RightArmShape);
    window.draw(m_LeftArmShape);
    window.draw(m_RightLegShape);
    window.draw(m_LeftLegShape);
}