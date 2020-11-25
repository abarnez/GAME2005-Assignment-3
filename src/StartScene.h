#pragma once
#ifndef __START_SCENE__
#define __START_SCENE__

#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Button.h"

class StartScene final : public Scene
{
public:
	StartScene();
	~StartScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;
	
private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};
	Label* m_pGroupMemberLabel{};

	Ship* m_pShip{};

	Button* m_pScene1Button;
	Button* m_pScene2Button;
	Label* m_pScene1ButtonLabel;
	Label* m_pScene2ButtonLabel;
};

#endif /* defined (__START_SCENE__) */