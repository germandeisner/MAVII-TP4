#ifndef RAGDOLL_H
#define RAGDOLL_H
#pragma once
#include <Box2D/Box2D.h>
#include "Box2DHelper.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>
#include <stdlib.h>


using namespace sf; // Espacio de nombres para la biblioteca SFML



class Ragdoll
{
private:	
	//partes del cuerpo
	b2Body* m_Body;
	b2Body* m_Head;
	b2Body* m_RightArm;
	b2Body* m_LeftArm;
	b2Body* m_RightLeg;
	b2Body* m_LeftLeg;

	//Conexiones de las partes del cuerpo
	b2RevoluteJoint* m_NeckJoint;
	b2RevoluteJoint* m_RightShoulderJoint;
	b2RevoluteJoint* m_LeftShoulderJoint;
	b2RevoluteJoint* m_RightHipJoint;
	b2RevoluteJoint* m_LeftHipJoint;

	// Formas para renderizar
	sf::RectangleShape m_BodyShape;
	sf::CircleShape m_HeadShape;
	sf::RectangleShape m_RightArmShape;
	sf::RectangleShape m_LeftArmShape;
	sf::RectangleShape m_RightLegShape;
	sf::RectangleShape m_LeftLegShape;

	b2World* m_World;
	//Conversion de escala
	float conversion = 10;  //Ajusta el tamaño

public:
	Ragdoll();
	~Ragdoll();
	void Crear(b2World* world, const b2Vec2& position);
	void AplicarImpulso(const b2Vec2& impulso);
	void Actualizar();
	void Dibujar(sf::RenderWindow& wnd);
	
};

#endif