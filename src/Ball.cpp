#include "glm/gtx/string_cast.hpp"
#include "Scene2.h"
#include "TextureManager.h"
#include "Util.h"
#include "Game.h"
#include "Ball.h"

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/ball.png", "Ball");

	auto size = TextureManager::Instance()->getTextureSize("Ball");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(400.0f, 300.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(10.0f, 10.0f);
	getRigidBody()->isColliding = false;
	setType(BALL);
	

	pixelsPerMeter = 1;
	Gravity = 9.8f;
	Mass = 1;
}

Ball::~Ball()
= default;

void Ball::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	// draw the Bullet
	TextureManager::Instance()->draw("Ball", x, y, 0, 255, true);
}


void Ball::update()
{
	move();


}

void Ball::clean()
{

}

void Ball::addForce(glm::vec2 Amount)
{
	Force += Amount;
}

void Ball::move()
{
	float deltaTime = 1.0f / 60.0f;

	getRigidBody()->velocity += getRigidBody()->acceleration * deltaTime;
	getTransform()->position += getRigidBody()->velocity * deltaTime * pixelsPerMeter;
	//getRigidBody()->acceleration.y = Gravity;
	
}