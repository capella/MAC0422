#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {
	int N = atoi (argv[1]);
	int flag = 0, numero;
	char c;
	while (scanf ("%c", &c) != EOF) {
		if (c == '\n') flag++;
		if (flag == N) break;
	}
	scanf ("%d", &numero);
	printf("%d\n", numero);
	return 0;	
}