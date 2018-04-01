/***********************************************************************************/
//                                                                                 //
// Fichier main.h : contient les librairies et les signatures des fcts de main.c   //
//                                                                                 //
// Auteurs : Agnel Adrien                                                          //
//	       : Gabriel Fauquembergue                                                 //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : minishell.h                                                    //
//                                                                                 //
/***********************************************************************************/

#ifndef MINISHELL_h
#define MINISHELL_h

#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#include <readline/history.h>

/* Variables */
#define MAX_DIR 100
#define MAX_REP 5024
#define MAX_CMDS 1024
#define MAX_ARGS 128
#define MAX_PATH_SIZE 256

/* Structures pour une commande avec descripteurs , arguments , background, .. */
typedef struct command_t{
    char path[MAX_PATH_SIZE];
    char *argv[MAX_ARGS];
    int stdin;
    int stdout;
    int stderr;
    int status;
    int background;
    int builting;
    struct command_t* next; // ; , &
    struct command_t* next_true; // &&
    struct command_t* next_false; // ||
} command_t;

#endif
