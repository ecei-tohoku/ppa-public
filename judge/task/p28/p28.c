#include <stdio.h>
#include <stdlib.h>

void matrixsort(int **data, int N, int M, int ind, int rc, int order);

int main() {
  
  int i, j, N, M, ind, rc, order;
  int **data;
  
  scanf("%d %d %d", &ind, &rc, &order);
  scanf("%d %d", &N, &M);
  
  data = (int **)malloc(N * sizeof(int*));
  if (data==NULL) {
    printf("Can not allocate memory. 'data' is NULL.\n");
    return 1;
  }
  for (i=0; i<N; i++) {
    data[i] = (int *)malloc(M * sizeof(int));
  }
  
  for (i=0; i<M; i++) {
    for (j=0; j<N; j++) {
      scanf("%d",&data[i][j]);
    }
  }

  matrixsort(data,N,M,(ind-1),rc,order);
  
  for (i=0; i<N; i++) {
    for (j=0; j<M-1; j++) {
      printf("%d ",data[i][j]);
    }
    printf("%d\n",data[i][M-1]);
  }
  
  for (i=0; i<N; i++) {
    free(data[i]);
  }
  free(data);
  
  return 0;
}

void matrixsort(int **data, int N, int M, int ind, int rc, int order) {

  int i, j, k, tmp;
  
  if (rc==1) {
    for (i=0; i<M-1; i++) {
      for (j=i+1; j<M; j++) {
	if (order==1) {
	  if (data[ind][i]>data[ind][j]) {
	    for (k=0; k<N; k++) {
	      tmp = data[k][i];
	      data[k][i] = data[k][j];
	      data[k][j] = tmp;
	    }
	  }
	}
	else {
	  if (data[ind][i]<data[ind][j]) {
	    for (k=0; k<N; k++) {
	      tmp = data[k][i];
	      data[k][i] = data[k][j];
	      data[k][j] = tmp;
	    }
	  }
	}	  
      }
    }
  }
  else {
    for (i=0; i<N-1; i++) {
      for (j=i+1; j<N; j++) {
	if (order==1) {
	  if (data[i][ind]>data[j][ind]) {
	    for (k=0; k<M; k++) {
	      tmp = data[i][k];
	      data[i][k] = data[j][k];
	      data[j][k] = tmp;
	    }
	  }
	}
	else {
	  if (data[i][ind]<data[j][ind]) {
	    for (k=0; k<M; k++) {
	      tmp = data[i][k];
	      data[i][k] = data[j][k];
	      data[j][k] = tmp;
	    }
	  }
	}	  
      }
    }
  }
}
