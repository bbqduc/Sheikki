#include "engine.h"
#include <iostream>

Engine::Engine(int width, int height, int depth)
	: window(sf::VideoMode(width, height, depth), "Shake-engine"),
	graphics(),
	objects(),
	running(true)
{
	for(int i = 0; i < KEYS; ++i)
	{
		keysDown[i] = false;
	}
}

void Engine::removeProjectile(std::list<Projectile*>::iterator j)
{
	delete[] *j;
	projectiles.erase(j);
}

void Engine::gameLoop()
{
	window.SetActive();
	while(running){
		graphics.clearBuffers();
		processEvents();
		for(tObjects::iterator i = objects.begin(); i != objects.end(); ++i)
		{
			(*i)->tick();
			graphics.drawPhong(**i);
		}
		for(tTanks::iterator i = tanks.begin(); i != tanks.end(); ++i)
		{
			(*i)->tick();
			graphics.drawPhong(**i);
		}

		for(tProjectiles::iterator i = projectiles.begin(); i != projectiles.end();)
		{
			float TTL = (*i)->getTTL();
			(*i)->tick();
			if(TTL < 0.0f)
			{
				(*i)->setVelocity(0.0f);
				graphics.drawExplosion(glm::vec3((*i)->position[3]), -TTL, 100.0f);
				if(TTL < -100.0f)
				{
					tProjectiles::iterator j = i; ++i; removeProjectile(j);
					continue;
				}
			}
			else 
				graphics.drawPhong(**i);
			++i;
		}

		if(activeTank)
			activeTank->tick(keysDown, *this);
		window.Display();
	}
	window.Close();
}

void Engine::processEvents()
{
	sf::Event event;
	while (window.PollEvent(event))
	{
		// Close window : exit
		if (event.Type == sf::Event::Closed)
			running=false;
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
			running=false;
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
}

void Engine::addTank(Tank* tank, Shader* shader)
{
	tanks.push_back(tank);
}

void Engine::addProjectile(Projectile* projectile, Shader* shader)
{
	projectiles.push_back(projectile);
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

