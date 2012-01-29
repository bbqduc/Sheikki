#include "engine.h"
#include <iostream>
#include <GL/glfw.h>

bool Engine::running;
bool Engine::keysDown[Engine::KEYS];

void GLFWCALL handleKeyPress(int,int);
Engine::Engine(int width, int height, int depth)
	:graphics(),
	objects()
{
	running=true;
	glfwSetKeyCallback(handleKeyPress);
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
	while(running)
	{
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
				glm::vec3 explpos=glm::vec3((*i)->position[3]);
				graphics.drawExplosion(explpos, -TTL / 100.0f);
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
		glfwSwapBuffers();
	}
	glfwTerminate();
}

void Engine::processEvents()
{
	running=(bool)glfwGetWindowParam(GLFW_OPENED);
}

void GLFWCALL handleKeyPress(int key, int action)
{
	if(action==GLFW_PRESS)
	{
		if(key == GLFW_KEY_ESC)
			Engine::stop();
		if(key == GLFW_KEY_UP)
			Engine::setKey(Engine::UP);
		if(key == GLFW_KEY_DOWN)
			Engine::setKey(Engine::DOWN);
		if(key == GLFW_KEY_LEFT)
			Engine::setKey(Engine::LEFT);
		if(key == GLFW_KEY_RIGHT)
			Engine::setKey(Engine::RIGHT);
		if(key == 'A')
			Engine::setKey(Engine::A);
		if(key == 'Z')
			Engine::setKey(Engine::Z);
		if(key == 'Q')
			Engine::setKey(Engine::Q);
		if(key == 'E')
			Engine::setKey(Engine::E);
		if(key == GLFW_KEY_SPACE)
			Engine::setKey(Engine::SPACE);
	}	

	if(action==GLFW_RELEASE)
	{
		if(key == GLFW_KEY_UP)
			Engine::unsetKey(Engine::UP);
		if(key == GLFW_KEY_DOWN)
			Engine::unsetKey(Engine::DOWN);
		if(key == GLFW_KEY_LEFT)
			Engine::unsetKey(Engine::LEFT);
		if(key == GLFW_KEY_RIGHT)
			Engine::unsetKey(Engine::RIGHT);
		if(key == 'A')
			Engine::unsetKey(Engine::A);
		if(key == 'Z')
			Engine::unsetKey(Engine::Z);
		if(key == 'Q')
			Engine::unsetKey(Engine::Q);
		if(key == 'E')
			Engine::unsetKey(Engine::E);
		if(key == GLFW_KEY_SPACE)
			Engine::unsetKey(Engine::SPACE);
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

