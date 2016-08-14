#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include <readline/readline.h>
#include <readline/history.h>

#define PATH_SIZE 1000

void process (char *str);
char **divide (char *str);

int main(int argc, char const *argv[]) {
    char *line_read;
    char *request;
    char *path;

    path = malloc (PATH_SIZE * sizeof(char));
    request = malloc ((4 + PATH_SIZE) * sizeof(char));
    getcwd(path, PATH_SIZE);

    do {
        sprintf (request, "(%s): ", path);
        line_read = readline (request);

        if (line_read && *line_read) 
            add_history (line_read);

        process (line_read);
        free(line_read);
    } while (1);

    return 0;
}

void process (char *str) {
    /* Procura em ep1sh/bin */
    /* Procura no diretório atual */
    char **args;

    /* divide o texto*/
    args = divide (str);

    if (fork() == 0) {
        execv (args[0], args);
        execv (args[0], args);
        execv (args[0], args);
        printf("Não foi possível executar!\n");
    } else {
        wait(NULL);
    }
}

char **divide (char *str) {
    char ** result = NULL;
    char ** result_tmp = NULL;
    int result_s = 5;
    int result_count = 0;
    char * word;

    result = malloc(sizeof(char*)*result_s);
    word = strtok (str," ");

    while (word != NULL) {
        result_count++;
        if (result_count == result_s-1) {
            result_s *= 2;
            result_tmp = realloc (result, sizeof(char*)*result_s);
            free (result);
            result = result_tmp;
        }
        result[result_count-1] = word;
        word = strtok (NULL," ");
    }
    result[result_count] = (char *)0;
    return result;
}
