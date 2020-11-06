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
	void move(float dir);

	float ACCELERATION;

private:
	glm::vec2 m_direction;
};


