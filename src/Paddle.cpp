#include "Paddle.h"
#include "glm/gtx/string_cast.hpp"
#include "Scene1.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"

Paddle::Paddle()
{
	TextureManager::Instance()->load("../Assets/textures/paddle.png", "Paddle");

	auto size = TextureManager::Instance()->getTextureSize("Paddle");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PADDLE);
}


Paddle::~Paddle()
= default;

void Paddle::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Paddle
	TextureManager::Instance()->draw("Paddle", x, y, Rotation, 255, true);
}


void Paddle::update()
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

void Paddle::clean()
{

}

void Paddle::addForce(glm::vec2 Amount)
{
	Force += Amount;
}

/*void Paddle::move()
{
	float deltaTime = 1.0f / 60.0f;

	getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	getTransform()->position += getRigidBody()->velocity * deltaTime * pixelsPerMeter;

}*/

void Paddle::move(float dir) {
	getRigidBody()->velocity.x = dir * ACCELERATION;
}

