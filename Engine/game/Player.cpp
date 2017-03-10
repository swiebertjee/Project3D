#include "../game/Player.hpp"

#include "../game/Level.hpp"
#include "mge/core/Mesh.hpp"
#include "mge/config.hpp"
#include "mge/materials/ChangeColorMaterial.hpp"
#include "mge/auxiliary/AudioManager.h"
#include "PickUps/PickUp.hpp"
#include "PickUps/Splash.hpp"
#include "PickUps/Speed.hpp"

#include "Enums.hpp"

Player::Player(Id playerId, glm::vec2 boardPos, float pTime, float pWait, bool controlled) : GameObject("temp")
{
	_name = "Player" + playerId;
	_id = playerId;

	this->setLocalPosition(glm::vec3(boardPos.x, 1.0f, boardPos.y)); 

	_movement = new MovementBehaviour(this, boardPos, 1.0f, pTime, pWait, controlled);
	this->setBehaviour(_movement);
	if (!controlled) {
		//_visualization = new VisualPickup();
	}
	//this->scale(glm::vec3(0.3f, 0.3f, 0.8f));
	this->setMesh(Mesh::load(config::MGE_MODEL_PATH + "elementcube.obj"));

	glm::vec3 color(
		playerId == Id::p1 ? 1 : playerId == Id::p2 ? 0 : playerId == Id::p3 ? 0 : 0.87f,
		playerId == Id::p2 ? 1 : playerId == Id::p4 ? 0.72f : 0,
		playerId == p3 ? 1 : playerId == Id::p4 ? 0.53f : 0);

	this->setMaterial(new ChangeColorMaterial(Texture::load(config::MGE_TEXTURE_PATH + "player.png"), Texture::load(config::MGE_TEXTURE_PATH + "player_highlight.png"), color));
};

void Player::StorePickUp(PickUp* pickUp)
{
	if (_pickUp == NULL)
	{
		switch (pickUp->GetType())
		{
		case Effect::splash:
			_pickUp = new Splash(0);
			if (IsControlled())
				AudioManager::get()->PlaySoundW(SFX::grabPickup1);
			_visualization->visualizeSplash();
			break;
		case Effect::speed:
			_visualization->visualizeSpeed();
			_pickUp = new Speed(0);
			if (IsControlled())
				AudioManager::get()->PlaySoundW(SFX::grabPickup1);
			break;
		}
	}
}

void Player::UsePickUp()
{
	if (_pickUp != NULL)
	{
		Level* level = Level::get();
		if (level->GetServer() != NULL)
		{
			_pickUp->applyPickUp(this);
		}

		_visualization->clear();
		delete _pickUp;
		_pickUp = NULL;
	}
}

void Player::addScore(int pScore)
{
	_score += pScore;
	//std::cout << "Player " << _id << " scored: " << pScore << std::endl;
}

int Player::getScore()
{
	return _score;
}

glm::vec2 Player::getBoardPos()
{
	return _movement->getBoardPos();
}

void Player::setBoardPos(glm::vec2 pos)
{
	_movement->setBoardPos(pos);
}

glm::vec2 Player::getNextPos()
{
	return _movement->getNextPos();
}

Id Player::getId()
{
	return _id;
}

bool Player::IsControlled()
{
	return _movement->IsControlled();
}