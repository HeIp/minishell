/***********************************************************************************/
//                                                                                 //
// Fichier structures.h : contient les librairies et les signatures de :           //
// structures.c                                                                    //
//                                                                                 //
// Auteur  : Agnel Adrien                                                          //
//	                                                                               //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : minishell.h                                                    //
//                                                                                 //
/***********************************************************************************/

#ifndef EXEC_h
#define EXEC_h

#include <sys/types.h>
#include <sys/wait.h>

#include "minishell.h"
#include "builtin.h"

/* signatures des fonctions */
int exec_cmd(command_t * cmd, char repertoire[MAX_REP]);

int exec_line(command_t *line, char dir [MAX_REP]);

#endif
