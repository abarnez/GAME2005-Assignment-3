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
	float nextPosition;
	bool showWire;

	glm::vec2 Force;
	void RandomPos();

};


