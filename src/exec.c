/***********************************************************************************/
//                                                                                 //
// Fichier exec.c : fonction d execution des cmds                                  //
//                                                                                 //
// Auteur : Agnel Adrien                                                          //
//	                                                                               //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : exec.h                                                         //
//                                                                                 //
/***********************************************************************************/

#include "exec.h"

/*
 Fonction exec_line
 Paramètre command_t *line : ligne contenant les commandes
 Paramètre char repertoire[MAX_REP] : repertoire cible pour commande cd
 Role : Permet  d executer une ligne
 Retourne: 0 si tout est ok
 */
int exec_line(command_t *line, char repertoire[MAX_REP])
{
    command_t * cmd = line;
    
    while(cmd != NULL){
        exec_cmd(cmd, repertoire);
        
        if(cmd->next_true != NULL)
        {
            if(WEXITSTATUS(cmd->status)!=0)
                cmd=cmd->next_true;
            else
                cmd = NULL;
            continue;
        }
        
        if(cmd->next_false != NULL)
        {
            if(WEXITSTATUS(cmd->status)==0)
                cmd = cmd->next_false;
            else
                cmd = NULL;
            continue;
        }
        cmd = cmd->next;
    }
    return 0;
}

/*
 Fonction exec_cmd
 Paramètre command_t *line : ligne contenant les commandes
 Paramètre char repertoire[MAX_REP] : repertoire cible pour commande cd
 Role : Permet  d executer une commande builtin ou non
 Retourne: 0 si tout est ok
 */
int exec_cmd(command_t * cmd, char repertoire[MAX_REP] ) {
	pid_t pid;
	
	/* Gérer ici les commandes "built-in". */
	if (cmd->builting == 1){
		return cmd_cd(cmd,repertoire);
	}
	
	if (cmd->builting == 2) {
		return cmd_clear();
	}
	
	if (cmd->builting == 3) {
		return cmd_export(cmd);
	}
    
    if (cmd->builting == 4) {
        return cmd_unset(cmd);
    }
    
    if (cmd->builting == 5) {
        return cmd_exit(cmd);
    }
    
    if (cmd->builting == 6) {
        return cmd_echo_$$(cmd);
    }
    
	if ((pid=fork())) {
       if(cmd->stdin != STDIN_FILENO) close(cmd->stdin);
        if(cmd->stdout != STDOUT_FILENO && cmd->stdout != STDERR_FILENO){
           close(cmd->stdout);
        }
        if(cmd->stderr != STDERR_FILENO && cmd->stderr != STDOUT_FILENO) {
         close(cmd->stderr);
        }
        
		if (!cmd->background) {
			waitpid(pid, &cmd->status, 0);
		} else {
            if (cmd->builting != 0)
			fprintf(stderr, "[%d]\n", pid);
		}
		return WEXITSTATUS(cmd->status);
	} else {
		dup2(cmd->stdin, STDIN_FILENO);
		dup2(cmd->stdout, STDOUT_FILENO);
		dup2(cmd->stderr, STDERR_FILENO);
		
		execv(cmd->path, cmd->argv);
		return -1;
	}
}
