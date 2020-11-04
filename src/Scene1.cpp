#include "Scene1.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

Scene1::Scene1()
{
	Scene1::start();
}

Scene1::~Scene1()
= default;

void Scene1::draw()
{
	TextureManager::Instance()->draw("background", 300.0f, 150.0f, 0, 255, true);
	drawDisplayList();

	//SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void Scene1::update()
{
	updateDisplayList();
	// Create bullets at different time frame
	if (createBullets)
	{
		currentTime = SDL_GetTicks();
		if (currentTime > lastTime + 1000 * bulletSpawnTime)
		{
			lastTime = currentTime;
			m_pBullet[bulletCount]->getTransform()->position = glm::vec2(0, 50);
			m_pBullet[bulletCount]->RandomPos();
			bulletCount++;
		}
		if (bulletCount == 10)
		{
			createBullets = false;
		}
	}

	// Check collision of bullet to tank
	for (int i = 0; i < 10; i++)
	{
		if (m_pBullet[i]->getTransform()->position.y >= m_pTank->getTransform()->position.y - m_pTank->getHeight())
		{
			glm::vec2 pos = m_pBullet[i]->getTransform()->position;
			glm::vec2 pos2 = m_pTank->getTransform()->position;
			float a = pos.x - pos2.x;
			float b = pos.y - pos2.y;
			float c = sqrt(a * a + b * b);

			if (c < ((m_pBullet[i]->getHeight() / 2) + (m_pTank->getHeight() / 2)))
			{
				std::cout << "Hit height tank at " << c << "\n";
				m_pBullet[i]->RandomPos();
				SoundManager::Instance().playSound("Explode");
			}
			else if (c < ((m_pBullet[i]->getWidth() / 2) + (m_pTank->getWidth() / 2)))
			{
				std::cout << "Hit width tank at " << c << "\n";
				m_pBullet[i]->RandomPos();
				SoundManager::Instance().playSound("Explode");
			}
		}
	}
}

void Scene1::clean()
{
	removeAllChildren();
}

void Scene1::handleEvents()
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
		m_pTank->move(-1);

	else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		m_pTank->move(1);

	else
		m_pTank->move(0);
}

void Scene1::start()
{
	TextureManager::Instance()->load("../Assets/textures/bg.jpg", "background"); 
	SoundManager::Instance().load("../Assets/audio/explode.ogg", "Explode", SOUND_SFX);

	// Set GUI Title
	m_guiTitle = "Scene 1";
	
	// tanky tank stuff 
	m_pTank = new Tank();
	addChild(m_pTank);
	m_pTank->getTransform()->position = glm::vec2(550, 750);

	Speed = 9.8f;
	bulletCount = 0;
	createBullets = false;
	lastTime = 0;
	bulletSpawnTime = 0.5f;

	for (int i = 0; i < 10; i++)
	{
		m_pBullet[i] = new Bullet();
		addChild(m_pBullet[i]);
		m_pBullet[i]->getTransform()->position.y = -100;
		m_pBullet[i]->getRigidBody()->mass = 1;
		m_pBullet[i]->pixelsPerMeter = 1;
		m_pBullet[i]->Gravity = Speed;
	}

	// Back Button
	m_pBackButton = new Button("../Assets/textures/backButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100, 50);
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
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 500, 30.0f);

	addChild(m_pInstructionsLabel);
}

void Scene1::GUI_Function()
{
	ImGui::NewFrame();
	
	ImGui::Begin("Edit Variables", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	if (ImGui::Button("Play"))
	{
		createBullets = true;
		bulletCount = 0;
	}

	if (ImGui::Button("Reset"))
	{
		createBullets = false;
		for (int i = 0; i < 10; i++)
		{
			m_pBullet[i]->doesUpdate = false;
			m_pBullet[i]->getTransform()->position.y = -100;
		}
	}

	if (ImGui::Button("Pause"))
	{

	}

	if (ImGui::SliderFloat("Bullet Spawn Time (s)", &bulletSpawnTime, 1.0f, 100.0f))
	{
		// Set label bitch
	}

	if (ImGui::SliderFloat("Mass (Kg)", &m_pTank->getRigidBody()->mass, 1.0f, 100.0f))
	{
		// Set label bitch
	}

	if (ImGui::SliderFloat("Speed of Tank", &m_pTank->ACCELERATION, 1.0f, 500.0f))
	{
		// Set label bitch
	}

	if (ImGui::SliderFloat("Gravity", &Speed, 1.0f, 500.0f))
	{
		for (int i = 0; i < 10; i++)
		{
			m_pBullet[i]->pixelsPerMeter = Speed;
		}
		// Set label bitch
	}

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

void Scene1::SetText()
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

void Scene1::CreateLabels()
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