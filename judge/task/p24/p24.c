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

void print_array_range_(const int* const array, const int N, const int p, const int r) {
  int ri = 0;
  for (; ri < N; ++ri) {
    if (ri < p || r < ri) {
      printf(" **");
    } else {
      printf(" %2d", array[ri]);
    }
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



int mrg_sort(int *, int , int , int );
int merge(int *, int , int , int , int );

int main() {

  int N, *array, i;

  scanf("%d", &N);
  array = func_mallocation_(2*N);
  for(i=0; i<N; i++) scanf("%d", &(array[i]));
  printf("INIT:::::::"); print_array_range_(array, N, 0, N-1);
  i=mrg_sort(array, N, 0, N-1);
  printf("DONE:::::::"); print_array_range_(array, N, 0, N-1);
  printf("%d\n", i);

  free(array);

  return 0;
}

int mrg_sort(int* array, int N, int p, int q) {

  int comp_count, mid_pos, num_elem;

  comp_count = 0;

  if(p == q) return comp_count;
  else {
    num_elem = q - p + 1;
    mid_pos = p + (int)(num_elem/2);
    if(num_elem%2) mid_pos++;
    comp_count += mrg_sort(array, N, p, mid_pos-1);
    comp_count += mrg_sort(array, N, mid_pos, q);
    comp_count += merge(array, N, p, q, mid_pos);

    return comp_count;
  }

}

int merge(int* array, int N, int p, int q, int r) {

  int comp_count, i1, i2, iT;

  comp_count = 0; i1 = p; i2 = r; iT = N+p;
  while(i1<r && i2<=q) {
    comp_count++;
    if(comp_(array, i1, i2)) {
        func_copy_val_(array, i1, iT);
        i1++; iT++;
    }
    else {
        func_copy_val_(array, i2, iT);
        i2++; iT++;
    }
  }

  while(i1<r) {func_copy_val_(array, i1, iT); i1++; iT++;}
  while(i2<=q){func_copy_val_(array, i2, iT); i2++; iT++;}

  for(iT=p; iT<=q; iT++) func_copy_val_(array, N+iT, iT);

  printf("MERG(%2d,%2d)", p, q);
  print_array_range_(array, N, p, q);

  return comp_count;

}
