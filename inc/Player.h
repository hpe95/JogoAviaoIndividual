#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "BaseCreator.h"
#include "Timer.h"
#include "Bullet.h"

#include <string>
#include <SDL2/SDL.h>

class Player : public SDLGameObject{
public:
	Player();

	void load(const LoaderParams* pParams);
	void draw();
	void update();
	void clean();
	int getLife(){
		return m_life;
	}
	void setLife(int life){
		m_life = life;
	}
private:
	void handleInput();
	BulletCreator bulletCreator;
	Uint32 m_time;
	int m_life;
	int m_fireRate;
	//std::vector<Enemy*> m_enemy;
	Enemy* m_enemy1 = NULL;
	Enemy* m_enemy2 = NULL;
};

class PlayerCreator : public BaseCreator{
	GameObject* createGameObject() const{
		return new Player();
	}
};

#endif
