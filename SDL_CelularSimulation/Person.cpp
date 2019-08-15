#include "Person.h"
#include "PRandom.h"

Person::Person(int x, int y, Colony* colony, int strenght, bool disease, World* world)
	: mDisease(disease)
	, mStr(strenght)
	, mColony(colony)
	, mAge(1)
	, mBirthProgress(0)
	, posX(x)
	, posY(y)
	, mWorld(world)
{
}

Person::~Person()
{
}

void Person::update(double deltaTime)
{
	if (mBirthProgress < 500) {
		mBirthProgress++;
		printf("Birth progress: %i\n", mBirthProgress);
	}
	else
	{
		mBirthProgress = 0;
		//Look for free adjacent tiles
		for (int x = posX - 1; x <= posX + 1; x++) {
			for (int y = posY - 1; y <= posY + 1; y++) {
				if (mWorld->isLandAt(x, y)) {
					if (mWorld->getPersonAt(x, y) == nullptr) {
						printf("Spawning person at X:%i Y:%i\n", x, y);
						int strenght = std::clamp(this->getStrenght() + PRandom::RandomInt(0, 5), 0, 100);
						bool disease = mDisease ? (PRandom::RandomInt(0, 1) > 0 ? false : true) : false;
						Person* newPers = new Person(x, y, mColony, 100, false, mWorld);
						mColony->addPerson(newPers);
						goto STOP;
					}
				}
			}
		}
	STOP:
		{}
	}
	moveInRandomDirection(deltaTime);
}


void Person::render(SDL_Renderer* renderer)
{
	//Rendering according to the grid, pos * size gives the position in world coordinates, not grid coordinates
	SDL_Rect persRect = { posX * persSizeW, posY * persSizeH, persSizeW, persSizeH };
	SDL_SetRenderDrawColor(renderer, mColony->getColor().r, mColony->getColor().g, mColony->getColor().b, mColony->getColor().a);
	SDL_RenderFillRect(renderer, &persRect);
}

void Person::moveInRandomDirection(double deltaTime)
{
	int movingDirection = PRandom::RandomInt(0, 3);
	// 0 = up
	// 1 = left
	// 2 = down
	// 3 = right

	int nextPosX = posX;
	int nextPosY = posY;

	switch (movingDirection)
	{
	case 0:
		nextPosY++;
		break;
	case 1:
		nextPosX++;
		break;
	case 2:
		nextPosY--;
		break;
	case 3:
		nextPosX--;
		break;
	default:
		break;
	}

	//Check to see if still inside grid
	if (World::GRID_SIZE_X > nextPosX) {
		if (World::GRID_SIZE_Y > nextPosY) {
			//There is no person on the chunk where we want to move
			if (mWorld->getPersonAt(nextPosX, nextPosY) == nullptr) {

				if (mWorld->isLandAt(nextPosX, nextPosY)) {
					//printf("Person at X:%i Y:%i moving to X:%i Y:%i\n", posX, posY, nextPosX, nextPosY);
					mWorld->RegisterMoveOnGrid(this, nextPosX, nextPosY);
					posX = nextPosX;
					posY = nextPosY;
				}
				else {
					//printf("Person at X:%i Y:%i unable to move because water at X:%i Y:%i\n", posX, posY, nextPosX, nextPosY);
				}
			}
			else {
				//printf("Person at X:%i Y:%i unable to move because person at X:%i Y:%i\n", posX, posY, nextPosX, nextPosY);
			}
		}
	}


}
