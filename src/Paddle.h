#pragma once

#include "DisplayObject.h"
#include "TextureManager.h"

class Paddle final : public DisplayObject
{
public:
	Paddle();
	~Paddle();

	// Inherited via GameObject
	void draw() override;
	void update() override;
	void clean() override;
	void move(float dir);

	bool doesUpdate = false;
	float ACCELERATION = 200.0f;

private:
	glm::vec2 m_direction;
};


#pragma once
