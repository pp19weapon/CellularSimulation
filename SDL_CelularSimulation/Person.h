#pragma once
#include "Colony.h"
#include "World.h"
#include <random>

class Person
{
public:
	Person(int x, int y, Colony* colony, int strenght, bool disease, World* world);
	~Person();

public:
	bool hasDisease() { return mDisease; }
	int getAge() const { return mAge; }
	int getStrenght() const { return mStr; }
	Colony* getColonyID() const { return mColony; }
	int getPosX() { return posX; }
	int getPosY() { return posY; }

	void update(double deltaTime);
	void render(SDL_Renderer* renderer);

private:
	bool mDisease;
	int mAge;
	int mStr;
	int mBirthProgress;
	Colony* mColony;
	World* mWorld;

	
	int posX, posY;
	//Get the size of the rendering rectangle, it's the same as 1 chunk in the grid
	const int persSizeH = World::MAP_SIZE_Y / World::GRID_SIZE_Y;
	const int persSizeW = World::MAP_SIZE_X / World::GRID_SIZE_X;

	void moveInRandomDirection(double deltaTime);



};

