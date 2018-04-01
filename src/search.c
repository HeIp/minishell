/***********************************************************************************/
//                                                                                 //
// Fichier search.c : fonction de recherche des cmd                                //
//                                                                                 //
// Auteurs : Agnel Adrien                                                          //
//	       : Gabriel Fauquembergue                                                 //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : search.h                                                       //
//                                                                                 //
/***********************************************************************************/

#include "search.h"

/*
 Fonction search_cmd
 Paramètre command_t *cmd : structure commande
 Role : Recherche si la commande est builtin ou non et cherche le path si non builtin et l'ajoute dans la structure
 Retourne 0 si ok
 */
int search_cmd (command_t * cmd) {
	char * syspath = getenv("PATH");
	char * path, * path_sav;
	if (syspath == NULL) {
		fprintf (stderr,"Variable PATH == NULL \n");
		return 1;
	}
	
	if (cmd->argv[0] == NULL) {
		return 2;
	}
	
    /* Si la cmd est builting ecrire son flag reference dans sa structure".
     cd, export, exit, ...
     */
    
	if (strcmp("cd",cmd->argv[0]) == 0) {
		cmd->builting = 1;
		return 0;
	}
	
	if (strcmp ("clear", cmd->argv[0]) == 0){
		cmd->builting = 2;
		return 0;
	}
	
	if (strcmp ("export", cmd->argv[0])==0){
		cmd->builting = 3;
		return 0;
	}
    
    if (strcmp ("unset", cmd->argv[0])==0){
        cmd->builting = 4;
        return 0;
    }
    
    if (strcmp ("exit", cmd->argv[0])==0){
        cmd->builting = 5;
        return 0;
    }
    
    if (strcmp ("echo", cmd->argv[0])==0){
        if (cmd->argv[1] != NULL){
            if (strcmp ("$$", cmd->argv[1])==0){
                cmd->builting = 6;
                return 0;
            }
        }
    }
	
	if (*(cmd->argv[0]) == '/'){
        // global path
		strncpy(cmd->path,cmd->argv[0],MAX_PATH_SIZE - 1);
		if (access(cmd->path, X_OK) != 0) cmd->path[0] ='\0';
	}
	else {
		syspath = strdup(syspath);
		path_sav = syspath;
		for((path = strtok_r(syspath,":",&path_sav)); path; path = strtok_r(NULL,":",&path_sav)) {
			strncpy(cmd->path,path,MAX_PATH_SIZE - strlen(cmd->argv[0]) - 2);
			strcat(cmd->path,"/");
			strcat(cmd->path, cmd->argv[0]);
			if (access(cmd->path, X_OK) == 0) break;
			cmd->path[0]='\0';
		}
	}
	free(syspath);
	if (cmd->path[0]=='\0'){
        fprintf(stderr,"%s : commande introuvable. \n",cmd->argv[0]);
		return 3;
	}
	return 0;
}

/*
 Fonction all_search_cmd
 Paramètre command_t commands [MAX_CMDS] : tableau des commandes
 Paramètre unsigned int *idx_cmd : indice pour se deplacer dans le tableau des commandes
 Role : Recherche des commandes dans le PATH.
 Retourne 0 si ok
 */
int all_search_cmd (command_t commands [MAX_CMDS], int idx_cmd){
	int flag = 0;
	for (int i = 0; i < idx_cmd; ++i){
		flag = search_cmd(&commands[i]);
		if (flag != 0) break;
	}
	return flag;
}
