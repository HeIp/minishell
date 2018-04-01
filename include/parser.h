/***********************************************************************************/
//                                                                                 //
// Fichier parser.h : contient les librairies et les signatures de parser.c        //
//                                                                                 //
// Auteur : Agnel Adrien                                                          //
//	                                                                               //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : minishell.h                                                    //
//                                                                                 //
/***********************************************************************************/

#ifndef PARSER_h
#define PARSER_h

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <glob.h>

#include "minishell.h"
#include "outils.h"


/* signatures des fonctions */
int parsing(command_t commands [MAX_CMDS], char * str, unsigned int* idx_cmd);

#endif
