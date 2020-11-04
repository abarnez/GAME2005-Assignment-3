#pragma once

#include "DisplayObject.h"
#include "TextureManager.h"

class Bullet final : public DisplayObject
{
public:
	Bullet();
	~Bullet();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void addForce(glm::vec2 Amount);
	void move();

	bool doesUpdate = false; 

	float Gravity;
	float pixelsPerMeter;
	float Mass;

	glm::vec2 Force;
	void RandomPos();

private:

	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;

	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;

};


