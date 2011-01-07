#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <windows.h>


void DrawPixel(SDL_Surface *screen, int x, int y,Uint8 R, Uint8 G, Uint8 B);
void InitImages(void);
void DrawIMG(SDL_Surface *img, int x, int y);
void DrawIMG(SDL_Surface *img, int x, int y, int w, int h, int sx, int sy);
void DrawBG(void);
void DrawScene(void);
void InitGame(void);


SDL_Surface *back;
SDL_Surface *batA;
SDL_Surface *batB;
SDL_Surface *ball;
SDL_Surface *screen;

SDL_Surface *digit[6];

int VG= 50;
int xpos=620, ypos=VG;
int xpos1=2, ypos1=VG;
int xpos2=300, ypos2= 50;

int Win;
int Win1= 0;
int Win2= 0;

 bool redraw= false;
 bool CloseThread= false;
 bool NewGame= false;

DWORD WINAPI GoBall (LPVOID pParam)
{
    int VX, VY;
    VX= 2;
    VY= 3;


    while (true)
    {
        if (CloseThread)
        {

            MessageBoxA(NULL, "fes", "fdsf", MB_OK);
            break;
        }

        Sleep(10);
        xpos2+= VX;
        ypos2+= VY;
        if (xpos2<=xpos1+14)
        {
            if (!((ypos2>=ypos1-12)&&(ypos2<=ypos1+85-12)))
            {
                MessageBoxA(NULL, "HAHA", "RIGTH WINS", MB_OK);
                Win= 1;
                Win2++;
                NewGame= true;
                break;
            }

            VX= -1*VX;
        }
        if (xpos2>=xpos-25)
        {
            if (!((ypos2>=ypos-12)&&(ypos2<=ypos+85-12)))
            {
                MessageBoxA(NULL, "HAHA", "LEFT WINS", MB_OK);
                Win= 2;
                Win1++;
                NewGame= true;
                break;

            }

            VX= -1*VX;
        }
        if (ypos2<=VG)
            VY= -1*VY;
        if (ypos2>=480-25)
            VY= -1*VY;


        if (Win1==5 || Win2==5)
            Win1=Win2= 0;


    }

    return 0;
}

/* ------------------------------------------- */
int main(int argc, char *argv[]){

 Uint8* keys;
 char mes[100];

srand(time(0));

 if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 ){
   printf("Unable to init SDL: %s\n", SDL_GetError());
   exit(1);
 }

 atexit(SDL_Quit);

 SDL_WM_SetCaption("arcanoid","arcanoid");
 SDL_WM_SetIcon(SDL_LoadBMP("icon.bmp"), NULL);

 screen = SDL_SetVideoMode(640, 480, 32, SDL_SWSURFACE);
 if ( screen == NULL ){
   printf("Unable to set 640x480 video: %s\n", SDL_GetError());
   exit(1);
 }

 InitImages();
 InitGame();


CreateThread(NULL, 0, GoBall , (LPVOID)0, NULL, NULL);

DrawScene();
 int done=0;
 while(done == 0)
 {

   SDL_Event event;

   while ( SDL_PollEvent(&event) )
   {
     if ( event.type == SDL_QUIT ){ done = 1; }
     if ( event.type == SDL_KEYDOWN )
     {
       if ( event.key.keysym.sym == SDLK_ESCAPE ){ done = 1; }
     }
   }

    if (NewGame)
    {
        bool t= false;
        if ((Win1!=5)&&(Win2!=5))
        {
            InitGame();
            CreateThread(NULL, 0, GoBall , (LPVOID)0, NULL, NULL);
        }
        if (Win1==5)
        {
            strcpy(mes, "The first one wins!\nDo you want to play again?");
            t= true;
        } else
        if (Win2==5)
        {
            strcpy(mes, "The second one wins!\nDo you want to play again?");
            t= true;
        }
        if (t)
        if (MessageBoxA(NULL, mes, "Game Over", MB_YESNO)==IDYES)
        {
            InitGame();
            CreateThread(NULL, 0, GoBall , (LPVOID)0, NULL, NULL);
        } else
            break;

    }


   keys = SDL_GetKeyState(NULL);

   if(keys[SDLK_UP])
   {
       if (ypos-4>=VG)
        ypos -= 4;
   }
   if(keys[SDLK_DOWN])
   {
       if (ypos+4<=480-85)
        ypos += 4;
   }


   if(keys[SDLK_w])
   {
       if (ypos1-4>=VG)
        ypos1 -= 4;
   }

    if(keys[SDLK_s])
    {
        if (ypos1+4<=480-85)
         ypos1 += 4;
    }


    while (redraw)
    {

    }
    DrawScene();
 }
 CloseThread= true;
SDL_Quit();
 return 0;

}

/* ------------------------------------------- */
void InitImages(){

 back=SDL_LoadBMP("bg.bmp");
 batA=SDL_LoadBMP("image.bmp");
 batB=SDL_LoadBMP("image1.bmp");
 ball=SDL_LoadBMP("image2.bmp");
 digit[0]= SDL_LoadBMP("0.bmp");
 digit[1]= SDL_LoadBMP("1.bmp");
 digit[2]= SDL_LoadBMP("2.bmp");
 digit[3]= SDL_LoadBMP("3.bmp");
 digit[4]= SDL_LoadBMP("4.bmp");
 digit[5]= SDL_LoadBMP("5.bmp");

}



/* ------------------------------------------- */
void DrawIMG(SDL_Surface *img, int x, int y){

 SDL_Rect dest;
 dest.x = x;
 dest.y = y;

 SDL_BlitSurface(img, NULL, screen, &dest);

}

/* ------------------------------------------- */
void DrawIMG(SDL_Surface *img, int x, int y, int w, int h, int sx, int sy){

 int a=0;
 SDL_Rect dest;
 dest.x = x;
 dest.y = y;

 SDL_Rect src;
 src.x = sx;
 src.y = sy;
 src.w = w;
 src.h = h;

 SDL_BlitSurface(img, &src, screen, &dest);

}
/* ------------------------------------------- */


/* ------------------------------------------- */

/* ------------------------------------------- */
void DrawBG(){

 DrawIMG(back, 0, 0);

}

/* ------------------------------------------- */
void DrawScene(){


 redraw= true;


 DrawIMG(back, 0, 0);
 DrawIMG(batA, xpos1 , ypos1);
 DrawIMG(batB, xpos , ypos );
 DrawIMG(ball, xpos2 , ypos2);
 for(int i=0; i<640; i++)
    DrawPixel(screen, i, VG, 0, 0, 0);
  DrawIMG(digit[Win1], 20 , 10);
  DrawIMG(digit[Win2], 600 , 10);

 SDL_Flip(screen);

 redraw= false;

}

void DrawPixel(SDL_Surface *screen, int x, int y,Uint8 R, Uint8 G, Uint8 B)
{
    Uint32 *p;
    Uint32 color = SDL_MapRGB(screen->format, R, G, B);
    p = (Uint32 *)screen->pixels + y * screen->pitch/4 + x;
    *p=color;

}

void InitGame(void)
{
    VG= 50;
    xpos=620;
    ypos=VG;
    xpos1=2;
    ypos1=VG;
    xpos2=50;
    ypos2= rand()%400+50;
    redraw= false;
    CloseThread= false;
    NewGame= false;

}
