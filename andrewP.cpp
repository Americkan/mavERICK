//Andrew Parker
//March 2, 2017
//Group 6
//***********************************************************************
//My portion of the project was handling collision between the objects,
//and implementing the sound functionality for the game.
//***********************************************************************
//
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include </usr/include/AL/alut.h>
#include <GL/glx.h>
#include "fonts.h"
#include "header.h"

using namespace std;

#ifdef USE_OPENAL_SOUND
void initSound();
void cleanSounds();
void playBackGround();
void stopBackGround();
void blaster();
void explosion();
void bossMusic();
void bossStop();
void deathSound();
void shieldUp();
void score100();
void score250();
void score500();
void score1M();
void dangerS();
void unzip();
void delete_sounds();
#endif
//void death();
//void winG();
//void getHighScores();
//void updateHighScores();
//void showScores();
//void showHighScores(int);
void shipCollisionAlien(Game);
void shipCollisionMoving(Game);
void shipCollisionMoving2(Game);
void shipCollisionMoving3(Game);
void shipCollisionBoss(Game);
void shipCollisionGold(Game);
void shipCollisionTert(Game);
void shipCollisionMoving(Game);
void shipCollisionShields(Game);
void shipCollisionBoost(Game);
void bulletToAlien(Game);
void bulletToBoss(Game);
void bulletToMoving(Game);
void bulletToMoving2(Game);
void bulletToMoving3(Game);
void bulletToGold(Game);
void bulletToTert(Game);

int gmode = 0;
int dth = 0;
int won = 0;
int dang = 0;
int pierce = 0;
//int sc = 0;
int score = 0;
//int scoresI[10];
//char scoresC[10][50];
ALuint alBuffer[11];
ALuint alSource[11];


//This functions diplays the game over text
void death()
{
    char text[3][60] = {"GAME OVER.", 
	"You have died.",
	"Press ESC to end."};

    Rect re;
    glEnable(GL_TEXTURE_2D);

    re.bot = yres/2+20;
    re.left = xres/2-80;
    re.center = 0;

    for (int i = 0; i < 3; i++) {
	ggprint16 (&re, 0, 0xff0000, text[i]);
	re.bot = re.bot - 30;
    }
}

//This text is displayed when game victory conditions are met
void winG()
{
    char text[3][60] = {"BOSS DEFEATED.", 
	"You have won.",
	"Press ESC to end."};

    Rect re;
    glEnable(GL_TEXTURE_2D);

    re.bot = yres/2+20;
    re.left = xres/2-80;
    re.center = 0;

    for (int i = 0; i < 3; i++) {
	ggprint16 (&re, 0, 0xffffff, text[i]);
	re.bot = re.bot - 30;
    }
    //glDisable(GL_TEXTURE_2D);
}

#ifdef USE_OPENAL_SOUND
//This function initializes all sound files for the game
void initSound()
{
    unzip();
    alutInit(0, NULL);
    if (alGetError() != AL_NO_ERROR) {
	cout << "ERROR: alutInit()\n";
	return;
    }
    alGetError();

    float vec[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);


    alBuffer[0] = alutCreateBufferFromFile("sounds/8BitBack.wav");
    alBuffer[1] = alutCreateBufferFromFile("sounds/blaster.wav");
    alBuffer[2] = alutCreateBufferFromFile("sounds/explosion.wav");
    alBuffer[3] = alutCreateBufferFromFile("sounds/BossMusic.wav");
    alBuffer[4] = alutCreateBufferFromFile("sounds/DeathSound.WAV");
    alBuffer[5] = alutCreateBufferFromFile("sounds/ShieldPickUp.WAV");
    alBuffer[6] = alutCreateBufferFromFile("sounds/250KSound.WAV");
    alBuffer[7] = alutCreateBufferFromFile("sounds/100KSound.WAV");
    alBuffer[8] = alutCreateBufferFromFile("sounds/500KSound.WAV");
    alBuffer[9] = alutCreateBufferFromFile("sounds/1MSound.WAV");
    alBuffer[10] = alutCreateBufferFromFile("sounds/DangerSound.wav");

    alGenSources(11, alSource);
    alSourcei(alSource[0], AL_BUFFER, alBuffer[0]);
    alSourcei(alSource[1], AL_BUFFER, alBuffer[1]);
    alSourcei(alSource[2], AL_BUFFER, alBuffer[2]);
    alSourcei(alSource[3], AL_BUFFER, alBuffer[3]);
    alSourcei(alSource[4], AL_BUFFER, alBuffer[4]);
    alSourcei(alSource[5], AL_BUFFER, alBuffer[5]);
    alSourcei(alSource[6], AL_BUFFER, alBuffer[6]);
    alSourcei(alSource[7], AL_BUFFER, alBuffer[7]);
    alSourcei(alSource[8], AL_BUFFER, alBuffer[8]);
    alSourcei(alSource[9], AL_BUFFER, alBuffer[9]);
    alSourcei(alSource[10], AL_BUFFER, alBuffer[9]);

    alSourcef(alSource[0], AL_GAIN, 1.0f);
    alSourcef(alSource[0], AL_PITCH, 1.0f);
    alSourcef(alSource[0], AL_LOOPING, AL_TRUE);

    alSourcef(alSource[1], AL_GAIN, 1.0f);
    alSourcef(alSource[1], AL_PITCH, 1.0f);
    alSourcef(alSource[1], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[2], AL_GAIN, 0.7f);
    alSourcef(alSource[2], AL_PITCH, 1.0f);
    alSourcef(alSource[2], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[3], AL_GAIN, 1.0f);
    alSourcef(alSource[3], AL_PITCH, 1.0f);
    alSourcef(alSource[3], AL_LOOPING, AL_TRUE);

    alSourcef(alSource[4], AL_GAIN, 1.0f);
    alSourcef(alSource[4], AL_PITCH, 1.0f);
    alSourcef(alSource[4], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[5], AL_GAIN, 1.0f);
    alSourcef(alSource[5], AL_PITCH, 1.0f);
    alSourcef(alSource[5], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[6], AL_GAIN, 1.0f);
    alSourcef(alSource[6], AL_PITCH, 1.0f);
    alSourcef(alSource[6], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[7], AL_GAIN, 1.0f);
    alSourcef(alSource[7], AL_PITCH, 1.0f);
    alSourcef(alSource[7], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[8], AL_GAIN, 1.0f);
    alSourcef(alSource[8], AL_PITCH, 1.0f);
    alSourcef(alSource[8], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[9], AL_GAIN, 1.0f);
    alSourcef(alSource[9], AL_PITCH, 1.0f);
    alSourcef(alSource[9], AL_LOOPING, AL_FALSE);

    alSourcef(alSource[10], AL_GAIN, 1.0f);
    alSourcef(alSource[10], AL_PITCH, 1.0f);
    alSourcef(alSource[10], AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	cout << "ERROR: setting source\n";
	return;
    }
}

//This function is used to clean the sound sources and buffers upon exit
void cleanSounds()
{
    alDeleteSources(1, &alSource[0]);
    alDeleteSources(1, &alSource[1]);
    alDeleteSources(1, &alSource[2]);
    alDeleteSources(1, &alSource[3]);
    alDeleteSources(1, &alSource[4]);
    alDeleteSources(1, &alSource[5]);
    alDeleteSources(1, &alSource[6]);
    alDeleteSources(1, &alSource[7]);
    alDeleteSources(1, &alSource[8]);
    alDeleteSources(1, &alSource[9]);
    alDeleteSources(1, &alSource[10]);

    alDeleteBuffers(1, &alBuffer[0]);
    alDeleteBuffers(1, &alBuffer[1]);
    alDeleteBuffers(1, &alBuffer[2]);
    alDeleteBuffers(1, &alBuffer[3]);
    alDeleteBuffers(1, &alBuffer[4]);
    alDeleteBuffers(1, &alBuffer[5]);
    alDeleteBuffers(1, &alBuffer[6]);
    alDeleteBuffers(1, &alBuffer[7]);
    alDeleteBuffers(1, &alBuffer[8]);
    alDeleteBuffers(1, &alBuffer[9]);
    alDeleteBuffers(1, &alBuffer[10]);

    ALCcontext *Context = alcGetCurrentContext();
    ALCdevice *Device = alcGetContextsDevice(Context);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);
    alcCloseDevice(Device);
    return;
}

//This function begins playing the main background music for the game
//in a loop
void playBackGround()
{	
    alSourcePlay(alSource[0]);
    return;
}

//This function stops the background music from playing for whatever
//desired reason
void stopBackGround()
{
    alSourceStop(alSource[0]);
    return;
}

//This function plays the sound that alerts the player to the boss' closing
//distance
void dangerS()
{
    alSourcePlay(alSource[10]);
    dang = 1;
    return;
}

//Thus plas the basic blaster sound effect the the ship projectiles
void blaster()
{
    alSourcePlay(alSource[1]);
    return;
}

//This plays the sound for the death of an enemy alien
void explosion()
{
    alSourcePlay(alSource[2]);
    return;
}

//Thus plays the special music for when the boss enemy appears
void bossMusic()
{
    alSourcePlay(alSource[3]);
    return;
}

//This function stops the boss music from playing for whatever reason
void bossStop()
{
    alSourceStop(alSource[3]);
    return;
}

//Thus function plays the sound that results from the players death
void deathSound()
{
    alSourcePlay(alSource[4]);
    return;
}

//This function plays the sound alerting the player that they picked up
//a special item
void shieldUp()
{
    alSourcePlay(alSource[5]);
    return;
}

//basic sound indicating score progression
void score100()
{
    alSourcePlay(alSource[6]);
    return;
}

//basic sound indicating score progression
void score250()
{
    alSourcePlay(alSource[7]);
    return;
}

//basic sound indicating score progression
void score500()
{
    alSourcePlay(alSource[8]);
    return;
}

//basic sound indicating score progression
void score1M()
{
    alSourcePlay(alSource[9]);
    return;
}

//Unzips the compressed sound files, readying them for play
void unzip()
{
    system("unzip sounds.zip");
    return;
}

//deletes the unzipped sound files ensuring smalles possible game
//file size
void delete_sounds()
{
    remove("sounds/8BitBack.wav");
    remove("sounds/blaster.wav");
    remove("sounds/explosion.wav");
    remove("sounds/BossMusic.wav");
    remove("sounds/DeathSound.WAV");
    remove("sounds/ShieldPickUp.WAV");
    remove("sounds/100KSound.WAV");
    remove("sounds/250KSound.WAV");
    remove("sounds/500KSound.WAV");
    remove("sounds/1MSound.WAV");
    remove("sounds/DangerSound.wav");
    remove("sounds");
    return;
}
#endif

/*void getHighScores()
  {
  int i = 0;
  ifstream fin;
  fin.open("scores.txt");
  while (!fin.eof()) {
  fin.getline(scoresC[i],50);
  i++;
  sc = i;
  }
  for (int j = 0; j < i; j++) {
  scoresI[j] = atoi(scoresC[j]);
  }
  fin.close();
  return;
  }*/

//This function displays the current score to the player
//as they play
void showScores()
{
    char name[20] = {"Score:"};
    char scor[30];

    Rect scores;
    glEnable(GL_TEXTURE_2D);

    scores.bot = 70;
    scores.left = 630;
    scores.center = 0;
    ggprint16(&scores, 0, 0xffff00, name);
    scores.left = 690;
    sprintf(scor, "%d", score);
    ggprint16(&scores, 0, 0xffff00, scor);

    return;
}

/*void showHighScores(int yres)
  {
  Rect re;
  glEnable(GL_TEXTURE_2D);

  re.bot = yres / 2;
  re.left = 500;
  re.center = 0;

  for (int i = 0; i < sc; i++) {
  ggprint16 (&re, 0, 0x00ffffff, scoresC[i]);
  re.bot = re.bot - 30;
  }
  return;
  }*/

//Function implementing the collision of the ship projectile to
//an enemy type
void bulletToAlien(Game *g)
{
    Flt d0, d1, dist;
    t_AlienEnemy *a = g->alienFalling;
    while (a) {
	t_AlienEnemy *save = a->next;
	for (int i = 0; i < g->nbullets; i++) {
	    Bullet *b = &g->barr[i];
	    d0 = b->pos[0] - a->pos[0];
	    d1 = b->pos[1] - a->pos[1];
	    dist = (d0*d0 + d1*d1);
	    if (dist < (a->radius*a->radius)) {
#ifdef USE_OPENAL_SOUND
		explosion();
#endif
		if (a->prev == NULL && a->next == NULL) {
		    g->alienFalling = NULL;
		    delete a;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 10000;
		    MaverickBossIncomingUpdate();
		    break;
		} else if (a->prev == NULL) {
		    g->alienFalling = a->next;
		    a->next->prev = NULL;
		    delete a;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 10000;
		    MaverickBossIncomingUpdate();
		    break;
		} else if (a->next == NULL) {
		    a->prev->next = NULL;
		    delete a;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 10000; 
		    MaverickBossIncomingUpdate();
		    break;
		} else if (a->prev != NULL 
			&& a->next != NULL) {
		    a->prev->next = a->next;
		    a->next->prev = a->prev;
		    delete a;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 10000;

		    MaverickBossIncomingUpdate();
		    break;
		}
	    }
	}
	a = save;
    }
    return;
}

//Function implementing the collision of the ship projectile to
//an enemy type
void bulletToMoving(Game *g)
{
    Flt d0, d1, dist;

    t_alien *ma = g->alienShip;
    for (int i = 0; i < g->nbullets; i++) {
	Bullet *b = &g->barr[i];
	d0 = b->pos[0] - ma->pos[0];
	d1 = b->pos[1] - ma->pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (ma->radius*ma->radius)) {
	    if (ma != NULL) {
		MaverickUpdateAlienONE();
		if (pierce == 0) {
		    g->barr[i] = g->barr[--g->nbullets];
		}
		if (alienONEHealth == 70) {
		    delete ma;
		    mov1 = false;	//variable indicating the death
		    			//of a special enemy
		}
		break;
	    }
	}
    }

    return;
}

//Function implementing the collision of the ship projectile to
//an enemy type
void bulletToMoving2(Game *g)
{
    Flt d0, d1, dist;

    t_alien2 *ma2 = g->alienShip2;
    for (int i = 0; i < g->nbullets; i++) {
	Bullet *b = &g->barr[i];
	d0 = b->pos[0] - ma2->pos[0];
	d1 = b->pos[1] - ma2->pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (ma2->radius*ma2->radius)) {
	    if (ma2 != NULL) {
		MaverickUpdateAlienTWO();
		g->barr[i] = g->barr[--g->nbullets];
		if (alienTWOHealth == 70) {
		    delete ma2;
		    mov2 = false;	//variable indicating the death
		    			//of a special enemy
		}
		break;
	    }
	}
    }

    return;
}

//Function implementing the collision of the ship projectile to
//the boss enemy type
void bulletToBoss(Game *g)
{
    Flt d0, d1, dist;

    t_Boss *ba = g->bossFalling;
    for (int i = 0; i < g->nbullets; i++) {
	Bullet *b = &g->barr[i];
	d0 = b->pos[0] - ba->pos[0];
	d1 = b->pos[1] - ba->pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (ba->radius*ba->radius)) {
	    if (ba != NULL) {
		MaverickUpdateBossHealth();
		g->barr[i] = g->barr[--g->nbullets];
		if (position4 == 630) {
		    delete ba;
		    won = 1;
#ifdef USE_OPENAL_SOUND
		    bossStop();
#endif
		    baws = false;	//variable indicating boss is active
		    deadbaws = true;	//variable indicating boss death
		}
		break;
	    }
	}
    }
    return;
}

//Function implementing the collision of the ship projectile to
//an enemy type
void bulletToMoving3(Game *g)
{
    Flt d0, d1, dist;

    t_alien3 *ma3 = g->alienShip3;
    for (int i = 0; i < g->nbullets; i++) {
	Bullet *b = &g->barr[i];
	d0 = b->pos[0] - ma3->pos[0];
	d1 = b->pos[1] - ma3->pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (ma3->radius*ma3->radius)) {
	    if (ma3 != NULL) {
		MaverickUpdateAlienTHREE();
		g->barr[i] = g->barr[--g->nbullets];
		if (alienTHREEHealth == 70) {
		    delete ma3;
		    mov3 = false;	//variable used to indicate
		    			//death of special enemy
		}
		break;
	    }
	}
    }

    return;
}

//Function implementing the collision of the ship projectile to
//an enemy type
void bulletToTert(Game *g)
{
    Flt d0, d1, dist;

    t_AlienTertiary *ta = g->alientertiaryFalling;
    //t_AlienTertiary *save = ta->next;
    while (ta) {
	t_AlienTertiary *save = ta->next;
	for (int i = 0; i < g->nbullets; i++) {
	    Bullet *b = &g->barr[i];
	    d0 = b->pos[0] - ta->pos[0];
	    d1 = b->pos[1] - ta->pos[1];
	    dist = (d0*d0 + d1*d1);
	    if (dist < (ta->radius*ta->radius)) {
#ifdef USE_OPENAL_SOUND
		explosion();
#endif
		if (ta->prev == NULL && ta->next == NULL) {
		    g->alientertiaryFalling = NULL;
		    delete ta;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 5000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ta->prev == NULL) {
		    g->alientertiaryFalling = ta->next;
		    ta->next->prev = NULL;
		    delete ta;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 5000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ta->next == NULL) {
		    ta->prev->next = NULL;
		    delete ta;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 5000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ta->prev != NULL 
			&& ta->next != NULL) {
		    ta->prev->next = ta->next;
		    ta->next->prev = ta->prev;
		    delete ta;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 5000;

		    MaverickBossIncomingUpdate();
		    break;
		}
	    }
	}
	ta = save;
    }
    return;
}

//Function implementing the collision of the ship projectile to
//an enemy type
void bulletToGold(Game *g)
{
    Flt d0, d1, dist;

    t_GoldAlienEnemy *ga = g->goldalienFalling;
    while (ga) {
	t_GoldAlienEnemy *save = ga->next;
	for (int i = 0; i < g->nbullets; i++) {
	    Bullet *b = &g->barr[i];
	    d0 = b->pos[0] - ga->pos[0];
	    d1 = b->pos[1] - ga->pos[1];
	    dist = (d0*d0 + d1*d1);
	    if (dist < (ga->radius*ga->radius)) {
#ifdef USE_OPENAL_SOUND
		explosion();
#endif
		if (ga->prev == NULL && ga->next == NULL) {
		    g->goldalienFalling = NULL;
		    delete ga;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 100000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ga->prev == NULL) {
		    g->goldalienFalling = ga->next;
		    ga->next->prev = NULL;
		    delete ga;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 100000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ga->next == NULL) {
		    ga->prev->next = NULL;
		    delete ga;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 100000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ga->prev != NULL 
			&& ga->next != NULL) {
		    ga->prev->next = ga->next;
		    ga->next->prev = ga->prev;
		    delete ga;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 100000;

		    MaverickBossIncomingUpdate();
		    break;
		}
	    }
	}
	ga = save;
    }
    return;
}

//Function implementing collision between the player ship and
//an enemy type
void shipCollisionAlien(Game *g)
{
    Flt d0, d1, dist;

    t_AlienEnemy *a = g->alienFalling;
    while (a) {
	t_AlienEnemy *save = a->next;
	d0 = a->pos[0] - g->ship.pos[0];
	d1 = a->pos[1] - g->ship.pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (g->ship.radius*g->ship.radius)) {
	    if (gmode == 0) {
		MaverickUpdate();
		if (position2 == 630) {
		    dth = 1;	//variable used to trigger death flag
#ifdef USE_OPENAL_SOUND
		    deathSound();
#endif
		}
	    }
	    if (a->prev == NULL && a->next == NULL) {
		g->alienFalling = NULL;
		delete a;
	    } else if (a->prev == NULL) {
		g->alienFalling = a->next;
		a->next->prev = NULL;
		delete a;
	    } else if (a->next == NULL) {
		a->prev->next = NULL;
		delete a;
	    } else if (a->prev != NULL && a->next != NULL) {
		a->prev->next = a->next;
		a->next->prev = a->prev;
		delete a;
	    }
	    score += 1000;

	    MaverickBossIncomingUpdate();
	}
	a = save;
    }
    return;
}

//Function implementing collision between the player ship and
//the boss enemy type
void shipCollisionBoss(Game *g)
{
    Flt d0, d1, dist;

    t_Boss *ba = g->bossFalling;
    d0 = ba->pos[0] - g->ship.pos[0];
    d1 = ba->pos[1] - g->ship.pos[1];
    dist = (d0*d0 + d1*d1);
    if (dist < (g->ship.radius*g->ship.radius)) {
	if (gmode == 0) {
	    MaverickUpdate();
	    if (position2 == 630) {
#ifdef USE_OPENAL_SOUND
		deathSound();
#endif
		dth = 1;	//variable used to trigger death flag
	    }
	}
    }

    return;
}

//Function implementing collision between the player ship and
//an enemy type
void shipCollisionMoving(Game *g)
{
    Flt d0, d1, dist;

    t_alien *ma = g->alienShip;
    d0 = ma->pos[0] - g->ship.pos[0];
    d1 = ma->pos[1] - g->ship.pos[1];
    dist = (d0*d0 + d1*d1);
    if (dist < (g->ship.radius*g->ship.radius)) {
	if (gmode == 0) {
	    MaverickUpdate();
	    if (position2 == 630) {
		dth = 1;	//variable used to trigger death flag
#ifdef USE_OPENAL_SOUND
		deathSound();
#endif
	    }
	}
    }

    return;
}

//Function implementing collision between the player ship and
//an enemy type
void shipCollisionMoving2(Game *g)
{
    Flt d0, d1, dist;

    t_alien2 *ma2 = g->alienShip2;
    d0 = ma2->pos[0] - g->ship.pos[0];
    d1 = ma2->pos[1] - g->ship.pos[1];
    dist = (d0*d0 + d1*d1);
    if (dist < (g->ship.radius*g->ship.radius)) {
	if (gmode == 0) {
	    MaverickUpdate();
	    if (position2 == 630) {
		dth = 1;	//variable used to trigger death flag
#ifdef USE_OPENAL_SOUND
		deathSound();
#endif
	    }
	}
    }

    return;
}

//Function implementing collision between the player ship and
//an enemy type
void shipCollisionMoving3(Game *g)
{
    Flt d0, d1, dist;

    t_alien3 *ma3 = g->alienShip3;
    d0 = ma3->pos[0] - g->ship.pos[0];
    d1 = ma3->pos[1] - g->ship.pos[1];
    dist = (d0*d0 + d1*d1);
    if (dist < (g->ship.radius*g->ship.radius)) {
	if (gmode == 0) {
	    MaverickUpdate();
	    if (position2 == 630) {
		dth = 1;	//variable used to trigger death flag
#ifdef USE_OPENAL_SOUND
		deathSound();
#endif
	    }
	}
    }

    return;
}

//Function implementing collision between the player ship and
//an enemy type
void shipCollisionTert(Game *g)
{
    Flt d0, d1, dist;

    t_AlienTertiary *ta = g->alientertiaryFalling;
    while (ta) {
	t_AlienTertiary *save = ta->next;
	d0 = ta->pos[0] - g->ship.pos[0];
	d1 = ta->pos[1] - g->ship.pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (g->ship.radius*g->ship.radius)) {
	    if (gmode == 0) {
		MaverickUpdate();
		if (position2 == 630) {
		    dth = 1;
#ifdef USE_OPENAL_SOUND
		    deathSound();
#endif
		}
	    }
	    if (ta->prev == NULL && ta->next == NULL) {
		g->alientertiaryFalling = NULL;
		delete ta; 
	    } else if (ta->prev == NULL) {
		g->alientertiaryFalling = ta->next;
		ta->next->prev = NULL;
		delete ta;
	    } else if (ta->next == NULL) {
		ta->prev->next = NULL;
		delete ta;
	    } else if (ta->prev != NULL && ta->next != NULL) {
		ta->prev->next = ta->next;
		ta->next->prev = ta->prev;
		delete ta;
	    }
	    score += 500;

	    MaverickBossIncomingUpdate();
	}
	ta = save;
    }
    return;
}

//Function implementing collision between the player ship and
//an enemy type
void shipCollisionGold(Game *g)
{
    Flt d0, d1, dist;

    t_GoldAlienEnemy *ga = g->goldalienFalling;
    while (ga) {
	t_GoldAlienEnemy *save = ga->next;
	d0 = ga->pos[0] - g->ship.pos[0];
	d1 = ga->pos[1] - g->ship.pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (g->ship.radius*g->ship.radius)) {
	    if (gmode == 0) {
		MaverickUpdate();
		if (position2 == 630) {
		    dth = 1;
#ifdef USE_OPENAL_SOUND
		    deathSound();
#endif
		}
	    }
	    if (ga->prev == NULL && ga->next == NULL) {
		g->goldalienFalling = NULL;
		delete ga;
	    } else if (ga->prev == NULL) {
		g->goldalienFalling = ga->next;
		ga->next->prev = NULL;
		delete ga;
	    } else if (ga->next == NULL) {
		ga->prev->next = NULL;
		delete ga;
	    } else if (ga->next != NULL && ga->prev != NULL) {
		ga->prev->next = ga->next;
		ga->next->prev = ga->prev;
		delete ga;
	    }
	    score += 100000;
	    MaverickBossIncomingUpdate();
	}
	ga = save;
    }
    return;
}

//Function implementing collision between the player ship and
//an enemy type
void shipCollisionShields(Game *g)
{
    Flt d0, d1, dist;

    t_Shields *s = g->shieldsFalling;
    while (s) {
	d0 = s->pos[0] - g->ship.pos[0];
	d1 = s->pos[1] - g->ship.pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (g->ship.radius*g->ship.radius)) {
	    MaverickUpdateShields();
#ifdef USE_OPENAL_SOUND
	    shieldUp();
#endif
	    if (s->prev == NULL) {
		if (s->next == NULL) {
		    g->shieldsFalling = NULL;
		} else {
		    s->next->prev = NULL;
		    g->shieldsFalling = s->next;
		}
	    } else {
		if (s->next == NULL) {
		    s->prev->next = NULL;
		} else {
		    s->prev->next = s->next;
		    s->next->prev = s->prev;
		}
	    }
	    delete s;
	}
	s = s->next;
    }
    return;
}

//Function implementing collision between the player ship and
//an enemy type
void shipCollisionBoost(Game *g)
{
    Flt d0, d1, dist;

    t_Boost *b = g->boostFalling;
    while (b) {
	d0 = b->pos[0] - g->ship.pos[0];
	d1 = b->pos[1] - g->ship.pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (g->ship.radius*g->ship.radius)) {
	    MaverickUpdateBoost();
	    if (b->prev == NULL) {
		if (b->next == NULL) {
		    g->boostFalling = NULL;
		} else {
		    b->next->prev = NULL;
		    g->boostFalling = b->next;
		}
	    } else {
		if (b->next == NULL) {
		    b->prev->next = NULL;
		} else {
		    b->prev->next = b->next;
		    b->next->prev = b->prev;
		}
	    }
	    delete b;
	}
	b = b->next;
    }
    return;
}
