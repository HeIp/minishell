/***********************************************************************************/
//                                                                                 //
// Fichier outils.h : permet de reset et init structures et fermer les             //
// descripteurs                                                                    //
//                                                                                 //
// Auteur : Agnel Adrien                                                          //
//	                                                                               //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : minishell.h                                                    //
//                                                                                 //
/***********************************************************************************/

#ifndef OUTILS_h
#define OUTILS_h

#include "minishell.h"

void closeFile (command_t commands [MAX_CMDS], int idx_cmd );
void resetTab (command_t commands [MAX_CMDS],int idx_cmd);
void initStruct (command_t * cmd);


#endif
