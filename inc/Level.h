#ifndef LEVEL_H
#define LEVEL_H

#include "Layer.h"
#include "Player.h"
#include "EnemyShooter1.h"
#include "EnemyShooter2.h"
#include <string>
#include <vector>

struct Tileset{
	int firstGridID;
	int tileWidth;
	int tileHeight;
	int spacing;
	int margin;
	int width;
	int height;
	int numColumns;
	std::string name;
};

class Level{
public:
	~Level(){}

	void update();
	void render();

	std::vector<Tileset>* getTilesets(){
		return &m_tilesets;
	}

	std::vector<Layer*>* getLayers(){
		return &m_layers;
	}
	Player* getPlayer(){
		return m_player;
	}

	void setPlayer(Player *p_player){
		m_player = p_player;
	}

	void setEnemyShooter1(EnemyShooter1 *p_enemyShooter1){
		m_enemyShooter1 = p_enemyShooter1;
	}

	EnemyShooter1* getEnemyShooter1(){
		return m_enemyShooter1;
	}

	void setEnemyShooter2(EnemyShooter2 *p_enemyShooter2){
		m_enemyShooter2 = p_enemyShooter2;
	}

	EnemyShooter2* getEnemyShooter2(){
		return m_enemyShooter2;
	}

private:
	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
	Player *m_player = NULL;
	EnemyShooter1 *m_enemyShooter1 = NULL;
	EnemyShooter2 *m_enemyShooter2 = NULL;
	friend class LevelParser;
	Level(){}
};

#endif
