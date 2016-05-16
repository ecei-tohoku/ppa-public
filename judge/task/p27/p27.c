#include <stdio.h>

int tmax(int N);
int tmin(int N);

int main() {
  
  int N;
  
  scanf("%d",&N);
  
  printf("%d %d\n",tmax(N),tmin(N));
  
  return 0;
}


int tmax(int N) {
  
  if (N>=2) {
    return 2*tmax(N/2)+N-1;
  }
  else {
    return 0;
  }
}

int tmin(int N) {
  
  if (N>=2) {
    return 2*tmin(N/2)+N/2;
  }
  else {
    return 0;
  }
}
