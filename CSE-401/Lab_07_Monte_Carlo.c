#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int circle, square;
double ans; 

void *runner(void *param); 
double generateRandomNumber(); 

int main(int argc, char *argv[]){
  pthread_t tid;
  pthread_attr_t attr;

  if (argc != 2) {
	  fprintf(stderr,"usage: a.out <integer value>\n");
  	return -1;
  }

  if (atoi(argv[1]) < 0) {
	  fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	  return -1;
  }

  pthread_attr_init(&attr);
  pthread_create(&tid,&attr,runner,argv[1]);
  pthread_join(tid,NULL);

  printf("ans = %lf\n",ans);
}

double generateRandomNumber() {
    int randNum = rand();  
    double result = ((double)randNum / RAND_MAX) * 2 - 1;
    return result;
}

void *runner(void *param) {
	int i, upper = atoi(param);
	double x, y, dis;

	for(int i=1; i<=upper; i++){
		x = generateRandomNumber();
		y = generateRandomNumber();
		dis = sqrt((x*x)+(y*y));
		
		if(dis<1){		
			circle++;
			square++;
		}else{
			square++;
		}
	}
	
	printf("Circle - %d\tSquare - %d\n", circle, square);
	ans = 4*(double)circle/(double)square;
	pthread_exit(0);
}
