#ifndef PSP

#include "defender.h"
#include "Level.h"

void Level::render() const {

	//draw ceiling
	glColor3ub(0, 10, 100);
	glBegin(GL_QUAD_STRIP);
	for (int k=0; k<level->ceilingLength; ++k) {
    	glVertex3f(level->ceiling[k].x, level->ceiling[k].y, 0.0);
    	glVertex3f(level->ceiling[k].x, 1.0, 0.0);
	}
	glEnd();
	
	 // draw ground
	glColor3ub(0, 100, 0);
	glBegin(GL_QUAD_STRIP);
	for (int k=0; k<level->groundLength; ++k) {
    	glVertex3f(level->ground[k].x, level->ground[k].y, 0.0);
    	glVertex3f(level->ground[k].x, 0.0, 0.0);
	}
	glEnd();
}


void Ship::render() const{
	glPushMatrix();
		glTranslatef(position.x, position.y, 0.0f);
		glScalef(0.1, 0.08, 1);
		glColor3ub(0,200, 0);
		glBegin(GL_QUADS);      
   			glVertex3f(0.0, 0.0, 0.0);
    			glVertex3f(1.0, 0.4, 0.0);
    			glVertex3f(1.0, 0.6, 0.0);
    			glVertex3f(0.0, 1.0, 0.0);

				glColor3ub(0, 0, 200);  

    			glVertex3f(0.0, 0.47, 0.0);
    			glVertex3f(1.1, 0.47, 0.0);
   			glVertex3f(1.1, 0.53, 0.0);
    			glVertex3f(0.0, 0.53, 0.0);
		glEnd();
	glPopMatrix();
}
void Bullet::render() const {
	glColor3f(0,1,0);
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glScalef(0.04, 0.04, 1);

	glBegin(GL_QUADS);		
		glVertex3f(0, 0, 0);
		glVertex3f(1, 0, 0);
		glVertex3f(1, .1, 0);
		glVertex3f(0, .1, 0);
    glEnd();	
	glPopMatrix();
}


void Bomb::render() const {}


void renderRadar() {
	glPushMatrix();
		glTranslatef(RADAR_X,RADAR_Y,0.0f);
		glScalef(RADAR_WIDTH,RADAR_HEIGHT,1);
		glColor3ub(0,0,0);
		//radar box
			glBegin(GL_QUADS);
				glVertex3f(0.0,0.0,0.0);
				glVertex3f(1.0,0.0,0.0);
				glVertex3f(1.0,1.0,0.0);
				glVertex3f(0.0,1.0,0.0);
			glEnd();
			glColor3ub(0,255,0);
			
		//scale and draw scaled level
		glScalef(0.05,1,1);
			level->render();
	glPopMatrix();


}

void Enemy::render() const {

	//draw enemy
	glPushMatrix();
		glTranslatef(position.x, position.y, 0.0f);
		glScalef(-0.1, 0.08, 1);		//minus to flip opposite direction to players ship
		glColor3ub(200,0, 0);			//draws enemy red
		glBegin(GL_QUADS);      
   			glVertex3f(0.0, 0.0, 0.0);
    		glVertex3f(1.0, 0.4, 0.0);
    		glVertex3f(1.0, 0.6, 0.0);
    		glVertex3f(0.0, 1.0, 0.0);

			glColor3ub(0, 0, 200);  

    		glVertex3f(0.0, 0.47, 0.0);
    		glVertex3f(1.1, 0.47, 0.0);
   			glVertex3f(1.1, 0.53, 0.0);
    		glVertex3f(0.0, 0.53, 0.0);
			glEnd();
	glPopMatrix();
}

int initGraphics() {
	
	glfwInit(); 
	glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
	if ( !glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 0,0,0,0,0,0, GLFW_WINDOW) ) { 
		glfwTerminate(); 
		std::cerr <<"glfwOpenWindow failed" <<endl;
		return 1; 
	}
	
	glfwSetWindowPos(100, 100);
	glfwSetWindowTitle("Defender");

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(0, ASPECT, 0, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();							// reset the model view matrix

	// timing information
    startTime = currentTime = glfwGetTime();
	previousBulletTime = 0.0;

	return 0;		// success
	
}

int deinitGraphics() {
	glfwTerminate();
	return 0;		// success
}

void render() {
    // update frame timer
	previousTime = currentTime;
	currentTime = glfwGetTime();
	dt = currentTime - previousTime;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1,0,0);
    glPushMatrix();
    	glTranslatef(-level->position.x, 0, 0);	//move game objects relative to level movement
    	level->render();
    	ship.render();
		for(int enemy = 0;enemy < level->enemyLength;++enemy)level->enemies[enemy].render();
		
	glPopMatrix();
	renderRadar();
		
    glfwSwapBuffers(); 
}
void getInput() {
	//quits the game
	if (glfwGetKey(GLFW_KEY_ESC) || !glfwGetWindowParam(GLFW_OPENED)) {
    	gameState = GAME_QUIT;
    	return;
	}
	
	//move ship commands
	ship.velocity = Vector2f::ZERO;
	if (glfwGetKey(GLFW_KEY_UP)) {
    	ship.velocity.y = 0.7;
	} else if (glfwGetKey(GLFW_KEY_DOWN)) {
    	ship.velocity.y = -0.7;
	}
	if (glfwGetKey(GLFW_KEY_LEFT)) {
    	ship.velocity.x = level->velocity.x-0.5;
	} else if (glfwGetKey(GLFW_KEY_RIGHT)) {
    	ship.velocity.x = level->velocity.x + 0.5;
	}
	//ship.shoot = glfwGetKey(GLFW_KEY_SPACE);
}
#endif
