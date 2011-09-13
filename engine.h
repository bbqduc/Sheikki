#ifndef ENGINE_H
#define ENGINE_H

#include "graphics.h"
#include "entity.h"
#include <SFML/Window.hpp>
#include <list>

class Engine
{
	private:
		static enum {UP, DOWN, LEFT, RIGHT, A, Z, Q, E, SPACE} keys; 
		static const unsigned int KEYS=9;
		bool keysDown[KEYS];
		sf::Window window;	
		Graphics graphics;
		std::vector<Shader*> unused_shaders;
		std::vector<Shader*> shader_storage; // Just for demo purposes.
		std::list<std::pair<Entity*, Shader*> > objects;
		Entity* activeEntity; // This is the object being controlled by user input

		void processEvents();
		void handleKeyPress(sf::Event& e);
		void applyInput(Entity* entity, sf::Uint32 delta);

	public:
		Engine(int width = 800, int height = 600, int depth = 32);
		void addEntity(Entity* entity, Shader* shader=NULL);
		void addShader(Shader* shader) {unused_shaders.push_back(shader);}
		void renderWithShader(Entity* entity, Shader* shader);
		Shader* getShader(Entity* entity) const;
		void setActive(Entity* entity);

		void gameLoop();
};
#endif
