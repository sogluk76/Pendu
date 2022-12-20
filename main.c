#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//variable globales
char mot[50];
char mot2[50];
int erreurs = 0;
int t = 0;
//afficher la liste des lettres deja utilisé
void afficherChaine(char chaine[], char lettre)
{

    int i = 0;
    printf("lettre deja utilisée: ");
    while( chaine [i] != '_')
    {
        printf("%c / ",chaine [i]);
        i++;
    }
    printf("\n");
}
// ajouter la lettre saisie
void ajoutercharactere( char chaine[], char lettre)
{

    int i = 0;
    while( chaine [i] != '_')
    {
        i++;
    }
    chaine[i] = lettre;
}
//affiche le mot a touve
void affichermot(char mot[])
{
    int i = 0;
    while( mot[i] != '\0')
    {
        printf("%c ",mot [i]);
        i++;
    }
    printf("\n");
}

//remplacer le "_" avec la lettre choisie si elle est bonne
void MettreAJourMotCache(char mot[], char motcache[], char lettre)
{
    int i = 0;
    bool trouve = false;
    while( mot[i] != '\0')
    {
        if(mot[i] == lettre)
        {
            motcache[i] = lettre;
            trouve = true;
        }

        i++;
    }

    if (!trouve)
    {
        erreurs++;
        printf("cette lettre n'est pas dans le mot.\n");
    }
}




//detecter si le mot est devine
bool MotEstDevine(char motcache[])
{
    int i = 0;
    while(motcache[i] != '\0')
    {
        if(motcache[i] == '_')
        {
            return false;
        }
        i++;
    }
    return true;
}


//afficher le pendu avec ces 10 etapes
void affichePendu (int tentavite)
{
    const char *pendu[]=
    {
        "\n\n\n\n\n\n\n\n\n",
        "\n\n\n\n\n\n\n\n- - - - - - -\n",
        "\n|  \n| \n| \n| \n| \n| \n|\n- - - - - - -\n",
        "_ _ _ _ _ _ _ \n|\n|\n|\n|\n|\n|\n|\n- - - - - - -\n",
        "_ _ _ _ _ _ _ \n| /          \n|/           \n|\n|\n|\n| \n|\n- - - - - - -\n",
        "_ _ _ _ _ _ _ \n| /         | \n|/          O \n|\n|\n|\n| \n|\n- - - - - - -\n",
        "_ _ _ _ _ _ _ \n| /         | \n|/          O \n|           |\n|           | \n| \n|\n|\n- - - - - - -\n",
        "_ _ _ _ _ _ _ \n| /         | \n|/          O \n|          /|\n|         / |  \n|             \n|                \n|\n- - - - - - -\n",
        "_ _ _ _ _ _ _ \n| /         | \n|/          O \n|          /|\\\n|         / | \\ \n|             \n|                \n|\n- - - - - - -\n",
        "_ _ _ _ _ _ _ \n| /         | \n|/          O \n|          /|\\\n|         / | \\ \n|          /      \n|         /          \n|\n- - - - - - -\n",
        "_ _ _ _ _ _ _ \n| /         | \n|/          O \n|          /|\\\n|         / | \\ \n|          / \\     \n|         /   \\         \n|\n- - - - - - -\n",

    };

    printf("%s", pendu[tentavite]);
}


//choisir un mot au hasard
void mot_hasard()
{
    int NombreMots = 144;
    FILE *fmots;
    fmots = fopen("mots.txt", "r");

    int idx_mot = rand() % NombreMots;

    for (int n=0; n<idx_mot; n++)
    {
        fgets(mot, sizeof(mot), fmots);
    }

    fclose(fmots);
}

int main()
{
  int taille;
  char lettre;
  bool gagne;
  
  // boucle infinie principale 
  do {
        erreurs = 0;  // remettre variable globale a 0
        system("clear");  // vide l'écran
        srand(time(NULL));  // Init le generateur de nombre aléatoire
        char lettreSaisie[] = "_______________________________________________________________________________________";
        char motcache[] = "__________________________________";
        lettre = '\0';
        gagne = false;
        
        //début de boucle
        int reponce = 0;

        // boucle jusqu'à un choix correct de l'utilisateur 
        do
          {
           printf("choisir le nombre de joueur:\n");
           printf("1: 1 joueur\n2: 2 joueurs\n");
           scanf(" %d",&reponce);
          //si touche 1 entrer mettre mode solo
          if (reponce == 1)
          {
              printf("tu a choisi le mode solo, le mot est choisi aléatoirement.\n");
              sleep(2);
              system("clear");
              
              //sert a prendre la taille du mot aleatoire et mettre un \0 au bon endroit
              mot_hasard();
              taille = strlen(mot);
              motcache[taille -1] = '\0';
          }
          //si touche 2 entrer mettre mode duo
          else if (reponce == 2)
          {
              printf("tu a choisi le mode deux joueurs.\n");
              printf("choisissez votre mot.\n");
              scanf("%s",&mot);
              taille = strlen(mot);
              motcache[taille] = '\0';
              sleep(2);
              system("clear");
          }
          else
          {
            printf("seulement utilise la touche 1 ou la touche 2\n");
            sleep (2);
            system("clear");
          }
        }
        while(reponce != 1 & reponce != 2);
        // fin boucle choix utilisateur  

          
        // boucle du jeu  
        do
        {
            ajoutercharactere(lettreSaisie, lettre);
            afficherChaine(lettreSaisie, lettre);
            affichePendu(erreurs);
            printf("%d erreur(s)\n",erreurs);
            affichermot(motcache);
            printf("saisisez une lettre;\n");
            scanf(" %c",&lettre);
            printf("lettre saisie: %c\n",lettre);
            MettreAJourMotCache(mot, motcache, lettre);
            sleep(1);
            system ("clear");
            if (erreurs >= 10)
            {  
                gagne = true;
                affichePendu(erreurs);
                printf("%d erreur(s)\n",erreurs);
                printf("dommage tu as perdu!\n");
                printf("le mot était: %s\n",mot);
            }
            // condition pour gagne
            if (MotEstDevine(motcache))
            {
                affichePendu(erreurs);
                gagne = true;
                printf("bravo tu as gagné!\n");
                printf("%d erreur(s)\n",erreurs);
                printf("le mot était: %s\n",mot);
            }
        }
        //fin de boucle si gagne
        while(!gagne);
        sleep(3);
    }
    while(t == 0);//retour debut jeux pour le recommencer
    return 0;
}