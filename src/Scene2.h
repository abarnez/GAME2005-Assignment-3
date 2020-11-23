#pragma once

#include "Scene.h"
#include "Bullet.h"
#include "Button.h"
#include "Label.h"
#include "Paddle.h"
#include "Ball.h"

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

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

	//LootCrate* m_pLootCrate;
	bool m_playerFacingRight;

	float bVelocity;
	float momentumCoefficient;
	bool isCube, justHitObject;

	// UI Items
	Button* m_pBackButton;
	Button* m_pNextButton;
	Label* m_pInstructionsLabel;
	Label* m_pInstructionsLabel2;
	Paddle* m_pPaddle;
	Ball* m_pBall;
	int mouse_x;
	int mouse_y;
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
