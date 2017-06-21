#include "Enemy.h"

#include <string>
#include "Game.h"
#include "MainMenuState.h"
using namespace std;

Enemy::Enemy() : SDLGameObject(){
	m_totalHealth = 500;
	m_actualHealth = m_totalHealth;
	//m_velocity.setY(2);
	//m_velocity.setX(0.001);
}

void Enemy::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);

	//m_velocity.setY(2);
}

void Enemy::takeDamage(int damage){
	if(damage >= 0){
		m_actualHealth -= damage;
	} else {
		m_actualHealth = 0;
	}
}

void Enemy::update(){
	//m_currentFrame = int(((SDL_GetTicks() / 100) % 5));

	// if(m_position.getY() < 0){
	// 	m_velocity.setY(2);
	// } else if(m_position.getY() > 400){
	// 	m_velocity.setY(-2);
	// }

	m_velocity.setX(-1);
	if(m_actualHealth == 0){
		Game::Instance().getStateMachine()->changeState(new MainMenuState());
		Game::Instance().setScore(0);
		
	}

	SDLGameObject::update();
}

void Enemy::clean(){
	SDLGameObject::clean();
}

void Enemy::draw(){
	SDLGameObject::draw();
}
