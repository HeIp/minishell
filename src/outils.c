/***********************************************************************************/
//                                                                                 //
// Fichier outils.c : Gestions structures et descripteurs files                    //
//                                                                                 //
// Auteurs : Agnel Adrien                                                          //
//	       : Gabriel Fauquembergue                                                 //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : outils.h                                                      //
//                                                                                 //
/***********************************************************************************/

#include "outils.h"

/*
 Fonction resetTab
 Paramètre command_t commands [MAX_CMDS] : Tableau des commandes
 Paramètre int idx_cmd : nombre de commandes
 Role : Permet reset le tableau des commandes
 Retourne: Aucun
 */
void resetTab (command_t commands [MAX_CMDS],int idx_cmd) {
	for (int i = 0; i < idx_cmd; ++i) {
		command_t * supp = malloc(sizeof(supp));
		commands [i] = *supp;
	}
}

/*
 Fonction initStruct
 Paramètre command_t *cmd : structure commande
 Role : Permet d initialiser une structure
 Retourne: Aucun
 */
void initStruct (command_t *cmd){
    cmd->stdin=0;
    cmd->stdout=1;
    cmd->stderr=2;
    cmd->background=0;
    cmd->next = NULL;
    cmd->next_true = NULL;
    cmd->next_false = NULL;
}

