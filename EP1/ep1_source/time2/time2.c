/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#include "time2.h"
static int set = 0;
static struct timeval begin;

double time2 () {
	double elapsed;
	struct timeval end;
	if (set == 0) {
		set = 1;
		gettimeofday(&begin, 0);
		return 0.0;
	} else {
		gettimeofday(&end, 0);
		elapsed = end.tv_sec - begin.tv_sec;
		elapsed += (end.tv_usec - begin.tv_usec) / 1000000.0;
		return elapsed;
	}
}
