//modified by: Andrew Parker, Erick Toscano, Erick Herrera
//date: February 2, 2017
//purpose: Group 6 Project 
//
//
//
//
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <ctime>
//#include <fcntl.h>
//#include <sys/stat.h>
#include <cmath>
#include <X11/Xlib.h>
//#include <X11/Xutil.h>
//#include <GL/gl.h>
//#include <GL/glu.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include </usr/include/AL/alut.h>
#include "ppm.h"
#include "log.h"

#include "fonts.h"
#include "header.h"

using namespace std;
//X Windows variables
Display *dpy;
Window win;
GLXContext glc;
int a;
int b;
int something = 1;
int something2 = 1;



int x;
int y;
int z;
bool danger = false;
//=======================================================================
//Setup timers
const double physicsRate = 1.0 / 60.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
//unsigned int upause=0;
double timeDiff(struct timespec *start, struct timespec *end) {
	return (double)(end->tv_sec - start->tv_sec ) +
			(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
	memcpy(dest, source, sizeof(struct timespec));
}
//=======================================================================


//====== GLOBAL VARIABLES!!
int xres=1250, yres=900;
int state_help = 0;
//int state_menu = 0;          //menu is at end of file


//constants
const float timeslice = 1.0f;
const float gravity = -0.2f;
const Flt MINIMUM_ASTEROID_SIZE = 60.0;
const int MAX_BULLETS = 1000;


/*class Input {                //input at end of file
  public:
    char text[100];
    int size;
    Input() {
      text[0] = '\0';
      size = 12;
    }
}input;*/

//:
int keys[65536];
Game game;
//int nbuttons = 0;

int main(void)
{
	logOpen();
	initXWindows();
	init_opengl();
#ifdef USE_OPENAL_SOUND
	initSound();		// initialize all sound
	playBackGround();	// call function to begin backgound music
#endif
	//Game game;
	init(&game);
	getHighScores();
	srand(time(NULL));
	clock_gettime(CLOCK_REALTIME, &timePause);
	clock_gettime(CLOCK_REALTIME, &timeStart);
    set_mouse_position(100,100);
	int done=0;
	while (!done) {
		while (XPending(dpy)) {
			XEvent e;
			XNextEvent(dpy, &e);
			check_resize(&e);
			done = check_mouse(&e, &game);
			check_keys(&e);
		}
		clock_gettime(CLOCK_REALTIME, &timeCurrent);
		timeSpan = timeDiff(&timeStart, &timeCurrent);
		timeCopy(&timeStart, &timeCurrent);
		physicsCountdown += timeSpan;
		while (physicsCountdown >= physicsRate) {
			physics(&game);
			physicsCountdown -= physicsRate;
		}
		render(&game);
		glXSwapBuffers(dpy, win);
	}
	cleanupXWindows();
	cleanup_fonts();
	logClose();
#ifdef USE_OPENAL_SOUND
	cleanSounds();	// recall functions to stop sound and delete sources
	delete_sounds(); // delete uncompressed sound files
#endif
	return 0;
}

void cleanupXWindows(void)
{
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

void set_title(void)
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "3350 - mavERICKs++");
}

void setup_screen_res(const int w, const int h)
{
	xres = w;
	yres = h;
}

void initXWindows(void)
{
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
	XSetWindowAttributes swa;
	setup_screen_res(xres, yres);
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {
		std::cout << "\n\tcannot connect to X server" << std::endl;
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if (vi == NULL) {
		std::cout << "\n\tno appropriate visual found\n" << std::endl;
		exit(EXIT_FAILURE);
	} 
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | ButtonPress | ButtonRelease |
        KeyPressMask | KeyReleaseMask |
		PointerMotionMask | StructureNotifyMask;// | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, xres, yres, 0,
			vi->depth, InputOutput, vi->visual,
			CWColormap | CWEventMask, &swa);
	set_title();
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

    if (game.mouseControl)
        show_mouse_cursor(0);
    else
        show_mouse_cursor(1);
}

void reshape_window(int width, int height)
{
	//window has been resized.
	setup_screen_res(width, height);
	//
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, xres, 0, yres, -1, 1);
	set_title();
}

void check_resize(XEvent *e)
{
	//The ConfigureNotify is sent by the
	//server if the window is resized.
	if (e->type != ConfigureNotify)
		return;
	XConfigureEvent xce = e->xconfigure;
	if (xce.width != xres || xce.height != yres) {
		//Window size did change.
		reshape_window(xce.width, xce.height);
	}
}

void init(Game *g) {
    //g->nbuttons = init_ButtonsMain(g);
    //cout << "\t\t\tbuttons: " << g->nbuttons << endl;
	//build 10 asteroids...
	for (int j=0; j<0; j++) {
		Asteroid *a = new Asteroid;
		a->nverts = 0;
		a->radius = rnd()*80.0f + 40.0f;
		Flt r2 = a->radius / 2.0f;
		Flt angle = 0.0f;
		Flt inc = (PI * 2.0f) / (Flt)a->nverts;
		for (int i=0; i<a->nverts; i++) {
			a->vert[i][0] = sin(angle) * (r2 + rnd() * a->radius);
			a->vert[i][1] = cos(angle) * (r2 + rnd() * a->radius);
			angle += inc;
		}
		a->pos[0] = (Flt)(rand() % xres);
		a->pos[1] = (Flt)(rand() % yres);
		a->pos[2] = 0.0f;
		a->angle = 0.0;
		a->rotate = rnd() * 4.0f - 2.0f;
		a->color[0] = 0.8;
		a->color[1] = 0.8;
		a->color[2] = 0.7;
		a->vel[0] = (Flt)(rnd()*2.0f-1.0);
		a->vel[1] = (Flt)(rnd()*2.0f-1.0);
		//std::cout << "asteroid" << std::endl;
		//add to front of linked list
		a->next = g->ahead;
		if (g->ahead != NULL)
			g->ahead->prev = a;
		g->ahead = a;
		g->nasteroids++;
	}
	clock_gettime(CLOCK_REALTIME, &g->bulletTimer);
	memset(keys, 0, 65536);
}

void normalize(Vec v) {
	Flt len = v[0]*v[0] + v[1]*v[1];
	if (len == 0.0f) {
		v[0] = 1.0;
		v[1] = 0.0;
		return;
	}
	len = 1.0f / sqrt(len);
	v[0] *= len;
	v[1] *= len;
}

void set_mouse_position(int x, int y)
{
  XWarpPointer(dpy, None, win, 0, 0, 0, 0, x, y);
}


void show_mouse_cursor(const int onoff)
{
	if (onoff) {
		//this removes our own blank cursor.
		XUndefineCursor(dpy, win);
		return;
	}
	//vars to make blank cursor
	Pixmap blank;
	XColor dummy;
	char data[1] = {0};
	Cursor cursor;
	//make a blank cursor
	blank = XCreateBitmapFromData (dpy, win, data, 1, 1);
	if (blank == None)
		std::cout << "error: out of memory." << std::endl;
	cursor = XCreatePixmapCursor(dpy, blank, blank, &dummy, &dummy, 0, 0);
	XFreePixmap(dpy, blank);
	//this makes you the cursor. then set it using this function
	XDefineCursor(dpy, win, cursor);
	//after you do not need the cursor anymore use this function.
	//it will undo the last change done by XDefineCursor
	//(thus do only use ONCE XDefineCursor and then XUndefineCursor):
}

int check_mouse(XEvent *e, Game *g)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;

    //-menu
    //int i, x, y;
    int lbutton = 0;
    int rbutton = 0;
    //-
	static int ct=0;
	//std::cout << "m" << std::endl << std::flush;
	if (e->type == ButtonRelease) {
		return 0;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
            //-menu
            lbutton = 1;
            //a little time between each bullet
          if (g->mouseControl) {
            struct timespec bt;
            clock_gettime(CLOCK_REALTIME, &bt);
            double ts = timeDiff(&g->bulletTimer, &bt);
            if (ts > 0.1) {
              timeCopy(&g->bulletTimer, &bt);
              //shoot a bullet...
              if (g->nbullets < MAX_BULLETS) {
                Bullet *b = &g->barr[g->nbullets];
                timeCopy(&b->time, &bt);
                b->pos[0] = g->ship.pos[0];
                b->pos[1] = g->ship.pos[1];
                b->vel[0] = g->ship.vel[0];
                b->vel[1] = g->ship.vel[1];
                //convert ship angle to radians
                Flt rad = ((g->ship.angle+90.0) / 360.0f) * PI * 2.0;
                //convert angle to a vector
                Flt xdir = cos(rad);
                Flt ydir = sin(rad);
                b->pos[0] += xdir*20.0f;
                b->pos[1] += ydir*20.0f;
                b->vel[0] += xdir*6.0f + rnd()*0.1;
                b->vel[1] += ydir*6.0f + rnd()*0.1;
                b->color[0] = 1.0f;
                b->color[1] = 1.0f;
                b->color[2] = 1.0f;
                g->nbullets++;
              }
            }
          }
        }
		if (e->xbutton.button==3) {
			//Right button is down
            //-game
            rbutton = 1;
            if(rbutton){}
            //-
		}
	}
	//keys[XK_Up] = 0;
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		int xdiff = savex - e->xbutton.x;
		int ydiff = savey - e->xbutton.y;
		if (++ct < 10)
			return 0;		
		//std::cout << e->xbutton.x << "-" << yres-e->xbutton.y << std::endl;
        //cout << "This is Erick T: ERICK H call or text 661 3764277" << endl;
		//std::flush;

        if (g->mouseControl) {
		    if (xdiff > 0) {
			    //std::cout << "xdiff: " << xdiff << std::endl << std::flush;
			    g->ship.angle += 0.05f * (float)xdiff;
			    if (g->ship.angle >= 360.0f)
				    g->ship.angle -= 360.0f;
		    }
		    else if (xdiff < 0) {
			    //std::cout << "xdiff: " << xdiff << std::endl << std::flush;
			    g->ship.angle += 0.05f * (float)xdiff;
			    if (g->ship.angle < 0.0f)
				    g->ship.angle += 360.0f;
		    }
		    if (ydiff > 0) {
			    //apply thrust
			    //convert ship angle to radians
			    Flt rad = ((g->ship.angle+90.0) / 360.0f) * PI * 2.0;
			    //convert angle to a vector
			    Flt xdir = cos(rad);
			    Flt ydir = sin(rad);
			    g->ship.vel[0] += xdir * (float)ydiff * 0.01f;
			    g->ship.vel[1] += ydir * (float)ydiff * 0.01f;
			    Flt speed = sqrt(g->ship.vel[0]*g->ship.vel[0]+
					        g->ship.vel[1]*g->ship.vel[1]);
			    if (speed > 10.0f) {
				    speed = 10.0f;
				    normalize(g->ship.vel);
				    g->ship.vel[0] *= speed;
				    g->ship.vel[1] *= speed;
			    }
			    g->mouseThrustOn = true;
			    clock_gettime(CLOCK_REALTIME, &g->mouseThrustTimer);
            }
		    set_mouse_position(100,100);
		    savex=100;
		    savey=100;
	    }
    }
    int done = 0;

    if (game.state_menu) {
        done = check_MainButtons(e, g, xres, yres, lbutton);
    }
    if (game.state_newG) {
        newGame(xres, yres);
        check_NewGButtons(e, g, xres, yres, lbutton);
    }
    if (game.state_sett) {
        check_SettButtons(e, g, xres, yres, lbutton);
    }

    return done?done:0;
}



void check_keys(XEvent *e)
{
	//keyboard input?
	static int shift=0;
	int key = XLookupKeysym(&e->xkey, 0);
    //cout << key << endl;
	//This code maintains an array of key status values.
	if (e->type == KeyRelease) {
		keys[key]=0;
		if (key == XK_Up)	// check for up arrow key release
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return;
	}
	if (e->type == KeyPress) {
		keys[key]=1;
		if (key == XK_Up)	// check for up arrow key press
		if (key == XK_Shift_L || key == XK_Shift_R) {
			shift=1;
			return;
		}
	} else {
		return;
	}
	if (shift){}
    if (game.state_newG) {
        game.state_newG = userName(key);
    } else {
	switch(key) {
		case XK_Escape:
            game.state_menu ^= 1;
            game.state_newG = 0;
            game.state_sett = 0;
            game.state_cred = 0;
            if (game.mouseControl)
                game.mouseControl ^= 1;
            break;
        case XK_h:
	        state_help ^= 1;
            break;
	    case XK_g:
	        gmode ^= 1;
	        break;
	    case XK_p:
	        pierce ^= 1;
	        break;
        case XK_x:
            break;
		case XK_f:
			break;
		case XK_s:
			break;
		case XK_Down:
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;
           
	}}
	return;
}

void deleteAsteroid(Game *g, Asteroid *node)
{
  //if (g) {}    //you can remove this line
  //if (node) {} //you can remove this line

  //to do:
  //Delete a node from asteroid linked-list
  /*	if (node->prev == NULL && node->next == NULL) {
		g->ahead = NULL;
		delete node;
		}
		else if (node->prev == NULL) {
		g->ahead = node->next;
		node->next->prev = NULL;
		delete node;
		}
		else if (node->next == NULL) {
		node->prev->next = NULL;
		delete node;
		}
		else if (node->next != NULL && node->prev != NULL) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
		delete node;
		}*/

  //remove a node from doubly-linked list
  if (node->prev == NULL) {
	if (node->next == NULL) {
	  //only 1 item in list.
	  g->ahead = NULL;
	} else {
	  //at beginning of list.
	  node->next->prev = NULL;
	  g->ahead = node->next;
	}
  } else {
	if (node->next == NULL) {
	  //at end of list.
	  node->prev->next = NULL;
	} else {
	  //in middle of list.
	  node->prev->next = node->next;
	  node->next->prev = node->prev;
	}
  }
  delete node;
  node = NULL;
}

void buildAsteroidFragment(Asteroid *ta, Asteroid *a)
{
	//build ta from a
	ta->nverts = 0;
	ta->radius = a->radius / 2.0f;
	Flt r2 = ta->radius / 2.0f;
	Flt angle = 0.0f;
	Flt inc = (PI * 2.0f) / (Flt)ta->nverts;
	for (int i=0; i<ta->nverts; i++) {
		ta->vert[i][0] = sin(angle) * (r2 + rnd() * ta->radius);
		ta->vert[i][1] = cos(angle) * (r2 + rnd() * ta->radius);
		angle += inc;
	}
	ta->pos[0] = a->pos[0] + rnd()*10.0f-5.0f;
	ta->pos[1] = a->pos[1] + rnd()*10.0f-5.0f;
	ta->pos[2] = 0.0f;
	ta->angle = 0.0f;
	ta->rotate = a->rotate + (rnd() * 4.0f - 2.0f);
	ta->color[0] = 0.8f;
	ta->color[1] = 0.8f;
	ta->color[2] = 0.7f;
	ta->vel[0] = a->vel[0] + (rnd()*2.0f-1.0f);
	ta->vel[1] = a->vel[1] + (rnd()*2.0f-1.0f);
	//std::cout << "frag" << std::endl;
}

void physics(Game *g)
{
    if(!game.state_menu && !game.state_newG && !game.state_sett &&
       !game.state_cred) {
    //if(!game.state_menu){
	Flt d0,d1,dist;
	//Update ship position
	g->ship.pos[0] += g->ship.vel[0];
	g->ship.pos[1] += g->ship.vel[1];
	//Check for collision with window edges
	if (g->ship.pos[0] < 0.0f) {
		g->ship.pos[0] += (float)xres;
	}
	else if (g->ship.pos[0] > (float)xres) {
		g->ship.pos[0] -= (float)xres;
	}
	else if (g->ship.pos[1] < 0.0f) {
		g->ship.pos[1] += (float)yres;
	}
	else if (g->ship.pos[1] > (float)yres) {
		g->ship.pos[1] -= (float)yres;
	}

	MaverickMoveAlien(g);
	MaverickMoveAlien2(g);
	MaverickMoveAlien3(g);

	//
	//
	//Update bullet positions
	struct timespec bt;
	clock_gettime(CLOCK_REALTIME, &bt);
	for (int i=0; i<g->nbullets; i++) {
		Bullet *b = &g->barr[i];
		//How long has bullet been alive?
		double ts = timeDiff(&b->time, &bt);
		if (ts > 2.5f) {
		    std::cout << "max time passed" << std::endl;
		    g->barr[i] = g->barr[--g->nbullets];
		
			//Delete bullet here.

			continue;
		}
		//move the bullet
		b->pos[0] += b->vel[0];
		b->pos[1] += b->vel[1];
		//Check for collision with window edges
		if (b->pos[0] < 0.0f) {
			b->pos[0] += (float)xres;
		}
		else if (b->pos[0] > (float)xres) {
			b->pos[0] -= (float)xres;
		}
		else if (b->pos[1] < 0.0f) {
			b->pos[1] += (float)yres;
		}
		else if (b->pos[1] > (float)yres) {
			b->pos[1] -= (float)yres;
		}
		//b = b->next;
	}
	if (deadbaws == false) {
		shipCollisionAlien(&game);
		//shipCollisionMoving(&game);
		shipCollisionGold(&game);
		shipCollisionTert(&game);
		shipCollisionShields(&game);
		shipCollisionBoost(&game);
	}
#ifdef USE_OPENAL_SOUND
	if (score == 100000) {
	    score100();
	}
	else if (score == 250000) {
	    score250();
	}
	else if (score == 500000 || score == 1500000 || score == 2500000) {
	    score500();
	}
	else if (score == 1000000 || score == 2000000 || score == 3000000) {
	    score1M();
	}
#endif
	//
	//Update asteroid positions
	Asteroid *a = g->ahead;
	while (a) {
		a->pos[0] += a->vel[0];
		a->pos[1] += a->vel[1];
		//Check for collision with window edges
		if (a->pos[0] < -100.0f) {
			a->pos[0] += (float)xres+200;
		}
		else if (a->pos[0] > (float)xres+100.0f) {
			a->pos[0] -= (float)xres+200.0f;
		}
		else if (a->pos[1] < -100.0f) {
			a->pos[1] += (float)yres+200.0f;
		}
		else if (a->pos[1] > (float)yres+100.0f) {
			a->pos[1] -= (float)yres+200.0f;
		}
		a->angle += a->rotate;
		a = a->next;
	}
	if (deadbaws == false) {
		bulletToAlien(&game);
		if (baws == true) {
			bulletToBoss(&game);
		}
		if (mov1 == true) {
			bulletToMoving(&game);
		}
		if (mov2 == true) {
			bulletToMoving2(&game);
		}
		if (mov3 == true) {
			bulletToMoving3(&game);
		}
		bulletToGold(&game);
		bulletToTert(&game);
	}
	//showScores();
	//
	//Asteroid collision with bullets?
	//If collision detected:
	//     1. delete the bullet
	//     2. break the asteroid into pieces
	//        if asteroid small, delete it
	a = g->ahead;
	while (a) {
		//is there a bullet within its radius?
		for (int i=0; i<g->nbullets; i++) {
			Bullet *b = &g->barr[i];
			d0 = b->pos[0] - a->pos[0];
			d1 = b->pos[1] - a->pos[1];
			dist = (d0*d0 + d1*d1);
			if (dist < (a->radius*a->radius)) {
				//std::cout << "asteroid hit." << std::endl;
				//this asteroid is hit.
				if (a->radius > MINIMUM_ASTEROID_SIZE) {
					//break it into pieces.
					Asteroid *ta = a;
					//expl();
					buildAsteroidFragment(ta, a);
					int r = rand() % 10 + 5;
					for (int k=0; k<r; k++) {
						//get the next asteroid position in the array
						Asteroid *ta = new Asteroid;
						buildAsteroidFragment(ta, a);
						//add to front of asteroid linked list
						ta->next = g->ahead;
						if (g->ahead != NULL)
							g->ahead->prev = ta;
						g->ahead = ta;
						g->nasteroids++;
					}
				} else {
					a->color[0] = 1.0;
					a->color[1] = 0.1;
					a->color[2] = 0.1;
					//asteroid is too small to break up
					//delete the asteroid and bullet
					Asteroid *savea = a->next;
					//expl();
					deleteAsteroid(g, a);
					a = savea;
					g->nasteroids--;
					std::cout << "small asteroid collision" << std::endl;
					g->barr[i] = g->barr[--g->nbullets];
				}
				//Delete bullet here.
				//How?
				//Move the array's last element to where this element is.	
				//Then update the array count, nbullets.
				//--like we did with water particles--
				/*if (dist < (a->radius*a->radius)) {
					if (a->radius < 20.0f) {
					    g->barr[i] = g->barr[--g->nbullets];
					}
				}*/
				
				if (a == NULL)
					break;
				//continue;
			}
			//b = b->next;
		}
		if (a == NULL)
			break;
		a = a->next;
	}
	//---------------------------------------------------
	//check keys pressed now
	if (keys[XK_Left]) {
	    if(position3 >= 630){
		g->ship.pos[0] -= 17.0f;
		MaverickDecreaseBoost();
	    }
	    else {
		g->ship.pos[0] -= 10.0f;
		//if (g->ship.angle >= 360.0f)
		//	g->ship.angle -= 360.0f;
	    }
	}
	if (keys[XK_Right]) {
	    if(position3 >= 630) {
		g->ship.pos[0] += 17.0f;
		MaverickDecreaseBoost();
	    }

	    else {
		g->ship.pos[0] += 10.0f;
		//if (g->ship.angle < 0.0f)
		//	g->ship.angle += 360.0f;
	    }
	}
	if (keys[XK_Up]) {
	    if(position3 >= 630) {
		g->ship.pos[1] += 17.0f;
		MaverickDecreaseBoost();
	    }

	    else {
		g->ship.pos[1] += 10.0f;
	    }
		//apply thrust
		//convert ship angle to radians
		//Flt rad = ((g->ship.angle+90.0f) / 360.0f) * PI * 2.0f;
		//convert angle to a vector
		//Flt xdir = cos(rad);
		//Flt ydir = sin(rad);
		//g->ship.vel[0] += xdir*0.02f;
		//g->ship.vel[1] += ydir*0.02f;
		//Flt speed = sqrt(g->ship.vel[0]*g->ship.vel[0]+
		//	g->ship.vel[1]*g->ship.vel[1]);
		//if (speed > 10.0f) {
		//	speed = 10.0f;
		//	normalize(g->ship.vel);
		//	g->ship.vel[0] *= speed;
		//	g->ship.vel[1] *= speed;
		//}
	}
	if (keys[XK_Down]) {
	    if (position3 >= 630) {
		g->ship.pos[1] -= 17.0f;
		MaverickDecreaseBoost();
	    }

	    else {
		g->ship.pos[1] -= 10.0f;
	    }
	}
	if (keys[XK_space]) {
		//a little time between each bullet
		struct timespec bt;
		clock_gettime(CLOCK_REALTIME, &bt);
		double ts = timeDiff(&g->bulletTimer, &bt);
		if (ts > 0.1) {
		  timeCopy(&g->bulletTimer, &bt);
		  if (g->nbullets < MAX_BULLETS) {
			//shoot a bullet...
			Bullet *b = &g->barr[g->nbullets];
			timeCopy(&b->time, &bt);
			b->pos[0] = g->ship.pos[0];
			b->pos[1] = g->ship.pos[1];
			b->vel[0] = g->ship.vel[0];
			b->vel[1] = g->ship.vel[1];
#ifdef USE_OPENAL_SOUND
			blaster();	// call function to create sound
#endif
			//convert ship angle to radians
			Flt rad = ((g->ship.angle+90.0f) / 360.0f) * PI * 2.0f;
			//convert angle to a vector
			Flt xdir = cos(rad);
			Flt ydir = sin(rad);
			b->pos[0] += xdir*20.0f;
			b->pos[1] += ydir*20.0f;
			b->vel[0] += xdir*6.0f + rnd()*0.1f;
			b->vel[1] += ydir*6.0f + rnd()*0.1f;
			b->color[0] = 1.0f;
			b->color[1] = 1.0f;
			b->color[2] = 1.0f;
			g->nbullets++;
		  }
		}
	}
	if (g->mouseThrustOn) {
	  //should thrust be turned off
	  struct timespec mtt;
	  clock_gettime(CLOCK_REALTIME, &mtt);
	  double tdif = timeDiff(&mtt, &g->mouseThrustTimer);
	  //std::cout << "tdif: " << tdif << std::endl;
	  if (tdif < -0.3)
		g->mouseThrustOn = false;
	}
	}



}

void render(Game *g)
{
	//float wid;
	Rect r;
	glClear(GL_COLOR_BUFFER_BIT);
	//
	r.bot = yres - 20;
	r.left = 10;
	r.center = 0;

	//Maverick();
	Maverick2(yres);
	MaverickBackground();
	//MaverickHealthFill();
	//MaverickHealthFillActual();
	//MaverickBoostFill();
	//MaverickBoostFillActual();
	//MaverickShieldFill();
	//MaverickShieldFillActual();
	//MaverickHealth();
	//MaverickBoost();
	//MaverickShield();
	//MaverickShip();
	if(score < 100000){
	if (something == 1) {
	    MaverickMakeEnemyONE(g);
	    MaverickMakeEnemyTWO(g);
	    MaverickMakeEnemyTHREE(g);
	    something = 0;
	}
	MaverickEnemyONE(g);
	MaverickEnemyTWO(g);
	MaverickEnemyTHREE(g);
	//MaverickPopulateEnemies();
	if (x % 100 == 0) {
	    MaverickCreateAliens(g, 10);
	}
	x = x+1;
	MaverickDrawAliens(g);

	MaverickDrawGoldAliens(g);
	if (a % 700 == 0) {
	    MaverickCreateGoldAliens(g, 1);
	}
	a = a+1;

	MaverickDrawTertiaryAliens(g);
	if (b % 20 == 0) {
	    MaverickCreateTertiaryAliens(g, 5);
	}
	b = b+1;
	}

	if (y % 1000 == 0) {
	    MaverickCreateShields(g, 1);
	}
	y = y+1;
	MaverickDrawShields(g);
	if (z % 1000 == 0) {
	    MaverickCreateBoost(g, 1);
	}
	z = z+1;
	MaverickDrawBoost(g);


	if (score > 100000) {
	    if(something2 == 1) {
		MaverickMakeBoss(g);
		something2 += 1;
	    }
	    
	    MaverickBoss(g);
	    MaverickMoveBoss(g);
	    //y = y+3;
	    //z = z+3;
	}
	showScores();
	MaverickBossFill();
	MaverickBossFillActual();
	

	MaverickHealthFill();
	MaverickHealthFillActual();
	MaverickBoostFill();
	MaverickBoostFillActual();
	MaverickShieldFill();
	MaverickBossText(yres);
	MaverickHealthText(yres);
	MaverickBoostText(yres);
	MaverickShieldText(yres);
	MaverickDangerText(danger);
	MaverickShieldFillActual();




	ggprint8b(&r, 16, 0x00ff0000, "Space mavERICK (Tom Cruise Simulator)");
	ggprint8b(&r, 16, 0x00ffff00, "n bullets: %i", g->nbullets);
	ggprint8b(&r, 16, 0x00ffff00, "n asteroids: %i", g->nasteroids);
	//-------------------------------------------------------------------------
	//Draw the ship
	glColor3fv(g->ship.color);
	glPushMatrix();
	glTranslatef(g->ship.pos[0], g->ship.pos[1], g->ship.pos[2]);
	//float angle = atan2(ship.dir[1], ship.dir[0]);
	//glRotatef(g->ship.angle, 0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	//glVertex2f(-10.0f, -10.0f);
	//glVertex2f(  0.0f, 20.0f);
	//glVertex2f( 10.0f, -10.0f);
	glVertex2f(-12.0f, -10.0f);
	glVertex2f(  0.0f,  20.0f);
	glVertex2f(  0.0f,  -6.0f);
	glVertex2f(  0.0f,  -6.0f);
	glVertex2f(  0.0f,  20.0f);
	glVertex2f( 12.0f, -10.0f);
	glEnd();
	MaverickShip();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f(0.0f, 0.0f);
	glEnd();
    glPopMatrix();


    if (keys[XK_Up] || g->mouseThrustOn) {
		int i;
		//draw thrust
		Flt rad = 90.0f/360.0f*PI*2.0f; //((g->ship.angle+90.0f) / 360.0f) * PI * 2.0f;
		//convert angle to a vector
		Flt xdir = cos(rad);
		Flt ydir = sin(rad);
		Flt xs,ys,xe,ye,r;
		glBegin(GL_LINES);
		for (i=0; i<16; i++) {
			xs = -xdir * 11.0f + rnd() * 4.0f - 2.0f;
			ys = -ydir * 11.0f + rnd() * 4.0f - 2.0f;
			r = rnd()*40.0f + 40.0f;
			xe = -xdir * r + rnd() * 18.0f - 9.0f;
			ye = -ydir * r + rnd() * 18.0f - 9.0f;
			glColor3f(rnd() * 0.3f + 0.7f, rnd() * 0.3f + 0.7f, 0);
			glVertex2f(g->ship.pos[0]+xs,g->ship.pos[1]+ys);
			glVertex2f(g->ship.pos[0]+xe,g->ship.pos[1]+ye);
		}
		glEnd();
	}
	//-------------------------------------------------------------------------
	//Draw the asteroids
	Asteroid *a = g->ahead;
	while (a) {
		//Log("draw asteroid...\n");
		glColor3fv(a->color);
		glPushMatrix();
		glTranslatef(a->pos[0], a->pos[1], a->pos[2]);
		glRotatef(a->angle, 0.0f, 0.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		//Log("%i verts\n",a->nverts);
		for (int j=0; j<a->nverts; j++) {
			glVertex2f(a->vert[j][0], a->vert[j][1]);
		}
		glEnd();
		//glBegin(GL_LINES);
		//	glVertex2f(0,   0);
		//	glVertex2f(a->radius, 0);
		//glEnd();
		glPopMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_POINTS);
		glVertex2f(a->pos[0], a->pos[1]);
		glEnd();
		a = a->next;
	}
	//-------------------------------------------------------------------------
	//Draw the bullets
	for (int i=0; i<g->nbullets; i++) {
		Bullet *b = &g->barr[i];
		//Log("draw bullet...\n");
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POINTS);
		glVertex2f(b->pos[0],      b->pos[1]);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]);
		glVertex2f(b->pos[0],      b->pos[1]-1.0f);
		glVertex2f(b->pos[0],      b->pos[1]+1.0f);
		glColor3f(0.8f, 0.8f, 0.8f);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]-1.0f);
		glVertex2f(b->pos[0]-1.0f, b->pos[1]+1.0f);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]-1.0f);
		glVertex2f(b->pos[0]+1.0f, b->pos[1]+1.0f);
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
    if (state_help) {
	//	glDisable(GL_TEXTURE_2D);
		help(yres);
		showHighScores(yres);
    }

    if (game.state_menu || game.state_newG || game.state_sett ||
        game.state_cred)
        game.frame = 1;
    else
        game.frame = 0;

    if (game.frame)
        frameMenu();

    if (game.state_menu) {
   //   glDisable(GL_TEXTURE_2D);
      
      mainMenu(xres, yres, g);

    }
    if (game.state_newG) {
        game.state_menu = 0;
        newGame(xres, yres);
        drawShipsOptions(xres, yres);
    }
    if (game.state_sett) {
        game.state_menu = 0;
        gameSettings(xres, yres, g);
    }
    if (game.state_cred) {
        game.state_menu = 0;
        gameCredits(xres, yres);
    }
}


