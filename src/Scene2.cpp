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
		
		/*auto now = SDL_GetTicks();
		auto currentPos = m_pPaddle->getTransform()->position;

		auto deltaTime = now - lastMovement;
		auto distance = glm::vec2(abs(currentPos.x - mouse_x), abs(currentPos.y - mouse_y));

		auto speed = glm::vec2(round(distance.x / deltaTime * 1000), round(distance.y / deltaTime * 1000));

		m_pPaddle->getRigidBody()->velocity = speed;
		//std::cout << "Speed X: " << speed.x << ", Y: " << speed.y << "\n";
		m_pPaddle->getTransform()->position = glm::vec2(mouse_x, mouse_y);

		lastMovement = now;*/

		// Get Mouse pos, displacement & move paddle in that direction. Multiply displacement for heightened speed.

		float xMinusX = mouse_x - m_pPaddle->getTransform()->position.x;
		float yMinusY = mouse_y - m_pPaddle->getTransform()->position.y;
		glm::vec2 displacement = glm::vec2(xMinusX, yMinusY);
		m_pPaddle->getRigidBody()->velocity = glm::vec2(displacement.x * 10, displacement.y * 10);
		m_pPaddle->getTransform()->position += displacement * 0.1f;

		// glm::vec2(mouse_x, mouse_y);//m_pPaddle->getRigidBody()->velocity;

	}
}

void Scene2::update()
{
	//Collision check
	float height = m_pBall->getHeight() / 2;
	float width = m_pBall->getWidth() / 2;

	if (isBox)
	{
		CollisionManager::AABBCheck(m_pBall, m_pPaddle);
	}
	else
	{
		CollisionManager::circleAABBCheck(m_pBall, m_pPaddle);
	}

	if (m_pBall->getTransform()->position.y <= 0 + height)
	{
		m_pBall->getTransform()->position.y = height + 1;
		m_pBall->getRigidBody()->velocity.y = -(m_pBall->getRigidBody()->velocity.y - momentumCoefficient * m_pBall->getRigidBody()->velocity.y);
	}
	else if (m_pBall->getTransform()->position.y >= Config::SCREEN_HEIGHT - height)
	{
		m_pBall->getTransform()->position.y = Config::SCREEN_HEIGHT - height - 1;
		m_pBall->getRigidBody()->velocity.y = -(m_pBall->getRigidBody()->velocity.y - momentumCoefficient * m_pBall->getRigidBody()->velocity.y);
	}
	else if (m_pBall->getTransform()->position.x <= 0 + width)
	{
		m_pBall->getTransform()->position.x = width + 1;
		m_pBall->getRigidBody()->velocity.x = -(m_pBall->getRigidBody()->velocity.x - momentumCoefficient * m_pBall->getRigidBody()->velocity.x);
	}
	else if (m_pBall->getTransform()->position.x >= Config::SCREEN_WIDTH - width)
	{
		m_pBall->getTransform()->position.x = Config::SCREEN_WIDTH - width - 1;
		m_pBall->getRigidBody()->velocity.x = -(m_pBall->getRigidBody()->velocity.x - momentumCoefficient * m_pBall->getRigidBody()->velocity.x);
	}

	//lables
	SetText();

	updateDisplayList();
}

void Scene2::clean()
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_0))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
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

	isBox = false;
	momentumCoefficient = 0.6f;
	lastMovement = SDL_GetTicks();

	//Paddle
	m_pPaddle = new Paddle();
	addChild(m_pPaddle);
	m_pPaddle->getTransform()->position = glm::vec2(550, 750);

	m_pPaddle->getRigidBody()->mass = 5;

	//Ball
	m_pBall = new Ball();
	addChild(m_pBall);
	m_pBall->getTransform()->position = glm::vec2(550, 100);

	m_pBall->getRigidBody()->mass = 3;

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
	
	if (ImGui::Checkbox("Make box?", &isBox))
	{
		m_pBall->objectName = isBox ? "Box" : "Ball";
		m_pBall->getTransform()->position = glm::vec2(550, 100);
		m_pBall->getRigidBody()->velocity.x = 0;
		m_pBall->getRigidBody()->velocity.y = 0;
	}

	ImGui::SliderFloat("Momentum Decrease by (%)", &momentumCoefficient, 0, 1);

	if (ImGui::SliderFloat("Player Mass (kg)", &m_pPaddle->getRigidBody()->mass, 3, 10))
	{
		if (m_pPaddle->getRigidBody()->mass < m_pBall->getRigidBody()->mass)
			m_pPaddle->getRigidBody()->mass = m_pBall->getRigidBody()->mass;
	}

	ImGui::SliderFloat("Ball/Box Mass (kg)", &m_pBall->getRigidBody()->mass, 3, 10);

	ImGui::Separator();

	ImGui::End();
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
	
}

void Scene2::SetText()
{
	std::string Text = "";
	Text = "Ball Velocity (x, y): (" + std::to_string(m_pBall->getRigidBody()->velocity.x) + ", " + std::to_string(m_pBall->getRigidBody()->velocity.y) + ")";
	VelocityLabel->setText(Text);

	Text = "Ball Position (x, y): (" + std::to_string(m_pBall->getTransform()->position.x) + ", " + std::to_string(m_pBall ->getTransform()->position.y) + ")";
	PositionLabel->setText(Text);

	Text = "Paddle Velocity (x, y): (" + std::to_string(m_pPaddle->getRigidBody()->velocity.x) + ", " + std::to_string(m_pPaddle->getRigidBody()->velocity.y) + ")";
	pVelocityLabel->setText(Text);

	Text = "Paddle Position (x, y): (" + std::to_string(m_pPaddle->getTransform()->position.x) + ", " + std::to_string(m_pPaddle->getTransform()->position.y) + ")";
	pPositionLabel->setText(Text);
}

void Scene2::CreateLabels()
{
	m_pInstructionsLabel = new Label("Press the grave accent (`) to toggle simulation menu", "Consolas", 20.0f, { 0, 255, 0, 255 });
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 500, 30.0f);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel2 = new Label("Press (1) to open Scene 1 | Press (0) to go to the Menu", "Consolas", 20.0f, { 0, 255, 0, 255 });
	m_pInstructionsLabel2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 500, 50.0f);
	addChild(m_pInstructionsLabel2);

	VelocityLabel = new Label;
	VelocityLabel->getTransform()->position = glm::vec2(240.0f, 700.0f);
	addChild(VelocityLabel);

	PositionLabel = new Label;
	PositionLabel->getTransform()->position = glm::vec2(250.0f, 685.0f);
	addChild(PositionLabel);

	pVelocityLabel = new Label;
	pVelocityLabel->getTransform()->position = glm::vec2(255.0f, 720.0f);
	addChild(pVelocityLabel);

	pPositionLabel = new Label;
	pPositionLabel->getTransform()->position = glm::vec2(260.0f, 735.0f);
	addChild(pPositionLabel);
}