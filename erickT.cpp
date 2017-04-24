//needs: xres, yres
#include "fonts.h"
#include <GL/glx.h>
#include <GL/glu.h>
#include "header.h"


void mainMenu(int xres, int yres, Game *g) {
  Rect m;
 // int loc[2] = {0};
//  int xres = x;
//  int yres = y;

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
    glBindTexture(GL_TEXTURE_2D, 0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
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
  
  if (g->button[0].over == 1){
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

  if (g->button[1].over == 1){
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

  if (g->button[2].over == 1){
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
  //ggprint17(&m, 0,  0x0000000, "SCORES");
  ggprint17(&m, 0,  0x0000000, ":EXIT:");
  
  m.bot = cy - 43;
  m.left = cx-20;
  m.center = 0;
  ggprint17(&m, 0,  0x0000000, "CREDITS");
  
  glDisable(GL_TEXTURE_2D);
//======>>End Menu 
}

int init_ButtonsMain(Game *g){
  int buttons = 0;
  //size and positions of every clickable button
  //new
  g->button[buttons].r.left = 497;
  g->button[buttons].r.right = 600;
  g->button[buttons].r.bot = 477;
  g->button[buttons].r.top = 504;
  buttons++;
 //settings
  g->button[buttons].r.left = 600;
  g->button[buttons].r.right = 740;
  g->button[buttons].r.bot = 447;
  g->button[buttons].r.top = 475;
  buttons++;
 //scores
  g->button[buttons].r.left = 497;
  g->button[buttons].r.right = 600;
  g->button[buttons].r.bot = 418;
  g->button[buttons].r.top = 443;
  buttons++;
 
  return buttons;
}

void newGame(char input[], int size, int xres, int yres) {
//=============> INPUT BOX

  Rect m;
  int loc[2] = {0};
  //int xres = x;
  //int yres = y;

  int cx = xres / 2;
  int cy = yres / 2;
  glColor3f(1.0,1.0,0.0);

  cx = loc[0] + cx - 100;
  cy = loc[1] + cy - 40;

  glBegin(GL_QUADS);
    glVertex2i(cx, cy+163);              //1 lower left corner
    glVertex2i(cx, cy+179);              //2 upper left  "
    glVertex2i(cx + size*12, cy+179); 	 //3 upper right "
    glVertex2i(cx + size*12, cy+163);    //4 lower right "
  glEnd();

  glEnable(GL_TEXTURE_2D);
  m.bot = cy+163;
  m.left = cx;
  m.center = 0;
  ggprint8b(&m, 16,  0x00000000, input);

  //==========end box

 // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 // glDisable(GL_BLEND);

}
void gameSettings(int xres, int yres)
{
  int sum = xres + yres;
  if(sum){}
}
void gameScores(int xres, int yres) 
{
  int sum = xres + yres;
  if(sum){}
}
void gameCredits(int xres, int yres)
{
  int sum = xres + yres;
  if(sum){}
}
