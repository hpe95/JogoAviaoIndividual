#ifndef __ENEMYBULLET__
#define __ENEMYBULLET__

#include "SDLGameObject.h"
#include "Vector2D.h"
#include "Player.h"
#include "LoaderParams.h"
class EnemyBullet : public SDLGameObject{
public:
	EnemyBullet(Player* target);
	~EnemyBullet();

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

	void setPlayer(Player *target){
		m_player = target;
	}

private:
	//double rotateTowards(Vector2D);

	int m_moveSpeed;

	Player *m_player;

	Uint32 timeToLive;
	Uint32 bornTime;

	bool m_active;
};

class EnemyBulletCreator{
public:
	EnemyBullet* create(Player *target){
		for(auto bullet : bullets){
			if(!bullet->isActive()){
				bullet->setActive();
				bullet->setPlayer(target);
				return bullet;
			}
		}
		
		bullets.push_back(new EnemyBullet(target));
		return bullets.back();
	}

private:
	std::vector<EnemyBullet*> bullets;
};

#endif