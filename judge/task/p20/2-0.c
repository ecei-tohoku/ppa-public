#include <stdio.h>
#include <stdlib.h>

int* func_swap_(int* const array, const int pos_a,const int pos_b) {
  int tmp = array[pos_a];
  array[pos_a] = array[pos_b];
  array[pos_b] = tmp;
  printf("SWAP(%2d,%2d)", pos_a, pos_b);
  return array;
}

int comp_(int* const array, const int pos_a, const int pos_b) {
  if (array[pos_a] < array[pos_b]) return 1;
  return 0;
}

void print_array_(const int* const array,const int N) {
  int ri = 0;
  for (; ri < N; ++ri) {
    printf(" %2d", array[ri]);
  }
  printf("\n");
}

int* func_mallocation_(const int N) {
  int* data = (int*)malloc(N * sizeof(int));
  if (data == NULL) {
    printf("Can not allocate memory. 'data' is NULL.\n");
    exit(EXIT_FAILURE);
  }
  return data;
}



int reverse_array(int *, int);

int main() {

  int N, *array, i;

  scanf("%d", &N);
  array = func_mallocation_(N);
  for(i=0; i<N; i++) scanf("%d", &(array[i]));
  printf("INIT:::::::"); print_array_(array, N);
  i=reverse_array(array, N);
  printf("DONE:::::::"); print_array_(array, N);
  printf("%d\n", i);

  free(array);

  return 0;
}

int reverse_array(int *array, int N) {

  int pos_a, pos_b, comp_count;
  pos_a = 0; pos_b = N-1; comp_count = 0;

  while(pos_a < pos_b) {
    comp_count+=2;
    if(comp_(array, pos_a, pos_b) || comp_(array, pos_b, pos_a)) {
        array = func_swap_(array, pos_a, pos_b);
        print_array_(array, N);
    }

    pos_a++; pos_b--;
  }
  return comp_count;
}
