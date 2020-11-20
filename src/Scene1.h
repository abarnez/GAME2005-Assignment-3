#pragma once

#include "Scene.h"
#include "Bullet.h"
#include "Button.h"
#include "Label.h"
#include "Tank.h"
#include "BulletPool.h"

#include <queue>

class Scene1 : public Scene
{
public:
	Scene1();
	~Scene1();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void SpawnBullet();
	void ResetScene();

private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	BulletPool* m_pPool;

	int maxNumBullets;
	static const int maxBullets = 100;
	Tank* m_pTank;
	float Speed;

	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;

	unsigned int lastTime, currentTime;
	bool showBullets, showWire;
	float bulletSpawnTime;

	float bulletSpawnStart;
	
	// Bullet Pool
	std::queue<Bullet*> m_pBulletPool;

	// mass, position, velocity, acceleration, force
	Label* MassLabel{};
	Label* PositionLabel{};
	Label* VelocityLabel{};
	Label* AccelerationLabel{};
	Label* ForceLabel{};
	Label* ThetaLabel{};

	void SetText();
	void CreateLabels();
};