#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	int N = atoi (argv[1]);
	int *todos = malloc (N * sizeof(int));
	int i;
	int numero;
	printf("%d\n", N);
	for (i = 0; i < N; i++) {
		scanf ("%d", &todos[i]);
	}
	printf ("tempo <- c(");
	for (i = 0; i < N; i++) {
		printf ("%d", todos[i]);
		if (i < N-1) 
			printf(", ");
	}
	printf(")");
	free (todos);
	return 0;
}