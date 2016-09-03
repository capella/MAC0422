#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/syscall.h>
#include <sys/wait.h>

#include <readline/readline.h>
#include <readline/history.h>

#define PATH_SIZE 1000
#define CD_ERROR "Não foi possível mudar de diretório!\n"
#define CHMOD_ERROR "Não foi possível mudar as permisões do arquivo `%s`!\n"
#define CMD_NOT_FOUND_ERROR "Não encontramos o comando!\n"

/* Recebe a string str e processa a instrução dada nela. Retorna 1
 * se tem que finalizar o programa ou 0. */
int process (char *str, char **env);

/* Recebe a string str e devolve um vetor de strings make_args e o numero
   (argc) de elementos nesse vetor. */
char **make_args (char *str, int *argc);

/* Desaloca os argumentos criados */
void clear_args (char **args);

int main (int argc, char const *argv[], char *env[]) {
    char *line_read;
    char *request;
    char *path;

    path = malloc (PATH_SIZE * sizeof(char));
    request = malloc ((4 + PATH_SIZE) * sizeof(char));

    while (1) {
        getcwd(path, PATH_SIZE);
        sprintf (request, "(%s): ", path);
        line_read = readline (request);

        if (line_read && *line_read && line_read != 0) {
            add_history (line_read);
            if (process (line_read, env)) break;
        }
        free(line_read);
        line_read = NULL;
    }
    if (line_read != NULL) free (line_read);
    clear_history ();
    free (path);
    free (request);
    return 0;
}

int process (char *str, char **env) {
    char **args;
    int argc;
    unsigned int tmp;
    int ret = 0;
    /* make_args o texto*/
    args = make_args (str, &argc);

    if (strcmp(args[0], "exit") == 0) {
        ret = 1;
    } else if (strcmp(args[0], "cd") == 0) {
        if (chdir(args[1]) != 0) {
            printf(CD_ERROR);
        }
    } else if (strcmp(args[0], "chmod") == 0) {
        sscanf(args[1], "%o", &tmp);
        if (syscall(SYS_chmod, args[2], tmp) != 0) {
            printf(CHMOD_ERROR, args[2]);
        }
    } else if (strcmp(args[0], "id") == 0) {
        printf("%d\n", geteuid());
    } else {
        if (fork() == 0) {
            execve (args[0], args, env);
            printf (CMD_NOT_FOUND_ERROR);
            ret = 1;
        } else {
            wait(NULL);
        }
    }
    clear_args (args);
    return ret;
}

char **make_args (char *str, int *argc) {
    char ** result = NULL;
    char ** result_tmp = NULL;
    int result_s = 5;
    char * word;

    *argc = 0;
    result = malloc(sizeof(char*)*result_s);
    word = strtok (str," ");

    while (word != NULL) {
        *argc += 1;
        if (*argc == result_s-1) {
            result_s *= 2;
            result_tmp = realloc (result, sizeof(char*)*result_s);
            free (result);
            result = result_tmp;
        }
        result[*argc-1] = word;
        word = strtok (NULL," ");
    }
    result[*argc] = (char *)0;
    return result;
}

void clear_args (char **args) {
    if (args == NULL) return;
    free (args);
}

