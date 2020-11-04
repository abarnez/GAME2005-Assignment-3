#include "Bullet.h"
#include "glm/gtx/string_cast.hpp"
#include "Scene1.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"

Bullet::Bullet()
{
	TextureManager::Instance()->load("../Assets/textures/bullet.png", "Bullet");

	auto size = TextureManager::Instance()->getTextureSize("Bullet");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(BULLET);
}


Bullet::~Bullet()
= default;

void Bullet::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Bullet
	TextureManager::Instance()->draw("Bullet", x, y, Rotation, 255, true);
}


void Bullet::update()
{
	if (doesUpdate) move();
}

void Bullet::clean()
{

}

void Bullet::addForce(glm::vec2 Amount)
{
	Force += Amount;
}

void Bullet::move()
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
