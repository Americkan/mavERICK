//Andrew Parker
//March 2, 2017
//Group 6 - Lab 5
//
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <time.h>
#include <fstream>
#include <fcntl.h>
#include <sys/stat.h>
#include </usr/include/AL/alut.h>
#include <GL/glx.h>
#include "fonts.h"

using namespace std;

void initSound();
void backGround();
void playBackGround(ALuint);
void blaster();
void expl();
void unzip();
void help(int);
void delete_sounds();
void getHighScores();
//void updateHighScores();
void showHighScores(int);

int music = 0;
int thr = 0;
int sc = 0;
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
