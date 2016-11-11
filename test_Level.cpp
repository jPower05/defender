// ===============================================
// @file   text_Pool.cpp
// @author kmurphy
// @practical defender
// @brief  Test driver for class Level
// ===============================================

#include "Level.h"

void Level::render () const {}
void Enemy::render () const {}
void Enemy::update (float dt) {}

int main() {
	Level level("test");
	
	std::cout <<"Level is \n" <<level;
	return 0;
}


