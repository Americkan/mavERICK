//Author: Erick Herrera
//Starting Date: 2/21/2017
//Group:6  - Space Maverick

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
int boost = 1;

Ppmimage *shieldImage = NULL;
GLuint shieldTexture;
int shield = 1;

Ppmimage *shipImage = NULL;
GLuint shipTexture;
int ship = 1;

Ppmimage *enemy1Image = NULL;
GLuint enemy1Texture;
int enemy1 = 1; 

void GAMEOVERSCREEN (void);
void showGAMEOVERSCREEN ();
void Maverick2(int);
void MaverickBackground();
void MaverickHealth();
void MaverickHealthText(int);
void MaverickBoost();
void MaverickBoostText(int);
void MaverickShield();
void MaverickShieldText(int);

void MaverickShip();

void MaverickEnemyONE();
unsigned char *buildAlphaData(Ppmimage *img);

void Maverick () {
    for (int i = 0; i < 10; i++) {
	    cout << "mavERICK";
	    cout << "\n";
    }
}


void Maverick2 (int yres) {
    char name[10] = {"mavERICK"};

    Rect maverick;
    glEnable(GL_TEXTURE_2D);

    maverick.bot = yres/11;
    maverick.left = 850;
    maverick.center = 0;
    ggprint16(&maverick, 0, 0x00ffffff, name);
}

void MaverickHealthFill (float health) {
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(2, 0);
	glVertex2f(3, 0);
	glVertex2f(4, 0);
	glVertex2f(5, 0);
	glVertex2f(1, health);
	glVertex2f(0, health);
	glEnd();
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
    glGenTextures(1, &boostTexture);
    boostImage = ppm6GetImage("./assets/boostBar.ppm");
    int boostW = boostImage->width;
    int boostH = boostImage->height;
    glBindTexture(GL_TEXTURE_2D, boostTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, boostW, boostH, 0, GL_RGB, GL_UNSIGNED_BYTE, boostImage->data);

    //---------------------Shield-----------------------------------------------
    glGenTextures(1, &shieldTexture);
    shieldImage = ppm6GetImage("./assets/boostBar.ppm");
    unsigned char *shield = buildAlphaData(shieldImage);
    int shieldW = shieldImage->width;
    int shieldH = shieldImage->height;
    glBindTexture(GL_TEXTURE_2D, shieldTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, shieldW, shieldH, 0, GL_RGBA, GL_UNSIGNED_BYTE, shield);

    //---------------------Basic Ship-------------------------------------------
    glGenTextures(1, &shipTexture);
    shipImage = ppm6GetImage("./assets/ship.ppm");
    unsigned char *ship = buildAlphaData(shipImage);
    int shipW = shipImage->width;
    int shipH = shipImage->height;
    glBindTexture(GL_TEXTURE_2D, shipTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, shipW, shipH, 0, GL_RGBA, GL_UNSIGNED_BYTE, ship);

    //---------------------EnemyONE Ship-------------------------------------------
    glGenTextures(1, &enemy1Texture);
    enemy1Image = ppm6GetImage("./assets/alienShip.ppm");
    int enemy1W = enemy1Image->width;
    int enemy1H = enemy1Image->height;
    glBindTexture(GL_TEXTURE_2D, enemy1Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    unsigned char *alien = buildAlphaData(enemy1Image);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, enemy1W, enemy1H, 0, GL_RGBA, GL_UNSIGNED_BYTE, alien);


}
/*    //Background and Gameover screens for the game. 
    background = ppm6GetImage("./assets/background.ppm");
    gameover = ppm6GetImage("./assets/gameover.ppm");

    //------Bullet ---------------------------------------------------
    glGenTextures(1, &bulletImage);
    bullet = ppm6GetImage("./assets/basicBullet.ppm");
    int bulletW = bullet->width;
    int bulletH = bullet->height;
    glBindTexture(GL_TEXTURE_2D, bulletImage);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, bulletW, bulletH, 0, GL_RGB, GL_UNSIGNED_BYTE, bullet->data);

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

    //-----------Ship Upgrade 2 Image---------------------------------
    glGenTextures(1, &shipUpgrade2Image);
    shipUpgrade2 = ppm6GetImage("./assets/shipUpgrade2.ppm");
    int shipUpgrade2W = shipUpgrade2->width;
    int shipUpgrade2H = shipUpgrade2->height;
    glBindTexture(GL_TEXTURE_2D, shipUpgrade2Image);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, shipUpgrade2W, shipUpgrade2H, 0, GL_RGB, GL_UNSIGNED_BYTE, shipUpgrade2->data);

    //-----------Ship Upgrade 3 Image---------------------------------
    glGenTextures(1, &shipUpgrade3Image);
    shipUpgrade3 = ppm6GetImage("./assets/shipUpgrade3.ppm");
    int shipUpgrade3W = shipUpgrade3->width;
    int shipUpgrade3H = shipUpgrade3->height;
    glBindTexture(GL_TEXTURE_2D, shipUpgrade3Image);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, shipUpgrade3W, shipUpgrade3H, 0, GL_RGB, GL_UNSIGNED_BYTE, shipUpgrade3->data);


    //Game over Screen
    glGenTextures(1, &gameoverImage);
    int gameoverW = gameover->width;
    int gameoverH = gameover->height;
    glBindTexture(GL_TEXTURE_2D, gameoverImage);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, gameoverW, gameoverH, 0, GL_RGB, GL_UNSIGNED_BYTE, gameover->data);

    glEnable(GL_TEXTURE_2D);
    initialize_fonts();
    
}*/

void MaverickBackground() {
    if(background) {
	glBindTexture(GL_TEXTURE_2D, backgroundTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0,0);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, yres);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, yres);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, 0);
	glEnd();
    }
}

void MaverickHealth() {
    if(health) {
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

void MaverickBoost() {
    if(boost) {
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

void MaverickShield() {
    if(shield) {
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

void MaverickEnemyONE() {
    if(enemy1) {
        float wid = 35.0f;
        glPushMatrix();
        glTranslatef(xres - 100, yres - 400, 0.0f);
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

void MaverickHealthText (int yres) {
    char name[20] = {"mavERICK Health"};

    Rect maverick;
    glEnable(GL_TEXTURE_2D);

    maverick.bot = yres - 850;
    maverick.left = 450;
    maverick.center = 0;
    ggprint16(&maverick, 0, 0x00ff00, name);
}

void MaverickBoostText (int yres) {
    char name[20] = {"mavERICK Boost"};

    Rect maverick;
    glEnable(GL_TEXTURE_2D);

    maverick.bot = yres - 875;
    maverick.left = 450;
    maverick.center = 0;
    ggprint16(&maverick, 0, 0x000000ff, name);
}

void MaverickShieldText (int yres) {
    char name[20] = {"mavERICK Shields"};

    Rect maverick;
    glEnable(GL_TEXTURE_2D);

    maverick.bot = yres - 900;
    maverick.left = 450;
    maverick.center = 0;
    ggprint16(&maverick, 0, 0x00800080, name);
}

void MaverickShip() {
    if(ship) {
        float wid = 35.0f;
        glPushMatrix();
        glTranslatef(xres - 500, yres -500, 0.0f);
        glBindTexture(GL_TEXTURE_2D, shipTexture);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
        glEnd();
        glPopMatrix();
    }
}

unsigned char *buildAlphaData(Ppmimage *img) 
{ 
    int i;
    int a,b,c;
    unsigned char *newdata, *ptr;
    unsigned char *data = (unsigned char *)img->data;
    newdata = (unsigned char *)malloc(img->width * img->height * 4);
    ptr = newdata;
    for(i=0; i<img->width * img->height *3; i+=3) {
	a = *(data+0);
	b = *(data+1);
	c = *(data+2);
	if (a == 255 && b == 255 && c == 255) {
	    *(ptr+0) = a;
	    *(ptr+1) = b;
	    *(ptr+2) = c;
	    *(ptr+3) = 0;
	}

	else {
	    *(ptr+0) = a;
	    *(ptr+1) = b;
	    *(ptr+2) = c;
	    *(ptr+3) = 1;
	}
	ptr += 4;
	data += 3;

    }

    return newdata;
}
