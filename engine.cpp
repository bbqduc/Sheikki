#include "engine.h"
#include <iostream>


Engine::Engine(int width, int height, int depth)
	: window(sf::VideoMode(width, height, depth), "Shake-engine"),
	graphics(),
	objects()
{
	for(int i = 0; i < 6; ++i)
		keysDown[i] = false;
}

void Engine::gameLoop()
{
	while(window.IsOpened()){

		window.SetActive();
		graphics.draw(objects);
		window.Display();

		processEvents();
		applyInput(activeEntity);
		sf::Sleep(0.001);
	}
}

void Engine::processEvents()
{
	sf::Event event;
	while (window.PollEvent(event))
	{
		// Close window : exit
		if (event.Type == sf::Event::Closed)
			window.Close();
		// Resize event : adjust viewport
		if (event.Type == sf::Event::Resized)
			graphics.reshape(event.Size.Width, event.Size.Height);

		// Escape key : exit
		if ((event.Type == sf::Event::KeyPressed || event.Type == sf::Event::KeyReleased))
			handleKeyPress(event);
	}
}

void Engine::handleKeyPress(sf::Event& event)
{
	if(event.Type == sf::Event::KeyPressed)
	{
		std::cerr << "YOU SEEM TO HAVE PRESSED A KEY!!\n";
		if(event.Key.Code == sf::Keyboard::Escape)
			window.Close();
		if(event.Key.Code == sf::Keyboard::Up)
			keysDown[UP] = true;
		if(event.Key.Code == sf::Keyboard::Down)
			keysDown[DOWN] = true;
		if(event.Key.Code == sf::Keyboard::Left)
			keysDown[LEFT] = true;
		if(event.Key.Code == sf::Keyboard::Right)
			keysDown[RIGHT] = true;
		if(event.Key.Code == sf::Keyboard::A)
			keysDown[A] = true;
		if(event.Key.Code == sf::Keyboard::Z)
			keysDown[Z] = true;
		if(event.Key.Code == sf::Keyboard::Q)
			keysDown[Q] = true;
		if(event.Key.Code == sf::Keyboard::E)
			keysDown[E] = true;
	}	

	if(event.Type == sf::Event::KeyReleased)
	{
		std::cerr << "YOU SEEM TO HAVE RELEASED A KEY!!\n";
		if(event.Key.Code == sf::Keyboard::Up)
			keysDown[UP] = false;
		if(event.Key.Code == sf::Keyboard::Down)
			keysDown[DOWN] = false;
		if(event.Key.Code == sf::Keyboard::Left)
			keysDown[LEFT] = false;
		if(event.Key.Code == sf::Keyboard::Right)
			keysDown[RIGHT] = false;
		if(event.Key.Code == sf::Keyboard::A)
			keysDown[A] = false;
		if(event.Key.Code == sf::Keyboard::Z)
			keysDown[Z] = false;
		if(event.Key.Code == sf::Keyboard::Q)
			keysDown[Q] = false;
		if(event.Key.Code == sf::Keyboard::E)
			keysDown[E] = false;
	}
}

void Engine::applyInput(Entity* entity)
{
	if(entity == NULL)
		return;
	if(keysDown[UP])
		entity->rotatePitch(0.01f);
	if(keysDown[DOWN])
		entity->rotatePitch(-0.01f);
	if(keysDown[Q])
		entity->rotateRoll(-0.01f);
	if(keysDown[E])
		entity->rotateRoll(0.01f);
	if(keysDown[LEFT])
		entity->rotateYaw(-0.01f);
	if(keysDown[RIGHT])
		entity->rotateYaw(0.01f);
	if(keysDown[A])
		entity->move(0,0,-0.1f);
	if(keysDown[Z])
		entity->move(0,0,0.1f);
}

Entity& Engine::addEntity(Entity& entity)
{
	objects.push_back(entity);
	return objects.back();
}

void Engine::setActive(Entity& entity)
{
	activeEntity = &entity;
}

