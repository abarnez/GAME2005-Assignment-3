#include "Tank.h"
#include "glm/gtx/string_cast.hpp"
#include "Scene1.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"

Tank::Tank()
{
	TextureManager::Instance()->load("../Assets/textures/player_sprite.png", "Tank");

	auto size = TextureManager::Instance()->getTextureSize("Tank");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(TANK);
}


Tank::~Tank()
= default;

void Tank::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Tank
	TextureManager::Instance()->draw("Tank", x, y, Rotation, 255, true);
}


void Tank::update()
{
	if (doesUpdate) move();
}

void Tank::clean()
{

}

void Tank::addForce(glm::vec2 Amount)
{
	Force += Amount;
}

void Tank::move()
{
	float deltaTime = 1.0f / 60.0f;

	getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	getTransform()->position += getRigidBody()->velocity * deltaTime * pixelsPerMeter;

	//getRigidBody()->acceleration = glm::vec2(0.0f, Gravity);
	//getRigidBody()->acceleration += Force / getRigidBody()->mass;
	//getRigidBody()->velocity += getRigidBody()->acceleration;
	//getTransform()->position += getRigidBody()->velocity * deltaTime;

	//Force = glm::vec2(0.0f, 0.0f);
	//getRigidBody()->velocity *= 0.9f;
}

