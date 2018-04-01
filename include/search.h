/***********************************************************************************/
//                                                                                 //
// Fichier search.h : contient les librairies et les signatures de :               //
// search.c                                                                        //
//                                                                                 //
// Auteur : Agnel Adrien                                                          //
//	                                                                               //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : minishell.h                                                    //
//                                                                                 //
/***********************************************************************************/

#ifndef SEARCH_h
#define SEARCH_h

#include "minishell.h"

/* signatures des fonctions */
int search_cmd (command_t * cmd);
int all_search_cmd (command_t commands [MAX_CMDS], int idx_cmd);

#endif
