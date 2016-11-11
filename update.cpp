#include "defender.h"
#include "math.h"

void Ship::update(float dt)  {
	//update position
	position += dt * velocity;
	
	//restrict movement
	position.x = clamp(position.x, level->position.x, level->position.x + ASPECT*0.66);
	
}


void Bullet::update(float dt)  {}
void Bomb::update(float dt)  {}
void Enemy::update(float dt)  {}

void update() {
	level->update(dt);
	ship.update(dt);
	for(int enemy = 0; enemy < level->enemyLength;enemy++)level->enemies[enemy].update(dt);
}
