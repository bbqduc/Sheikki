#include "engine.h"
#include <iostream>

Engine::Engine(int width, int height, int depth)
	: window(sf::VideoMode(width, height, depth), "Shake-engine"),
	graphics(),
	objects()
{
	for(int i = 0; i < KEYS; ++i)
	{
		keysDown[i] = false;
	}
}

void Engine::gameLoop()
{
	window.SetActive();
	while(window.IsOpen()){
		graphics.draw(objects);
		window.Display();

		processEvents();
		applyInput(activeEntity, window.GetFrameTime());
		sf::Sleep(1);
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
		if(event.Key.Code == sf::Keyboard::Space)
			keysDown[SPACE] = true;
	}	

	if(event.Type == sf::Event::KeyReleased)
	{
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
		if(event.Key.Code == sf::Keyboard::Space)
			keysDown[SPACE] = false;
	}
}

void Engine::applyInput(Entity* entity, sf::Uint32 delta)
{
	if(entity == NULL)
		return;
	if(keysDown[UP])
		entity->rotatePitch(0.1f*delta);
	if(keysDown[DOWN])
		entity->rotatePitch(-0.1f*delta);
	if(keysDown[Q])
		entity->rotateRoll(-0.1f*delta);
	if(keysDown[E])
		entity->rotateRoll(0.1f*delta);
	if(keysDown[LEFT])
		entity->rotateYaw(-0.1f*delta);
	if(keysDown[RIGHT])
		entity->rotateYaw(0.1f*delta);
	if(keysDown[A])
		entity->thrusters(0.005f*delta);
	if(keysDown[Z])
		entity->thrusters(-0.005f*delta);

	static bool justonce=false;
	if(keysDown[SPACE])
	{
		if(!justonce)
		{
			Shader* s=getShader(activeEntity);
			if(s!=unused_shaders.back())
			{
				if(shader_storage.size()==0) shader_storage.push_back(s);
				renderWithShader(activeEntity, unused_shaders.back());
			}
			else
			{
				renderWithShader(activeEntity, shader_storage.back());
			}
			justonce=true;
		}
	}
	else justonce=false;
}

void Engine::addEntity(Entity* entity, Shader* shader)
{
	objects.push_back(std::make_pair(entity,shader));
}

void Engine::renderWithShader(Entity* entity, Shader* shader)
{
	bool success=false;
	for(auto it=objects.begin(); it!=objects.end(); ++it)
	{
		if(it->first==entity)
		{
			it->second=shader;
			success=true;
			break;
		}
	}
	if(!success) std::cerr << "Couldn't set shader to entity. Entity doesn't exist." << std::endl;
}

Shader* Engine::getShader(Entity* entity) const
{
	bool success=false;
	Shader* ret=NULL;
	for(auto it=objects.begin(); it!=objects.end(); ++it)
	{
		if(it->first==entity)
		{
			ret=it->second;
			success=true;
			break;
		}
	}
	if(!success) std::cerr << "Couldn't get shader from entity. Entity doesn't exist." << std::endl;
	return ret;
}

void Engine::setActive(Entity* entity)
{
	activeEntity = entity;
}

