#pragma once
#include "Bullet.h"
#include <vector>

class BulletPool
{
public:
	BulletPool(unsigned int);
	~BulletPool();

	Bullet* Spawn();
	void Despawn(Bullet* bullet);
	std::vector<Bullet*> active;
	std::vector<Bullet*> inactive;

	void ResetAll();

private:
	std::vector<Bullet*> inuse;
};


