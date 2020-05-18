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



int sel_sort(int *, int);

int main() {

  int N, *array, i;

  scanf("%d", &N);
  array = func_mallocation_(N);
  for(i=0; i<N; i++) scanf("%d", &(array[i]));
  printf("INIT:::::::"); print_array_(array, N);
  i=sel_sort(array, N);
  printf("DONE:::::::"); print_array_(array, N);
  printf("%d\n", i);

  free(array);

  return 0;
}

int sel_sort(int *array, int N) {

  int init_pos, min_pos, cur_pos, comp_count;

  comp_count = 0;
  for(init_pos=0; init_pos < N-1; init_pos++) {
    min_pos = init_pos;
    for(cur_pos=init_pos+1; cur_pos<N; cur_pos++) {
        comp_count++;
        if(comp_(array, cur_pos, min_pos)) min_pos = cur_pos;
    }
    if(min_pos != init_pos) {
        func_swap_(array, init_pos, min_pos);
        print_array_(array, N);
    }
  }

  return comp_count;
}
