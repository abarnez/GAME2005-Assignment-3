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

	glm::vec2 pos[10];
	float w = getWidth(), h = getHeight();
	pos[0] = glm::vec2(x - w / 2, y);
	pos[1] = glm::vec2(x + w / 2, y);
	pos[2] = glm::vec2(x - w / 2, y + h / 2);
	pos[3] = glm::vec2(x + w / 2, y + h / 2);
	// Top
	Util::DrawLine(pos[0], pos[1], glm::vec4(0, 1, 0, 1));
	// Bottom
	Util::DrawLine(pos[2], pos[3], glm::vec4(0, 1, 0, 1));
	// Left
	Util::DrawLine(pos[0], pos[2], glm::vec4(0, 1, 0, 1));
	// Right
	Util::DrawLine(pos[1], pos[3], glm::vec4(0, 1, 0, 1));

	pos[4] = glm::vec2(x - w / 4, y - 10);
	pos[5] = glm::vec2(x + w / 5, y - 10);
	pos[6] = glm::vec2(x - w / 4, y);
	pos[7] = glm::vec2(x + w / 5, y);

	// Top
	Util::DrawLine(pos[4], pos[5], glm::vec4(0, 1, 0, 1));
	// Left
	Util::DrawLine(pos[4], pos[6], glm::vec4(0, 1, 0, 1));
	// Right
	Util::DrawLine(pos[5], pos[7], glm::vec4(0, 1, 0, 1));
}


void Tank::update()
{
	float deltaTime = 1.0f / 60.0f;
	getTransform()->position += getRigidBody()->velocity * deltaTime;
	lastX = getTransform()->position.x;
	lastY = getTransform()->position.y;

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
}

void Tank::clean()
{

}

void Tank::move(float dir) {
	getRigidBody()->velocity.x = dir * ACCELERATION;
}

void Tank::freeze()
{
	getRigidBody()->velocity.x = 0;
	getRigidBody()->acceleration.x = 0;
	m_direction.x = 0;
}
