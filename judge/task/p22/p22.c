#include <stdio.h>
#include <stdlib.h>

int selectionsort(int *data, int N);

int main() {
  
  int i, N, cnt;
  int *data;
  
  scanf("%d",&N);
  
  data = (int*)malloc(N * sizeof(int));
  if (data==NULL) {
    printf("Can not allocate memory. 'data' is NULL.\n");
    return 1;
  }
  
  for (i=0; i<N; i++) {
    scanf("%d",&data[i]);
  }
  
  cnt = selectionsort(data,N);
  
  for (i=0; i<N-1; i++) {
    printf("%d ", data[i]);
  }
  printf("%d\n",data[N-1]);
  printf("%d\n",cnt);
  
  free(data);
  
  return 0;
}

int selectionsort(int *data, int N) {
  int i, j, tmp, min, cnt=0;
  for (i = 0; i < N - 1; i++) {
    min = i;
    for (j = i + 1; j < N; j++) {
      cnt++;
      if (data[min] > data[j]) {
	min = j;
      }
    }
    tmp = data[i];
    data[i] = data[min];
    data[min] = tmp;
  }
  return cnt;
}
