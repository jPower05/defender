#include "defender.h"
#include "math.h"

#include <iostream>

float firingTime = 0;

void Ship::update(float dt)  {
	//update position
	position += dt * velocity;
	
	//restrict movement
	position.x = clamp(position.x, level->position.x, level->position.x + ASPECT*0.66);

	
	//std::cout << "Ship position " << position.x << " " << position.y << std::endl;

	
	
}



void Bullet::update(float dt)  {
	position += dt*velocity;
}



void Bomb::update(float dt)  {}
void Enemy::update(float dt)  {}

void update() {
	level->update(dt);
	ship.update(dt);
	for(int enemy = 0; enemy < level->enemyLength;enemy++)level->enemies[enemy].update(dt);
	checkShipCollisionWithGround();
}




void checkShipCollisionWithGround(){
	//Find the two points of the ground the ship is between. 
	//loop through all points of ground
		for( int k=0; k<level->groundLength; ++k) {
			if (level->ground[k].x >= ship.position.x) {
				//if the ground point is just past the ship use this point
				float pastPointX = level->ground[k].x;
				float pastPointY = level->ground[k].y;
				//std::cout<< "The past point is " << pastPointX << " " << pastPointY << std::endl;

				//Use the point previous which should be just behind the ship
				float previousPointX = level->ground[k-1].x;
				float previousPointY = level->ground[k-1].y;
				//std::cout<< "The previous point is " << previousPointX << " " << previousPointY << std::endl;
			
				
				const float EPSILON = 0.001f;

				float a = (pastPointY - previousPointY) / (previousPointX - previousPointX);
   				float b = previousPointY - a * previousPointX;
   				if ( fabs(ship.position.y - (a*ship.position.x+b)) < EPSILON)
   				{
   	    			std::cout<<"Collision"<<std::endl;
				}
			}
   		
		}

	
}

	
	
		
