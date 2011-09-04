#ifndef ENGINE_H
#define ENGINE_H

#include "graphics.h"
#include "entity.h"
#include <SFML/Window.hpp>
#include <list>

class Engine
{
	static enum {UP, DOWN, LEFT, RIGHT, A, Z, Q, E} keys; 
	bool keysDown[8];
	sf::Window window;	
	Graphics graphics;
	std::list<Entity> objects;
	Entity* activeEntity; // This is the object being controlled by user input

	void processEvents();
	void handleKeyPress(sf::Event&);
	void applyInput(Entity*);

	public:
	Engine(int width = 800, int height = 600, int depth = 32);
	Entity& addEntity(Entity&);
	void setActive(Entity&);

	void gameLoop();
};
#endif
