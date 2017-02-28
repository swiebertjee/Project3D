#include "Tile.hpp"
#include "mge/core/World.hpp"
#include "mge/config.hpp"
#include "mge/auxiliary/TextureCache.hpp"

Tile::Tile(glm::vec3 pPosition, Mesh* pMesh) : GameObject("tile")
{
	this->setLocalPosition(pPosition);

	_material = new LitMaterial(LitMaterial::vertex);
	//Texture * texture = Texture::load(config::MGE_TEXTURE_PATH + "playfield_tile_sg_Ambient_occlusion.png");
	_material = new LitMaterial();
	this->setMaterial(_material);
	this->setMesh(pMesh);
}

void Tile::setOwner(Id pPlayer)
{
	_owner = pPlayer;

	switch (pPlayer)
	{
	case none:
		_material->setColor(glm::vec3(1));
		break;

	case p1:
		_material->setColor(glm::vec3(1, 0, 0));
		break;

	case p2:
		_material->setColor(glm::vec3(0, 1, 0));
		break;

	case p3:
		_material->setColor(glm::vec3(0, 0, 1));
		break;

	case p4:
		_material->setColor(glm::vec3(0.87f, 0.72f, 0.53f));
		break;
	}
}

Id Tile::getOwner()
{
	return _owner;
}