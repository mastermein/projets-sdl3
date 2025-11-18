#include<SDL3/SDL.h> // Rend disponibles toutes les fonctions et types SDL dont on a besoin.

int main()
{
// initialisation de sdl
SDL_Init(SDL_INIT_VIDEO);
// SDL_Init permet d'initialiser (video ; audio ...)
// mais ici nous initialisons la video


// creation de fenetre
SDL_Window* window = SDL_CreateWindow("Mastermein", 800 , 600 , SDL_WINDOW_FULLSTREEN);
// SDL_CreateWindow cree une fenetre avec les arguments (nom,largeur,hauteur, flags(FULLSCREEN , RESIZABLE)


//creation d'un renderer ( moteur de rendu 2d permettant de dessiner dans la fenetre)
SDL_Renderer* renderer = SDL_CreateRenderer(window , nullptr);

SDL_Event e; // variable e de type SDL_Event qui va contenir les événements (clavier, souris, fermeture de fenêtre, etc.).
/* C’est le “message” que SDL te donne pour te dire :

l’utilisateur a cliqué

l’utilisateur a appuyé sur une touche

la fenêtre a été redimensionnée

la fenêtre demande à se fermer

la souris a bougé

une manette a été branchée / débranchée

etc.*/

bool run = true; // Booléen contrôlant la boucle principale (true tant que l'application tourne).

// positions de depart du carre
int x  = 200;
int y = 200;

while (run) // boucle principale du programme qui tourne tant que run est true.
{
    // lecture des evenements

    while(SDL_PollEvent(&e)) // SDL_PollEvent récupère un événement et le place dans e. Si aucun événement, la fonction retourne 0 et on sort de la boucle interne.
    // On traite chaque événement un par un (si plusieurs événements sont en file, on les consomme tous).
    {
        if (e.type== SDL_Event_QUIT)
        {
            run=false; /* Si l’utilisateur clique sur la croix de la fenêtre (ou autrement demande la fermeture), on met run = false → la boucle principale s’arrêtera et le programme se fermera proprement.*/
        }

        // Gestion du clavier 

        if(e.type == SDL_EVENT_KEY_DOWN)
        {
        /* Quand une touche est pressee, e.key.key contient quel bouton.

On compare avec SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT.*/
            switch (e.key.key)
            {
                case SDLK_UP: y-=10; break;
                case SDLK_DOWN: y+=10; break;
                case SDLK_LEFT: x-=10; break;
                case SDLK_RIGHT: x+=10; break;
            }
        }

    }
        //preparation du dessin

        // effacer l'ecran en noir
    SDL_SetRenderDrawcolor (renderer , 0,0,0,255); 
    SDL_RenderClear(renderer); /* Remplit toute la cible de rendu (l’ecran) avec la couleur courante et on obtient un ecran noir propre a chaque frame. */

        // Dessiner le carre bleu
    SDL_Rect carre = { x,y,100,100}; // Declare un rectangle aux coordonnees (x,y) de taille 100×100.
    SDL_SetRenderDrawcolor(renderer,0,0,255,255); //Change la couleur de dessin en bleu.
    SDL_RenderFillRect(renderer, &carre); // Remplit le carre avec la couleur courante (donc dessine le carre bleu).

    // affichage du rendu
    SDL_RenderPresent(renderer); // Permet de presenter ce qu’on a dessine a l’ecran


    /* Le programme retourne à while (run) 
    il va relire les evenements, gerer les nouvelles touches, redessiner, etc... dans une boucle infinie jusqu’a run = false.*/
}

// nettoyage apres sortie de la boucle
SDL_DestroyRenderer(renderer);// libere les resources du renderer
SDL_DestroyWindow(window); // detruit la fenetre
SDL_Quit();// ferme SDL proprement
return 0;
}


// pour la compilation 
//   g++ sdl3.cpp -lSDL3 -o sdl3

// execution
// ./sdl3.exe