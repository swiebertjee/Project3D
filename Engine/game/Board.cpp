#include "../game/Board.hpp"
#include "Tile.hpp"

#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/auxiliary/MeshCache.hpp"

Board::Board() : GameObject("Board")
{
	initializeBoard();
}

void Board::setOwner(glm::vec2 boardPos, Id player)
{
	if (outOfBounds(boardPos))
		return;

	_boardArray[(int)boardPos.x][(int)boardPos.y]->setOwner(player);
}

void Board::initializeBoard() 
{
	Mesh* planeMesh;
	if (MeshCache::exists(config::MGE_MODEL_PATH + "playfield_tile.obj")) {
		planeMesh = MeshCache::find(config::MGE_MODEL_PATH + "playfield_tile.obj");
	}
	else {
		planeMesh = Mesh::load(config::MGE_MODEL_PATH + "playfield_tile.obj");
		MeshCache::push(planeMesh);
	}

	for (int i = 0; i < _size.x; i++) {
		for (int j = 0; j < _size.y; j++) 
		{
			Tile * tile = new Tile(glm::vec3(j, 0.f, i), planeMesh);
			_boardArray[j][i] = tile;
			tile->setParent(this);
		}
	}
}

bool Board::outOfBounds(glm::vec2 pos)
{
	if (pos.x < 0 || pos.y < 0 || pos.x >= 9 || pos.y >= 9)
		return true;

	return false;
}

int Board::getScore(Id pPlayerId)
{
	int score = 0;

	for (int i = 0; i < _size.x; i++) {
		for (int j = 0; j < _size.y; j++) {

			Tile* tile = _boardArray[j][i];

			if (tile->getOwner() == pPlayerId)
			{
				score++;
				tile->setOwner(none);
			}
		}
	}
	return score;
}

void Board::fireAbility(glm::vec2 pBoardPos)
{
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			glm::vec2 pos = pBoardPos + glm::vec2(i, j);

			if (!outOfBounds(pos))
			{
				Tile* tile = _boardArray[(int)pos.x][(int)pos.y];

				if (tile->getOwner() != none)
					tile->setOwner(fire);
			}
		}
	}
}

void Board::earthAbility(glm::vec2 pBoardPos)
{
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			glm::vec2 pos = pBoardPos + glm::vec2(i, j);

			if (!outOfBounds(pos))
			{
				Tile* tile = _boardArray[(int)pos.x][(int)pos.y];

				if (tile->getOwner() == none)
					tile->setOwner(earth);
			}
		}
	}
}