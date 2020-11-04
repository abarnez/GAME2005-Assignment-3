#pragma once

#include "Scene.h"
#include "Bullet.h"
#include "Button.h"
#include "Label.h"
#include "Tank.h"

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

private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	
	glm::vec2 m_mousePosition;

	Tank* m_pTank;
	Bullet* m_pBullet[10];
	float Speed;

	bool m_playerFacingRight;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;

	unsigned int lastTime, currentTime;
	bool createBullets;
	int bulletCount;
	float bulletSpawnTime;
	float Mass;

	// mass, position, velocity, acceleration, force
	Label* MassLabel{};
	Label* PositionLabel{};
	Label* VelocityLabel{};
	Label* AccelerationLabel{};
	Label* ForceLabel{};
	Label* ThetaLabel{};

	void SetText();
	void CreateLabels();
	void SetRandomPos(Bullet* bullet);
};