//Andrew Parker
//March 2, 2017
//Group 6 - Lab 5
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
#endif
void backGround();
void playBackGround(ALuint);
void blaster();
void expl();
void unzip();
void help(int);
void delete_sounds();
void getHighScores();
//void updateHighScores();
void showScores();
void showHighScores(int);
void shipCollisionAlien(Game);
void shipCollisionGold(Game);
void shipCollisionTert(Game);
void shipCollisionShields(Game);
void shipCollisionBoost(Game);
void bulletToAlien(Game);

int music = 0;
int thr = 0;
int sc = 0;
int score = 0;
int scoresI[10];
char scoresC[10][50];
ALuint alBuffer[4];
ALuint alSource[4];

void help(int yres)
{
	char text[3][60] = {"Use space to shoot.", 
		"Use up arrow key for thrust.",
		"Use left and right arrow keys to change direction."};

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
	alBuffer[3] = alutCreateBufferFromFile("sounds/thrusters.wav");

	alGenSources(4, alSource);
	alSourcei(alSource[0], AL_BUFFER, alBuffer[0]);
	alSourcei(alSource[1], AL_BUFFER, alBuffer[1]);
	alSourcei(alSource[2], AL_BUFFER, alBuffer[2]);
	alSourcei(alSource[3], AL_BUFFER, alBuffer[3]);

	alSourcef(alSource[0], AL_GAIN, 1.0f);
	alSourcef(alSource[0], AL_PITCH, 1.0f);
	alSourcef(alSource[0], AL_LOOPING, AL_TRUE);

	alSourcef(alSource[1], AL_GAIN, 1.0f);
	alSourcef(alSource[1], AL_PITCH, 1.0f);
	alSourcef(alSource[1], AL_LOOPING, AL_FALSE);

	alSourcef(alSource[2], AL_GAIN, 1.0f);
	alSourcef(alSource[2], AL_PITCH, 1.0f);
	alSourcef(alSource[2], AL_LOOPING, AL_FALSE);

	alSourcef(alSource[3], AL_GAIN, 1.0f);
	alSourcef(alSource[3], AL_PITCH, 1.0f);
	alSourcef(alSource[3], AL_LOOPING, AL_FALSE);

	if (alGetError() != AL_NO_ERROR) {
		cout << "ERROR: setting source\n";
		return;
	}
}
void backGround()
{
	if (music == 0) {
		music ^= 1;
		playBackGround(alSource[0]);
	} else {
		alDeleteSources(1, &alSource[0]);
		alDeleteSources(1, &alSource[1]);
		alDeleteSources(1, &alSource[2]);
		alDeleteSources(1, &alSource[3]);
		alDeleteBuffers(1, &alBuffer[0]);
		alDeleteBuffers(1, &alBuffer[1]);
		alDeleteBuffers(1, &alBuffer[2]);
		alDeleteBuffers(1, &alBuffer[3]);

		ALCcontext *Context = alcGetCurrentContext();
		ALCdevice *Device = alcGetContextsDevice(Context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(Context);
		alcCloseDevice(Device);
		return;
	}
}

void playBackGround(ALuint source)
{
	for (int i=0; i < 15; i++) {
		alSourcePlay(source);
		usleep(20500);
	}
	return;
}

void blaster()
{
	alSourcePlay(alSource[1]);
	return;
}

void expl()
{
	alSourcePlay(alSource[2]);
	return;
}

void thrust()
{
	if (thr == 0) {
		alSourcePlay(alSource[3]);
		thr ^= 1;
	} else { 
		alSourceStop(alSource[3]);
		thr ^= 1;
	}
	return;

}

void unzip()
{
	system("unzip sounds.zip");
	return;
}

void delete_sounds()
{
	system("rm -R sounds");
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
		for (int i = 0; i < g->nbullets; i++) {
			Bullet *b = &g->barr[i];
			d0 = b->pos[0] - a->pos[0];
			d1 = b->pos[1] - a->pos[1];
			dist = (d0*d0 + d1*d1);
			if (dist < (a->radius*a->radius)) {
				if (a->prev == NULL) {
					if (a->next == NULL) {
						g->alienFalling = NULL;
					} else {
						a->next->prev = NULL;
						g->alienFalling = a->next;
						}
				} else {
					if (a->next == NULL) {
						a->prev->next = NULL;
					} else {
						a->prev->next = a->next;
						a->next->prev = a->prev;
						}
					}
				delete a;
				g->barr[i] = g->barr[--g->nbullets];
				score += 1000;
			}
			//a = a->next;
		}
		a = a->next;
	}
	return;
}
void bulletToTert(Game *g)
{
	Flt d0, d1, dist;
	t_AlienTertiary *ta = g->alientertiaryFalling;
	while (ta) {
		for (int i = 0; i < g->nbullets; i++) {
			Bullet *b = &g->barr[i];
			d0 = b->pos[0] - ta->pos[0];
			d1 = b->pos[1] - ta->pos[1];
			dist = (d0*d0 + d1*d1);
			if (dist < (ta->radius*ta->radius)) {
				if (ta->prev == NULL) {
					if (ta->next == NULL) {
						g->alientertiaryFalling 
						    = NULL;
					} else {
						ta->next->prev = NULL;
						g->alientertiaryFalling 
						    = ta->next;
						}
				} else {
					if (ta->next == NULL) {
						ta->prev->next = NULL;
					} else {
						ta->prev->next = ta->next;
						ta->next->prev = ta->prev;
						}
					}
				delete ta;
				g->barr[i] = g->barr[--g->nbullets];
				score += 500;
			}
			//a = a->next;
		}
		ta = ta->next;
	}
	return;
}

void bulletToGold(Game *g)
{
	Flt d0, d1, dist;
	t_GoldAlienEnemy *ga = g->goldalienFalling;
	while (ga) {
		for (int i = 0; i < g->nbullets; i++) {
			Bullet *b = &g->barr[i];
			d0 = b->pos[0] - ga->pos[0];
			d1 = b->pos[1] - ga->pos[1];
			dist = (d0*d0 + d1*d1);
			if (dist < (ga->radius*ga->radius)) {
				if (ga->prev == NULL) {
					if (ga->next == NULL) {
						g->goldalienFalling = NULL;
					} else {
						ga->next->prev = NULL;
						g->goldalienFalling 
						    = ga->next;
						}
				} else {
					if (ga->next == NULL) {
						ga->prev->next = NULL;
					} else {
						ga->prev->next = ga->next;
						ga->next->prev = ga->prev;
						}
					}
				delete ga;
				g->barr[i] = g->barr[--g->nbullets];
				score += 10000;
			}
			//a = a->next;
		}
		ga = ga->next;
	}
	return;
}

void shipCollisionAlien(Game *g)
{
	Flt d0, d1, dist;
	//cout << "in collision" << endl;
	t_AlienEnemy *a = g->alienFalling;
	while (a) {
		d0 = a->pos[0] - g->ship.pos[0];
		d1 = a->pos[1] - g->ship.pos[1];
		dist = (d0*d0 + d1*d1);
		if (dist < (g->ship.radius*g->ship.radius)) {
			MaverickUpdate();
			if (a->prev == NULL) {
				if (a->next == NULL) {
					g->alienFalling = NULL;
				} else {
					a->next->prev = NULL;
					g->alienFalling = a->next;
					}
			} else {
				if (a->next == NULL) {
					a->prev->next = NULL;
				} else {
					a->prev->next = a->next;
					a->next->prev = a->prev;
					}
				}
			delete a;
			score += 1000;
			//a = NULL;
		}
		a = a->next;
	}
	return;
}

void shipCollisionTert(Game *g)
{
	Flt d0, d1, dist;

	t_AlienTertiary *ta = g->alientertiaryFalling;
	while (ta) {
		d0 = ta->pos[0] - g->ship.pos[0];
		d1 = ta->pos[1] - g->ship.pos[1];
		dist = (d0*d0 + d1*d1);
		if (dist < (g->ship.radius*g->ship.radius)) {
			MaverickUpdate();
			if (ta->prev == NULL) {
				if (ta->next == NULL) {
					g->alientertiaryFalling = NULL;
				} else {
					ta->next->prev = NULL;
					g->alientertiaryFalling = ta->next;
					}
			} else {
				if (ta->next == NULL) {
					ta->prev->next = NULL;
				} else {
					ta->prev->next = ta->next;
					ta->next->prev = ta->prev;
					}
				}
			delete ta;
			score += 500;
			//ta = NULL;
		}
		ta = ta->next;
	}
	return;
}

void shipCollisionGold(Game *g)
{
	Flt d0, d1, dist;

	t_GoldAlienEnemy *ga = g->goldalienFalling;
	while (ga) {
		d0 = ga->pos[0] - g->ship.pos[0];
		d1 = ga->pos[1] - g->ship.pos[1];
		dist = (d0*d0 + d1*d1);
		if (dist < (g->ship.radius*g->ship.radius)) {
			MaverickUpdate();
			if (ga->prev == NULL) {
				if (ga->next == NULL) {
					g->goldalienFalling = NULL;
				} else {
					ga->next->prev = NULL;
					g->goldalienFalling = ga->next;
					}
			} else {
				if (ga->next == NULL) {
					ga->prev->next = NULL;
				} else {
					ga->prev->next = ga->next;
					ga->next->prev = ga->prev;
					}
				}
			delete ga;
			score += 10000;
			//ga = NULL;
		}
		ga = ga->next;
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
			//MaverickUpdate();
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
			//MaverickUpdate();
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
