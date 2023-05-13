#include "SpawnerSystem.h"
#include <fstream>

std::vector<Entity> WallSpawner::Spawn(Position position, char subType) {
	int map_width = 0;
	int map_height = 0;

	std::vector<Entity> to_add;

	std::ifstream map_file("Maps/lvl1.txt");

	map_file >> map_width;
	map_file >> map_height;


	switch (subType) {
	case 'w':
		break;
	case' ':
		break;
	case 'b':
		break;
	default:
		break;
	}

	return to_add;
}