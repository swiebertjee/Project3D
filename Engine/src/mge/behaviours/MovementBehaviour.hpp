#ifndef MOVEMENTBEHAVIOUR_H
#define MOVEMENTBEHAVIOUR_H

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <glm.hpp>
#include "../game/Tile.hpp"

class MovementBehaviour : public AbstractBehaviour
{
	public:
		MovementBehaviour(GameObject* pPlayer, Tile* boardArray[9][9], float pJumpHeight, float pTime, float pWait);
		virtual ~MovementBehaviour();

		virtual void update(float pStep);
		void message(sendMsg::Message) { };
	private:

		void checkKeys();
		void setDirection();
		
		void roll(float pStep);
		void move(float pPhase, float pTime);


		enum Direction
		{
			none,
			up,
			down,
			left,
			right
		};
		
		GameObject* player;

		//set
		Tile* boardArray[9][9];

		float totalTime = 1;
		float waitPerc = 0.2f;
		float jumpHeight = 0.4f;

		//updated
		glm::vec3 axis = glm::vec3(1,0,0);
		glm::vec3 trans = glm::vec3(1, 0, 0);

		glm::mat4 worldMat;

		bool moving = true;

		float moveTime = totalTime;
		float curTime = 0;
		float deltaTime = 0;
		float lastMoveTime = 0;
		float distance = 1;
		float lastHeight = 0;
		Direction cDir = none;
		Direction dDir = none;
};

#endif // ROTATINGBEHAVIOUR_H
