#pragma once
#include "Bullet.h"

class BulletPool
{
public:
	BulletPool(unsigned int);
	~BulletPool();

	Bullet* Spawn();

	void Despawn(Bullet*);
private:
	std::vector<Bullet*> active;
	std::vector<Bullet*> inactive;
};


