#include "Scene1.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include <algorithm>

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
	SetText();
	updateDisplayList();
	if (showBullets)
	{
		float tx = m_pTank->getTransform()->position.x, ty = m_pTank->getTransform()->position.y;
		float tw = m_pTank->getWidth();
		glm::vec2 pos[4];
		pos[0] = glm::vec2(tx - tw / 2, ty);
		pos[1] = glm::vec2(tx + tw / 2, ty);
		pos[2] = glm::vec2(tx - tw / 4, ty - 10);
		pos[3] = glm::vec2(tx + tw / 5, ty - 10);

		// Create bullets at different time frame
		float deltaTime = 1.0f / Config::FPS;
		if (SDL_GetTicks() - bulletSpawnStart >= bulletSpawnTime * 1000)
		{
			// Spawn bullet
			if (m_pPool->active.size() < maxNumBullets)
			{
				SpawnBullet();
			}
			if (m_pPool->active.size() > maxNumBullets)
			{
				Bullet* bullet = (m_pPool->active.back());
				m_pPool->inactive.push_back(bullet);
				bullet->getTransform()->position.y = -50;
				bullet->doesUpdate = false;
				m_pPool->active.pop_back();
			}
		}

		for (std::vector<Bullet*>::iterator _It = m_pPool->active.begin(); _It != m_pPool->active.end(); _It++)
		{
			Bullet* bullet = (*_It);
			bullet->Gravity = Speed;
			bullet->getRigidBody()->acceleration.y = Speed;
			bullet->showWire = showWire;
			float bw = bullet->getWidth();
			float bh = bullet->getHeight();
			float curX = bullet->getTransform()->position.x, curY = bullet->getTransform()->position.y;
			glm::vec2 nextPos = bullet->getTransform()->position + bullet->getRigidBody()->velocity * deltaTime * bullet->pixelsPerMeter;
			float nextX = nextPos.x;
			float nextY = nextPos.y;

			glm::vec2 bpos[4];

			// Bottom-Left
			bpos[0] = glm::vec2(nextX - bw / 4, nextY + bh / 2);
			// Bottom-Right
			bpos[1] = glm::vec2(nextX + bw / 3, nextY + bh / 2);

			// Bottom-Left current
			bpos[2] = glm::vec2(curX - bw / 4, curY + bh / 2);
			// Bottom-Right current
			bpos[3] = glm::vec2(curX + bw / 3, curY + bh / 2);

			if (CollisionManager::doesCollide(pos[2], pos[3], bpos[2], bpos[3]))
			{
				bullet->getTransform()->position.y = pos[0].y - bullet->getHeight() / 2;
				std::cout << "cur pos HIT top tank collider " << "curY: " << bpos[2].y << "nextY: " << nextY << "\n";
				SoundManager::Instance().playSound("Explode");
				bullet->RandomPos();
			}
			else if (CollisionManager::doesCollide(pos[0], pos[1], bpos[2], bpos[3]))
			{
				bullet->getTransform()->position.y = pos[0].y - bullet->getHeight() / 2;
				std::cout << "cur pos HIT bottom tank collider " << "curY: " << bpos[0].y << "nextY: " << nextY << "\n";
				SoundManager::Instance().playSound("Explode");
				bullet->RandomPos();
			}
			else if (CollisionManager::doesCollide(pos[2], pos[3], bpos[0], bpos[1]))
			{
				bullet->nextPosition = pos[2].y - bullet->getHeight() / 2;
				std::cout << "next pos HIT top tank collider " << "x: " << bpos[0].x << "\n";
			}
			else if (CollisionManager::doesCollide(pos[0], pos[1], bpos[0], bpos[1]))
			{
				bullet->nextPosition = pos[0].y - bullet->getHeight() / 2;
				std::cout << "next pos HIT bottom tank collider " << "x: " << bpos[0].x << "\n";
			}

			// Hit bottom of screen
			if (curY >= Config::SCREEN_HEIGHT - bullet->getHeight() / 2)
			{
				bullet->RandomPos();
			}
		}
	}
}

void Scene1::clean()
{
	ResetScene();
	removeAllChildren();
}

void Scene1::handleEvents()
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

	showWire = false;
	
	// tanky tank stuff 
	m_pTank = new Tank();
	addChild(m_pTank);
	m_pTank->getTransform()->position = glm::vec2(550, 750);
	m_pTank->showWire = showWire;

	Speed = 9.8f;
	showBullets = false;
	lastTime = 0;
	bulletSpawnTime = 0.5f;
	maxNumBullets = 10;
	
	m_pPool = new BulletPool(maxBullets);
	for (int i = 0; i < maxBullets; i++)
	{
		Bullet* bullet = new Bullet();
		m_pPool->inactive.push_back(bullet);
		bullet->getTransform()->position.y = -50;
		addChild(bullet);
	}

	// Back Button
	m_pBackButton = new Button("../Assets/textures/orangeButton.png", "backButton", BACK_BUTTON);
	m_pBackButton->getTransform()->position = glm::vec2(100, 50);
	m_pBackButtonLabel = new Label("Main Menu", "Dock51", 25, { 255, 255, 255, 255 }, m_pBackButton->getTransform()->position);
	m_pBackButton->addEventListener(CLICK, [&]()-> void
	{
		m_pBackButton->setActive(false);
		TheGame::Instance()->changeSceneState(START_SCENE);
	});

	m_pBackButton->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pBackButton->setAlpha(128);
		m_pBackButtonLabel->setColour({ 255, 255, 255, 128 });
	});

	m_pBackButton->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pBackButton->setAlpha(255);
		m_pBackButtonLabel->setColour({ 255, 255, 255, 255 });
	});
	addChild(m_pBackButton);
	addChild(m_pBackButtonLabel);

	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the grave accent (`) to toggle simulation menu", "Consolas", 20.0f, { 0, 255, 0, 255 });
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 500, 30.0f);
	addChild(m_pInstructionsLabel);

	m_pInstructionsLabel2 = new Label("Press (2) to open scene 2 | Press (0) to go to the Menu", "Consolas", 20.0f, { 0, 255, 0, 255 });
	m_pInstructionsLabel2->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH - 500, 50.0f);
	addChild(m_pInstructionsLabel2);

	CreateLabels();
	
}

void Scene1::GUI_Function()
{
	ImGui::NewFrame();
	
	ImGui::Begin("Edit Variables", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);
	if (ImGui::Button("Play"))
	{
		bulletSpawnStart = SDL_GetTicks();
		showBullets = true;

		for (std::vector<Bullet*>::iterator _It = m_pPool->active.begin(); _It != m_pPool->active.end(); _It++)
		{
			Bullet* bullet = (*_It);
			bullet->doesUpdate = true;
		}
	}

	if (ImGui::Button("Reset"))
	{
		ResetScene();
	}

	if (ImGui::Button("Pause"))
	{
		showBullets = false; 
		for (std::vector<Bullet*>::iterator _It = m_pPool->active.begin(); _It != m_pPool->active.end(); _It++)
		{
			Bullet* bullet = (*_It);
			bullet->doesUpdate = false;
		}
	}

	ImGui::SliderFloat("Bullet Start Spawn Time (s)", &bulletSpawnTime, 0.5f, 5);

	ImGui::SliderInt("Max bullets on screen", &maxNumBullets, 1, 100);

	ImGui::SliderFloat("Speed of Tank", &m_pTank->ACCELERATION, 1, 1000);

	ImGui::SliderFloat("Gravity", &Speed, 1, 5000);

	if (ImGui::Checkbox("Show wire frame?", &showWire))
	{
		m_pTank->showWire = showWire;
	}

	ImGui::Separator();

	ImGui::End();
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}

void Scene1::SetText()
{
	std::string Text = "";
	Text = "Tank Position (x): " + std::to_string(m_pTank->getTransform()->position.x);
	tankPosLabel->setText(Text);

	Text = "Tank Speed (x): " + std::to_string(m_pTank->getRigidBody()->velocity.x);
	tankSpeedLabel->setText(Text);

	Text = "Bullet Speed: " + std::to_string(Speed);
	bulletSpeedLabel->setText(Text);

	Text = "Bullets on Screen: " + std::to_string(m_pPool->active.size());
	maxBulletLabel->setText(Text);
}

void Scene1::CreateLabels()
{
	const SDL_Color black = { 0, 0, 0, 255 };

	tankPosLabel = new Label("","Consolas",20, black);
	tankPosLabel->getTransform()->position = glm::vec2(180.0f, 125.0f);
	addChild(tankPosLabel);

	tankSpeedLabel = new Label("", "Consolas", 20, black);
	tankSpeedLabel->getTransform()->position = glm::vec2(160.0f, 150.0f);
	addChild(tankSpeedLabel);

	bulletSpeedLabel = new Label("", "Consolas", 20, black);
	bulletSpeedLabel->getTransform()->position = glm::vec2(140.0f, 175.0f);
	addChild(bulletSpeedLabel);

	maxBulletLabel = new Label("", "Consolas", 20, black);
	maxBulletLabel->getTransform()->position = glm::vec2(130.0f, 200.0f);
	addChild(maxBulletLabel);
}

void Scene1::SpawnBullet()
{
	Bullet* bullet = m_pPool->Spawn();
	if (bullet)
	{
		bullet->pixelsPerMeter = 1;
		bullet->Gravity = Speed;
		bullet->RandomPos();
		bullet->doesUpdate = true;
	}

	bulletSpawnStart = SDL_GetTicks();
}

void Scene1::ResetScene()
{
	showBullets = false;
	for (std::vector<Bullet*>::iterator _It = m_pPool->active.begin(); _It != m_pPool->active.end(); _It++)
	{
		Bullet* bullet = (*_It);
		bullet->getTransform()->position.y = -50;
		bullet->doesUpdate = false;
	}
	m_pPool->ResetAll();
}