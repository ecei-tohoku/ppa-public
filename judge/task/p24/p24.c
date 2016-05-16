#include <stdio.h>

float resistance(int N, float rx, float ry, float rz);

int main() {
  
  int N;
  float rx, ry, rz;
  
  scanf("%d",&N);
  scanf("%f",&rx);
  scanf("%f",&ry);
  scanf("%f",&rz);
  
  printf("%.3f\n",resistance(N,rx,ry,rz));
  
  return 0;
}

float resistance(int N, float rx, float ry, float rz) {
  
  if (N>1)
    return rx+rz+1/(1/ry+1/resistance(N-1,rx,ry,rz));
  else
    return rx+ry+rz;
}
