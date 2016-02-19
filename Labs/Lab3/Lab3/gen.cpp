#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

 int main() {
	int i;
	int x=0;
	int y=10;
        FILE *file;
        file = fopen("test.txt", "w");
	if(file==NULL) {
	       printf("An error has occurred.\n");
	       return 1;
	}
	srandom(time(NULL));
	unsigned int random_num;
	for(i=0 ; i<1000 ; i++, x++)
	{
		/*if(x == 100)
		{
			y=y+10;
			x=0;
		}*/
		random_num = ((random()%250));
		fprintf(file, "%d\n", random_num);
	}
	fclose(file);
	return 0;
 }
