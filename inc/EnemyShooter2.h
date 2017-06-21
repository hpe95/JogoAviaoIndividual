#ifndef __ENEMYSHOOTER2__
#define __ENEMYSHOOTER2__

#include "Enemy.h"
#include "Player.h"
#include "EnemyBullet.h"

class EnemyShooter2 : public Enemy{
public:
	EnemyShooter2();
	virtual void load(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	virtual void attack();
	Player *m_player = NULL	;
	int m_fireRate;
	EnemyBulletCreator bulletCreator;
};

class EnemyShooter2Creator : public BaseCreator{
	GameObject* createGameObject() const{
		return new EnemyShooter2();
	}
};

#endif