/***********************************************************************************/
//                                                                                 //
// Fichier builtin.c : fonction d execution des cmds builtin                       //
//                                                                                 //
// Auteur : Agnel Adrien                                                          //
//	                                                                               //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : builtin.h                                                      //
//                                                                                 //
/***********************************************************************************/

#include "builtin.h"

/*
 Fonction cmd_exit
 Paramètre : Aucun
 Role : Permet d arreter la console
 Retourne 0 si tout est ok
 */
int cmd_exit () {
    exit(EXIT_SUCCESS);
    return 0;
}

/*
 Fonction cmd_clear
 Paramètre : Aucun
 Role : Permet de nettoyer l ecran de la console
 Retourne 0 si tout est ok
 */
int cmd_clear () {
	printf("\033[2J\033[1;1H");
	return 0;
}

/*
 Fonction cmd_cd
 Paramètre command_t *cmd : structure avec les commandes
 Paramètre char repertoire [MAX_REP]: Contient le repertoire cible
 Role : Permet de se deplacer
 Retourne 0 si tout est ok
 */
int cmd_cd(command_t *cmd, char repertoire [MAX_REP]){
	if (cmd->argv[1] == NULL){
		chdir (getenv("HOME"));
		char * new = getenv("HOME");
		strcpy(repertoire, new);
		
	} else {
		if (chdir (cmd->argv[1]) == -1){
			fprintf(stderr, "Aucun dossier nomme : %s \n", cmd->argv[1]);
			return 1;
		}
		if (*(cmd->argv[1]) == '/')
			strcpy(repertoire, cmd->argv[1]);
		
		else{
			char* saveptr;
			char* token;
			char* str = strdup(cmd->argv[1]);
			while ((token = strtok_r(str, "/", &saveptr))){
				str = NULL;
				if (strcmp(token, "..") == 0){
					int i = (int) (strlen(repertoire));
					while (repertoire[i] != '/' && i != 1){
						repertoire[i] = '\0';
						--i;
					}
					repertoire [i] = '\0';
					continue;
				}
				if (repertoire [strlen(repertoire)-1] != '/')
					strcat(repertoire, "/");
				strcat(repertoire,token);
			}

		}
	}
	return 0;
}

/*
 Fonction cmd_export
 Paramètre command_t *cmd : structure avec les commandes
 Role : Permet d enregister une variable dans le tableau env.
 Retourne 0 si tout est ok
 */
int cmd_export (command_t *cmd) {
	char* saveptr;
	char* str = strdup(cmd->argv[1]);
    char *error = "export : erreur de syntaxe \n";
	
	if (str == NULL) {
        write(cmd->stderr,error,strlen(error));
		return 0;
	}
	
	char * nomVar = strtok_r(str, "=", &saveptr);
	str = NULL;
	if (nomVar == NULL) {
        write(cmd->stderr,error,strlen(error));
		return 0;
	}
	char * valeurVar = strtok_r(str, "=", &saveptr);
	if (valeurVar == NULL) {
        write(cmd->stderr,error,strlen(error));
		return 0;
	}
	setenv(nomVar,valeurVar,1);
	return 0;
}

/*
 Fonction cmd_unset
 Paramètre command_t *cmd : structure avec les commandes
 Role : Permet de supprimer une variable dans le tableau env.
 Retourne 0 si tout est ok
 */
int cmd_unset (command_t *cmd){
    char *error = "unset : erreur de syntaxe \n";
    if(cmd->argv[1] == NULL){
        write(cmd->stderr,error,strlen(error));
        return 0;
    }
    unsetenv(cmd->argv[1]);
    return 0;
}

/*
 Fonction cmd_echo_$$
 Paramètre command_t *cmd : structure avec les commandes
 Role : Afficher le PID du processus Shell en cours.
 Retourne 0 si tout est ok
 */
int cmd_echo_$$(command_t *cmd){
    printf("PID: %d\n", getpid());
    return 0;
}
