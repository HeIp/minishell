/***********************************************************************************/
//                                                                                 //
// Fichier builtin.h : contient les librairies et les signatures de builtin.c      //
//                                                                                 //
// Auteur : Agnel Adrien                                                          //
//	                                                                               //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : minishell.h                                                    //
//                                                                                 //
/***********************************************************************************/

#ifndef BUILTIN_h
#define BUILTIN_h

#include "minishell.h"

int cmd_exit();
int cmd_clear ();
int cmd_cd (command_t *cmd,char repertoire [MAX_REP]);
int cmd_export (command_t *cmd);
int cmd_unset (command_t *cmd);

int cmd_echo_$$(command_t *cmd);

#endif
