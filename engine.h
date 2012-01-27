#ifndef ENGINE_H
#define ENGINE_H

#include "graphics.h"
#include "entity.h"
#include "tank.h"
#include "projectile.h"
#include <SFML/Window.hpp>
#include <list>

class Engine
{
	typedef std::list<Entity*> tObjects;
	typedef std::list<Tank*> tTanks;
	typedef std::list<Projectile*> tProjectiles;
	private:
		static const unsigned int KEYS=9;
		bool keysDown[KEYS];
		sf::Window window;	
		Graphics graphics;
		std::vector<Shader*> unused_shaders;
		std::vector<Shader*> shader_storage; // Just for demo purposes.

		std::list<Entity*> objects;
		std::list<Tank*> tanks;
		std::list<Projectile*> projectiles;

		Tank* activeTank; // This is the object being controlled by user input

		void processEvents();
		void handleKeyPress(sf::Event& e);
		void applyInput(Entity* entity, sf::Uint32 delta);

		bool running;

	public:
		static enum {UP, DOWN, LEFT, RIGHT, A, Z, Q, E, SPACE} keys; 

		Engine(int width = 800, int height = 600, int depth = 32);
		void addModel(std::string id, Model& model);
		const Model& getModel(std::string id);

		void addObject(Entity* entity, Shader* shader=NULL);
		void addTank(Tank* tank, Shader* shader=NULL);
		void addProjectile(Projectile* projectile, Shader* shader=NULL);
		void removeProjectile(std::list<Projectile*>::iterator j);


		void addShader(Shader* shader) {unused_shaders.push_back(shader);}
		void setActive(Tank* tank);

		void gameLoop();
};
#endif
