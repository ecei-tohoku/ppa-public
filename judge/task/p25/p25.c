#include <stdio.h>
#include <stdlib.h>

int mergesort(int *data, int *a, int *b, int *c, int p, int q);
int merge(int *a, int *b, int *c, int end_a, int end_b);

int main() {
  
  int i, N, cnt;
  int *data, *a, *b, *c;
  
  scanf("%d",&N);
  
  data = (int*)malloc(N * sizeof(int));
  if (data==NULL) {
    printf("Can not allocate memory. 'data' is NULL.\n");
    return 1;
  }
  a = (int*)malloc(N * sizeof(int));
  if (a==NULL) {
    printf("Can not allocate memory. 'a' is NULL.\n");
    return 1;
  }
  b = (int*)malloc(N * sizeof(int));
  if (data==NULL) {
    printf("Can not allocate memory. 'b' is NULL.\n");
    return 1;
  }
  c = (int*)malloc(N * sizeof(int));
  if (data==NULL) {
    printf("Can not allocate memory. 'c' is NULL.\n");
    return 1;
  }
  
  for (i=0; i<N; i++) {
    scanf("%d",&data[i]);
  }
  
  cnt = mergesort(data,a,b,c,0,N-1);
  
  for (i=0; i<N-1; i++) {
    printf("%d ", data[i]);
  }
  printf("%d\n",data[N-1]);
  printf("%d\n",cnt);
  
  free(data);
  free(a);
  free(b);
  free(c);
  
  return 0;
}

int mergesort(int *data, int *a, int *b, int *c, int p, int q) {
  int i, med, cnt=0;
  if (p < q) {
    med = (p + q)/2;
    cnt += mergesort(data, a, b ,c, p, med);
    cnt += mergesort(data, a, b, c, med + 1, q);
    for (i = p; i <= med; i++) {
      a[i - p] = data[i];
    }
    for (i = med + 1; i <= q; i++) {
      b[i - med - 1] = data[i];
    }
    cnt += merge(a, b, c, med - p + 1, q - med);
    for (i = p; i <= q; i++) {
      data[i] = c[i - p];
    }
  }
  return cnt;
}

int merge(int *a, int *b, int *c, int end_a, int end_b) {
  int i = 0, j = 0, k = 0, cnt = 0;

  while ((i < end_a) && (j < end_b)) {
    cnt++;
    if (a[i] < b[j]){
      c[k] = a[i];
      k++;
      i++;
    }
    else {
      c[k] = b[j];
      k++;
      j++;
    }
  }
  if (i >= end_a) {
    while (j < end_b) {
      c[k] = b[j];
      k++;
      j++;
    }
  }
  else {
    while (i < end_a) {
      c[k] = a[i];
      k++;
      i++;
    }
  }
  return cnt;
}


