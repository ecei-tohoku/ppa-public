#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int dp(char *x, int Lx, char *y, int Ly, int **ed);
int min3(int a, int b, int c);
int d(char x, char y);

int main() {

  char x[25], **dict;
  int i, j, Lx, Ly, N, *len, min_id[3];
  int **ed;

  scanf("%d",&N);

  dict = (char **)malloc(sizeof(char *)*N);
  for (i=0; i<N; i++) dict[i] = (char *)malloc(sizeof(char)*25);
  for (i=0; i<N; i++) scanf("%s",dict[i]);

  len = (int *)malloc(sizeof(int)*N);
  
  while (scanf("%s",x)!=EOF) {
    Lx = strlen(x);
    for (i=0; i<3; i++) min_id[i] = -1;
    for (i=0; i<N; i++) {
      Ly = strlen(dict[i]);

      ed = (int **)malloc(sizeof(int *)*(Lx+1));
      for (j=0; j<Lx+1; j++) ed[j] = (int *)malloc(sizeof(int)*(Ly+1));

      len[i] = dp(x,Lx,dict[i],Ly,ed);
      
      if (min_id[0]==-1||len[min_id[0]]>len[i]) {
	min_id[2] = min_id[1];
	min_id[1] = min_id[0];
	min_id[0] = i;
      }
      else if (min_id[1]==-1||len[min_id[1]]>len[i]) {
	min_id[2] = min_id[1];
	min_id[1] = i;
      }
      else if (min_id[2]==-1||len[min_id[2]]>len[i]) min_id[2] = i;
	
      for (j=0; j<Lx+1; j++) free(ed[j]);
      free(ed);
    }

    for (i=0; i<3; i++) {
      printf("rank: %d, ed = %d, string = %s\n",i+1,len[min_id[i]],dict[min_id[i]]);
    }
    //for (i=0; i<Lx+1; i++) free(ed[i]);
    //free(ed);
    
  }
  
  for (i=0; i<N; i++) free(dict[i]);
  free(dict);
  free(len);
  
  return 0;
}

int dp(char *x, int Lx, char *y, int Ly, int **ed) {
  int i, j;
  
  for (j=0; j<Lx+1; j++) ed[j][0] = j;
  for (j=0; j<Ly+1; j++) ed[0][j] = j;
  
  for (i=1; i<Lx+1; i++) {
    for (j=1; j<Ly+1; j++) {
      ed[i][j] = min3(ed[i-1][j-1]+d(x[i-1],y[j-1]),
		      ed[i-1][j]+1,
		      ed[i][j-1]+1);
    }
  }
  return ed[Lx][Ly];
}

int min3(int a, int b, int c) {
  int min;
  min = a;
  if (b<min) min = b;
  if (c<min) min = c;
  return min;
}

int d(char x, char y) {
  return (x==y) ? 0 : 1;
}
