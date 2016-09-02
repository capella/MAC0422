#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "load-process/load-process.h"
#include "first-come-first-served/first-come-first-served.h"

void (*p_init)();
void (*p_run)(int);
void (*p_exec)(char *, int, void *(*)(void *), void *);
void nada (int pid, float durattion);

int main(int argc, char const *argv[]) {

	p_init = &fcfs_init;
	p_run = &fcfs_run;
	p_exec = &fcfs_exec;

	load_file((void *)argv[1]);
	p_exec("load_process", -1, load, (void *)p_exec);

	p_init();

	return 0;
}
