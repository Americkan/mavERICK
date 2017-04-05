#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "ppm.h"
//#include "ppm.cpp"
#include <stdio.h>
#include <unistd.h> //for sleep function
#include "log.h"
#include "fonts.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

extern "C"
{
#include "fonts.h"
}

using namespace std;

//defined types
typedef float Flt;
typedef float Vec[3];
typedef Flt	Matrix[4][4];

//macros
#define rnd() (((double)rand())/(double)RAND_MAX)
#define random(a) (rand()%a)
#define VecZero(v) (v)[0]=0.0,(v)[1]=0.0,(v)[2]=0.0
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2]
#define VecDot(a,b)	((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecSub(a,b,c) (c)[0]=(a)[0]-(b)[0]; \
                      (c)[1]=(a)[1]-(b)[1]; \
                      (c)[2]=(a)[2]-(b)[2]


#define PI 3.141592653589793
#define ALPHA 1

//X Windows variables
extern Display *dpy;
extern Window win;
extern GLXContext glc;

extern int xres;
extern int yres;
extern const int MAX_BULLETS;



extern const double physicsRate;
extern const double oobillion;
extern struct timespec timeStart, timeCurrent;
extern struct timespec timePause;
extern double physicsCountdown;
extern double timeSpan;

extern double timeDiff(struct timespec*, struct timespec*);
extern void timeCopy(struct timespec*, struct timespec*);

struct Ship {
	Vec dir;
	Vec pos;
	Vec vel;
	float angle;
	float color[3];
	Ship() {
		VecZero(dir);
		pos[0] = (Flt)(xres/2);
		pos[1] = (Flt)(yres/2);
		pos[2] = 0.0f;
		VecZero(vel);
		angle = 0.0;
		color[0] = 1.0;
		color[1] = 1.0;
		color[2] = 1.0;
	}
};

struct Bullet {
	Vec pos;
	Vec vel;
	float color[3];
	struct timespec time;
	struct Bullet *prev;
	struct Bullet *next;
	Bullet() {
		prev = NULL;
		next = NULL;
	}
};

struct Asteroid {
	Vec pos;
	Vec vel;
	int nverts;
	Flt radius;
	Vec vert[8];
	float angle;
	float rotate;
	float color[3];
	struct Asteroid *prev;
	struct Asteroid *next;
	Asteroid() {
		prev = NULL;
		next = NULL;
	}
};

 
struct Game {
	Ship ship;
	Bullet *barr;
	Asteroid *ahead;
	int nasteroids;
	int nbullets;
	struct timespec bulletTimer;
    struct timespec mouseThrustTimer;
    bool mouseThrustOn;
	Game() {
		ahead = NULL;
		barr = new Bullet[MAX_BULLETS];
		nasteroids = 0;
		nbullets = 0;
        mouseThrustOn = false;
	}
    ~Game() {
      delete [] barr;
    }
};

//Function prototypes
//

//Erick H's Prototypes
extern void Maverick();
extern void Maverick2(int);
extern void MaverickBackground();
extern void MaverickHealth();
extern void MaverickBoost();
extern void MaverickHealthText(int);
extern void MaverickBoostText(int);
extern void MaverickShip();


//Andrew P's Prototypes
extern void initSound();
extern void backGround();
extern void thrust();
extern void blaster();
extern void expl();
extern void unzip();
extern void delete_sounds();
extern void help(int);



//Erick T's Prototypes


//JT's Prototypes




//Unknown at the moment
extern void menu( char[], int );
  
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
void check_mouse(XEvent *e, Game *game);
int check_keys(XEvent *e);
void init(Game *g);
void init_sounds(void);
void physics(Game *game);
void render(Game *game);
void set_mouse_position(int x, int y);
void show_mouse_cursor(const int onoff);

#endif

