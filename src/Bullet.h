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

	void move();
	void RandomPos();

	bool doesUpdate, showWire; 
	float Gravity, pixelsPerMeter, Mass, nextPosition;

};


