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

//extern "C"
//{
//#include "fonts.h"
//}

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
#define MAXBUTTONS 4

//X Windows variables
extern Display *dpy;
extern Window win;
extern GLXContext glc;

extern int xres;
extern int yres;
extern bool danger;
extern const int MAX_BULLETS;
extern int position3;



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
	Flt radius;
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
		radius = 40.0f;
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

typedef struct t_alien {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_alien *prev;
	struct t_alien *next;
} Alien;
//Alien alien;

typedef struct t_alien2 {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_alien2 *prev;
	struct t_alien2 *next;
} Alien2;

typedef struct t_alien3 {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_alien3 *prev;
	struct t_alien3 *next;
} Alien3;

typedef struct t_AlienEnemy {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_AlienEnemy *prev;
	struct t_AlienEnemy *next;
} AlienEnemy;

typedef struct t_GoldAlienEnemy {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_GoldAlienEnemy *prev;
	struct t_GoldAlienEnemy *next;
} GoldAlienEnemy;

typedef struct t_AlienTertiary {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_AlienTertiary *prev;
	struct t_AlienTertiary *next;
} AlienTertiary;

typedef struct t_Boss {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_Boss *prev;
	struct t_Boss *next;
} Boss;

typedef struct t_Boost {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_Boost *prev;
	struct t_Boost *next;
} Boost;

typedef struct t_Shields {
	int type;
	int linewidth;
	int sound;
	Vec pos;
	Vec lastpos;
	Vec vel;
	Vec maxvel;
	Vec force;
	Flt radius;
	float length;
	struct t_Shields *prev;
	struct t_Shields *next;
} Shields;

typedef struct t_button {
  Rect r;
  int over;
  int down;
  int click;
  float dcolor[3];
}Button;
 
struct Game {
	Ship ship;
	Bullet *barr;
	Asteroid *ahead;
	t_alien *alienShip;
	t_alien2 *alienShip2;
	t_alien3 *alienShip3;
	t_AlienEnemy *alienFalling;
	t_GoldAlienEnemy *goldalienFalling;
	t_AlienTertiary *alientertiaryFalling;
	t_Boss *bossFalling;
	t_Boost *boostFalling;
	t_Shields *shieldsFalling;
    Button button[MAXBUTTONS];
    int nbuttons;
	int nasteroids;
	int state_menu;
    int state_newG;
	int nbullets;
	struct timespec bulletTimer;
    struct timespec mouseThrustTimer;
    bool mouseThrustOn;
    bool mouseControl;
	Game() {
		ahead = NULL;
		barr = new Bullet[MAX_BULLETS];
		alienShip = NULL;
		alienFalling = NULL;
		nasteroids = 0;
		nbullets = 0;
        state_menu = 1;
        state_newG = 0;
        nbuttons = 0;
        mouseThrustOn = false;
        mouseControl = false;
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
extern void MaverickShield();
extern void MaverickHealthText(int);
extern void MaverickBoostText(int);
extern void MaverickShieldText(int);
extern void MaverickDangerText(bool);
extern void MaverickScoreText();
extern void MaverickShip();

extern void MaverickHealthFill();
extern void MaverickHealthFillActual();
extern void MaverickBoostFill();
extern void MaverickBoostFillActual();
extern void MaverickShieldFill();
extern void MaverickShieldFillActual();
extern void MaverickUpdate();
extern void MaverickUpdateShields();
extern void MaverickUpdateBoost();
extern void MaverickDecreaseBoost();

extern void MaverickMakeEnemyONE(Game *g);
extern void MaverickEnemyONE(Game *g);
extern void MaverickMakeEnemyTWO(Game *g);
extern void MaverickEnemyTWO(Game *g);
extern void MaverickMakeEnemyTHREE(Game *g);
extern void MaverickEnemyTHREE(Game *g);

extern void MaverickMoveAlien(Game *g);
extern void MaverickMoveAlien2(Game *g);
extern void MaverickMoveAlien3(Game *g); 
extern void MaverickDeleteEnemyONE(Alien *node, Game *g);
extern void MaverickDeleteEnemyTWO(Alien2 *node, Game *g);
extern void MaverickDeleteEnemyTHREE(Alien3 *node, Game *g);

extern void MaverickCreateAliens(Game *g, int);
extern void MaverickDrawAliens(Game *g);
extern void MaverickDeleteAliens(AlienEnemy *node, Game *g);
extern void MaverickCreateGoldAliens(Game *g, int);
extern void MaverickDrawGoldAliens(Game *g);
extern void MaverickDeleteGoldAliens(GoldAlienEnemy *node, Game *g);
extern void MaverickCreateTertiaryAliens(Game *g, int);
extern void MaverickDrawTertiaryAliens(Game *g);
extern void MaverickDeleteTertiaryAliens(AlienTertiary *node, Game *g);
extern void MaverickCreateShields(Game *g, int);
extern void MaverickDrawShields(Game *g);
extern void MaverickDeleteShields(Shields *node, Game *g);
extern void MaverickCreateBoost(Game *g, int);
extern void MaverickDrawBoost(Game *g);
extern void MaverickDeleteBoost(Boost *node, Game *g);
extern void MaverickPopulateEnemies();


//Andrew P's Prototypes
#ifdef USE_OPENAL_SOUND
extern void initSound();
extern void backGround();
extern void thrust();
extern void blaster();
extern void expl();
extern void unzip();
extern void delete_sounds();
#endif

extern void help(int);
extern void getHighScores();
extern void showHighScores(int);
extern void showScores();

extern void shipCollisionAlien(Game *);
extern void shipCollisionMoving(Game *);
extern void shipCollisionGold(Game *);
extern void shipCollisionTert(Game *);
extern void shipCollisionShields(Game *);
extern void shipCollisionBoost(Game *);
extern void bulletToAlien(Game *);
extern void bulletToMoving(Game *);
extern void bulletToMoving2(Game *);
extern void bulletToMoving3(Game *);
extern void bulletToTert(Game *);
extern void bulletToGold(Game *);



//Erick T's Prototypes
extern void mainMenu( int, int, Game*);
extern int init_ButtonsMain(Game*);
extern int init_ButtonsNewG(Game*);
extern void newGame(int, int);
extern int userName(int);
extern void gameSettings( int, int );
extern void gameScores( int, int );
extern void gameCredits( int, int );
extern int check_MainButtons(XEvent*, Game*, int, int ,int);
extern int check_NewGButtons(XEvent*, Game*, int, int, int);
extern void drawShipsOptions(int xres, int yres);

//Unknown
void initXWindows(void);
void init_opengl(void);
void cleanupXWindows(void);
void check_resize(XEvent *e);
int check_mouse(XEvent *e, Game *game);
void check_keys(XEvent *e);
void init(Game *g);
void init_sounds(void);
void physics(Game *game);
void render(Game *game);
void set_mouse_position(int x, int y);
void show_mouse_cursor(const int onoff);

#endif

