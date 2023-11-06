#include <SDL2/SDL.h>
#include <unistd.h>
#include "function.h"

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 600
#define FPS 60
#define tabMax 6


/* Variable */

int x = 0;
int y = 0;

int ballx=WINDOW_WIDTH/2;
int bally=WINDOW_HEIGHT-100;
int rayonBall=10;
int vitesseX = 3;
int vitesseY = -5;

int xBarre = 300;
int yBarre = WINDOW_HEIGHT-50;
;
int longBarre = 100;
int hauteurBarre = 10;
int deplTouche = 20;


int xBrique=0;
int yBrique;
int xEcart = 27;
int yEcart = 20;
int longBrique = 70;
int hauteurBrique = 50;
int espaceBrique = 50;
int nbcolonne = 4 ;
int nbligne = 3 ;
int nbbrique;
int vieBrique[tabMax]={0,1,2,3,4,5};


/*Initialisation du jeu*/

void init_game(){
    //mettre votre code d'initialisation ici
    nbbrique = nbligne*nbcolonne;
}


/*BALLE*/

void rebondBall(){
    if (ballx >= WINDOW_WIDTH-rayonBall){
    vitesseX = vitesseX*(-1);}
    if (ballx <= rayonBall) 
    {vitesseX = vitesseX*(-1);}

    if (bally >= WINDOW_HEIGHT-rayonBall)
    {vitesseY = vitesseY*(-1);}
    if (bally <= rayonBall) 
    {vitesseY = vitesseY*(-1);}
}

void drawBall(){
    drawCircle(ballx,bally,rayonBall);
    ballx=ballx+ vitesseX;
    bally=bally+ vitesseY;
}

/*BARRE*/

void drawBarre(){
    drawRect(xBarre,yBarre,longBarre,hauteurBarre);
}

void rebondBarre (){
   
    if(((ballx >= xBarre) && (ballx <= xBarre+longBarre)) && (bally >= yBarre))
    {vitesseY= vitesseY*(-1);}

}

/*Brique*/

void rebondBrique (){
    
    /*
        if((bally<=yBrique+hauteurBrique+rayonBall) &&
        ((ballx<=xBrique+longBrique) && (ballx>=xBrique))){
            vitesseY=vitesseY*(-1); 
        }

        if((bally<=yBrique-rayonBall) && 
        ((ballx<=xBrique+longBrique) && (ballx>=xBrique))){
            vitesseY=vitesseY*(-1);
        }

        if((ballx>=xBrique-rayonBall) && 
        ((bally>=yBrique) && (bally<=yBrique+hauteurBrique))){
            vitesseX=vitesseX*(-1);
        }

        if((ballx<=xBrique+longBrique+rayonBall) && 
        ((bally>=yBrique) && (bally<=yBrique+hauteurBrique))){    
            vitesseX=vitesseX*(-1);
        }
  */ }
   


void drawBrick(){


        for (int i=0;i<nbcolonne;i++){      /*Correspond au ligne de mes briques*/
            for (int j=i; j<nbbrique;j=j+4){   /*Correspond au colonne de mes briques*/
                if (vieBrique[i]==1){
                xBrique=(xEcart+(i*longBrique));
                yBrique=(yEcart+i)/nbcolonne*(hauteurBrique)*j;
                drawRect(xBrique,yBrique,longBrique,hauteurBrique);
                }
                if (((ballx>xBrique) &&(ballx<xBrique+longBrique) &&
                (yBrique>yBrique) && (bally>yBrique+hauteurBrique))){
                    vitesseY=-vitesseY;
                    vieBrique[i]=0;
                }
            }
        }
}


/*Jeu*/

void drawGame(){
    /* Ici je dessine mon jeu
     * exemple position x, y modifiés dans KeyPressed() et utilisés pour
     * pouvoir deplacer la figure à chaque boucle de gameLoop()
     */
    clear();
    drawBall();
    drawBarre();
    drawBrick();
    rebondBall();
    rebondBarre ();
    actualize();
    usleep(1000000 / FPS); // 60 images par seconde | 1000000 = 1 seconde
}
void KeyPressed(SDL_Keycode touche){
    /** @brief event.key.keysym.sym renvoi la touche appuyé
     *
     */
    switch (touche) {
        // Voir doc SDL_Keycode pour plus de touches https://wiki.libsdl.org/SDL_Keycode
        // ici exemple ou appuyer sur les touches Q | D modifie x (position du carré dans drawGame())
        case SDLK_q:
            //touche q appuyé
            printf("Q\n");
                if (xBarre >= 0){
                    xBarre=xBarre-deplTouche;
;}
                else;
            break;
        case SDLK_d:
            //touche d appuyé
            printf("D\n");
            if (xBarre <= WINDOW_WIDTH-longBarre){
                    xBarre=xBarre+deplTouche;}
                else;
            break;
        case SDLK_ESCAPE:
            freeAndTerminate();
            break;
        default:
            break;
    }
}
void joyButtonPressed(){
}

void gameLoop() {
    int programLaunched = 1;
    while (programLaunched == 1) {
        // Boucle pour garder le programme ouvert
        // lorsque programLaunched est different de 1
        // on sort de la boucle, donc de la fonction
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // boucle pour la gestion d'évenement
            switch (event.type) {
                /** event.type renvoi le type d'evenement qui se passe
                 * (si on appuie sur une touche, clique de souris...)
                 * en fonction du type d'évènement on à alors
                 * différentes information accessibles
                 * voir doc pour plus d'event https://wiki.libsdl.org/SDL_EventType
                 */
                case SDL_QUIT:
                    // quand on clique sur fermer la fénêtre en haut à droite
                    programLaunched = 0;
                    break;
                case SDL_MOUSEBUTTONUP:
                    /* clique de la souris
                     * event.motion.y | event.motion.x pour les positions de la souris
                     */
                    printf("position de la souris x : %d , y : %d\n", event.motion.x, event.motion.y);
                    break;
                case SDL_KEYDOWN:
                    KeyPressed(event.key.keysym.sym);
                    break;
                case SDL_JOYBUTTONDOWN:
                    break;
                default:
                    break;
            }
        }
        /* coder ici pour que le code s'execute après chaque évenement
         * exemple dessiner un carré avec position int x, int y qu'on peut
         * deplacer lorsqu'on appuie sur une touche
         */
        drawGame();
    }
}

int main(){
    /** @description 3 fonctions dans le main qui permettent de créer l'application et la maintenir ouverte :
     *  init(...) : initialiser la SDL/ fenêtre
     *  gameLoop() : boucle de jeu dans laquelle l'application reste ouverte
     *  freeAndTerminate() : quitte le programme proprement
     */
    init(WINDOW_WIDTH, WINDOW_HEIGHT);
    init_game();
    gameLoop();
    printf("Fin du programme\n");
    freeAndTerminate();
}