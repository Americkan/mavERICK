//Andrew Parker
//March 2, 2017
//Group 6
//
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
void unzip();
void delete_sounds();
#endif
void help(int);
void getHighScores();
//void updateHighScores();
void showScores();
void showHighScores(int);
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

int music = 0;
int thr = 0;
int gmode = 0;
int pierce = 0;
int sc = 0;
int score = 0;
int scoresI[10];
char scoresC[10][50];
ALuint alBuffer[10];
ALuint alSource[10];

void help(int yres)
{
	char text[3][60] = {"Use space to shoot.", 
		"Use B for schockwave.",
		"Use arrow keys to change direction."};

	Rect re;
	glEnable(GL_TEXTURE_2D);

	re.bot = yres / 11;
	re.left = 10;
	re.center = 0;

	for (int i = 0; i < 3; i++) {
		ggprint16 (&re, 0, 0x00aaff00, text[i]);
		re.bot = re.bot - 30;
	}
}

#ifdef USE_OPENAL_SOUND
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

	alGenSources(10, alSource);
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

	if (alGetError() != AL_NO_ERROR) {
		cout << "ERROR: setting source\n";
		return;
	}
}
void cleanSounds()
{
	/*if (music == 0) {
		music ^= 1;
		playBackGround(alSource[0]);
	} else {*/
		
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

		ALCcontext *Context = alcGetCurrentContext();
		ALCdevice *Device = alcGetContextsDevice(Context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(Context);
		alcCloseDevice(Device);
		return;
	//}
}

void playBackGround()
{	
	//alSourcef(alSource[0], AL_LOOPING, AL_TRUE);
	//for (int i=0; i < 15; i++) {
		alSourcePlay(alSource[0]);
	//	usleep(20500);
	//}
	return;
}

void stopBackGround()
{
	alSourceStop(alSource[0]);
	//alSourcef(alSource[0], AL_LOOPING, AL_FALSE);
	return;
}

void blaster()
{
	alSourcePlay(alSource[1]);
	return;
}

void explosion()
{
	alSourcePlay(alSource[2]);
	return;
}

void bossMusic()
{
	//alSourcef(alSource[3], AL_LOOPING, AL_TRUE);
	//for (int i=0; i < 3; i++) {
		alSourcePlay(alSource[3]);
	//	usleep(20000);
	//}
	return;
}

void bossStop()
{
    alSourceStop(alSource[3]);
    return;
}

void deathSound()
{
	alSourcePlay(alSource[4]);
	return;
}

void shieldUp()
{
	alSourcePlay(alSource[5]);
	return;
}

void score100()
{
	alSourcePlay(alSource[6]);
	return;
}

void score250()
{
	alSourcePlay(alSource[7]);
	return;
}

void score500()
{
	alSourcePlay(alSource[8]);
	return;
}

void score1M()
{
	alSourcePlay(alSource[9]);
	return;
}


void unzip()
{
	system("unzip sounds.zip");
	return;
}

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

void getHighScores()
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
}

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

void showHighScores(int yres)
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
}

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
		    //a = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 1000;
		    MaverickBossIncomingUpdate();
		    break;
		} else if (a->prev == NULL) {
		    //ta->next->prev = NULL;
		    g->alienFalling = a->next;
		    a->next->prev = NULL;
		    delete a;
		    //a = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 1000;
		    MaverickBossIncomingUpdate();
		    break;
		} else if (a->next == NULL) {
		    a->prev->next = NULL;
		    delete a;
		    //a = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 1000; 
		    MaverickBossIncomingUpdate();
		    break;
		} else if (a->prev != NULL 
			&& a->next != NULL) {
		    a->prev->next = a->next;
		    a->next->prev = a->prev;
		    delete a;
		    //a = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 1000;

		    MaverickBossIncomingUpdate();
		    break;
		}
		//delete a;
		//g->barr[i] = g->barr[--g->nbullets];
		//score += 1000;
	    }
	    //a = a->next;
	    //a = savea;
	}
	a = save;
    }
    return;
}

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
	    		mov1 = false;
		}
	    	break;
	    }
	}
    }

    return;
}

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
	    		mov2 = false;
		}
	    	break;
	    }
	}
    }

    return;
}

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
		    baws = false;
		    deadbaws = true;
		}
	    	break;
	    }
	}
    }
    return;
}

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
	    		mov3 = false;
		}
	    	break;
	    }
	}
    }

    return;
}

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
		    //ta = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 500;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ta->prev == NULL) {
		    //ta->next->prev = NULL;
		    g->alientertiaryFalling = ta->next;
		    ta->next->prev = NULL;
		    delete ta;
		    //ta = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 500;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ta->next == NULL) {
		    ta->prev->next = NULL;
		    delete ta;
		    //ta = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 500;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ta->prev != NULL 
			&& ta->next != NULL) {
		    ta->prev->next = ta->next;
		    ta->next->prev = ta->prev;
		    delete ta;
		    //ta = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 500;

		    MaverickBossIncomingUpdate();
		    break;
		}
		//delete ta;
		//ta = NULL;
		//g->barr[i] = g->barr[--g->nbullets];
		//score += 500;
	    }
	    //a = a->next;
	    //ta = savea;

	}
	ta = save;
    }
    return;
}

void bulletToGold(Game *g)
{
    Flt d0, d1, dist;

    t_GoldAlienEnemy *ga = g->goldalienFalling;
    //t_GoldAlienEnemy *save = ga->next;
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
		    //ga = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 10000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ga->prev == NULL) {
		    //ta->next->prev = NULL;
		    g->goldalienFalling = ga->next;
		    ga->next->prev = NULL;
		    delete ga;
		    //ga = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 10000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ga->next == NULL) {
		    ga->prev->next = NULL;
		    delete ga;
		    //ga = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 10000;

		    MaverickBossIncomingUpdate();
		    break;
		} else if (ga->prev != NULL 
			&& ga->next != NULL) {
		    ga->prev->next = ga->next;
		    ga->next->prev = ga->prev;
		    delete ga;
		    //ga = NULL;
		    if (pierce == 0) {
			g->barr[i] = 
			    g->barr[--g->nbullets];
		    }
		    score += 10000;

		    MaverickBossIncomingUpdate();
		    break;
		}
		//delete ga;
		//ga = NULL;
		//g->barr[i] = g->barr[--g->nbullets];
		//score += 10000;
	    }
	    //a = a->next;
	    //ga = savea;
	}
	ga = save;
    }
    return;
}

void shipCollisionAlien(Game *g)
{
    Flt d0, d1, dist;
    //cout << "in collision" << endl;
    t_AlienEnemy *a = g->alienFalling;
    //t_AlienEnemy *save = a->next;
    while (a) {
	t_AlienEnemy *save = a->next;
	d0 = a->pos[0] - g->ship.pos[0];
	d1 = a->pos[1] - g->ship.pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (g->ship.radius*g->ship.radius)) {
	    if (gmode == 0) {
		MaverickUpdate();
	    }
	    if (a->prev == NULL && a->next == NULL) {
		g->alienFalling = NULL;
		delete a;
		//a = NULL;
	    } else if (a->prev == NULL) {
		//ta->next->prev = NULL;
		g->alienFalling = a->next;
		a->next->prev = NULL;
		delete a;
		//a = NULL;
	    } else if (a->next == NULL) {
		a->prev->next = NULL;
		delete a;
		//a = NULL;
	    } else if (a->prev != NULL && a->next != NULL) {
		a->prev->next = a->next;
		a->next->prev = a->prev;
		delete a;
		//a = NULL;
	    }
	    //delete a;
	    //a = NULL;
	    score += 1000;

		    MaverickBossIncomingUpdate();
	}
	a = save;
    }
    return;
}

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
	    }
	}

    return;
}

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
	    }
	    // can delete following block
	    /*if (ma != NULL) {
	    	delete ma;
	    	mov1 = false;
	    	break;
	    }*/
	}

    return;
}

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
	    }
	    /*if (ma2 != NULL) {
	    	delete ma2;
	    	mov2 = false;
	    	break;
	    }*/
	}

    return;
}

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
	    }
	    /*if (ma3 != NULL) {
	    	delete ma3;
	    	mov3 = false;
	    	break;
	    }*/
	}

    return;
}

void shipCollisionTert(Game *g)
{
    Flt d0, d1, dist;

    t_AlienTertiary *ta = g->alientertiaryFalling;
    //t_AlienTertiary *save = ta->next;
    while (ta) {
	t_AlienTertiary *save = ta->next;
	d0 = ta->pos[0] - g->ship.pos[0];
	d1 = ta->pos[1] - g->ship.pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (g->ship.radius*g->ship.radius)) {
	    if (gmode == 0) {
		MaverickUpdate();
	    }
	    if (ta->prev == NULL && ta->next == NULL) {
		g->alientertiaryFalling = NULL;
		delete ta;
		//ta = NULL;
	    } else if (ta->prev == NULL) {
		//ta->next->prev = NULL;
		g->alientertiaryFalling = ta->next;
		ta->next->prev = NULL;
		delete ta;
		//ta = NULL;
	    } else if (ta->next == NULL) {
		ta->prev->next = NULL;
		delete ta;
		//ta = NULL;
	    } else if (ta->prev != NULL && ta->next != NULL) {
		ta->prev->next = ta->next;
		ta->next->prev = ta->prev;
		delete ta;
		//ta = NULL;
	    }
	    //delete ta;
	    //ta = NULL;
	    score += 500;

		    MaverickBossIncomingUpdate();
	}
	ta = save;
    }
    return;
}

void shipCollisionGold(Game *g)
{
    Flt d0, d1, dist;

    t_GoldAlienEnemy *ga = g->goldalienFalling;
    //t_GoldAlienEnemy *save = ga->next;
    while (ga) {
	t_GoldAlienEnemy *save = ga->next;
	d0 = ga->pos[0] - g->ship.pos[0];
	d1 = ga->pos[1] - g->ship.pos[1];
	dist = (d0*d0 + d1*d1);
	if (dist < (g->ship.radius*g->ship.radius)) {
	    if (gmode == 0) {
		MaverickUpdate();
	    }
	    if (ga->prev == NULL && ga->next == NULL) {
		g->goldalienFalling = NULL;
		delete ga;
		//ga = NULL;
	    } else if (ga->prev == NULL) {
		//ga->next->prev = NULL;
		g->goldalienFalling = ga->next;
		ga->next->prev = NULL;
		delete ga;
		//ga = NULL;
	    } else if (ga->next == NULL) {
		ga->prev->next = NULL;
		delete ga;
		//ga = NULL;
	    } else if (ga->next != NULL && ga->prev != NULL) {
		ga->prev->next = ga->next;
		ga->next->prev = ga->prev;
		delete ga;
		//ga = NULL;
	    }
	    //delete a;
	    //ga = NULL;
	    score += 10000;
	    MaverickBossIncomingUpdate();
	}
	ga = save;
    }
    return;
}

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
	    //s = NULL;
	}
	s = s->next;
    }
    return;
}

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
	    //b = NULL;
	}
	b = b->next;
    }
    return;
}
