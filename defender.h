// ===============================================
// @file   defender.h
// @author jpower
// @practical defender
// @brief  Header file for PSP+GLFW(OpenGL) defender game
// ===============================================

#ifndef DEFENDER_H
#define DEFENDER_H

// uncomment next line for PSP executable
// #define PSP 1

// ===============================================
// Headers
// ===============================================
#ifdef PSP								// system specific headers
#else 									  
	#ifdef __APPLE__   						
		#include <GLFW/glfw3.h> 
	#else          						
		#include <GL/glfw.h> 
	#endif
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "Vector2f.h"
#include "Pool.h"

// ===============================================
// Global identifiers
// ===============================================

// setup screen (on both the PSP and OpenGL) with 
// coordinates (0,0) on lower left to (ASPECT,1) on upper right

#ifdef PSP								// PSP specific headers
	const int WINDOW_WIDTH = SCEGU_SCR_WIDTH;  // 480
	const int WINDOW_HEIGHT = SCEGU_SCR_HEIGHT; // 272
#else
	const float SCALE = 1;
	const int WINDOW_WIDTH = (int) (480*SCALE);
	const int WINDOW_HEIGHT = (int) (272*SCALE);
	const float ASPECT = float(WINDOW_WIDTH)/float(WINDOW_HEIGHT);


#endif


//Constants for Radar Screen

	const float RADAR_HEIGHT = 0.1;
	const float RADAR_WIDTH = ASPECT * 0.8;		
	
	const float RADAR_X = (ASPECT - RADAR_WIDTH) / 2;
	const float RADAR_Y = 1.0 - RADAR_HEIGHT;

// state for main game loop
enum GameState {GAME_INTRO, GAME_START, LEVEL_START, LEVEL_PLAY, LEVEL_OVER, GAME_OVER, GAME_QUIT};
extern GameState gameState;

const float SHIP_FIRE_DELAY = 0.4f;

const float BULLET_DIE_DELAY = 1.0f;
const float BULLET_SPEED = 3.0f*0.1f;

using namespace std;

// Basic games object wth state, position and velocity
class Entity {
public:
	enum State {ASLEEP, AWAKE, DEAD};
	
	State state;
	Vector2f position;
	Vector2f velocity;
	
	virtual void render () const = 0;

	virtual void update (float dt) = 0;

	virtual std::string toString() const = 0;

	friend std::ostream& operator <<(std::ostream& outputStream, const Entity& entity) {
		outputStream <<entity.toString();
		return outputStream;
	}		
};


class Ship : public Entity {
	
public:	
	Ship() {
		state = AWAKE;
		position = Vector2f(0.02f, 0.5f);
		velocity = Vector2f(0,0);
		bool shoot;
		float firingTime;
	}

	void render () const;
	void shootBullet();
	bool checkCanFire();
	
	void update (float dt);
	
	std::string toString() const {
		std::ostringstream outs;
		outs <<"Position = " <<position <<"\t Velocity = " <<velocity;
		return outs.str();
	};
	
};
extern Ship ship;


class Enemy : public Entity {
	
public:	
	enum Type {SIMPLE, TRACKING};

	Type type;
	
	Enemy () {
		type = SIMPLE;
		state = ASLEEP;
		position = Vector2f::ZERO;
		velocity = Vector2f::ZERO;
		
	} 
	
	void render () const;
	
	void update (float dt);
	
	std::string toString() const {
		std::ostringstream outs;
		outs <<"Enemy Type =" <<type <<"\t Position = " <<position <<"\t Velocity = " <<velocity;
		return outs.str();
	}
};


class Bullet : public Entity {
public:
	Bullet() { 
		state = AWAKE;
		position = Vector2f(0,0);
		velocity = Vector2f(2,0);
	}

	void render () const;
	
	void update (float dt);

	std::string toString() const {
		std::ostringstream outs;
		outs <<"Bullet " <<"\t Position = " <<position <<"\t Velocity = " <<velocity;
		return outs.str();
	}
};
typedef Pool<Bullet> BulletPool;
//extern BulletPool shipBullets;
//extern BulletPool enemyBullets;


class Bomb : public Entity {
	
public:
	Bomb() {
		state = AWAKE;
		position = Vector2f(0,0);
		velocity = Vector2f(.1,0);
	}

	void render () const;
	
	void update (float dt);

	std::string toString() const {
		std::ostringstream outs;
		outs <<"Bomb " <<"\t Position = " <<position <<"\t Velocity = " <<velocity;
		return outs.str();
	}
	
};
typedef Pool<Bomb> BombPool;
extern BombPool shipBombs;


#include "Level.h"

// frame timing information
extern double startTime, currentTime, previousTime, dt;
extern double previousBulletTime, previousBombTime;

extern bool fire, fireBomb;


// ===============================================
// Function prototypes
// ===============================================
int initGraphics();
int deinitGraphics();
void render();
void update();
void getInput();
void renderRadar();
void checkShipCollisionWithGround();

#endif

