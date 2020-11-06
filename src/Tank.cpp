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
	ACCELERATION = 200;
	m_direction = glm::vec2(0, 0);
}


Tank::~Tank()
= default;

void Tank::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Tank
	TextureManager::Instance()->draw("Tank", x, y, 0, 255, true);
}


void Tank::update()
{
	if (getTransform()->position.x < getWidth() / 2)
	{
		getTransform()->position.x = getWidth() / 2;
		getRigidBody()->velocity.x = 0;
		getRigidBody()->acceleration.x = 0;
		m_direction.x = 1;
	}

	if (getTransform()->position.x > Config::SCREEN_WIDTH - getWidth() / 2)
	{
		getTransform()->position.x = Config::SCREEN_WIDTH - getWidth() / 2;
		getRigidBody()->velocity.x = 0;
		getRigidBody()->acceleration.x = 0;
		m_direction.x = -1;
	}

	float deltaTime = 1.0f / 60.0f;
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}

void Tank::clean()
{

}

/*void Tank::move()
{
	float deltaTime = 1.0f / 60.0f;

	getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	getTransform()->position += getRigidBody()->velocity * deltaTime * pixelsPerMeter;
	
}*/

void Tank::move(float dir) {
	getRigidBody()->velocity.x = dir * ACCELERATION;
}

