#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define maxepreuve 200
#define maxpays 150
#define maxathlete 10

/**TP 1 DU S2 DE BOUKHETALA ZAINEB ET BOUYOUHIAOUI MERIEM SECTION C GROUPE 09**/

/**déclaration de la liste chainée**/
typedef char nomathlete[25];
typedef struct concurrents* ptr;
struct concurrents
{
    nomathlete nomath;
    ptr next;
};
/** implémentation du modèle de la machine abstraite **/
void allouer(ptr* p)
{
    *p=(ptr)malloc(sizeof(struct concurrents));
}
char* valeur(ptr p)
{
    return((*p).nomath);
}
ptr suivant(ptr p)
{
    return((*p).next);
}
void liberer(ptr p)
{
    free(p);
}
void aff_val(ptr p,nomathlete nomath)
{
    strcpy((*p).nomath,nomath);
}
void aff_adr(ptr p,ptr q)
{
    (*p).next=q;
}

/**une procédure d'affichage**/
void afficher(ptr tete)
{
    ptr p;
    p=tete;
    printf("\n");
    while(p!=NULL)
    {
        printf("\nparticipant(e):  %s  ",valeur(p));
        p=suivant(p);
    }
    printf("\n");
}

/**longueur d'une LLC**/
int lengthLLC(ptr debut)
{
    int cpt;
    ptr p;
    cpt = 0;
    p = debut;
    while(p!=NULL)
    {
        cpt++;
        p = p->next;
    }
return cpt;
}

/**une fonction qui génère des chaines de caractères de longueur N aléatoire(ment)**/
char  *stringsrandomly ( int N )
{
    int k;
    char  * Chaine = malloc(N+1);
    char Chr1[26] = "abcdefghijklmnopqrstuvwxyz";
    for (k=0;k<N; k++)
    {
        *(Chaine+k) = Chr1[rand() % 26] ;
    }
    Chaine[k] =  '\0' ;/**ce caractère marque la fin de la chaine**/
    return (Chaine);
}

/** Une fonction qui retourne 1 si le nom d'athlete existe deja dans la LLC**/
int no_exist(ptr tete,nomathlete mot)
{
    ptr p;
    p=tete;
    int b;
    while(p!=NULL)
        {
            b = strcmp(valeur(p),mot);
            if(b==0){return 1;}/**the name exists in the linked list**/
            p = suivant(p);
        }
    return 0; /**the name exists nowhere in the list**/
}

/**Une procédure pour afficher le contenu de tabpays**/
void write1d(char  tabpays[maxpays][maxpays], int nbpays)
{
    int i;
    for(i=0;i<nbpays;i++)
    {
        printf("| %s ", tabpays[i]);
    }
 }

 /**Une procédure pour afficher le contenu de tabepreuve**/
 void write1de(char tabepreuve[maxepreuve][maxepreuve], int nbepreuve)
 {
    int i;
    for(i=0;i<nbepreuve;i++)
    {
        printf("| %s ", tabepreuve[i]);
    }
 }

/** Module principal 1: qui permet de créer tabpays et tabepreuve ainsi que la matrice de LLCs tabjo **/
void creer_tabjo(ptr tabjo[maxepreuve][maxpays],char tabpays[maxpays][maxpays],char tabepreuve[maxepreuve][maxepreuve]){
    int s;
    FILE *fpointer ; /**that stands for file pointer, it is mostly needed for the communication between the file and the program**/
    fpointer = fopen("epreuvejo.txt","r");
    for (s=0;s<maxepreuve;s++)
        {
            fscanf(fpointer, "%[^\n]", tabepreuve[s]);
            fprintf(fpointer,"\n");
        }
    fclose(fpointer); /**we're done with epreuvejo text file**/
    FILE *fptr ;
    char c;
    fptr = fopen("pays.txt","r");
    for (s=0;s<maxpays;s++)
    {
        fscanf(fptr, "%[^\n]", tabpays[s]);
        fprintf(fptr,"\n");
    }
    fclose(fptr); /**we're done with paysjo text file**/
    int i,k,j;
    ptr p,q;
    char * inter;
    int nbconcurrents;
    ptr tete; /**now to the matrix**/
    srand(time(0));  /**pour générer a chaque exécution de nouveaux noms aléatoires (c'est valide pour le nombre de concurrents aussi)**/
    for (i=0;i<maxepreuve;i++)
    {
        for(j=0;j<maxpays;j++)
        {
            tabjo[i][j]=NULL;
            nbconcurrents = 0+rand()%11;
            if (nbconcurrents!=0)
            {
                tete = NULL;                                 /**Cette partie concerne l'initialisation de la tete**/
                allouer(&p);
                inter = stringsrandomly(1+rand()%13);
                aff_val(p,inter);
                aff_adr(p,NULL);
                tete=p;
                q=p;
                for(k=1;k<nbconcurrents;k++)          /**La boucle pour remplir la llc selon le nbconcurrents**/
                {
                    allouer(&p);
                    inter = stringsrandomly(1+rand()%13);
                    if(!no_exist(tete,inter))   /** il faut verifier que la liste ne contient pas ce nom deja **/
                    {
                      aff_val(p,inter);
                      aff_adr(p,NULL);
                      aff_adr(q,p);
                      q=p;
                    } /**end if**/
                } /**accolade de la boucle de k**/
                tabjo[i][j]=tete;
            } /**accolade de la condition qu'il ya au moins un concurrent pour remplir la LLC **/
        } /**accolade de la boucle des colonnes de tabjo**/
    } /**accolade de la boucle des lignes de tabjo**/
}

/** Module principal 2: inserer un nouvel athlete **/
ptr inserath(nomathlete nom, int nume,int nump, ptr tabjo[maxepreuve][maxpays])
{
    ptr tete,p;
    tete = tabjo[nume][nump];
    if((lengthLLC(tabjo[nume][nump])<=maxathlete)&&(no_exist(tabjo[nume][nump],nom)==0))
        {
            allouer(&p);
            aff_val(p,nom);
            if(tete==NULL) {tete=p;}
            else
            {
                aff_adr(p,tete); /**On insere le nouveau athlete au niveau de la tete**/
                tete=p;      /**Mise a jour de la tete**/
            }
            printf("\nL'athlete est maintenant insere !!\n\nOn vous souhaite bon courage dans les jeux olympiques de cette annee %s !!!\n",nom);
        }
    else
          printf("On ne peut malheureusement pas acceder a votre requete : Le nom que vous avez saisi existe deja!\n");/**Si le nom d'athlete existe déja**/
    tabjo[nume][nump]=tete;
    return tete;
}

/** Module principal 3: afficher les noms de tous les athletes d'un pays donné, en les classant par épreuve **/
void listathpays(char pays[45],ptr tabjo[maxepreuve][maxpays],char  tabpays[maxpays][maxpays],char tabepreuve[maxepreuve][maxepreuve])
{
     ptr p;
     int c,i,j,k;
     c=-1; /**variable permettant de stocker l'indice du pays qu'on souhiate afficher, sinon afficher un message d'erreur s'il n'existe pas**/
     for(k=0;k<maxpays;k++)
     {
        if(strcmp(pays,tabpays[k])==0)
            {c = k;}
     }
     if(c==-1){printf("\nCE PAYS NE FAIT PAS PARTIE DES PAYS PARTICIPANTS\n");}
     else
     {
         for(j=0;j<maxepreuve;j++)/**la boucle pour afficher les participants de chaque épreuve de ce pays**/
         {
             if (tabjo[j][c]!=NULL){
             printf("\nLes participants de l'epreuve de %s \n ",tabepreuve[j]);
             p=tabjo[j][c];
             while(p!=NULL)
             {
                printf("\nparticipant(e) : %s",valeur(p));
                p=suivant(p);
             }
             printf("\n");
             }
         }
     }

}

/** Module principal 4: retourne 1 si la liste est vide (aucun athlete n'est inscrit a cette épreuve, 0 sinon **/
int sansath(int ne,ptr tabjo[maxepreuve][maxpays])
{
    int v,j; /**j maxpays**/
    j=0;
    ptr tete;
    v=1; /**VRAI**/
        while(j<maxpays)
        {
            tete=tabjo[ne][j];
            if(tete!=NULL)
            {
                v=0;
                return v;
            }
            j++;
        }

return v;
}

/** Module principal 5: afficher le contenu complet de tabjo, épreuve par épreuve **/
void listjo(ptr tabjo[maxepreuve][maxpays],char tabepreuve[maxepreuve][maxepreuve],char tabpays[maxpays][maxpays])
{
    ptr p;
    int i,j;
    int lines=0;   /**Les lignes d'affichage dans la console qu'on incrementera selon le nombre de lignes affichés**/
    for( i=0;i<maxepreuve;i++)
    {
        printf("***Epreuve %d : %s\n",i+1,tabepreuve[i]);
        printf("\n");
        lines+=2;
        for( j=0;j<maxpays;j++)
        {
            if(lines<800)
            {
                if(tabjo[i][j]!=NULL)
                {
                    printf("***Pays %d : %s\n",j+1,tabpays[j]);
                    p=tabjo[i][j];
                    while(p!=NULL)  /**afficher la liste de partctipants**/
                    {
                        printf("\nparticipant(e) : %s",valeur(p));
                        p=suivant(p);
                        lines++;
                    }
                    printf("\n");
                    lines+=2;
                }
                printf("\n");
            }
            else
            {
                printf("appuyez sur n'importe quelle touche deux fois pour continuer : ");
                getchar();
                getchar();
                system("cls");
                lines=0;
            }
        } /**Fin de la boucle de lignes dans tabepays et colonnes de tabjo**/
        printf("\n");
        lines++;

    }/**Fin de la boucle de lignes de tabepreuve et tabjo**/
}

/** Module principal 6: supprimer un pays **/
void suppays(char pays[45],char tabpays[maxpays][maxpays],ptr tabjo[maxepreuve][maxpays],int *nbpays)
{
    int i,j,k;
    int trouve;
    ptr p,q;
    i=0;
    trouve=1;
    while((i<maxpays)&&(trouve==1))
    {
        if (strcmp(pays,tabpays[i])==0) /**vérifier si le pays qu'on cherche se trouve dans la case tabpays[i]**/
        {
            trouve=0;
            for(j=i;j<maxpays;j++)
            {
                strcpy(tabpays[j],tabpays[j+1]);/**effectuer un décalage dans tabpays**/
            }
        }
        else {i++;}
    }

    if (trouve==1)
        {
            printf("\nCE PAYS NE FAIT PAS PARTIE DES PARTICIPANTS\n");
        }
    else
    {
        for(k=0;k<5;k++)/**loop pour libérer les LLC des participants du pays supprimé**/
        {
            p=tabjo[k][i];
            while(p!=NULL)
            {
                q=p;
                p=suivant(p);
                liberer(q);
            }
        }
        for(j=0;j<5;j++)
        {
            for(k=i;k<4;k++)
            {
                tabjo[j][k]=tabjo[j][k+1]; /**effectuer un décalage de colonnes dans tabjo**/
            }
        }
        printf("\nA la suite de l'annonce que ce pays ^%s^ a decide, pour des raisons budgetaires ou politiques, de ne pas participer aux Jeux Olympiques de cette edition.",pays);
        printf("\nDommage, on aurait aimer vous voir parmi nous lors de cette edition");
        *nbpays=*nbpays-1;
    } /**fermeture de l'accolade du else **/
}

/** Module principal 7: permet de supprimer un athlete **/
ptr supath(nomathlete nomath,int nume,int nump,ptr tabjo[maxepreuve][maxpays])
{
    ptr tete,s,q,p;
    tete = tabjo[nume][nump];
    p=tete; /**le pointeur de l'athlete qu'on va supprimer**/
    q=NULL; /**le pointeur de l'athlete qui se trouve avant lui dans la LLC**/
    s=NULL; /**le pointeur de l'athlete qui se trouve apres lui dans la LLC**/
    int trouv=0;
    if((strcmp(valeur(p),nomath)==0)&&(tete==p)) /**si l'athlete se trouve au debut de la LLC**/
    {
        tete = suivant(tete);
        liberer(p);
        return tete;
    }
    while(p!=NULL)
    {
        q=suivant(p);
        if(strcmp(valeur(p),nomath)==0)
        {
            liberer(p);
            aff_adr(s,q); /**effectuer un chainage pour reconstruire la llc après avoir supprimer l'athlète**/
            trouv=1;
        }
        s=p;
        p=suivant(p);
    }
    if (!trouv) {printf("Participant inexistant  !!\n"); }
    return tete;
}

/** Module principal 8: supprime les lignes vides: les epreuves pour lesquelles aucun participant n'a pu s'inscrire **/
void suplignesvides(ptr tabjo[maxepreuve][maxpays],char tabepreuve[maxepreuve][maxepreuve], int* nbepreuve)
{
	int i=0;
	int j,k;
	char* c ;
	while (i<maxepreuve)
	{
		if (sansath(i,tabjo)) /**si l'épreuve ne contient aucun athlète participant**/
		{
		    for(k=i;k<maxepreuve;k++)
            {
                for(j=0;j<maxpays;j++)
                {
                    tabjo[k][j]=tabjo[k+1][j]; /**effectuer un décalage de lignes dans tabjo**/
                }

            }
            for (j=i;j<maxepreuve;j++)
            {
                strcpy(tabepreuve[j],tabepreuve[j+1]); /**effectuer un décalage dans tabepreuve**/
            }
            i--; /**décrémenter i car on a supprimé une ligne**/
            *nbepreuve = *nbepreuve-1;
		}
        i++;
	}
}


/**LE MENU**/
int main()
{
    ptr tabjo[maxepreuve][maxpays];
    ptr tete;
    nomathlete nom;
    int i,j,nume,nump;
    char tabpays[maxpays][maxpays];
    char tabepreuve[maxepreuve][maxepreuve];
    char pays[45];
    creer_tabjo(tabjo,tabpays,tabepreuve); /**créer tabjo, tabepreuve, tabpays**/
    int CHOICE;
    int Fin=1; /**booléen utilisé pour manipuler la répétition des choix**/
    int FinProg=1; /**booléen utilisé pour manipuler le menu**/
    int nbepreuve=maxepreuve;/**initialiser nbepreuve**/
    int nbpays=maxpays; /**initialiser nbpays**/
    while(FinProg)
    {
        system("cls");
        system("COLOR 71");
        printf("************************************************************************************************************************");
        printf("\n                       Bienvenue a la platforme dediee aux jeux olympiques de cette annee!!!\n");
        printf("************************************************************************************************************************\n");
        printf("\n^^^^Liste des options^^^^: \n");
        printf("\n1) Inserer un nouvel athlete\n");
        printf("\n2) Afficher les noms d'athletes d'un pays donne\n");
        printf("\n3) Afficher tous les participants aux Jeux Olympiques\n");
        printf("\n4) Supprimer un pays de la competition\n");
        printf("\n5) Supprimer un athlete de la competition\n");
        printf("\n6) Quitter la platforme\n");
        printf("\nVeuillez saisir votre choix: ");
        scanf("%d",&CHOICE);
        switch(CHOICE)
        {
            case 1:
            {
                Fin=1;
                while(Fin)
                {
                    system("cls");
                    system("COLOR E2");
                    printf("*** Vous avez choisi d'inserer un nouvel athlete ***\n");
                    printf("\nveuillez saisir son nom: ");
                    scanf("%s",&nom);
                    printf("\nveuillez entrer le numero de son epreuve: ");
                    scanf("%d",&nume);
                    if(nume>maxepreuve){printf("\nle nombre que vous avez saisi depasse le nombre d'epreuves existantes dans cette edition des JO !!\n");}
                    else
                    {
                        printf("\nveuillez entrer le numero de son pays: ");
                        scanf("%d",&nump);
                        if(nump>maxpays)
                            {printf("\nle nombre que vous avez saisi depasse le nombre de pays participants dans cette edition des JO !!\n");}
                        else
                        {
                            afficher(tabjo[nume-1][nump-1]);
                            if ((lengthLLC(tabjo[nume-1][nump-1])==maxathlete))
                                printf("\nOn ne peut malheureusement pas acceder a votre requete : Le nombre maximum de candidats est deja atteint !\n");
                            else
                            {
                                tabjo[nume-1][nump-1]=inserath(nom,nume-1,nump-1,tabjo);
                                afficher(tabjo[nume-1][nump-1]);
                            }
                        }
                    }
                    printf("\nVoulez-vous repeter l'operation? (Tapez n'importe quel nombre pour repeter sinon 0 pour retourner au menu) : ");
                    scanf("%d",&Fin);
                }

           }
           break;
           case 2:
           {
                Fin=1;
                while(Fin)
                {
                    system("COLOR E2");
                    system("cls");
                    printf("*** Vous avez choisi de voir la liste des athletes d'un pays ***\n");
                    printf("\nveuillez entrer son nom : ");
                    scanf("%s",&pays);
                    pays[0]=toupper(pays[0]);
                    listathpays(pays,tabjo,tabpays,tabepreuve);
                    printf("Voulez-vous repeter l'operation? (Tapez n'importe quel nombre pour repeter sinon 0 pour retourner au menu) : ");
                    scanf("%d",&Fin);
                }
           }
           break;
           case 3:
           {
               Fin=1;
               while(Fin)
               {
                   system("cls");
                   system("COLOR E2");
                   printf("*** Vous avez choisi d'afficher la liste des participants au JO ***\n");
                   suplignesvides(tabjo,tabepreuve,&nbepreuve);
                   listjo(tabjo,tabepreuve,tabpays);
                   printf("\nVoulez-vous repeter l'operation? (Tapez n'importe quel nombre pour repeter sinon 0 pour retourner au menu) : ");
                   scanf("%d",&Fin);
                }
            }
            break;
            case 4:
            {
                Fin=1;
                while(Fin)
                {
                    system("cls");
                    system("COLOR E2");
                    printf("*** Vous avez choisi de supprimer un pays ***\n");
                    printf("veuillez entrer ce pays : ");
                    scanf("%s",&pays);
                    pays[0]=toupper(pays[0]);
                    suppays(pays,tabpays,tabjo,&nbpays);
                    printf("\n\nListe des pays participants :\n\n");
                    write1d(tabpays,nbpays);
                    printf("\nVoulez-vous repeter l'operation? (Tapez n'importe quel nombre pour repeter sinon 0 pour retourner au menu) : ");
                    scanf("%d",&Fin);
                }
           }
           break;
           case 5:
           {
                Fin=1;
                while(Fin)
                {
                    system("cls");
                    system("COLOR E2");
                    printf("*** Vous avez choisi de supprimer un athlete ***\n");
                    printf("\nveuillez entrer le numero de son epreuve: ");
                    scanf("%d",&nume);
                    if (nume<=nbepreuve)
                    {
                        printf("\nveuillez entrer le numero de son pays: ");
                        scanf("%d",&nump);
                        if (nump<=nbpays)
                        {
                            if (tabjo[nume-1][nump-1]==NULL){printf("Ce pays n'a pas participe a cette epreuve malheureusement");}
                            else
                            {
                                afficher(tabjo[nume-1][nump-1]);
                                printf("veuillez saisir le nom de cette athlete disqualifie ou blesse: ");
                                scanf("%s",&nom);
                                tabjo[nume-1][nump-1]=supath(nom,nume-1,nump-1,tabjo);
                                afficher(tabjo[nume-1][nump-1]);
                            }
                        }
                        else printf("Vous avez depasse le nombre d'epreuves qui auront lieu cette edition!!");
                    }
                    else printf("Vous avez depasse le nombre de pays partcipants aux jeux de cette annee!!");
                    printf("\nVoulez-vous repeter l operation? (Tapez n'importe quel nombre pour repeter sinon 0 pour retourner au menu) : ");
                    scanf("%d",&Fin);
                }
           }
           break;
           case 6:
           {
               printf("\nC'est malheureux mais vous avez choisi de nous quitter, au revoir !!");
               FinProg=0;
           }
           break;
           default :
           {
               printf("\nVous avez entrer un numero qui n'est pas sur le menu !!\n");
               printf("\nVoulez vous retourner vers le menu ou quitter(tapez 0)? : ");
               scanf("%d",&Fin);
               if(!Fin)
               {
                   printf("\nC'est malheureux mais vous avez choisi de nous quitter, au revoir !!");
                   return 0;
               }
            }
        }
    }
    return 0;
}
