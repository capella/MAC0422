#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#define PATH_SIZE 1000
#define CD_ERROR "Não foi possível mudar de diretório!\n"
#define CHMOD_ERROR "Não foi possível mudar as permisões do arquivo `%s`!\n"

void process (char *str);

/* Recebe a string str e devolve um vetor de strings divide e o numero
   (argc) de elementos nesse veotr */
char **divide (char *argv, int *argc);

int main(int argc, char const *argv[]) {
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
            process (line_read);
        }
        free(line_read);
    }
    return 0;
}

void process (char *str) {
    char **args;
    int argc;
    unsigned int tmp;

    /* divide o texto*/
    args = divide (str, &argc);

    if (strcmp(args[0], "exit") == 0) {
        exit (0);
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
            execv (args[0], args);
            printf("Não encontramos o comando!\n");
            exit(0);
        } else {
            wait(NULL);
        }
    }
}

char **divide (char *str, int *argc) {
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
