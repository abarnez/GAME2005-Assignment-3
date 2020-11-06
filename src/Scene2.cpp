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

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_3))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		m_pPaddle->move(-1);

	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		m_pPaddle->move(1);

	else
		m_pPaddle->move(0);
}

void Scene2::start()
{
	TextureManager::Instance()->load("../Assets/textures/scene_2_bg.jpg", "background");

	// Set GUI Title
	m_guiTitle = "Scene 1";
	

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH / 2, 700.0f);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
	});
	addChild(m_pBackButton);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the grave accent (`) to toggle simulation menu", "Consolas", 20.0f, { 0, 255, 0, 255 });
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH / 2, 750.0f);

	addChild(m_pInstructionsLabel);

	//Paddle
	m_pPaddle = new Paddle();
	addChild(m_pPaddle);
	m_pPaddle->getTransform()->position = glm::vec2(550, 750);
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
	}

	if (ImGui::Button("Pause"))
	{
		m_pLootCrate->doesUpdate = false;
	}

	if (ImGui::SliderFloat("Position", &TrianglePosX, 0.0f, Config::SCREEN_WIDTH) && !m_pLootCrate->doesUpdate)
		SetTriangle();

	if (ImGui::SliderFloat("Ramp Height", &TriangleHeight, 0.0f, 300.0f) && !m_pLootCrate->doesUpdate)
		SetTriangle();

	if (ImGui::SliderFloat("Ramp Width", &TriangleWidth, 0.0f, 400.0f) && !m_pLootCrate->doesUpdate)
		SetTriangle();

	if (ImGui::SliderFloat("Mass (Kg)", &m_pLootCrate->Mass, 1.0f, 100.0f) && !m_pLootCrate->doesUpdate)
		SetText();

	ImGui::Checkbox("Add friction?", &AddFriction);

	if (AddFriction)
	{
		ImGui::SliderFloat("Friction", &Friction, 0.0f, 0.999f);
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