#pragma once

#include "DisplayObject.h"
#include "TextureManager.h"

class Tank final : public DisplayObject
{
public:
	Tank();
	~Tank();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;
	

	void addForce(glm::vec2 Amount);
	void move(float dir);

	bool doesUpdate = false; 

	float Gravity = 9.8f;

	float Speed;
	float pixelsPerMeter;
	float Mass;

	float friction;
	float theta;
	float ACCELERATION = 200.0f;

	float Rotation = 0.0f;

	glm::vec2 Force;

private:

	// steering behaviours
	float m_maxSpeed;
	float m_turnRate;
	glm::vec2 m_direction;

	float m_currentHeading;
	glm::vec2 m_currentDirection;
	glm::vec2 m_targetPosition;
};


