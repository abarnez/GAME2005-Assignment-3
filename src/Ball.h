#pragma once

#include "DisplayObject.h"
#include "TextureManager.h"

class Ball final : public DisplayObject
{
public:
	Ball();
	~Ball();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;

	void addForce(glm::vec2 Amount);
	void move();

	bool cube = false;

	char* objectName;

	bool doesUpdate;

	float Gravity;
	float pixelsPerMeter;
	float Mass;

	glm::vec2 Force;
	
};


