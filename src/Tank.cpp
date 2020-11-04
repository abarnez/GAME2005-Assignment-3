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
	if (getTransform()->position.x < 50)
		getTransform()->position.x = 50;

	if (getTransform()->position.x > 1050)
		getTransform()->position.x = 1050;

	//if (doesUpdate) move();

	const float deltaTime = 1.0f / 60.f;
	float magnitude = Util::magnitude(m_direction);

	if (magnitude > 0) {


		getRigidBody()->acceleration = Util::normalize(m_direction) * ACCELERATION;
	}
	else if (Util::magnitude(getRigidBody()->velocity) > 0) {

		getRigidBody()->acceleration = Util::normalize(getRigidBody()->velocity * -ACCELERATION);

	}

	getRigidBody()->velocity += getRigidBody()->acceleration;

	if (Util::magnitude(getRigidBody()->velocity) < ACCELERATION) {
		getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
		getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	}

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
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
	

}

void Tank::moveLeft() {
	
	m_direction.x = -1;
}

void Tank::moveRight() {
	//if (getTransform()->position.x < 800)
	m_direction.x = 1;
}

void Tank::stopMoving() {
	m_direction.x = 0;

}

