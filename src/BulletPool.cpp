#include "BulletPool.h"
#include <iostream>
#include <vector>

BulletPool::BulletPool(unsigned int size)
{
	for (int i = 0; i < size; i++)
	{
		inactive.push_back(new Bullet());
	}

	std::cout << "Created pool w size of " << size << "\n";
}

Bullet* BulletPool::Spawn()
{
	Bullet* bullet = NULL;
	if (inactive.size() > 0)
	{
		bullet = inactive.back();
		bullet->active = true;
		inactive.pop_back();
	}
	return bullet;
}

void BulletPool::Despawn(Bullet* bullet)
{
	inactive.push_back(bullet);

	for (int i = 0; i < active.size(); i++)
	{
		if (active.at(i) == bullet)
		{
			active.erase(active.begin() + i);
			return;
		}
	}
}
