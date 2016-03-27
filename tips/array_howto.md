---
layout: page
title: 動的(大きさ可変)に配列を作る方法
---

```
#include <stdio.h>

double **a,*b;
int N;

main() {
  int i,j;

  scanf("%d",&N);

  a=(double **)malloc(N*sizeof(double *));
  for(i=0;i<N;i++) {
    a[i]=(double *)malloc(N*sizeof(double));
  }
  b=(double *)malloc(N*sizeof(double));

  for(i=0;i<N;i++) {
    for(j=0;j<N;j++){
      a[i][j]=i*N+j;
    }
  }
  for(i=0;i<N;i++) {
    for(j=0;j<N;j++){
      fprintf(stderr,"a[%d][%d]=%5.2f ",i,j,a[i][j]);
    }
    fprintf(stderr,"\n");
  }
}
```
