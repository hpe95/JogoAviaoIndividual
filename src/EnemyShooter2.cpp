#include "EnemyShooter2.h"
#include "Game.h"
#include "TextureManager.h"
#include "PlayState.h"
EnemyShooter2::EnemyShooter2() : Enemy(){
	m_fireRate = 10;
	TextureManager::Instance().load("assets/clash3.png", "bulletboss", Game::Instance().getRenderer());
}

void EnemyShooter2::load(const LoaderParams* pParams){
	Enemy::load(pParams);
	printf("Created EnemyShooter2\n");
}

void EnemyShooter2::draw(){
	Enemy::draw();
}

void EnemyShooter2::update(){
	m_currentFrame = int(((SDL_GetTicks() / 100) % 1));
	if(Game::Instance().getStateMachine()->currentState()->getStateID() == "PLAY"){
		PlayState *playState = dynamic_cast<PlayState*>(Game::Instance().getStateMachine()->currentState());
		if(playState->getLevel() != NULL && m_player == NULL){
			printf("Player is set\n");
			m_player = playState->getLevel()->getPlayer();
		}
	}

	if(m_position.getX() <= 1280)
		attack();
	/*if(!tilt){
		attack();
		tilt = true;
	}*/

	Enemy::update();
}

void EnemyShooter2::attack(){
	Vector2D pos = m_player->getPosition();
	Vector2D playerPivot = Vector2D(m_player->getWidth()/2+pos.getX(), m_player->getHeight()/2 + pos.getY());
	
	pos = getPosition();
	Vector2D bossPivot = Vector2D(getWidth()/2+pos.getX(), getHeight()/2 + pos.getY());
	Vector2D bossPivot1 = Vector2D(getWidth()/2+pos.getX(), (getHeight()/2 + pos.getY() + 30));

	Vector2D velocity = Vector2D(-1,0);

 	velocity = velocity.norm();
	EnemyBullet *bullet =  bulletCreator.create(m_player);
	EnemyBullet *bullet1 =  bulletCreator.create(m_player);
	bullet->load(velocity, bossPivot);
	bullet1->load(velocity, bossPivot1);
	Game::Instance().getStateMachine()->currentState()->addGameObject(bullet);
	Game::Instance().getStateMachine()->currentState()->addGameObject(bullet1);

}

void EnemyShooter2::clean(){
	Enemy::clean();
}
