#pragma once
#include "SDL.h"
#include <string>

class Person;


class World
{
public:
	World(SDL_Renderer* renderer);
	~World();

public:
	void update(double deltaTime);
	void render();

	bool isLandAt(int x, int y) const;
	//Returns NULLPTR of there is NO PERSON at given coordinates
	Person* getPersonAt(int x, int y) const;

	void addPersonToGrid(Person* pers, int x, int y) { worldGrid[x][y] = pers; }
	void RegisterMoveOnGrid(Person* movingPerson, int newX, int newY);

	static constexpr int MAP_SIZE_X = 640;
	static constexpr int MAP_SIZE_Y = 480;
	//ALWAYS DIVIDE WITH THE POWER OF 2 OR LOSS OF PRECISION
	static constexpr int GRID_SIZE_X = MAP_SIZE_X / 2;
	static constexpr int GRID_SIZE_Y = MAP_SIZE_Y / 2;
	
	static constexpr int CHUNK_SIZE_X = MAP_SIZE_X / GRID_SIZE_X;
	static constexpr int CHUNK_SIZE_Y = MAP_SIZE_Y / GRID_SIZE_Y;

private:
	SDL_Renderer* mRenderer = nullptr;
	SDL_Texture* worldMapTexture = nullptr;
	SDL_Surface* loadedMapSurface = nullptr;
	void loadWorldMapTexture(std::string path);
	Person* worldGrid[GRID_SIZE_X][GRID_SIZE_Y];

	bool isLandAtPixel(int x, int y) const;
};

