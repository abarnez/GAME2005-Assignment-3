#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{
	TextureManager::Instance()->draw("background", 300.0f, 150.0f, 0, 255, true);
	drawDisplayList();

	// DEBUG PURPOSES
	//TheGame::Instance()->changeSceneState(SCENE_2);
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(SCENE_1);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(SCENE_2);
	}
}

void StartScene::start()
{
	// Create background
	TextureManager::Instance()->load("../Assets/textures/bg.jpg", "background");

	const SDL_Color green = { 0, 255, 0, 255 };
	const SDL_Color cyan = { 0, 255, 255, 255 };

	m_pStartLabel = new Label("Minigames", "Dock51", 60, cyan, glm::vec2(Config::SCREEN_WIDTH / 2, 250.0f));
	m_pStartLabel->setParent(this);
	addChild(m_pStartLabel);

	m_pGroupMemberLabel = new Label("Tamerlan Tahirli - 101055392 -- Alexander Barnes - 101086806", "Consolas", 20, cyan, glm::vec2(Config::SCREEN_WIDTH / 2, 300.0f));
	m_pGroupMemberLabel->setParent(this);
	addChild(m_pGroupMemberLabel);

	m_pInstructionsLabel = new Label("Press Scene 1 or 2 or press 1 or 2 to begin", "Consolas", 40, green, glm::vec2(Config::SCREEN_WIDTH / 2, 400.0f));
	m_pInstructionsLabel->setParent(this);
	addChild(m_pInstructionsLabel);

	// Scene 1 Button
	m_pScene1Button = new Button();
	m_pScene1Button->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH / 2, 600.0f);
	m_pScene1ButtonLabel = new Label("Scene 1", "Dock51", 25, { 255, 255, 255, 255 }, m_pScene1Button->getTransform()->position);

	m_pScene1Button->addEventListener(CLICK, [&]()-> void
	{
		m_pScene1Button->setActive(false);
		TheGame::Instance()->changeSceneState(SCENE_1);
	});
	
	m_pScene1Button->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pScene1Button->setAlpha(128);
		m_pScene1ButtonLabel->setColour({ 255, 255, 255, 128 });
	});

	m_pScene1Button->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pScene1Button->setAlpha(255);
		m_pScene1ButtonLabel->setColour({ 255, 255, 255, 255 });
	});
	addChild(m_pScene1Button);
	addChild(m_pScene1ButtonLabel);


	// Scene 2 Button
	m_pScene2Button = new Button("../Assets/textures/orangeButton.png", "Scene2Button", SCENE2_BUTTON);
	m_pScene2Button->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH / 2, 675.0f);
	m_pScene2ButtonLabel = new Label("Scene 2", "Dock51", 25, { 255, 255, 255, 255 }, m_pScene2Button->getTransform()->position);

	m_pScene2Button->addEventListener(CLICK, [&]()-> void
		{
			m_pScene2Button->setActive(false);
			TheGame::Instance()->changeSceneState(SCENE_2);
		});

	m_pScene2Button->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pScene2Button->setAlpha(128);
			m_pScene2ButtonLabel->setColour({ 255, 255, 255, 128 });
		});

	m_pScene2Button->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pScene2Button->setAlpha(255);
			m_pScene2ButtonLabel->setColour({ 255, 255, 255, 255 });
		});
	addChild(m_pScene2Button);
	addChild(m_pScene2ButtonLabel);
}

