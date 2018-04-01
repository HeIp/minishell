/***********************************************************************************/
//                                                                                 //
// Fichier parser.c : Contient le parser : redirections , arguments                //
//                                                                                 //
// Auteurs : Agnel Adrien                                                          //
//	       : Gabriel Fauquembergue                                                 //
//                                                                                 //
//    Date : 28/05/2017                                                            //
//                                                                                 //
//    Dépendances : parser.h                                                       //
//                                                                                 //
/***********************************************************************************/

#include "parser.h"

/*
 Fonction parsing
 Paramètre command_t commands [MAX_CMDS] : tableau des commandes
 Paramètre char * entree : parser la ligne tape par l'utilisateur sur stind
 Paramètre unsigned int *idx_cmd : indice pour se deplacer dans le tableau des commandes
 Role : parser la ligne arguments de utilisateurs dans le tableau de commande.
 Retourne 0 si ok
 */
int parsing(command_t commands [MAX_CMDS], char * entree, unsigned int *idx_cmd){
    
    char* saveptr;
    char* token;
    char* str = strdup(entree);
    
    unsigned int idx_arg=0;
    
    /*initialisation d'une structure du tableau de structures*/
    initStruct(&commands[*idx_cmd]);
    
    /* lecture du tableau argv d une structure */
    while ((token = strtok_r(str, " ", &saveptr))) {
        str = NULL;
        if (token == NULL) break;
        
        if (strcmp(token, "&") && strcmp(token, ";") && strcmp(token, "&&") && strcmp(token, "||") && strcmp(token, "|")) {
            
            /* Gestions des joker */
            if (strstr(token,"*") != NULL) {
                glob_t g;
                if (glob(token,0,NULL,&g)==0){
                    for (int i=0;i<g.gl_pathc;++i)
                        commands[*idx_cmd].argv[idx_arg++]=strdup(g.gl_pathv[i]);
                }
                globfree(&g);
                continue;
            }
            
            /* Redirection simple */
            if (strcmp(token,">") == 0){
                token = strtok_r(str, " ", &saveptr);
                int fd = open(token,O_CREAT | O_WRONLY, S_IWRITE | S_IREAD);
                if (fd == -1) {
                    fprintf(stderr, "Imposible de créer le fichier : %s \n",token);
                    return 1;
                }
                commands[*idx_cmd].stdout=fd;
                continue;
            }
            
            /* append a la suite d'un fichier */
            if (strcmp(token,">>") == 0){
                token = strtok_r(str, " ",&saveptr);
                int fd = open(token , O_CREAT | O_WRONLY | O_APPEND, S_IWRITE | S_IREAD);
                if (fd == -1){
                    fprintf (stderr, "Impossible d'ajouter, ou de créer le fichier : %s \n",token);
                    return 2;
                }
                commands[*idx_cmd].stdout=fd;
                continue;
            }
            
            /* redirection flux d erreur sur fichier */
            if (strcmp(token,"2>") == 0){
                token = strtok_r(str, " ", &saveptr);
                int fd = open(token, O_CREAT | O_WRONLY, S_IWRITE | S_IREAD);
                if (fd == -1) {
                    fprintf(stderr, "Imposible de créer le fichier d'erreur: %s \n",token);
                    return 3;
                }
                commands[*idx_cmd].stderr=fd;
                continue;
            }
            
            /* redirection flux d erreur sur fichier avec append */
            if (strcmp(token,"2>>") == 0){
                token = strtok_r(str, " ",&saveptr);
                int fd = open(token , O_CREAT | O_WRONLY | O_APPEND, S_IWRITE | S_IREAD);
                if (fd == -1){
                    fprintf (stderr, "Impossible d'ajouter, ou de créer le fichier d'erreur : %s \n",token);
                    return 4;
                }
                commands[*idx_cmd].stderr=fd;
                continue;
            }
            
            /* lecture d un fichier */
            if (strcmp(token,"<") == 0){
                token = strtok_r(str, " ", &saveptr);
                int fd = open(token, O_RDONLY, S_IREAD);
                if (fd == -1) {
                    fprintf(stderr, "Imposible de lire le fichier : %s \n",token);
                    return 5;
                }
                commands[*idx_cmd].stdin=fd;
                continue;
            }
            
            /* redirection avec macro */
            if (strcmp(token, "<<") == 0) {
                
                token = strtok_r(str, " ", &saveptr);
                
                char filename[] = "/tmp/mytemp.XXXXX";
                int fd = mkstemp(filename);
                char line[1024];
                line[0] = 0;
                
                while (strncmp(line,token, strlen(token)) != 0 ){
                    fgets(line, 1024, stdin) ;
                    if(strncmp(line,token,strlen(token)) != 0)
                        write(fd,line,strlen(line));
                }
                
                fsync(fd);
                lseek(fd,0,SEEK_SET);
                
                commands[*idx_cmd].stdin=fd;
                continue;
            }
            
            /* transformer les variables */
            if (token[0] == '$' && token[1] != '$'){
                for (int i = 0; i < strlen(token); i++)
                    token[i] = token[i+1];
                commands[*idx_cmd].argv[idx_arg++] = getenv(token);
                continue;
            }
            
            if (strcmp(token,"2>&1") == 0) {
                commands[*idx_cmd].stderr= dup(commands[*idx_cmd].stdout);
                continue;
            }
            commands[*idx_cmd].argv[idx_arg++]=token;
            
        }
        else {
            
            commands[*idx_cmd].argv[idx_arg++] = NULL;
            idx_arg = 0;
            
            if (strcmp(token,"|") == 0){
                if (*idx_cmd == MAX_CMDS -1){
                    fprintf(stderr,"Trop de commande, impossible de faire la redirection avec le pipe. \n");
                    return 6;
                }
                int pipefd[2];
                pipe(pipefd);
                
                commands[*idx_cmd].stdout = dup(pipefd[1]); // sortie devient entrée du pipe.
                
                commands[*idx_cmd].background = 1;
                
                // next prend prochaine commande
                // cmd stind
                
                int i = *idx_cmd + 1 ;
                command_t *cmd = &commands[i];
                commands[*idx_cmd].next = cmd ;
                ++ *idx_cmd;
                initStruct(&commands[*idx_cmd]);
                
                cmd->stdin = dup(pipefd[0]); // entrée sur sortie de commande 2
                
                close(pipefd[0]);
                close(pipefd[1]);
                
                continue;
                
            }
            
            /* lancer une execution en background */
            if (strcmp(token,"&") == 0) {
                commands[*idx_cmd].background=1;
                continue;
            }
            
            if (strcmp(token,";") == 0) {
                int i = *idx_cmd + 1 ;
                command_t *cmd = &commands[i];
                commands[*idx_cmd].next = cmd ;
                ++ *idx_cmd;
                initStruct(&commands[*idx_cmd]);
                continue;
            }
            
            if (strcmp(token,"&&") == 0) {
                int i = *idx_cmd + 1 ;
                command_t *cmd = &commands[i];
                commands[*idx_cmd].next_false=cmd;
                ++ *idx_cmd;
                initStruct(&commands[*idx_cmd]);
                continue;
            }
            
            if (strcmp(token,"||") == 0) {
                int i = *idx_cmd + 1 ;
                command_t *cmd = &commands[i];
                commands[*idx_cmd].next_true=cmd;
                ++ *idx_cmd;
                initStruct(&commands[*idx_cmd]);
                continue;
            }
        }
        
        /* condition trop arguments */
        if (idx_arg == MAX_ARGS) {
            fprintf(stderr, "Il y a trop d'arguements. \n");
            return 7;
        }
        
        /* condition trop de commandes */
        if (*idx_cmd == MAX_CMDS) {
            fprintf(stderr, "Il y a trop de commandes. \n");
            return 7;
        }
    }
    commands[*idx_cmd].next= NULL;
    commands[*idx_cmd].next_false= NULL;
    commands[*idx_cmd].next_true= NULL;
    ++ *idx_cmd;
    return 0;
}
