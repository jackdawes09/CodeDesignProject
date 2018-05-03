#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Enemy.h"
#include "Bullet.h"
#include <assert.h>

Application2D::Application2D() 
{

}

Application2D::~Application2D() 
{

}

bool Application2D::startup() 
{
	
	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");
	m_GridTexture = new aie::Texture("./textures/grid_bg.png");
	m_Bullet = new aie::Texture("./textures/bullet.png");
	m_Enemy = new aie::Texture("./textures/frame2.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	

	m_cameraX = 0;
	m_cameraY = 0;
	m_shipX = 650;
	m_shipY = 75;
	m_BulletX = m_shipX;
	m_BulletY = m_shipY;
	m_timer = 0;

	hasFired = false;

	return true;
}

void Application2D::shutdown() 
{
	
	delete m_Bullet;
	delete m_GridTexture;
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;
}

void Application2D::update(float deltaTime) 
{

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();
	assert(input);

	// use arrow keys to move camera
	//if (input->isKeyDown(aie::INPUT_KEY_UP))
	//	m_cameraY += 500.0f * deltaTime;
	//
	//if (input->isKeyDown(aie::INPUT_KEY_DOWN))
	//	m_cameraY -= 500.0f * deltaTime;
	//
	//if (input->isKeyDown(aie::INPUT_KEY_LEFT))
	//	m_cameraX -= 500.0f * deltaTime;
	//
	//if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
	//	m_cameraX += 500.0f * deltaTime;

	// Increments score by 1 everytime the 'E' key is pressed
	if (input->wasKeyPressed(aie::INPUT_KEY_E))
		AddPoints();

	// Checks if the space key was pressed, spawns bullet and sets hasFired to true
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		m_BulletX = m_shipX;
		m_BulletY = m_shipY;
		hasFired = true;
	}

	// Moves the ship upward
	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_shipY += 800.0f * deltaTime;
	// Moves the ship downward
	if (input->isKeyDown(aie::INPUT_KEY_S))
		m_shipY -= 800.0f * deltaTime;
	// Moves the ship left
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_shipX -= 800.0f * deltaTime; 
	// Moves the ship right
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_shipX += 800.0f * deltaTime;
	// Moves the bullet upward when hasFired is set to true
	if (hasFired == true)
	{
		m_BulletY += 1200.0f * deltaTime;
	}

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void Application2D::draw() 
{

	// wipe the screen to the background colour
	clearScreen();

	// set the camera position before we begin rendering
	m_2dRenderer->setCameraPos(m_cameraX, m_cameraY);

	// begin drawing sprites
	m_2dRenderer->begin();

	// Create the Background
	m_2dRenderer->drawSprite(m_GridTexture, m_cameraX + 640, m_cameraY + 360 , 1280, 720);

	// demonstrate animation
	//m_2dRenderer->setUVRect(int(m_timer) % 8 / 8.0f, 0, 1.f / 8, 1.f / 8);
	//m_2dRenderer->drawSprite(m_texture, 200, 200, 100, 100);

	// demonstrate spinning sprite
	//m_2dRenderer->setUVRect(0,0,1,1);
	m_2dRenderer->drawSprite(m_shipTexture, m_shipX, m_shipY);

	// draw a thin line
	//m_2dRenderer->drawLine(300, 300, 600, 400, 2, 1);

	// draw a moving purple circle
	//m_2dRenderer->setRenderColour(1, 0, 1, 1);
	//m_2dRenderer->drawCircle(sin(m_timer) * 100 + 600, 150, 50);

	// draw a rotating red box
	//m_2dRenderer->setRenderColour(1, 0, 0, 1);
	//m_2dRenderer->drawBox(600, 500, 60, 20, m_timer);

	// draw a slightly rotated sprite with no texture, coloured yellow
	//m_2dRenderer->setRenderColour(1, 1, 0, 1);
	//m_2dRenderer->drawSprite(nullptr, 400, 400, 50, 50, 3.14159f * 0.25f);
	
	// output some text, uses the last used colour
	//char fps[32];
	//sprintf_s(fps, 32, "FPS: %i", getFPS());
	//m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", m_cameraX + 0, m_cameraY + 720 - 32);

	// Output a score
	char Score[50];
	sprintf_s(Score, 50, "Score: %i", Points);
	m_2dRenderer->drawText(m_font, Score, m_cameraX + 0,m_cameraY + 720 - 64); 

	// Draws Enemies
	m_2dRenderer->drawSprite(m_Enemy, 1000, 360, 150, 100, 4.75);
	m_2dRenderer->drawSprite(m_Enemy, 650, 675, 150, 100, 4.75);
	m_2dRenderer->drawSprite(m_Enemy, 500, 440, 150, 100, 4.75);
	m_2dRenderer->drawSprite(m_Enemy, 200 , 550, 150, 100, 4.75);

	// Draws Bullet
	if (hasFired == true)
	{
		m_2dRenderer->drawSprite(m_Bullet, m_BulletX, m_BulletY, 30, 45);
	}

	// done drawing sprites
	m_2dRenderer->end();

}

// Function to increment points by 1 when called
void Application2D::AddPoints()
{
	Points++;
}