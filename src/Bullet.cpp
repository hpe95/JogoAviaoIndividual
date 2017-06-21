#include "Bullet.h"
#include "SDLGameObject.h"
#include "Vector2D.h"
#include "LoaderParams.h"
#include "Timer.h"
#include "Player.h"
#include "Game.h"
#include "Physics.h"
#include "InputHandler.h"
#include "Enemy.h"
#include <iostream>
#include <string>   

Bullet::~Bullet(){
	//INFO("Bullet destroyed")
}

Bullet::Bullet(Enemy *p_enemy) : SDLGameObject(){

	setEnemy(p_enemy);

	timeToLive = 1000;
	m_active = true;
}

void Bullet::load(const LoaderParams* pParams){
	m_velocity = Vector2D(0,0);

	SDLGameObject::load(pParams);
}
/*
double Bullet::rotateTowards(Vector2D pPosition){
	Vector2D target = InputHandler::Instance().getMousePosition() - pPosition;
	target = target.norm();

	Vector2D horizontal(0,1);

	return Vector2D::angle(target, Vector2D(0, 1));
}*/
void Bullet::load(Vector2D pVelocity, Vector2D pPosition){
	//double angle = rotateTowards(pPosition);

	m_moveSpeed = 5;
	LoaderParams* pParams = new LoaderParams(pPosition.getX(), pPosition.getY(), 60, 30, "bullet", 0, 0, 0);
	SDLGameObject::load(pParams);

	m_currentFrame = 0;
	bornTime = Timer::Instance().step();
	m_velocity = pVelocity.norm() * m_moveSpeed;
}

void Bullet::draw(){
	SDLGameObject::draw();
}

void Bullet::update(){
	m_position += m_velocity;

	if(Timer::Instance().step() >= bornTime + timeToLive){
		m_active = false;
		Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
	}

	checkCollision();

}

void Bullet::checkCollision(){
	if(m_active){
		Vector2D pos = m_enemy->getPosition();
		Vector2D thisPos = getPosition();
		if(Physics::Instance().checkCollision(dynamic_cast<SDLGameObject*>(m_enemy), dynamic_cast<SDLGameObject*>(this))){
			m_active = false;
			Game::Instance().getStateMachine()->currentState()->removeGameObject(this);
			printf("COLLIDIIIIIIIU\n");
			m_enemy->takeDamage(100);
			int score = Game::Instance().getScore();
			Game::Instance().setScore(score + 10);
			TextureManager::Instance().loadText(std::to_string(Game::Instance().getScore()), "assets/fonts/Lato-Regular.ttf", "score", {0,0,0}, 50, Game::Instance().getRenderer());
			//INFO("Bullet collided");
		}
	}
}

void Bullet::clean(){
	SDLGameObject::clean();
}

