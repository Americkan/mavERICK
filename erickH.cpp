//Author: Erick Herrera
//Starting Date: 2/21/2017
//Group:6  - Space Maverick
//*********************************************************
//			NOTE
//The "init_opengl" void function code is omitted from the
//line count. So whatever the total line count is minus 141
//lines is the true count for me. 
//
//Total Lines: 804 lines
//Total Lines w/out spaces: 720 lines
//Total Lines Omitted: 141 lines
//Total Code counted: 579 lines 
//*********************************************************

#include <iostream>
#include "header.h"
#include "ppm.cpp"
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>

using namespace std;

Ppmimage *backgroundImage=NULL;
GLuint backgroundTexture;
int background = 1;

Ppmimage *healthImage = NULL;
GLuint healthTexture;
int health = 1;

Ppmimage *boostImage = NULL;
GLuint boostTexture;
GLuint silhouetteBoost;
int boost = 1;

Ppmimage *shieldImage = NULL;
GLuint shieldTexture;
GLuint silhouetteShields;
int shield = 1;

Ppmimage *shipImage = NULL;
GLuint shipTexture;
GLuint silhouetteShip;
int ship = 1;

Ppmimage *enemy1Image = NULL;
GLuint enemy1Texture;
int enemy1 = 1; 

Ppmimage *enemyImage = NULL;
GLuint enemyTexture;
int enemy = 1;
int enemyW, enemyH;

Ppmimage *enemyAlienImage = NULL;
GLuint silhouetteAlienEnemy;

int silhouette = 1;

void GAMEOVERSCREEN (void);
void showGAMEOVERSCREEN ();
void Maverick2(int);
void MaverickBackground();
void MaverickHealth();
void MaverickHealthText(int);
void MaverickHealthFill();
void MaverickHealthFillActual();
void MaverickBoostFill();
void MaverickBoostFillActual();
void MaverickShieldFill();
void MaverickShieldFillActual();
void MaverickBoost();
void MaverickBoostText(int);
void MaverickShield();
void MaverickShieldText(int);

void MaverickShip();
void MaverickMoveAlien();
void MaverickEnemyONE();
void MaverickCreateAliens(Game *g, int);
void MaverickDrawAliens(Game *g);
void MaverickDeleteAliens(AlienEnemy *node, Game *g);
void MaverickCreateShields(); 
void MaverickDrawShields();
void MaverickDeleteShields();
void MaverickPopulateEnemies();
unsigned char *buildAlphaData(Ppmimage *img);
Alien alien;
AlienEnemy *alienhead = NULL;

typedef struct t_Shields {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	float length;
	struct t_Shields *prev;
	struct t_Shields *next;
} Shields;
Shields *shieldshead = NULL;

typedef struct t_Boost {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	float length;
	struct t_Boost *prev;
	struct t_Boost *next;
} Boost;
Boost *boosthead = NULL;

typedef struct t_enemy {
    Vec pos;
    Vec vel;
} Enemy;
Enemy enemyPOP;

void Maverick () 
{
    for (int i = 0; i < 10; i++) {
	    cout << "mavERICK";
	    cout << "\n";
    }
}


void Maverick2 (int yres) 
{
    char name[10] = {"mavERICK"};

    Rect maverick;
    glEnable(GL_TEXTURE_2D);

    maverick.bot = yres/11;
    maverick.left = 850;
    maverick.center = 0;
    ggprint16(&maverick, 0, 0x00ffffff, name);
}

void init_opengl(void)
{
    //OpenGL initialization
    glViewport(0, 0, xres, yres);
    //Initialize matrices
    glMatrixMode(GL_PROJECTION); glLoadIdentity();
    glMatrixMode(GL_MODELVIEW); glLoadIdentity();
    //This sets 2D mode (no perspective)
    glOrtho(0, xres, 0, yres, -1, 1);
    //
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_FOG);
    glDisable(GL_CULL_FACE);
    //
    //Clear the screen to black
    glClearColor(0.0, 0.0, 0.0, 1.0);
    //Do this to allow fonts
    glEnable(GL_TEXTURE_2D);
    initialize_fonts(); 

    //----------------------Background--------------------------------------
    glGenTextures(1, &backgroundTexture);
    backgroundImage = ppm6GetImage("./assets/background.ppm");
    int w = backgroundImage->width;
    int h = backgroundImage->height;
    glBindTexture(GL_TEXTURE_2D, backgroundTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, backgroundImage->data);

    //----------------------Health-------------------------------------------
    glGenTextures(1, &healthTexture);
    healthImage = ppm6GetImage("./assets/healthBar.ppm");
    int healthW = healthImage->width;
    int healthH = healthImage->height;
    glBindTexture(GL_TEXTURE_2D, healthTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, healthW, healthH, 0, GL_RGB, GL_UNSIGNED_BYTE, healthImage->data);

    //---------------------Boost-----------------------------------------------
    system("convert ./assets/boost.png ./assets/boost.ppm");
    glGenTextures(1, &silhouetteBoost);
    glGenTextures(1, &boostTexture);
    boostImage = ppm6GetImage("./assets/boost.ppm");
    unsigned char *silhouetteData = buildAlphaData(boostImage);
    int boostW = boostImage->width;
    int boostH = boostImage->height;
    glBindTexture(GL_TEXTURE_2D, silhouetteBoost);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, boostW, boostH, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
    free(silhouetteData);

    //---------------------Shield-----------------------------------------------
    system("convert ./assets/shield.png ./assets/shield.ppm");
    glGenTextures(1, &silhouetteShields);
    glGenTextures(1, &shieldTexture);
    shieldImage = ppm6GetImage("./assets/shield.ppm");
    silhouetteData = buildAlphaData(shieldImage);
    int shieldW = shieldImage->width;
    int shieldH = shieldImage->height;
    glBindTexture(GL_TEXTURE_2D, silhouetteShields);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, shieldW, shieldH, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
    free(silhouetteData);
    //---------------------Basic Ship-------------------------------------------
    //system("convert ./assets/ship.png ./assets/ship.ppm");
    glGenTextures(1, &silhouetteShip);
    glGenTextures(1, &shipTexture);
    shipImage = ppm6GetImage("./assets/ship.ppm");
    silhouetteData = buildAlphaData(shipImage);
    int shipW = shipImage->width;
    int shipH = shipImage->height;
    glBindTexture(GL_TEXTURE_2D, silhouetteShip);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, shipW, shipH, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
    free(silhouetteData);

    //---------------------EnemyONE Ship-------------------------------------------
    glGenTextures(1, &enemy1Texture);
    enemy1Image = ppm6GetImage("./assets/alienShip.ppm");
    int enemy1W = enemy1Image->width;
    int enemy1H = enemy1Image->height;
    glBindTexture(GL_TEXTURE_2D, enemy1Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    unsigned char *alien1 = buildAlphaData(enemy1Image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, enemy1W, enemy1H, 0, GL_RGBA, GL_UNSIGNED_BYTE, alien1);

    alien.pos[0] = xres -100;
    alien.pos[1] = yres -400;

    //-----------------	Populate Enemies ------------------------------------------i
    system("convert ./assets/enemy.png ./assets/enemy.ppm");
    glGenTextures(1, &silhouetteAlienEnemy);
    glGenTextures(1, &enemyTexture);
    enemyImage = ppm6GetImage("./assets/enemy.ppm");
    silhouetteData = buildAlphaData(enemyImage);
    enemyW = enemyImage->width;
    enemyH = enemyImage->height;
    glBindTexture(GL_TEXTURE_2D, silhouetteAlienEnemy);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, enemyW, enemyH, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
    free(silhouetteData);
}
/*
    //------------High Score Image (Not the actual score) ------------
    glGenTextures(1, &highScoreImage);
    highScore = ppm6GetImage("./assets/highScore.ppm");
    int highScoreW = highScore->width;
    int highScoreH = highScore->height;
    glBindTexture(GL_TEXTURE_2D, highScoreImage);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, highScoreW, highScoreH, 0, GL_RGB, GL_UNSIGNED_BYTE, highScore->data);

    //-----------Ship Upgrade Image-----------------------------------
    glGenTextures(1, &shipUpgradeImage);
    shipUpgrade = ppm6GetImage("./assets/shipUpgrade.ppm");
    int shipUpgradeW = shipUpgrade->width;
    int shipUpgradeH = shipUpgrade->height;
    glBindTexture(GL_TEXTURE_2D, shipUpgradeImage);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, shipUpgradeW, shipUpgradeH, 0, GL_RGB, GL_UNSIGNED_BYTE, shipUpgrade->data);
}*/

void MaverickBackground() 
{
    if (background) {
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
	glEnd();
    }
}

void MaverickHealth() 
{
    if (health) {
	float wid = 35.0f;
	glPushMatrix();
	glTranslatef(xres - 100, yres -700, 0.0f);
	glBindTexture(GL_TEXTURE_2D, healthTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
	glEnd();
	glPopMatrix();
    }
}

void MaverickBoost() 
{
    if (boost) {
	float wid = 35.0f;
        glPushMatrix();
        glTranslatef(xres - 100, yres -900, 0.0f);
        glBindTexture(GL_TEXTURE_2D, boostTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
        glEnd();
        glPopMatrix();
    }
}

void MaverickShield() 
{
    if (shield) {
        float wid = 35.0f;
        glPushMatrix();
        glTranslatef(xres - 100, yres -200, 0.0f);
        glBindTexture(GL_TEXTURE_2D, shieldTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
        glEnd();
        glPopMatrix();
    }
}

void MaverickEnemyONE() 
{
    if (enemy1) {
        float wid = 35.0f;
        glPushMatrix();
        //glTranslatef(xres - 100, yres - 400, 0.0f);
	glTranslatef(alien.pos[0], alien.pos[1], 0.0f);
        glBindTexture(GL_TEXTURE_2D, enemy1Texture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
        glEnd();
        glPopMatrix();
    }
}

void MaverickHealthText (int yres) 
{
    char name[20] = {"mavERICK Health"};

    Rect maverick;
    glEnable(GL_TEXTURE_2D);

    maverick.bot = yres - 850;
    maverick.left = 450;
    maverick.center = 0;
    ggprint16(&maverick, 0, 0x00ff00, name);
}

void MaverickBoostText (int yres) 
{
    char name[20] = {"mavERICK Boost"};

    Rect maverick;
    glEnable(GL_TEXTURE_2D);

    maverick.bot = yres - 875;
    maverick.left = 450;
    maverick.center = 0;
    ggprint16(&maverick, 0, 0x000000ff, name);
}

void MaverickShieldText (int yres) 
{
    char name[20] = {"mavERICK Shields"};

    Rect maverick;
    glEnable(GL_TEXTURE_2D);

    maverick.bot = yres - 900;
    maverick.left = 450;
    maverick.center = 0;
    ggprint16(&maverick, 0, 0x00800080, name);
}

void MaverickHealthFill() 
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex2i(630, 50);
    glVertex2i(630, 70);
    glVertex2i(1130, 70);
    glVertex2i(1130, 50);
    glEnd();
    glColor3f(1, 1, 1);
    glPopMatrix();
}

void MaverickHealthFillActual() 
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.5, 1, 0.0);
    glVertex2i(630, 50);
    glVertex2i(630, 70);
    glVertex2i(1130, 70);
    glVertex2i(1130, 50);
    glEnd();
    glColor3f(1, 1, 1);
    glPopMatrix();
}

void MaverickBoostFill() 
{
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2i(630, 25);
    glVertex2i(630, 45);
    glVertex2i(1130, 45);
    glVertex2i(1130, 25);
    glEnd();
    glColor3f(1, 1, 1);
    glPopMatrix();
}

void MaverickBoostFillActual() 
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.417647, 0.917647);
    glVertex2i(630, 25);
    glVertex2i(630, 45);
    glVertex2i(1130, 45);
    glVertex2i(1130, 25);
    glEnd();
    glColor3f(1, 1, 1);
    glPopMatrix();
}

void MaverickShieldFill() 
{
    glPushMatrix();
    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
    glVertex2i(630, 0);
    glVertex2i(630, 20);
    glVertex2i(1130, 20);
    glVertex2i(1130, 0);
    glEnd();
    glColor3f(1, 1, 1);
    glPopMatrix();
}

void MaverickShieldFillActual() 
{
    glPushMatrix();
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.417647, 0.917647);
    glVertex2i(630, 0);
    glVertex2i(630, 20);
    glVertex2i(1130, 20);
    glVertex2i(1130, 0);
    glEnd();
    glColor3f(1, 1, 1);
    glPopMatrix();
}

void MaverickShip() 
{
    if (ship) {
        float wid = 35.0f;
        glPushMatrix();
        glTranslatef(0, 0, 0);
        glBindTexture(GL_TEXTURE_2D, silhouetteShip);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
        glEnd();
	glDisable(GL_ALPHA_TEST);
        glPopMatrix();
    }
}

void MaverickMoveAlien() 
{
    int addgrav = 1;
    alien.pos[0] += alien.vel[0];
    alien.pos[1] += alien.vel[1];
    if ((alien.pos[0] < - 140.0 && alien.vel[0] < 0.0) ||
	    (alien.pos[0] >= (float)xres+140.0 && alien.vel[0] > 0.0)) {
	alien.vel[0] = -alien.vel[0];
	addgrav = 0;
    }
    if ((alien.pos[1] < 150.0 && alien.vel[1] < 0.0) || 
	    (alien.pos[1] >= (float)yres && alien.vel[1] > 0.0)) {
	alien.vel[1] = -alien.vel[1];
	addgrav = 0; 
    }
    if (addgrav) {
    	alien.vel[1] -= 0.75;
    }
}

void MaverickCreateAliens(Game *g, const int n) //Taken from bigfoot framework
{
    int i;
    for (i = 0; i < n; i++) {
	AlienEnemy *node = new AlienEnemy;//(AlienEnemy *)malloc(sizeof(AlienEnemy));
	if (node == NULL) {
	    Log("error allocating node.\n");
	    exit(EXIT_FAILURE);
	}
	
	node->radius = 30.0f;	
	node->prev = NULL;
	node->next = NULL;
	node->sound=0;
	node->pos[0] = rnd() * (float)xres;
	node->pos[1] = rnd() * 100.0f + (float) yres;
	VecCopy(node->pos, node->lastpos);
	node->vel[0] = node->vel[1] = 0.0f;
	node->linewidth = enemyImage->width;
	//larger linewidth = faster speed
	node->maxvel[1] = (float) (node->linewidth*16);
	node->length = node->maxvel[1] * 0.2f;
	//put raindrop into linked list
	node->next = g->alienFalling;
	if (g->alienFalling != NULL) {
	    g->alienFalling->prev = node;
	}
	
	g->alienFalling = node;
    }
}

void MaverickDrawAliens(Game *g)
{
    AlienEnemy *node = g->alienFalling;
    while (node) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(node->pos[0],node->pos[1],node->pos[2]);
	node->pos[1] -=5; 
	glBindTexture(GL_TEXTURE_2D, silhouetteAlienEnemy);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	float w = 35.0f;
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(-w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w, w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i( w, w);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w,-w);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	node = node->next;
    }
    
    glLineWidth(1);
}

void MaverickDeleteAliens(AlienEnemy *node, Game *g)
{
	if (node->prev == NULL && node->next == NULL) {
		g->alienFalling = NULL;
	}
	else if (node->prev == NULL) {
		g->alienFalling = node->next;
		node->next->prev = NULL;
	}
	else if (node->next == NULL) {
		node->prev->next = NULL;
	}
	else {
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}

	delete node;
	node = NULL;
}

void MaverickPopulateEnemies()
{
    if (enemy) { 
        float wid = 35.0f;
        glPushMatrix();
        enemyPOP.pos[0] = xres - 200;
	enemyPOP.pos[1] = yres - 300;
        glTranslatef(enemyPOP.pos[0], enemyPOP.pos[1], 0.0f);
        glBindTexture(GL_TEXTURE_2D, enemyTexture);
        glBegin(GL_QUADS); 
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
        glEnd();
        glPopMatrix();
    }
}

void MaverickCreateShields(const int n)
{
    int i;
    for (i = 0; i < n; i++) {
	Shields *node = (Shields *)malloc(sizeof(Shields));
	if (node == NULL) {
	    Log("error allocating node.\n");
	    exit(EXIT_FAILURE);
	}
	
	node->prev = NULL;
	node->next = NULL;
	node->sound=0;
	node->pos[0] = rnd() * (float)xres;
	node->pos[1] = rnd() * 100.0f + (float) yres;
	VecCopy(node->pos, node->lastpos);
	node->vel[0] = node->vel[1] = 0.0f;
	node->linewidth = enemyImage->width;
	//larger linewidth = faster speed
	node->maxvel[1] = (float) (node->linewidth*16);
	node->length = node->maxvel[1] * 0.2f;
	//put raindrop into linked list
	node->next = shieldshead;
	if (shieldshead != NULL) {
	    shieldshead->prev = node;
	}
	
	shieldshead = node;
    }
}

void MaverickDrawShields()
{
    Shields *node = shieldshead;
    while (node) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(node->pos[0],node->pos[1],node->pos[2]);
	node->pos[1] -=5; 
	glBindTexture(GL_TEXTURE_2D, silhouetteShields);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	float w = 35.0f;
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(-w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w, w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i( w, w);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w,-w);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	node = node->next;
    }
    
    glLineWidth(1);
}

void MaverickDeleteShields(Shields *node)
{
	if (node->prev == NULL && node->next == NULL) {
		shieldshead = NULL;
	}
	else if (node->prev == NULL) {
		shieldshead = node->next;
		node->next->prev = NULL;
	}
	else if (node->next == NULL) {
		node->prev->next = NULL;
	}
}

void MaverickCreateBoost(const int n)
{
    int i;
    for (i = 0; i < n; i++) {
	Boost *node = (Boost *)malloc(sizeof(Boost));
	if (node == NULL) {
	    Log("error allocating node.\n");
	    exit(EXIT_FAILURE);
	}
	
	node->prev = NULL;
	node->next = NULL;
	node->sound=0;
	node->pos[0] = rnd() * (float)xres;
	node->pos[1] = rnd() * 100.0f + (float) yres;
	VecCopy(node->pos, node->lastpos);
	node->vel[0] = node->vel[1] = 0.0f;
	node->linewidth = boostImage->width;
	//larger linewidth = faster speed
	node->maxvel[1] = (float) (node->linewidth*16);
	node->length = node->maxvel[1] * 0.2f;
	//put raindrop into linked list
	node->next = boosthead;
	if (boosthead != NULL) {
	    boosthead->prev = node;
	}
	
	boosthead = node;
    }
}

void MaverickDrawBoost()
{
    Boost *node = boosthead;
    while (node) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(node->pos[0],node->pos[1],node->pos[2]);
	node->pos[1] -=5; 
	glBindTexture(GL_TEXTURE_2D, silhouetteBoost);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	float w = 35.0f;
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(-w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w, w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i( w, w);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w,-w);
	glEnd();
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
	node = node->next;
    }
    
    glLineWidth(1);
}

void MaverickDeleteBoost(Boost *node)
{
	if (node->prev == NULL && node->next == NULL) {
		boosthead = NULL;
	}
	else if (node->prev == NULL) {
		boosthead = node->next;
		node->next->prev = NULL;
	}
	else if (node->next == NULL) {
		node->prev->next = NULL;
	}
	else {
		node->next->prev = node->prev;
		node->prev->next = node->next;
	}

	delete node;
	node = NULL;
}


unsigned char *buildAlphaData(Ppmimage *img)
{
    int i;
    int a,b,c;
    unsigned char *newdata, *ptr;
    unsigned char *data = (unsigned char *)img->data;
    newdata = (unsigned char *)malloc(img->width * img->height * 4);
    ptr = newdata;
    for (i=0; i<img->width * img->height * 3; i+=3) {
	a = *(data+0);
	b = *(data+1);
	c = *(data+2);
	*(ptr+0) = a;
	*(ptr+1) = b;
	*(ptr+2) = c;
	*(ptr+3) = (a|b|c);
	ptr += 4;
	data += 3;
    }
    
    return newdata;
}

