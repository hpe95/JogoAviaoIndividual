#include "Player.h"
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "TextureManager.h"
#include "Game.h"
#include "PlayState.h"
#include <string>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

Player::Player() : SDLGameObject(){
	m_fireRate = 500;
	m_life = 100;
	TextureManager::Instance().load("assets/clash3.png", "bullet", Game::Instance().getRenderer());
	TextureManager::Instance().load("assets/health.png", "health", Game::Instance().getRenderer());
}

void Player::load(const LoaderParams* pParams){
	SDLGameObject::load(pParams);
}

void Player::draw(){
	SDLGameObject::draw();
}

void Player::update(){
	m_currentFrame = int(((SDL_GetTicks() / 100) % 1));
	if(Game::Instance().getStateMachine()->currentState()->getStateID() == "PLAY"){
		PlayState *playState = dynamic_cast<PlayState*>(Game::Instance().getStateMachine()->currentState());
		if((playState->getLevel() != NULL && m_enemy1 == NULL)){
			printf("Enemy is set\n");
			m_enemy1 = playState->getLevel()->getEnemyShooter2();
			
		}
	}
	handleInput();

	SDLGameObject::update();
}

void Player::clean(){
	SDLGameObject::clean();
}

void Player::handleInput(){
	Vector2D movement(0, 0);
	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_Z, 200)){
		//AudioManager::Instance().playChunk("assets/sounds/shot.wav");
		//INFO("FIRE RATE: " + m_fireRate);
		Vector2D pivot = Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY());
		Vector2D target = Vector2D(1,0);
		target = target.norm();
		Bullet *bullet =  bulletCreator.create(m_enemy1);
		bullet->load(target, Vector2D(m_width/2+m_position.getX(), m_height/2 + m_position.getY()));
		Game::Instance().getStateMachine()->currentState()->addGameObject(bullet);
		
	}

	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_UP)){
		movement += Vector2D(0,-1);
	}
	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_DOWN)){
		movement += Vector2D(0,1);
	}
	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_LEFT)){
		movement += Vector2D(-1,0);
	}
	if(InputHandler::Instance().isKeyDown(SDL_SCANCODE_RIGHT)){
		movement += Vector2D(1,0);
	}
	movement = movement.norm() * 10;

	m_velocity = movement;
	
}
