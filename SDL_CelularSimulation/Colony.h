#pragma once
#include "SDL.h"
#include <vector>

class Person;
class World;

class Colony
{
public:
	Colony(int population, int spawnPositionX, int spawnPositionY, int ID, World* world);
	~Colony();
	
	void update(double deltaTime);
	void render(SDL_Renderer* renderer);

	SDL_Color setColor(SDL_Color newColor) { mColor = newColor; }
	SDL_Color getColor() { return mColor; }

	void addPerson(Person* pers);

private:
	void InitialSpawn();

	int mPopulation;
	int mStartingPosX;
	int mStartingPoxY;
	int mID;
	World* mWorld;

	//Person* mPeople[1000];
	std::vector<Person*> mPeople;
	SDL_Color mColor;
};

