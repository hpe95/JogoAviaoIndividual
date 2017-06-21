#include "EnemyBullet.h"
#include "Physics.h"
#include "Game.h"
#include "GameOverState.h"
EnemyBullet::~EnemyBullet(){
}

EnemyBullet::EnemyBullet(Player *target) : SDLGameObject(){
	setPlayer(target);
	timeToLive = 5000;
	m_active = true;
}

void EnemyBullet::load(const LoaderParams* pParams){
	m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}

void EnemyBullet::load(Vector2D pVelocity, Vector2D pPosition){
	//double angle = rotateTowards(pPosition);

	m_moveSpeed = 3;
	LoaderParams* pParams = new LoaderParams(pPosition.getX(), pPosition.getY(), 40, 60, "bulletboss", 0, 0, 0);
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	bornTime = Timer::Instance().step();
	m_velocity = pVelocity.norm() * 2.5;
	//m_velocity = Vector2D(0.5, 0.5);
}

void EnemyBullet::draw(){
	SDLGameObject::draw();
}

void EnemyBullet::update(){
	m_position += m_velocity;

	if(Timer::Instance().step() >= bornTime + timeToLive){
		m_active = false;
		Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
	}

	checkCollision();

}

void EnemyBullet::checkCollision(){
	if(m_active){
		Vector2D pos = m_player->getPosition();
		Vector2D thisPos = getPosition();
		
		if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(m_player), dynamic_cast<SDLGameObject*>(this))){
			m_active = false;
			Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
			printf("Enemy bullet collided\n");
			m_player->setLife((m_player->getLife()) - 5);
			if(m_player->getLife() == 0){
				Game::Instance().getStateMachine()->changeState(new GameOverState());
				Game::Instance().setScore(0);
			}
			//m_player->setLife((m_player->getLife()) - 15);
			//Game::Instance().getStateMachine()->changeState(new GameOverState());
		}
	}
}

void EnemyBullet::clean(){
	SDLGameObject::clean();
}