#include "fonts.h"
#include <GL/glx.h>
#include <GL/glu.h>
#include <X11/keysym.h>
#include "header.h"
#include </usr/include/AL/alut.h>
//#include <fcntl.h>
//#include <sys/stat.h>
//#include <AL/al.h>
//#include <AL/alc.h>
//#include <iostream>
//#include <unistd.h>
//#include "ppm.cpp"
//#include <X11/Xlib.h>
//#include <conio.h>
//#include <stdlib.h>
//#include <al/al.h>
//#include <al/alc.h>
//#include <al/alu.h>
//#include <al/alut.h>
extern unsigned char *buildAlphaData(Ppmimage *img);
extern Ppmimage *ppm6GetImage(const char *filename);
extern void playBackGround(ALuint);
extern void backGround();

class Input {
    public:
        char text[100];
        int size;
        Input() {
            text[0] = '\0';
            size = 8;
        }
}input;

int overSett1 = 0;
int overSett2 = 0;

//ship1
Ppmimage *shipImage1 = NULL;
GLuint shipTexture1;
GLuint silhouetteShip1;
//ship2
Ppmimage *shipImage2 = NULL;
GLuint shipTexture2;
GLuint silhouetteShip2;
//ship3
Ppmimage *shipImage3 = NULL;
GLuint shipTexture3;
GLuint silhouetteShip3;

void frameMenu()
{
    // int cx = xres / 2;
    // int cy = yres / 2;

    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glLineWidth(1);

    glBegin(GL_POLYGON);  
    glColor3f(0.0, 0.0, 0.0); 
    glVertex2i(2, 852); //i
    glVertex2i(4, 131); //i
    glColor3f(0.0, 0.1, 0.7); 
    glVertex2i(124, 137);
    glVertex2i(124, 691);
    glVertex2i(177, 766);
    glEnd();

    glBegin(GL_POLYGON);  
    glColor3f(0.0, 0.0, 0.0); 
    glVertex2i(729, 852);//i
    glVertex2i(452, 852);//i
    glVertex2i(2, 852); //i
    glColor3f(0.0, 0.1, 0.7); 
    glVertex2i(177, 766);
    glVertex2i(382, 766);
    glVertex2i(452, 670);
    glVertex2i(729, 670);
    glVertex2i(831, 766);
    glEnd();

    glBegin(GL_POLYGON);  
    glColor3f(0.0, 0.0, 0.0); 
    glVertex2i(1248, 852);//i
    glVertex2i(729, 852);//i
    glColor3f(0.0, 0.1, 0.7); 
    glVertex2i(831, 766);
    glVertex2i(1027, 766);
    glVertex2i(1126, 691);
    glEnd();

    glBegin(GL_POLYGON);  
    glColor3f(0.0, 0.0, 0.0); 
    glVertex2i(1248, 7);//i
    glVertex2i(1248, 852);//i
    glColor3f(0.0, 0.1, 0.7); 
    glVertex2i(1126, 691);
    glVertex2i(1126, 137);
    glVertex2i(1027, 56);
    glEnd();

    glBegin(GL_POLYGON);  
    glColor3f(0.0, 0.0, 0.0); 
    glVertex2i(2, 7);//i
    glVertex2i(1248, 7);//i
    glColor3f(0.0, 0.1, 0.7); 
    glVertex2i(1027, 56);
    glVertex2i(177, 56);
    glEnd();

    glBegin(GL_POLYGON);  
    glColor3f(0.0, 0.0, 0.0); 
    glVertex2i(4, 131);//i
    glVertex2i(2, 7);//i
    glColor3f(0.0, 0.1, 0.7); 
    glVertex2i(177, 56);
    glVertex2i(124, 137);
    glEnd();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);
}

void mainMenu(int xres, int yres, Game *g)
{
    Rect m;
    int cx = xres / 2;
    int cy = yres / 2;

    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);


    /*======>> Buttons <<======*/
    //glColor3f(0.0,0.0,1.0); 
    //===>Menu title
    glBegin(GL_POLYGON);  
    glColor3f(0.0, 0.0, 0.0); 
    glVertex2i(cx + 20 ,   cy + 110);
    glVertex2i(cx + 113,   cy + 110);  //right 
    glVertex2i(cx + 115,   cy + 110);  //right top
    glColor3f(1.0, 1.0, 1.0); 
    glVertex2i(cx + 115,   cy + 80);   //right bottom
    glVertex2i(cx - 20 ,   cy + 80);    //down-right " ''\,, "
    glVertex2i(cx - 40 ,   cy + 90);    //down-left " ''\,, "
    glVertex2i(cx - 130,   cy + 90);   //left bottom
    glColor3f(0.0, 0.1, 0.7); 
    glVertex2i(cx - 135,   cy + 80);   //left pick
    glVertex2i(cx - 135,   cy + 120);  //left top
    glVertex2i(cx    ,   cy + 120);      //top " ``\,, "
    glEnd();
    //===>New game ]]===
    //  glBindTexture(GL_TEXTURE_2D, 0);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glBegin(GL_POLYGON);
    glVertex2i(cx - 20 , cy + 70);  
    glVertex2i(cx - 40 , cy + 80);  
    glVertex2i(cx - 130, cy + 80); //left up
    glVertex2i(cx - 130, cy + 60); //left down  
    glVertex2i(cx - 120, cy + 50); //left down  
    glVertex2i(cx - 40 , cy + 50);  
    glVertex2i(cx - 20 , cy + 60);  
    glVertex2i(cx + 115, cy + 60);  
    glVertex2i(cx + 115, cy + 70);  
    glEnd();

    if (g->button[0].over == 1) {
        glLineWidth(2);
        glColor3f(0.1, 0.0, 0.8); 
        glBegin(GL_POLYGON);
        glVertex2i(cx - 20 -2, cy + 70+2);  
        glVertex2i(cx - 40 -2, cy + 80+2);  
        glVertex2i(cx - 130-2, cy + 80+2); //left up
        glVertex2i(cx - 130-2, cy + 60+2); //left down  
        glVertex2i(cx - 120-2, cy + 50+2); //left down  
        glVertex2i(cx - 40 -2, cy + 50+2);  
        glVertex2i(cx - 20 -2, cy + 60+2);  
        glVertex2i(cx + 115+2, cy + 60+2);  
        glVertex2i(cx + 115+2, cy + 70+2);  
        glEnd();
        glLineWidth(1);
        glColor3f(0.0, 0.1, 0.7); 
    }

    //===>Settings ===[[
    glBegin(GL_POLYGON);
    glVertex2i(cx - 40 , cy + 40);  
    glVertex2i(cx - 20 , cy + 50);  
    glVertex2i(cx + 115, cy + 50); //right-up 
    glVertex2i(cx + 115, cy + 30); //right-down
    glVertex2i(cx + 105, cy + 20);  
    glVertex2i(cx - 20 , cy + 20);  
    glVertex2i(cx - 40 , cy + 30);  
    glVertex2i(cx - 130, cy + 30);  
    glVertex2i(cx - 130, cy + 40);  
    glEnd();

    if (g->button[1].over == 1) {
        glColor3f(0.0, 0.0, 0.8); 
        glBegin(GL_POLYGON);
        glVertex2i(cx - 40-2 , cy + 40+2);  
        glVertex2i(cx - 20-2 , cy + 50+2);  
        glVertex2i(cx + 115+2, cy + 50+2); //right-up 
        glVertex2i(cx + 115+2, cy + 30+2); //right-down
        glVertex2i(cx + 105+2, cy + 20+2);  
        glVertex2i(cx - 20-2 , cy + 20+2);  
        glVertex2i(cx - 40-2 , cy + 30+2);  
        glVertex2i(cx - 130-2, cy + 30+2);  
        glVertex2i(cx - 130-2, cy + 40+2);  
        glEnd();
        glColor3f(0.0, 0.1, 0.7); 
    }
    //===>High Scores ]]===
    glBegin(GL_POLYGON);
    glVertex2i(cx - 20 , cy + 10);  
    glVertex2i(cx - 40 , cy + 20);  
    glVertex2i(cx - 130, cy + 20); //left up
    glVertex2i(cx - 130, cy + 0); //left down  
    glVertex2i(cx - 120, cy - 10); //left down  
    glVertex2i(cx - 40 , cy - 10);  
    glVertex2i(cx - 20 , cy + 0);  
    glVertex2i(cx + 115, cy + 0);  
    glVertex2i(cx + 115, cy + 10);  
    glEnd();

    if (g->button[2].over == 1) {
        glColor3f(0.0, 0.0, 0.8); 
        glBegin(GL_POLYGON);
        glVertex2i(cx - 20-2 , cy + 10+2);  
        glVertex2i(cx - 40-2 , cy + 20+2);  
        glVertex2i(cx - 130-2, cy + 20+2); //left up
        glVertex2i(cx - 130-2, cy + 0+2); //left down  
        glVertex2i(cx - 120-2, cy - 10-2); //left down  
        glVertex2i(cx - 40-2, cy - 10-2);  
        glVertex2i(cx - 20-2 , cy + 0+2);  
        glVertex2i(cx + 115+2, cy + 0+2);  
        glVertex2i(cx + 115+2, cy + 10+2);  
        glEnd();
        glColor3f(0.0, 0.1, 0.7); 
    }
    //===>Credits ===[[
    glBegin(GL_POLYGON);
    glVertex2i(cx - 40 , cy - 20);  
    glVertex2i(cx - 20 , cy - 10);  
    glVertex2i(cx + 115, cy - 10); //right-up 
    glVertex2i(cx + 115, cy - 30); //right-down
    glVertex2i(cx + 105, cy - 40);  
    glVertex2i(cx - 20 , cy - 40);  
    glVertex2i(cx - 40 , cy - 30);  
    glVertex2i(cx - 130, cy - 30);  
    glVertex2i(cx - 130, cy - 20);  
    glEnd();

    if (g->button[3].over == 1) {
        glColor3f(0.0, 0.0, 0.8); 
        glBegin(GL_POLYGON);
        glVertex2i(cx - 40-2 , cy - 20-2);  
        glVertex2i(cx - 20-2 , cy - 10-2);  
        glVertex2i(cx + 115+2, cy - 10-2); //right-up 
        glVertex2i(cx + 115+2, cy - 30-2); //right-down
        glVertex2i(cx + 105+2, cy - 40-2);  
        glVertex2i(cx - 20-2 , cy - 40-2);  
        glVertex2i(cx - 40-2 , cy - 30-2);  
        glVertex2i(cx - 130-2, cy - 30-2);  
        glVertex2i(cx - 130-2, cy - 20-2);  
        glEnd();
        glColor3f(0.0, 0.1, 0.7); 
    }
    //===>End-Menu title
    glBegin(GL_POLYGON);  
    glColor3f(0.0, 0.0, 0.0); 
    glVertex2i(cx-20 ,   cy-50);
    glVertex2i(cx+115,   cy-50);  //right top
    glColor3f(1.0, 1.0, 1.0); 
    glVertex2i(cx+115,   cy-70);  //right bottom
    glVertex2i(cx-50 ,   cy-70);  //down-right " ''\,, "
    glColor3f(0.0, 0.1, 0.7); 
    glVertex2i(cx-70 ,   cy-60);  //down-left " ''\,, "
    glVertex2i(cx-130,   cy-60);  //left bottom
    glVertex2i(cx-135,   cy-70);  //left pick
    glVertex2i(cx-135,   cy-40);  //left top
    glVertex2i(cx-40 ,   cy-40);  //top " ``\,, "
    glEnd();

    //==>>Exit button
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    for (int i=0; i <=300; i++) {
        double angle = 2*PI*i/300;
        double x = 20* cos(angle);
        double y = 20* sin(angle);
        glVertex2i(50+x, 50+y);
    }
    glEnd();
    if (g->button[4].over == 1) {
        glColor3f(1.0, 0.0, 0.0); 
        glBegin(GL_LINE_LOOP);
        for (int i=0; i <=300; i++) {
            double angle = 2*PI*i/300;
            double x = 20* cos(angle);
            double y = 20* sin(angle);
            glVertex2i(50+x, 50+y);
        }
        glEnd();
    }

    glLineWidth(1);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);

    glEnable(GL_TEXTURE_2D);
    m.bot = cy + 77;
    m.left = cx-20;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, "MAIN MENU");

    m.bot = cy + 47;
    m.left = cx-110;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, "NEW");

    m.bot = cy + 17;
    m.left = cx-20;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, "SETTINGS");

    m.bot = cy - 13;
    m.left = cx-121;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, "SCORES");

    m.bot = cy - 43;
    m.left = cx-20;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, "CREDITS");

    glDisable(GL_TEXTURE_2D);
    //======>>End Menu 
}

int init_ButtonsMain(Game *g)
{
    int buttons = 0;
    //size and positions of every clickable button
    //new
    g->button[buttons].r.left = 497;
    g->button[buttons].r.right = 600;
    g->button[buttons].r.bot = 477;
    g->button[buttons].r.top = 504;
    //settings
    buttons++;
    g->button[buttons].r.left = 600;
    g->button[buttons].r.right = 740;
    g->button[buttons].r.bot = 447;
    g->button[buttons].r.top = 475;
    //scores
    buttons++;
    g->button[buttons].r.left = 497;
    g->button[buttons].r.right = 600;
    g->button[buttons].r.bot = 418;
    g->button[buttons].r.top = 443;
    //credits
    buttons++;
    g->button[buttons].r.left = 600;
    g->button[buttons].r.right = 740;
    g->button[buttons].r.bot = 387;
    g->button[buttons].r.top = 414;
    //exit
    buttons++;
    g->button[buttons].r.left = 31;
    g->button[buttons].r.right = 70;
    g->button[buttons].r.bot = 30;
    g->button[buttons].r.top = 67;
    buttons++;
    return buttons;
}

int init_ButtonsNewG(Game *g)
{
    int buttons = 0;
    //ship1
    g->button[buttons].r.left = 503;
    g->button[buttons].r.right = 568;
    g->button[buttons].r.bot = 355;
    g->button[buttons].r.top = 418;
    //ship2
    buttons++;
    g->button[buttons].r.left = 582;
    g->button[buttons].r.right = 647;
    g->button[buttons].r.bot = 355;
    g->button[buttons].r.top = 418;
    //ship3
    buttons++;
    g->button[buttons].r.left = 664;
    g->button[buttons].r.right = 727;
    g->button[buttons].r.bot = 355;
    g->button[buttons].r.top = 418;
    buttons++;
    return buttons;
}

int init_ButtonsSett(Game *g)
{
    int buttons = 0;
    //music?
    g->button[buttons].r.left = 515;
    g->button[buttons].r.right = 530;
    g->button[buttons].r.bot = 420;
    g->button[buttons].r.top = 435;
    //mouse?
    buttons++;
    g->button[buttons].r.left = 515;
    g->button[buttons].r.right = 530;
    g->button[buttons].r.bot = 390;
    g->button[buttons].r.top = 405;
    buttons++;
    return buttons;
}

int userName (int key)
{

    if ((key >= XK_a && key <= XK_z) || key == XK_space) {
        char k[2];
        k[0] = key;
        k[1] = '\0';
        strcat(input.text, k);
        input.text[0] = toupper(input.text[0]);
        return 1;
    }
    if (key == XK_BackSpace) {
        int slen = strlen(input.text);
        if (slen > 0)
            input.text[slen-1] = '\0';
        return 1;
    }
    if (key == XK_Escape) {
        return 0;
    }
    return 1;
}


void newGame(int xres, int yres)
{
    Rect m;
    int cx = xres / 2;
    int cy = yres / 2;

    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glColor3f(0.0, 0.1, 0.7); 
    glBegin(GL_POLYGON);
    glVertex2i(cx - 20 , cy + 70); // 
    glVertex2i(cx - 40 , cy + 80); // 
    glVertex2i(cx - 130, cy + 80); //left up
    glVertex2i(cx - 130, cy - 80);   
    glVertex2i(cx - 120, cy - 90);   
    glVertex2i(cx - 40 , cy - 90);  
    glVertex2i(cx - 20 , cy - 80);  
    glVertex2i(cx + 115, cy - 80);  
    glVertex2i(cx + 115, cy + 70);  //right up
    glEnd();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);

    //input box
    glColor3f(1.0,1.0,1.0);
    glBegin(GL_QUADS);
    glVertex2i(cx-10, cy+47);              //1 lower left corner
    glVertex2i(cx-10, cy+63);              //2 upper left  "
    glVertex2i(cx + input.size*12-10, cy+63); 	 //3 upper right "
    glVertex2i(cx + input.size*12-10, cy+47);    //4 lower right "
    glEnd();

    glEnable(GL_TEXTURE_2D);
    m.bot = cy + 47;
    m.left = cx-110;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, "Name:");

    m.bot = cy+45;
    m.left = cx-9;
    m.center = 0;
    ggprint13(&m, 16,  0x00000000, input.text);

    glEnable(GL_TEXTURE_2D);
    m.bot = cy + 7;
    m.left = cx-120;
    m.center = 0;
    ggprint13(&m, 0,  0x0000000, " -Choose ship to start playing- ");
}

void drawShipsOptions(int xres, int yres)
{
    glEnable(GL_TEXTURE_2D);
    int cx = xres / 2;
    int cy = yres / 2;
    //ship option

    //ship1
    glGenTextures(1, &silhouetteShip1);
    glGenTextures(1, &shipTexture1);
    shipImage1 = ppm6GetImage("./assets/ship11.ppm");
    unsigned char *silhouetteData = buildAlphaData(shipImage1);
    int shipW = shipImage1->width;
    int shipH = shipImage1->height;
    glBindTexture(GL_TEXTURE_2D, silhouetteShip1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, shipW, shipH, 0, GL_RGBA,\
            GL_UNSIGNED_BYTE, silhouetteData);
    free(silhouetteData);

    //ship2
    glGenTextures(1, &silhouetteShip2);
    glGenTextures(1, &shipTexture2);
    shipImage2 = ppm6GetImage("./assets/ship2.ppm");
    silhouetteData = buildAlphaData(shipImage2);
    int shipW2 = shipImage2->width;
    int shipH2 = shipImage2->height;
    glBindTexture(GL_TEXTURE_2D, silhouetteShip2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, shipW2, shipH2, 0, GL_RGBA,\
            GL_UNSIGNED_BYTE, silhouetteData);
    free(silhouetteData);

    //ship3
    glGenTextures(1, &silhouetteShip3);
    glGenTextures(1, &shipTexture3);
    shipImage3 = ppm6GetImage("./assets/ship3.ppm");
    silhouetteData = buildAlphaData(shipImage3);
    int shipW3 = shipImage3->width;
    int shipH3 = shipImage3->height;
    glBindTexture(GL_TEXTURE_2D, silhouetteShip3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, shipW3, shipH3, 0, GL_RGBA,\
            GL_UNSIGNED_BYTE, silhouetteData);
    free(silhouetteData);

    //ship1
    float wid = 35.0f;
    glPushMatrix();
    glTranslatef(cx-90, cy-40, 0.0f);
    glBindTexture(GL_TEXTURE_2D, silhouetteShip1);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();
    glPopMatrix();
    //ship2
    glPushMatrix();
    glTranslatef(cx-10, cy-40, 0.0f);
    glBindTexture(GL_TEXTURE_2D, silhouetteShip2);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();
    glPopMatrix();
    //ship3
    glPushMatrix();
    glTranslatef(cx+70, cy-40, 0.0f);
    glBindTexture(GL_TEXTURE_2D, silhouetteShip3);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid, -wid);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(wid, wid);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(wid, -wid);
    glEnd();
    glPopMatrix();

    glDisable(GL_ALPHA_TEST);
    glDisable(GL_TEXTURE_2D);
}
void gameSettings(int xres, int yres, Game *g)
{
    Rect m;
    int cx = xres / 2;
    int cy = yres / 2;

    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glColor3f(0.0, 0.1, 0.7); 
    glBegin(GL_POLYGON);
    glVertex2i(cx - 40 , cy + 40); //-
    glVertex2i(cx - 20 , cy + 50); //- 
    glVertex2i(cx + 115, cy + 50); //right-up 
    glVertex2i(cx + 115, cy - 55); 
    glVertex2i(cx + 105, cy - 65);  
    glVertex2i(cx - 20 , cy - 65);  
    glVertex2i(cx - 40 , cy - 55);  
    glVertex2i(cx - 130, cy - 55);  
    glVertex2i(cx - 130, cy + 40); //-
    glEnd();

    //music?
    glBegin(GL_POLYGON);
    glVertex2i(530, 420); 
    glVertex2i(515, 420); 
    glVertex2i(515, 435); 
    glVertex2i(530, 435); 
    glEnd();

    if (g->button[0].over == 1 || overSett1) {
        glColor3f(1.0, 0.0, 0.0); 
        glBegin(GL_POLYGON);
        glVertex2i(530, 420); 
        glVertex2i(515, 420); 
        glVertex2i(515, 435); 
        glVertex2i(530, 435); 
        glEnd();
        glColor3f(0.0, 0.1, 0.7); 
    }

    //mouse?
    glBegin(GL_POLYGON);
    glVertex2i(530, 390); 
    glVertex2i(515, 390); 
    glVertex2i(515, 405); 
    glVertex2i(530, 405); 
    glEnd();

    if (g->button[1].over == 1 || overSett2) {
        glColor3f(1.0, 0.0, 0.0); 
        glBegin(GL_POLYGON);
        glVertex2i(530, 390); 
        glVertex2i(515, 390); 
        glVertex2i(515, 405); 
        glVertex2i(530, 405); 
        glEnd();
        glColor3f(0.0, 0.1, 0.7); 
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);

    glEnable(GL_TEXTURE_2D);
    m.bot = cy + 17;
    m.left = cx-20;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, "SETTINGS");

    m.bot = cy-9;
    m.left = cx-85;
    m.center = 0;
    ggprint13(&m, 0,  0x0000000, "Music on/off");

    m.bot = cy - 40;
    m.left = cx-85;
    m.center = 0;
    ggprint13(&m, 0,  0x0000000, "Use mouse to play");

}
void gameScores(int xres, int yres) 
{
    int sum = xres + yres;
    if(sum){}
}
void gameCredits(int xres, int yres)
{
    Rect m;
    int cx = xres / 2;
    int cy = yres / 2;

    glEnable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    glColor3f(0.0, 0.1, 0.7); 
    glBegin(GL_POLYGON);
    glVertex2i(cx - 40 , cy - 20); //- 
    glVertex2i(cx - 20 , cy - 10); //- 
    glVertex2i(cx + 115, cy - 10); //right-up 
    glVertex2i(cx + 115, cy - 140); 
    glVertex2i(cx + 105, cy - 150);  
    glVertex2i(cx - 20 , cy - 150);  
    glVertex2i(cx - 40 , cy - 140);  
    glVertex2i(cx - 130, cy - 140);  
    glVertex2i(cx - 130, cy - 20); //- 
    glEnd();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_BLEND);

    glEnable(GL_TEXTURE_2D);
    m.bot = cy-43;
    m.left = cx-20;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, "CREDITS");

    m.bot = cy-70;
    m.left = cx-115;
    m.center = 0;
    ggprint17(&m, 0,  0x0000000, ".:Developers:.");
    m.bot = cy - 72;
    m.left = cx-115;
    m.center = 0;
    ggprint13(&m, 0,  0x0000000, "_____________________");

    m.bot = cy - 92;
    m.left = cx-57;
    m.center = 0;
    ggprint13(&m, 0,  0x0000000, "Herrera, Erick");

    m.bot = cy - 112;
    m.left = cx-63;
    m.center = 0;
    ggprint13(&m, 0,  0x0000000, "Parker, Andrew");

    m.bot = cy - 132;
    m.left = cx-62;
    m.center = 0;
    ggprint13(&m, 0,  0x0000000, "Toscano, Erick");
    glDisable(GL_TEXTURE_2D);
}

int check_MainButtons(XEvent *e, Game *g, int xres, int yres, int lbutton)
{
    int x, y, i;
    x = e->xbutton.x;
    y = e->xbutton.y;
    y = yres - y;
    if (xres){}

    g->nbuttons = init_ButtonsMain(g);

    for (i=0; i < g->nbuttons; i++) {
        g->button[i].over=0;
        if (x >= g->button[i].r.left && //left
                x <= g->button[i].r.right && //right
                y >= g->button[i].r.bot && //bot
                y <= g->button[i].r.top) { //top
            g->button[i].over = 1;
            if (g->button[i].over) {
                if (lbutton) {
                    switch (i) {
                        case 0:
                            //cout << "NEW()\n";
                            g->state_newG = 1;
                            //g->state_menu = 0;
                            break;
                        case 1:
                            g->state_sett = 1;
                            //cout << "SETT()\n";
                            break;
                        case 2:
                            cout << "SCORES()\n";
                            break;
                        case 3:
                            g->state_cred = 1;
                            //cout << "CREDITS()\n";
                            break;
                        case 4:
                            cout << "EXIT\n";
                            return 1;
                            break;
                    }
                }
            }
        }
    }
    return 0;
}

void check_NewGButtons(XEvent *e, Game *g, int xres, int yres, int lbutton)
{
    int x, y, i;
    x = e->xbutton.x;
    y = e->xbutton.y;
    y = yres - y;
    if (xres) {}

    g->nbuttons = init_ButtonsNewG(g);

    for (i=0; i < g->nbuttons; i++) {
        g->button[i].over=0;
        if (x >= g->button[i].r.left && //left
                x <= g->button[i].r.right && //right
                y >= g->button[i].r.bot && //bot
                y <= g->button[i].r.top) { //top
            g->button[i].over = 1;
            if (g->button[i].over) {
                if (lbutton) {
                    switch (i) {
                        case 0:
                            system(" cp ./assets/ship11.ppm ./assets/\
                                    ship.ppm");
                            g->state_newG = 0;
                            //g->state_menu = 0;
                            //return 1;
                            break;
                        case 1:
                            system("convert ./assets/ship2.png ./assets/\
                                    ship.ppm");
                            g->state_newG = 0;
                            //return 0;
                            break;
                        case 2:
                            system("convert ./assets/ship3.png ./assets/\
                                    ship.ppm");
                            g->state_newG = 0;
                            //return 0;
                            break;
                    }
                }
            }
        }
    }
    //return 0;
}

void check_SettButtons(XEvent *e, Game *g, int xres, int yres, int lbutton)
{
    int x, y, i;
    x = e->xbutton.x;
    y = e->xbutton.y;
    y = yres - y;

    ALuint alBuffer1[2];
    ALuint alSource1[2];

    alBuffer1[0] = alutCreateBufferFromFile("sounds/8bitBack.wav");
    alBuffer1[1] = alutCreateBufferFromFile("");

    alGenSources(2, alSource1);
    alSourcei(alSource1[0], AL_BUFFER, alBuffer1[0]);
    alSourcei(alSource1[1], AL_BUFFER, alBuffer1[1]);

    alSourcef(alSource1[0], AL_GAIN, 1.0f);
    alSourcef(alSource1[0], AL_PITCH, 1.0f);
    alSourcef(alSource1[0], AL_LOOPING, AL_TRUE);

    alSourcef(alSource1[1], AL_GAIN, 1.0f);
    alSourcef(alSource1[1], AL_PITCH, 1.0f);
    alSourcef(alSource1[1], AL_LOOPING, AL_FALSE);

    if (xres) {}
    g->nbuttons = init_ButtonsSett(g);

    for (i=0; i < g->nbuttons; i++) {
        g->button[i].over=0;
        if (x >= g->button[i].r.left && //left
                x <= g->button[i].r.right && //right
                y >= g->button[i].r.bot && //bot
                y <= g->button[i].r.top) { //top
            g->button[i].over = 1;
            if (g->button[i].over) {
                if (lbutton) {
                    switch (i) {
                        case 0:
                            overSett1 ^= 1;
                            if (overSett1) {
                                //backGround();
                                //playBackGround(alSource1[1]);
                                /*for (int i=0; i < 15; i++){
                                  alSourcePlay(alSource1[1]);
                                  usleep(20500);
                                  }*/
                            }else{
                                /*  for (int i=0; i < 15; i++){
                                    alSourcePlay(alSource1[0]);
                                    usleep(20500);
                                    }*/
                            }
                            // playBackGround(alSource1[0]);
                            //g->state_newG = 0;
                            break;
                        case 1:
                            overSett2 ^= 1;
                            g->mouseControl ^= 1;
                            g->state_sett = 0;
                            break;
                    }
                }
            }
        }
    }
}
