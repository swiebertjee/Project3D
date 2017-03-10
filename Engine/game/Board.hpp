#ifndef BOARD_H
#define BOARD_H

#include "../game/Tile.hpp"
#include "../game/Enums.hpp"

class Board : public GameObject
{
	
public:
	Board();

	bool outOfBounds(glm::vec2);
	void ResetBoard();
	void splash(Id playerId, glm::vec2 pBoardPos);

	void setOwner(glm::vec2 pBoardPos, Id pPlayer);
	Id getOwnerOfTile(glm::vec2 pBoardPos);

	int getScore(Id pPlayerId);
	void changeScore(Id pPlayerId, int change);
	Id getPlayerWithHighestScore();

	Tile* getTile(glm::vec2 pBoardPos);
	void resolveConnections();
	void resolveAreas();

	void checkTile(Tile* pTile);

private:
	vector<Tile*> _tilesToBeChecked;

	int _score[4] = { 0,0,0,0 };

	glm::vec2 _size = glm::vec2(9, 9);

	Tile* _boardArray[9][9];

	void initializeBoard();
};
#endif