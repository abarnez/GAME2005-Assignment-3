#include "BulletPool.h"
#include <iostream>

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
		inactive.pop_back();
		active.push_back(bullet);
		std::cout << "Spawned bullet. \nActive: " << active.size() << "\n";
	}
	else
	{
		//std::cout << "Bullet unable to be spawned. \n";
	}
	return bullet;
}

void BulletPool::Despawn(Bullet* bullet)
{
	inactive.push_back(bullet);

	for (std::vector<Bullet*>::iterator myIter = active.begin(); myIter != active.end(); myIter++)
	{
		if (*myIter == bullet)
		{
			active.erase(myIter);
			std::cout << "Bullet despawned.\nActive: " << active.size() << "\n";
			return;
		}
	}
}

void BulletPool::ResetAll()
{
	for (std::vector<Bullet*>::iterator myIter = active.begin(); myIter != active.end(); myIter++)
	{
		inactive.push_back(*myIter);
	}
	active.clear();
}
