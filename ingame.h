#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include <stdlib.h>
#include <math.h>

int GAME=1;

//FPS LIMIT
#define FPS_LIMIT 75
Uint32 then, now, frames; 
int fps;
//END 

/// STANDART VAR ////

float x;
float y;

float x2;
float y2;


#define velocity 3.5
float vel;
float vel2;
float vel3;
float vel4;

// ---- GAME KEYS -----//


int LEFT;

int RIGHT;

int UP;

int DOWN;

int FIRE;

int F;
int W;

//-----------------------------------------------//


typedef struct WiHi
{

    SDL_Surface  *tmp;

}
WH;


WH pic[1900];

// хранение данных в переменных
typedef struct SiHi
{

 Mix_Chunk  *tmp;

}
SH;

SH sn[500];

// Хранение музыки в переменных
typedef struct MiHi
{

Mix_Music  *tmp;

}
MH;

MH mn[100];





SDL_Surface *display;

SDL_Event event;
Uint8* keys;

TTF_Font *fnt;


//-------------
typedef struct stars
{
    float x;
    float y;
    float speed;
}
stars;

#define MAX_SPEED 6
#define MAX_STAR 30


//------
int box( int num, float x1, float y1, int num2, float x2, float y2)
{
    int ycol=0;
    int xcol=0;

    if
    ((y1+pic[num].tmp->h>y2) && (y1<y2+pic[num2].tmp->h))
    {
        ycol=0;
    }
    else
    {
        ycol=1;
    }

    if
    ((x1+pic[num].tmp->w>x2) && (x1<x2+pic[num2].tmp->w))
    {
        xcol=0;
    }
    else
    {
        xcol=1;
    }

    if
    (xcol || ycol)
        return 0;
    else
        return 1;

}


void clear()
{
	SDL_FillRect(display, NULL, SDL_MapRGB(display->format, 0, 0, 0));
}


void fx()
{

    while (SDL_PollEvent(&event))
    {
        if (event.type==SDL_QUIT)
        {
            GAME=0;
            SDL_Quit();
        }

        if (event.type==SDL_KEYDOWN)
        {
            if(event.key.keysym.sym==SDLK_ESCAPE)
            {
                GAME=0;
                SDL_Quit();
            }
        }
    }

    keys=SDL_GetKeyState(NULL);

    if(keys[SDLK_LEFT])
    {
	    LEFT=1; vel=velocity;
    }
    else
        LEFT=0;

    if(keys[SDLK_RIGHT])
    {
	    RIGHT=1;vel2=velocity;
    }
    else
        RIGHT=0;

    if(keys[SDLK_UP])
    {
	    UP=1;vel3=velocity;
    }
    else
        UP=0;

    if(keys[SDLK_DOWN])
    {
	    DOWN=1;vel4=velocity;
    }
    else
        DOWN=0;

    if(keys[SDLK_SPACE])
    {
    FIRE=1;
    }
    else
        FIRE=0;



    if(keys[SDLK_f])
    {
        F=1;
    }
    else
        F=0;

    if(keys[SDLK_w])
    {
        W=1;
    }
    else
        W=0;



    ///VELOCITY
    
    if (vel>0){vel=(float)(vel-0.1);}
    if (vel<=0){vel=0;}
    x=x-vel;

    if (vel2>0){vel2=(float)(vel2-0.1);}
    if (vel2<=0){vel2=0;}
    x=x+vel2;
    /////////////////


///VELOCITY2
    if (vel3>0){vel3=(float)(vel3-0.1);}
    if (vel3<=0){vel3=0;}
    y=y-vel3;

    if (vel4>0){vel4=(float)(vel4-0.1);}
    if (vel4<=0){vel4=0;}
    y=y+vel4;
    
    //FPS LIMIT

++frames; 

now = SDL_GetTicks();

if ( now > then ) {
fps= (int)((double)frames*1000)/(now-then);
} 
if ( fps > FPS_LIMIT ) {SDL_Delay(1000/FPS_LIMIT);}




//mouse();

    SDL_Flip(display);
    clear();
}




void colorfon(int r,int g, int b) //0-255
{
    SDL_FillRect(display, NULL, SDL_MapRGB(display->format,r , g, b));


}



void screen(int w, int h)
{

	SDL_Init (SDL_INIT_VIDEO|SDL_INIT_TIMER| SDL_INIT_AUDIO);

/*#ifdef __linux__
  putenv("SDL_VIDEODRIVER=dga");
#endif*/



//    display = SDL_SetVideoMode (w, h, 0, SDL_SWSURFACE | SDL_DOUBLEBUF| SDL_ANYFORMAT);
    display = SDL_SetVideoMode (w, h, 0, SDL_SWSURFACE | SDL_ANYFORMAT);

    SDL_WM_SetCaption ("Linux GAMES", NULL);
    TTF_Init();
    fnt = TTF_OpenFont("font.ttf", 20);

    //SOUND

    Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2024);

    
    
//for FPS limit
frames = 0;
then = SDL_GetTicks(); 

}

void screen(int w, int h, int full)
{
    SDL_Init (SDL_INIT_VIDEO|SDL_INIT_TIMER| SDL_INIT_AUDIO);
//    display = SDL_SetVideoMode (w, h, 0, SDL_HWSURFACE | SDL_DOUBLEBUF| SDL_ANYFORMAT|SDL_FULLSCREEN);
    display = SDL_SetVideoMode (w, h, 0, SDL_SWSURFACE | SDL_ANYFORMAT|SDL_FULLSCREEN);
    TTF_Init();
    fnt = TTF_OpenFont("font.ttf", 20);

//SOUND

    Mix_OpenAudio (44100, MIX_DEFAULT_FORMAT, 2, 2024);


//for FPS limit
frames = 0;
then = SDL_GetTicks(); 

}


void loadsprite(int num, char * name)
{

//    pic[num].tmp=SDL_LoadBMP(name);
pic[num].tmp=SDL_DisplayFormat(SDL_LoadBMP(name));

}



void sprite(int num, float x, float y)
{

    SDL_Rect shadow;
    shadow.x=(Sint16)x;
    shadow.y=(Sint16)y;
    SDL_SetColorKey(pic[num].tmp,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(pic[num].tmp->format,255,0,255));

    SDL_BlitSurface(pic[num].tmp,0,display,&shadow);

}

void sprite(int num, float x, float y, unsigned int a)
{

    SDL_Rect shadow;
    shadow.x=(Sint16)x;
    shadow.y=(Sint16)y;
    SDL_SetColorKey(pic[num].tmp,SDL_SRCCOLORKEY|SDL_RLEACCEL,SDL_MapRGB(pic[num].tmp->format,255,0,255));

    SDL_SetAlpha(pic[num].tmp, SDL_SRCALPHA|SDL_RLEACCEL,a);
    SDL_BlitSurface(pic[num].tmp,0,display,&shadow);

}



void print (char * txt,  float x, float y)
{

    SDL_Color color = {255,255,255,0};
    SDL_Rect dest= {(Sint16)x, (Sint16)y,0,0};
    pic[1000].tmp = TTF_RenderText_Blended( fnt, txt, color);
    SDL_BlitSurface( pic[1000].tmp,NULL, display,&dest );
    SDL_FreeSurface( pic[1000].tmp );

}





void print (int txt, float x, float y)
{

    SDL_Color color = {255,255,255,0};
    SDL_Rect dest= {(Sint16)x, (Sint16)y,0,0};

    char tmp[25];
    sprintf(tmp,"%i",txt);

    pic[1001].tmp = TTF_RenderText_Blended(fnt, tmp, color);
    SDL_BlitSurface( pic[1001].tmp,NULL, display,&dest );
    SDL_FreeSurface( pic[1001].tmp );

}



void mouseview(int i)
{

SDL_ShowCursor(i); 

}


void loadsound(char * name, int num)
{
sn[num].tmp = Mix_LoadWAV (name); 
     
     }

void sound (int num)
{
     	Mix_PlayChannel (-1, sn[num].tmp, 0);
     
     
     }

void loadmusic(char * name, int num)
{
       mn[num].tmp = Mix_LoadMUS (name);
     
     }


void music(int num)
{
     Mix_PlayMusic (mn[num].tmp, -1);
     
     }


void stopmusic()
{
     Mix_FadeOutMusic(1000);
     
     }
