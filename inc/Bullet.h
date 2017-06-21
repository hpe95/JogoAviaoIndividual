#ifndef BULLET_H
#define BULLET_H

#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "Vector2D.h"
#include "BaseCreator.h"
#include <iostream>
#include <vector>

class Enemy;

class Bullet : public SDLGameObject{
public:
	Bullet(Enemy* p_enemy);
	~Bullet();

	void load(Vector2D pVelocity, Vector2D pPosition);
	void load(const LoaderParams* pParams);
	void draw();
	void update();
	void clean();
	void checkCollision();

	bool isActive(){
		return m_active;
	}

	void setActive(bool p_active=true){
		m_active = p_active;
	}

	void setEnemy(Enemy *p_enemy){
		m_enemy = p_enemy;
	}


private:
	//double rotateTowards(Vector2D);

	int m_moveSpeed;

	Enemy *m_enemy;

	Uint32 timeToLive;
	Uint32 bornTime;

	bool m_active;
};

class BulletCreator{
public:
	Bullet* create(Enemy *p_enemy){
		for(auto bullet : bullets){
			if(!bullet->isActive()){
				bullet->setActive();
				bullet->setEnemy(p_enemy);
				return bullet;
			}
		}
		printf("A new bullet was created\n");
		bullets.push_back(new Bullet(p_enemy));
		return bullets.back();
	}

private:
	std::vector<Bullet*> bullets;
};

#endif
