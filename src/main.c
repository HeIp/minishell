/***********************************************************************************/
//                                                                                 //
// Fichier main.c : contient la boucle general avec toutes les fcts du minishell   //
//                                                                                 //
// Auteur : Agnel Adrien                                                          //
//	                                                                               //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : minishell.h                                                    //
//                                                                                 //
/***********************************************************************************/

#include "minishell.h"
#include "parser.h"
#include "search.h"
#include "exec.h"
#include "outils.h"


/*
 Fonction main
 Paramètre : Aucun
 Role : boucle general du programme
 Retourne: Aucun
 */
int main(int argc, const char * argv[]) {

    /* declaration de la structure pour stocker les futurs commandes tape par l utilisateur */
    command_t commands [MAX_CMDS];
    
    /* variable pour recuperer le stdin */
    char str [MAX_CMDS];
    
    /* variable pour recuperer la variable env HOME pour l afficher a chaque debut de nouvelle commande */
    char dir [MAX_REP];
    
    chdir(getenv("HOME"));
    strcpy(dir, getenv("HOME"));
    
    /* variables permettant d acceder aux différentes structures du tableau de structures */
    unsigned int idx_cmd = 0;
    
    /* Nettoyer la console avant de lancer le programme */
    cmd_clear();
    
    printf ("Pour quitter commande : quit \n");
	
    /* Boucle principal */
	while (1) {
		
        /* Nettoyer la console avant de lancer le programme */
		printf ("%s:$ ",dir);
		
        /*récupération de la commande via l'entrée stdin */
		fgets(str,MAX_CMDS,stdin);
        
        /* Completer la chaine par un caractere de fin de ligne */
		str[strlen(str)-1] = '\0';
        
        /* Permet d arreter la boucle */
		if (strcmp("quit",str) == 0) break;
		
        /* Parser la ligne du stdin */
		if (parsing(commands, str, &idx_cmd) != 0) {
			resetTab(commands, idx_cmd);
            idx_cmd = 0;
			printf("Erreur parsing.\n");
			continue;
		}
	
        /* Chercher les PATH des commandes */
		if (all_search_cmd(commands, idx_cmd) != 0) {
			resetTab(commands, idx_cmd);
            idx_cmd = 0;
			continue;
		}
	
        /* Execution de la lignes cmds */
		exec_line(commands,dir);

        /* reset de tous les elements pour refaire un tour de boucle */
		resetTab(commands, idx_cmd);
		idx_cmd = 0;
	}
	
	return EXIT_SUCCESS;
}
