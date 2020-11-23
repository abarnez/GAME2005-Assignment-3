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

	ACCELERATION = 200;
	m_direction = glm::vec2(0, 0);
}


Paddle::~Paddle()
= default;

void Paddle::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Paddle
	TextureManager::Instance()->draw("Paddle", x, y, 0, 255, true);

	float width = getWidth(), height = getHeight();
	glm::vec2 topLeft;
	topLeft = glm::vec2(x - width / 2.05, y - 30);
	glm::vec2 topRight;
	topRight = glm::vec2(x + width / 2.05, y - 30);


	//defined bottom right and left corners
	glm::vec2 bottomRight;
	bottomRight = topRight + glm::vec2(0.0f, 60.0f);
	glm::vec2 bottomLeft;
	bottomLeft = topLeft + glm::vec2(0.0f, 60.0f);
	
	Util::DrawLine(topLeft, topRight);

}


void Paddle::update()
{
	float deltaTime = 1.0f / 60.0f;
	getTransform()->position += getRigidBody()->velocity * deltaTime;

	if (getTransform()->position.x < getWidth() / 2)
	{
		getTransform()->position.x = getWidth() / 2;
		freeze();
	}
	else if (getTransform()->position.x > Config::SCREEN_WIDTH - getWidth() / 2)
	{
		getTransform()->position.x = Config::SCREEN_WIDTH - getWidth() / 2;
		freeze();
	}

	getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
}

void Paddle::clean()
{

}

void Paddle::move(float dir) {
	getRigidBody()->velocity.x = dir * ACCELERATION;
}

void Paddle::freeze()
{
	getRigidBody()->velocity.x = 0;
	getRigidBody()->acceleration.x = 0;
	m_direction.x = 0;
}

