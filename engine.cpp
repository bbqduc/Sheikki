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
	while(window.IsOpened()){
		graphics.clearBuffers();
		processEvents();
		for(auto i = objects.begin(); i != objects.end(); ++i)
		{
			(*i)->tick();
			graphics.draw(*i);
		}
		for(auto i = tanks.begin(); i != tanks.end(); ++i)
		{
			(*i)->tick();
			graphics.draw(*i);
		}
			
		for(auto i = projectiles.begin(); i != projectiles.end();)
		{
			(*i)->tick();
			graphics.draw(*i);
			if((*i)->getTTL() < 0.0f)
			{
				auto j = i; ++i; projectiles.erase(j);
			}
			else ++i;
		}

		if(activeTank)
			activeTank->tick(keysDown, *this);
		sf::Sleep(1);
		window.Display();
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

void Engine::addObject(Entity* entity, Shader* shader)
{
	objects.push_back(entity);
	entity->activeShader = shader;
}

void Engine::addTank(Tank* tank, Shader* shader)
{
	tanks.push_back(tank);
	tank->activeShader = shader;
}

void Engine::addProjectile(Projectile* projectile, Shader* shader)
{
	projectiles.push_back(projectile);
	projectile->activeShader = shader;
}

void Engine::renderWithShader(Entity* entity, Shader* shader)
{
	bool success=false;
	for(auto it=objects.begin(); it!=objects.end(); ++it)
	{
		if(*it == entity)
		{
			(*it)->activeShader = shader;
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
		if(*it==entity)
		{
			ret=(*it)->activeShader;
			success=true;
			break;
		}
	}
	if(!success) std::cerr << "Couldn't get shader from entity. Entity doesn't exist." << std::endl;
	return ret;
}

void Engine::setActive(Tank* tank)
{
	activeTank = tank;
}

void Engine::addModel(std::string id, Model& model)
{
	graphics.addModel(id, model);
}

const Model& Engine::getModel(std::string id)
{
	return graphics.getModel(id);
}

