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
		SDL_ShowCursor(1);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
	else
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_ShowCursor(0);
		SDL_GetMouseState(&mouse_x, &mouse_y);
		float direction = mouse_x - m_pPaddle->getTransform()->position.x;
		m_pPaddle->getRigidBody()->velocity.x = direction * 3;

	}
}

void Scene2::update()
{
	bVelocity = m_pBall->getRigidBody()->velocity.x;

	//paddle top left top right	
	float paddle_x = m_pPaddle->getTransform()->position.x;
	float paddle_y = m_pPaddle->getTransform()->position.y;
	float paddle_width = m_pPaddle->getWidth();
	glm::vec2 topLeft;
	topLeft = glm::vec2(paddle_x - paddle_width / 4 , paddle_y - 20);
	glm::vec2 topRight;
	topRight = glm::vec2(paddle_x + paddle_width / 4 , paddle_y - 20);
	
	//ball bottom left bottom right
	float ball_x = m_pBall->getTransform()->position.x;
	float ball_y = m_pBall->getTransform()->position.y;
	float ball_width = m_pBall->getWidth();
	float ball_height = m_pBall->getHeight();
	glm::vec2 bottomLeft;
	bottomLeft = glm::vec2(ball_x - ball_width / 2, ball_y + ball_height / 2);
	glm::vec2 bottomRight;
	bottomRight = glm::vec2(ball_x + ball_width / 2, ball_y + ball_height / 2);

	float height = m_pBall->getHeight() / 2;
	float width = m_pBall->getWidth() / 2;

	//Collision check
	if (CollisionManager::circleAABBCheck(m_pBall, m_pPaddle))
	{
		float reduceVelocityByCoefficient = m_pBall->getRigidBody()->velocity.y - momentumCoefficient * m_pBall->getRigidBody()->velocity.y;
		m_pBall->getRigidBody()->velocity.y = -reduceVelocityByCoefficient;
	}
	else if (m_pBall->getTransform()->position.y <= 0 + height)
	{
		float reduceVelocityByCoefficient = m_pBall->getRigidBody()->velocity.y - momentumCoefficient * m_pBall->getRigidBody()->velocity.y;
		m_pBall->getRigidBody()->velocity.y = -reduceVelocityByCoefficient;

		std::cout << "Velocity on y:" << m_pBall->getRigidBody()->velocity.y << "\n";
	}
	else if (m_pBall->getTransform()->position.y >= Config::SCREEN_HEIGHT - height)
	{
		float reduceVelocityByCoefficient = m_pBall->getRigidBody()->velocity.y - momentumCoefficient * m_pBall->getRigidBody()->velocity.y;
		m_pBall->getRigidBody()->velocity.y = -reduceVelocityByCoefficient;

		std::cout << "Velocity on y:" << m_pBall->getRigidBody()->velocity.y << "\n";
	}
	else if (m_pBall->getTransform()->position.x <= 0 + width)
	{
		float reduceVelocityByCoefficient = m_pBall->getRigidBody()->velocity.x - momentumCoefficient * m_pBall->getRigidBody()->velocity.x;
		m_pBall->getRigidBody()->velocity.x = -reduceVelocityByCoefficient;

		std::cout << "Velocity on x:" << m_pBall->getRigidBody()->velocity.x << "\n";
	}
	else if (m_pBall->getTransform()->position.x >= Config::SCREEN_WIDTH - width)
	{
		float reduceVelocityByCoefficient = m_pBall->getRigidBody()->velocity.x - momentumCoefficient * m_pBall->getRigidBody()->velocity.x;
		m_pBall->getRigidBody()->velocity.x = -reduceVelocityByCoefficient;

		std::cout <<  "Velocity on x:" << m_pBall->getRigidBody()->velocity.x << "\n";
	}
	
	float bottom = m_pPaddle->getTransform()->position.y + m_pPaddle->getHeight() / 2;
	float top = m_pPaddle->getTransform()->position.y - m_pPaddle->getHeight() / 2;
	float left = m_pPaddle->getTransform()->position.x - m_pPaddle->getWidth() / 2;
	float right = m_pPaddle->getTransform()->position.x + m_pPaddle->getWidth() / 2;

	//lables
	SetText();

	updateDisplayList();
}



void Scene2::clean()
{
	SDL_ShowCursor(1);
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

	isCube = false;
	momentumCoefficient = 0;

	//Paddle
	m_pPaddle = new Paddle();
	addChild(m_pPaddle);
	m_pPaddle->getTransform()->position = glm::vec2(550, 750);

	//Ball
	m_pBall = new Ball();
	addChild(m_pBall);
	m_pBall->getTransform()->position = glm::vec2(550, 100);

	CreateLabels();
	
}

void Scene2::GUI_Function()
{
	ImGui::NewFrame();
	
	ImGui::Begin("Game Menu", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	if (ImGui::Button("Play"))
	{
		m_pBall->getRigidBody()->velocity.x = 100;
		m_pBall->getRigidBody()->velocity.y = 200;
	}

	if (ImGui::Button("Reset"))
	{
		m_pBall->getRigidBody()->velocity.x = 0;
		m_pBall->getRigidBody()->velocity.y = 0;
		m_pBall->getTransform()->position = glm::vec2(550, 100);
	}
	
	if (ImGui::Checkbox("Make cube?", &isCube))
	{
		m_pBall->objectName = isCube ? "Cube" : "Ball";
		m_pBall->getTransform()->position = glm::vec2(550, 100);
		m_pBall->getRigidBody()->velocity.x = 0;
		m_pBall->getRigidBody()->velocity.y = 0;
	}


	ImGui::SliderFloat("Momentum Decrease by (%)", &momentumCoefficient, 0, 1);
	ImGui::Separator();

	ImGui::End();
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
	
}

void Scene2::SetText()
{
	std::string Text = "";
	Text = "Velocity (x, y): (" + std::to_string(m_pBall->getRigidBody()->velocity.x) + ", " + std::to_string(m_pBall->getRigidBody()->velocity.y) + ")";
	VelocityLabel->setText(Text);

	Text = "Position (x, y): (" + std::to_string(m_pBall->getTransform()->position.x) + ", " + std::to_string(m_pBall ->getTransform()->position.y) + ")";
	PositionLabel->setText(Text);
}

void Scene2::CreateLabels()
{
	m_pInstructionsLabel = new Label("Press the grave accent (`) to toggle simulation menu", "Consolas", 20.0f, { 0, 255, 0, 255 });
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 500, 30.0f);
	addChild(m_pInstructionsLabel);

	VelocityLabel = new Label;
	VelocityLabel->getTransform()->position = glm::vec2(215.0f, 700.0f);
	addChild(VelocityLabel);

	PositionLabel = new Label;
	PositionLabel->getTransform()->position = glm::vec2(210.0f, 685.0f);
	addChild(PositionLabel);
}