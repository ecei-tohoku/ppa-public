#include <stdio.h>
#include <stdlib.h>

int* func_copy_val_(int* const array, const int pos_a, const int pos_b) {
  array[pos_b] = array[pos_a];
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



int ins_sort(int *, int);

int main() {

  int N, *array, i;

  scanf("%d", &N);
  array = func_mallocation_(N+1);
  for(i=0; i<N; i++) scanf("%d", &(array[i]));
  printf("INIT:::::::"); print_array_(array, N);
  i=ins_sort(array, N);
  printf("DONE:::::::"); print_array_(array, N);
  printf("%d\n", i);

  free(array);

  return 0;
}

int ins_sort(int *array, int N) {

  int cur_pos, end_pos, comp_count;

  comp_count = 0;
  for(end_pos=1; end_pos<N; end_pos++) {
    for(cur_pos=end_pos-1; cur_pos>=0; cur_pos--) {
        comp_count++;
        if(comp_(array, end_pos, cur_pos) != 1) break;
    }
    cur_pos += 1;
    if(end_pos!=cur_pos) {
        printf("INST(%2d,%2d)", end_pos, cur_pos);
        for(; cur_pos<end_pos; cur_pos++) {
            func_copy_val_(array, cur_pos, N);
            func_copy_val_(array, end_pos, cur_pos);
            func_copy_val_(array, N, end_pos);
        }
        print_array_(array, N);
    }
  }

  return comp_count;
}
