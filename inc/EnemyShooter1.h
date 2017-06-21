#ifndef __ENEMYSHOOTER1__
#define __ENEMYSHOOTER1__

#include "Enemy.h"
#include "Player.h"
#include "EnemyBullet.h"

class EnemyShooter1 : public Enemy{
public:
	EnemyShooter1();
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

class EnemyShooter1Creator : public BaseCreator{
	GameObject* createGameObject() const{
		return new EnemyShooter1();
	}
};

#endif