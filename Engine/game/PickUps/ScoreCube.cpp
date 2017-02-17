#include "ScoreCube.hpp"
#include "mge/core/World.hpp"
#include "mge/materials/LitMaterial.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"

#include "../game/Player.hpp"
#include "../game/Board.hpp"
#include "../game/Level.hpp"

ScoreCube::ScoreCube() : PickUp("ScoreCube")
{
	this->setMaterial(new LitMaterial(LitMaterial::fragment, glm::vec3(0, 1, 0)));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "special_cube.obj"));
	this->scale(glm::vec3(0.3f));

	_minDelay = 4;
	_maxDelay = 10;

	reset();
}

void ScoreCube::applyPickUp(Player* pPlayer)
{
	pPlayer->addScore(Level::getBoard()->getScore(pPlayer->getId()));
	reset();
}