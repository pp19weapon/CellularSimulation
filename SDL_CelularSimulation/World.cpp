#include "World.h"
#include "SDL_image.h"
#include <stdio.h>
#include "Person.h"

Colony* testColony;

World::World(SDL_Renderer* renderer)
	:mRenderer(renderer)
{
	std::fill(worldGrid[0], worldGrid[0] + (GRID_SIZE_X) * (GRID_SIZE_Y), nullptr);
	loadWorldMapTexture("map.png");

	//TODO Remove tests
	///Do tests
	int x = GRID_SIZE_X / 3;
	int y = GRID_SIZE_Y / 3;
	//printf("Is land at ( x:%i )( y:%i ) -> ( %d ).\n", x, y, isLandAt(x, y));
	//printf("Person at ( x:%i )( y:%i ) -> ( %i ).\n", x, y, worldGrid[x][y] ? 1 : 0);

	testColony = new Colony(1, x, y, 0, this);
	
}

World::~World()
{
	SDL_FreeSurface(loadedMapSurface);
	loadedMapSurface = nullptr;

	delete testColony;

	//delete worldMapTexture;
	worldMapTexture = nullptr;
}

void World::update(double deltaTime)
{
	testColony->update(deltaTime);
}

void World::render()
{
	SDL_RenderCopy(mRenderer, worldMapTexture, NULL, NULL);
	testColony->render(mRenderer);
}

bool World::isLandAt(int x, int y) const
{
	//Transform GRID coordinates to MAP coordinates(pixel)
	int mapX = x * CHUNK_SIZE_X;
	int mapY = y * CHUNK_SIZE_Y;

	for (int xx = mapX; xx < mapX + CHUNK_SIZE_X; xx++) {
		for (int yy = mapY; yy < mapY + CHUNK_SIZE_Y; yy++) {
			if (!isLandAtPixel(xx, yy)) {
				return false;
			}
		}
	}
	return true;
}

Person* World::getPersonAt(int x, int y) const
{
	if ((x > GRID_SIZE_X) || (y > GRID_SIZE_Y)) {
		printf("ERROR: Coordinates for getPersonAt are out of bounds of the grid!");
		return nullptr;
	}

	return worldGrid[x][y];
}

void World::RegisterMoveOnGrid(Person* movingPerson, int newX, int newY)
{
	if (worldGrid[newX][newY] == nullptr) {
		int tempX, tempY;
		tempX = movingPerson->getPosX();
		tempY = movingPerson->getPosY();
		worldGrid[newX][newY] = movingPerson;
		worldGrid[tempX][tempY] = nullptr;
	}
}


void World::loadWorldMapTexture(std::string path)
{
	loadedMapSurface = IMG_Load(path.c_str());
	if (loadedMapSurface == nullptr)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		worldMapTexture = SDL_CreateTextureFromSurface(mRenderer, loadedMapSurface);
		if (worldMapTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
	}
}

bool World::isLandAtPixel(int x, int y) const
{
	Uint32 pixelData;

	int bpp = loadedMapSurface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8* p = (Uint8*)loadedMapSurface->pixels + y * loadedMapSurface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		pixelData = *p;
		break;

	case 2:
		pixelData = *(Uint16*)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			pixelData = p[0] << 16 | p[1] << 8 | p[2];
		else
			pixelData = p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		pixelData = *(Uint32*)p;
		break;

	default:
		pixelData = 0;       /* shouldn't happen, but avoids warnings */
	}

	SDL_Color pixelColor;
	SDL_GetRGBA(pixelData, loadedMapSurface->format, &pixelColor.r, &pixelColor.g, &pixelColor.b, &pixelColor.a);

	SDL_Color waterColor;
	waterColor.a = 255;
	waterColor.b = 255;
	waterColor.g = 0;
	waterColor.r = 0;

	//printf("Pixel color at %i %i is r%i g%i b%i\n", x, y, pixelColor.r, pixelColor.g, pixelColor.b);

	if (
		(pixelColor.b == waterColor.b) &&
		(pixelColor.g == waterColor.g) &&
		(pixelColor.r == waterColor.r)
		)
	{
		return false;
	}
	else {
		return true;
	}
}
