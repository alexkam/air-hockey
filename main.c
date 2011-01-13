#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 24;

//surfaces
SDL_Surface *background = NULL;
SDL_Surface *ButPlay = NULL;
SDL_Surface *ButSound = NULL;
SDL_Surface *ButExit = NULL;
SDL_Surface *ButPlay2 = NULL;
SDL_Surface *ButSound2 = NULL;
SDL_Surface *ButExit2 = NULL;
SDL_Surface *message = NULL;
SDL_Surface *screen = NULL;
SDL_Surface *buttonsheet=NULL;
SDL_Surface *buttonSur=NULL;
SDL_Surface *addSur=NULL;
SDL_Surface *Song1 = NULL;
SDL_Surface *Song2 = NULL;
SDL_Surface *GameName = NULL;
SDL_Surface *Press = NULL;

//event structure
SDL_Event event;
SDL_Rect clips [4];
SDL_Rect box;


//font
TTF_Font *font1 = NULL;
TTF_Font *font2 = NULL;
TTF_Font *font3 = NULL;

//color of font
SDL_Color textColor = { 0, 0, 0 };
SDL_Color white = { 255, 255, 255 };

//music that will be played
Mix_Music *music = NULL;

SDL_Surface *load_image( char* filename ){

    // image that's loaded
    SDL_Surface* loadedImage = NULL;

    //optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename );

    //If image loaded
    if( loadedImage != NULL ){
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free old surface
        SDL_FreeSurface( loadedImage );

        //If surface was optimized
        if( optimizedImage != NULL ){
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF ) );
        }
    }

    //Return optimized surface
    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ){

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    SDL_BlitSurface( source, NULL, destination, &offset );
}

int init(){

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ){
        return 1;
    }

    //Set up screen
    buttonSur = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
    addSur = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up screen
    if( buttonSur == NULL )
    {
        return 1;
    }

    if( addSur == NULL ){
        return 1;
    }

    //Set up screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

    //If there was an error in setting up screen
    if( screen == NULL ){
        return 1;
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
        return 1;
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        return 1;
    }

    //Set the window caption
    SDL_WM_SetCaption( "Ping Pong ", NULL );

    //If everything initialized fine
    return 0;
}

int load_files(){
    //Load the background image
    background = load_image( "bg.png" );

    //Open font
    font1 = TTF_OpenFont( "font.ttf", 40 );
    font2 = TTF_OpenFont( "font.ttf", 20 );
    font3 = TTF_OpenFont( "font.ttf", 70 );


    //If there was a problem in loading background
    if( background == NULL ){
        return 1;
    }

    //If there was an error in loading font
    if( font1 == NULL ){
        return 1;
    }

    if( font2 == NULL ){
        return 1;
    }

    if( font3 == NULL ){
        return 1;
    }
    //Load music
    music = Mix_LoadMUS( "menumusic.wav" );

    //If there was a problem loading music
    if( music == NULL )
    {
        return 1;
    }

    //If everything loaded fine
    return 0;
}

void clean_up(){
    //Free the surfaces
    SDL_FreeSurface( background );
    SDL_FreeSurface( ButPlay );
    SDL_FreeSurface( ButSound );
    SDL_FreeSurface( ButExit );
    SDL_FreeSurface( ButPlay2 );
    SDL_FreeSurface( ButSound2 );
    SDL_FreeSurface( ButExit2 );
    SDL_FreeSurface( Song1 );
    SDL_FreeSurface( Song2 );
    SDL_FreeSurface( GameName );
    SDL_FreeSurface( Press );
    SDL_FreeSurface( buttonsheet );
    SDL_FreeSurface( buttonSur );
    SDL_FreeSurface( addSur );

    //Free the sound effects
    Mix_FreeMusic( music );

    //Close the font
    TTF_CloseFont( font1 );
    TTF_CloseFont( font2 );
    TTF_CloseFont( font3 );

    //Quit SDL_mixer
    Mix_CloseAudio();

    //Quit SDL_ttf
    TTF_Quit();

    //Quit SDL
    SDL_Quit();
}

int main( int argc, char* args[] ){
    //Quit flag
    int quit = 1;

    //Initialize
    if( init() == 1 ){
        return 1;
    }

    //Load the files
    if( load_files() == 1 ){
        return 1;
    }

    //Buttons in menu
    int b = 0;

    //Render the text
    ButPlay = TTF_RenderText_Solid( font1, "Play Game", textColor );
    ButSound = TTF_RenderText_Solid( font1, "Sound", textColor );
    ButExit = TTF_RenderText_Solid( font1, "Quit", textColor );
    ButPlay2 = TTF_RenderText_Solid( font1, "Play Game", white );
    ButSound2 = TTF_RenderText_Solid( font1, "Sound", white );
    ButExit2 = TTF_RenderText_Solid( font1, "Quit", white );
    Song1 = TTF_RenderText_Solid( font2, "Press <-- to sound off", textColor );
    Song2 = TTF_RenderText_Solid( font2, "Press --> to sound on", textColor );
    GameName = TTF_RenderText_Solid( font3, "Ping Pong", textColor  );
    Press = TTF_RenderText_Solid( font1, "Press any key", textColor  );


    //Show the message on the screen
    apply_surface( 0, 0, background, screen );
    apply_surface( 190 , 20 , GameName, buttonSur );
    apply_surface( SCREEN_WIDTH/2 -90, 400, Press, buttonSur );


    //Play music
    Mix_PlayMusic( music, -1 ) == -1;

   //While the user hasn't quit
    while( quit == 1 ){

        //While there's events to handle
        if( SDL_PollEvent( &event ) && event.type == SDL_KEYDOWN ){

            //Apply Surface
            apply_surface( 0, 0, background, screen );

            //Key States
            Uint8 *keystates = SDL_GetKeyState( NULL );

            //If user press Up
            if( keystates[ SDLK_UP ] ){
                b--;
                if (b<1){
                    b=5;
                }
            }

            //If user press Down
            if( keystates[ SDLK_DOWN ] ){
                b++;
                if (b>6){
                    b=1;
                }
            }

            //If user press Esc
            if( keystates[ SDLK_ESCAPE ] ){
                quit = 0;
            }

            //Main menu
            apply_surface( 245, SCREEN_HEIGHT/4 - 50, ButPlay, buttonSur );
            apply_surface( 280, SCREEN_HEIGHT/4 + 50, ButSound, buttonSur );
            apply_surface( 295, SCREEN_HEIGHT/4 + 200, ButExit, buttonSur );

            //Start
            if(b==1){
                    apply_surface( 240, SCREEN_HEIGHT/4 -53, ButPlay2, buttonSur );
                if( keystates[ SDLK_SPACE  ] ){
                    Mix_CloseAudio();
                    system( "Game.exe" );
               //     quit = 0;
                    exit(1);


                }
            }

            //Sound
            if(b==2){
                apply_surface( 275, SCREEN_HEIGHT/4 + 47, ButSound2, buttonSur );

                 if( keystates[ SDLK_SPACE  ] ){
                    apply_surface( SCREEN_WIDTH/2 -100, SCREEN_HEIGHT/2 -20, Song1, addSur );
                    apply_surface( SCREEN_WIDTH/2 -100, SCREEN_HEIGHT/2 +30, Song2, addSur );
                }
                //Turn on or off sound
                if( keystates[ SDLK_LEFT ] ){
                    Mix_HaltMusic();
                }
                else if( keystates[ SDLK_RIGHT ] ){

                    //Play music
                    Mix_PlayMusic( music, -1 ) == -1;
                }
            }


            //Exit
            if(b==3){
                apply_surface( 290, SCREEN_HEIGHT/4 + 200, ButExit2, buttonSur );
                if( keystates[ SDLK_SPACE  ] ){
                    quit = 0;
                }
            }

            //If the user has Xed out the window
            else if( event.type == SDL_QUIT ){
                //Quit the program
                quit = 0;
            }
        }

        //Update screen
        if( SDL_Flip( screen ) == -1 ){
            return 1;
        }
    }

    //Free surfaces, fonts and sounds
    clean_up();

    return 0;
}
