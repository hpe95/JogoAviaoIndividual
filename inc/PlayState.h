#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include "GameState.h"
#include "SDLGameObject.h"
#include "Level.h"

class PlayState : public GameState{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const {
		return s_playID;
	}

	Level* getLevel(){
		return pLevel;
	}

private:
	static const std::string s_playID;
	Level *pLevel = NULL;
	int m_playerLife = 100;
	Player *m_player;
	bool checkCollision(SDLGameObject *p1, SDLGameObject *p2);
};

#endif
