#include "Scene2.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

Scene2::Scene2()
{
	Scene2::start();
}

Scene2::~Scene2()
= default;

void Scene2::draw()
{
	TextureManager::Instance()->draw("background", 300.0f, 150.0f, 0, 255, true);

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void Scene2::update()
{
	//paddle top left top right	
	float paddle_x = m_pPaddle->getTransform()->position.x;
	float paddle_y = m_pPaddle->getTransform()->position.y;
	float paddle_width = m_pPaddle->getWidth();
	glm::vec2 topLeft;
	topLeft = glm::vec2(paddle_x - paddle_width / 2 , paddle_y);
	glm::vec2 topRight;
	topRight = glm::vec2(paddle_x + paddle_width / 2 , paddle_y);
	
	//ball bottom left bottom right
	float ball_x = m_pBall->getTransform()->position.x;
	float ball_y = m_pBall->getTransform()->position.y;
	float ball_width = m_pBall->getWidth();
	float ball_height = m_pBall->getHeight();
	glm::vec2 bottomLeft;
	bottomLeft = glm::vec2(ball_x - ball_width, ball_y + ball_height / 1.5);
	glm::vec2 bottomRight;
	bottomRight = glm::vec2(ball_x + ball_width, ball_y + ball_height / 1.5);
	std::cout << bottomLeft.x;
	//collision check
	if (CollisionManager::doesCollide(topLeft, topRight, bottomLeft, bottomRight)) {
	
		m_pBall->getRigidBody()->velocity.y = -m_pBall->getRigidBody()->velocity.y;
	}

	//paddle follow mouse pos
	SDL_GetMouseState(&mouse_x, &mouse_y);
	m_pPaddle->getTransform()->position.x = mouse_x;

	float height = m_pBall->getHeight() / 2;
	float width = m_pBall->getWidth() / 2;

	if (m_pBall->getTransform()->position.y <= 0 + height)
	{
		m_pBall->getRigidBody()->velocity.y = -m_pBall->getRigidBody()->velocity.y;
	}
	else if (m_pBall->getTransform()->position.y >= Config::SCREEN_HEIGHT - height)
	{
		m_pBall->getRigidBody()->velocity.y = -m_pBall->getRigidBody()->velocity.y;
	}
	else if (m_pBall->getTransform()->position.x <= 0 + width)
	{
		m_pBall->getRigidBody()->velocity.x = -m_pBall->getRigidBody()->velocity.x;
	}
	else if (m_pBall->getTransform()->position.x >= Config::SCREEN_WIDTH - width)
	{
		m_pBall->getRigidBody()->velocity.x = -m_pBall->getRigidBody()->velocity.x;
	}
	
	float bottom = m_pPaddle->getTransform()->position.y + m_pPaddle->getHeight() / 2;
	float top = m_pPaddle->getTransform()->position.y - m_pPaddle->getHeight() / 2;
	float left = m_pPaddle->getTransform()->position.x - m_pPaddle->getWidth() / 2;
	float right = m_pPaddle->getTransform()->position.x + m_pPaddle->getWidth() / 2;

	/*if (m_pBall->getTransform()->position.y <= top + m_pBall->getHeight() / 2
		&& m_pBall->getTransform()->position.y >= bottom - m_pBall->getHeight() / 2)
	{
		m_pBall->getRigidBody()->velocity.y = -m_pBall->getRigidBody()->velocity.y;
	}
	else if (m_pBall->getTransform()->position.y >= bottom - m_pBall->getHeight() / 2)
	{
		m_pBall->getRigidBody()->velocity.y = -m_pBall->getRigidBody()->velocity.y;
	}
	else if (m_pBall->getTransform()->position.x <= left + m_pBall->getWidth() / 2)
	{
		m_pBall->getRigidBody()->velocity.x = -m_pBall->getRigidBody()->velocity.x;
	}
	else if (m_pBall->getTransform()->position.x >= right - m_pBall->getWidth() / 2)
	{
		m_pBall->getRigidBody()->velocity.x = -m_pBall->getRigidBody()->velocity.x;
	}*/

	updateDisplayList();
}

void Scene2::clean()
{
	removeAllChildren();
}

void Scene2::handleEvents()
{
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
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

void Scene2::start()
{
	TextureManager::Instance()->load("../Assets/textures/scene_2_bg.jpg", "background");

	// Set GUI Title
	m_guiTitle = "Scene 2";
	
	SDL_ShowCursor(0);

	//Paddle
	m_pPaddle = new Paddle();
	addChild(m_pPaddle);
	m_pPaddle->getTransform()->position = glm::vec2(550, 750);

	//Ball
	m_pBall = new Ball();
	addChild(m_pBall);
	m_pBall->getTransform()->position = glm::vec2(550, 100);
	m_pBall->getRigidBody()->velocity.x = 100;
	m_pBall->getRigidBody()->velocity.y = 200;
}

void Scene2::GUI_Function()
{
	ImGui::NewFrame();
	
	ImGui::Begin("Edit Variables", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	/*if (ImGui::Button("Play"))
	{
		m_pLootCrate->doesUpdate = true;
	}

	if (ImGui::Button("Reset"))
	{
		m_pLootCrate->doesUpdate = false;
		SetTriangle();
		m_pLootCrate->getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
		m_pLootCrate->getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
		SetText();
	}*/

	ImGui::Separator();

	ImGui::End();
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

void Scene2::SetText()
{
/*	std::string Text = "";
	Text = "Mass: " + std::to_string(m_pLootCrate->Mass);
	MassLabel->setText(Text);

	Text = "Position (x, y): (" + std::to_string(m_pLootCrate->getTransform()->position.x) + ", " + std::to_string(m_pLootCrate->getTransform()->position.y) + ")";
	PositionLabel->setText(Text);

	Text = "Velocity (x, y): (" + std::to_string(m_pLootCrate->getRigidBody()->velocity.x) + ", " + std::to_string(m_pLootCrate->getRigidBody()->velocity.y) + ")";
	VelocityLabel->setText(Text);

	Text = "Acceleration (x, y): (" + std::to_string(m_pLootCrate->getRigidBody()->acceleration.x) + ", " + std::to_string(m_pLootCrate->getRigidBody()->acceleration.y) + ")";
	AccelerationLabel->setText(Text);

	Text = "Force: " + std::to_string(m_pLootCrate->Mass * m_pLootCrate->getRigidBody()->acceleration.x) + " N";
	ForceLabel->setText(Text);

	Text = "Theta: " + std::to_string(glm::degrees(Theta));
	ThetaLabel->setText(Text);*/
}

void Scene2::CreateLabels()
{
/*	const SDL_Color green = { 0, 255, 0, 255 };

	std::string Text = "";
	Text = "Mass: " + std::to_string(m_pLootCrate->Mass);
	MassLabel = new Label(Text, "Consolas", 15, green, glm::vec2(100.0f, 25.0f));
	MassLabel->setParent(this);
	addChild(MassLabel);

	Text = "Position (x, y): (" + std::to_string(m_pLootCrate->getTransform()->position.x) + ", " + std::to_string(m_pLootCrate->getTransform()->position.y) + ")";
	PositionLabel = new Label(Text, "Consolas", 15, green, glm::vec2(175.0f, 100.0f));
	PositionLabel->setParent(this);
	addChild(PositionLabel);

	Text = "Velocity (x, y): (" + std::to_string(m_pLootCrate->getRigidBody()->velocity.x) + ", " + std::to_string(m_pLootCrate->getRigidBody()->velocity.y) + ")";
	VelocityLabel = new Label(Text, "Consolas", 15, green, glm::vec2(175.0f, 50.0f));
	VelocityLabel->setParent(this);
	addChild(VelocityLabel);

	Text = "Acceleration (x, y): (" + std::to_string(m_pLootCrate->getRigidBody()->acceleration.x) + ", " + std::to_string(m_pLootCrate->getRigidBody()->acceleration.y) + ")";
	AccelerationLabel = new Label(Text, "Consolas", 15, green, glm::vec2(175.0f, 75.0f));
	AccelerationLabel->setParent(this);
	addChild(AccelerationLabel);

	Text = "Force: " + std::to_string(m_pLootCrate->Mass * m_pLootCrate->getRigidBody()->acceleration.x) + " N";
	ForceLabel = new Label(Text, "Consolas", 15, green, glm::vec2(100.0f, 125.0f));
	ForceLabel->setParent(this);
	addChild(ForceLabel);

	Text = "Theta: " + std::to_string(glm::degrees(Theta));
	ThetaLabel = new Label(Text, "Consolas", 15, green, glm::vec2(100.0f, 150.0f));
	ThetaLabel->setParent(this);
	addChild(ThetaLabel);*/
}