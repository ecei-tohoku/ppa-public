#include <stdio.h>
#include <stdlib.h>

void histogram(int *data, int N);

int main() {

  int i, N;
  float *data_f;
  int *data;
  
  scanf("%d",&N);
  
  data_f = (float*)malloc(N * sizeof(float));
  if (data_f==NULL) {
    printf("Can not allocate memory. 'data_f' is NULL.\n");
    return 1;
  }
  data = (int*)malloc(N * sizeof(int));
  if (data==NULL) {
    printf("Can not allocate memory. 'data' is NULL.\n");
    return 1;
  }
  
  for (i=0; i<N; i++) {
    scanf("%f",&data_f[i]);
  }
  for (i=0; i<N; i++) {
    data[i] = (int)(data_f[i]+0.5);
  }

  histogram(data,N);
  
  free(data_f);
  free(data);

  return 0;
}

void histogram(int *data, int N) {
  int MIN, MAX, i, j;
  
  MIN = data[0];
  MAX = data[0];
  for (i=1; i<N; i++) {
    if (data[i]<MIN) {
      MIN = data[i];
    }
    else if (data[i]>MAX) {
      MAX = data[i];
    }
  }
  
  for (i=MIN; i<=MAX; i++) {
    printf("%2d ",i);
    for (j=0; j<N; j++) {
      if (data[j]==i) {
	printf("*");
      }
    }
    printf("\n");
  }
}
