#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p2_header.h"

int sel_sort(int *, int);

int main () {
  int N, *array, i;

  scanf("%d", &N);                                  // 入力配列の要素数
  array = func_mallocation_(N);                     // 配列に動的メモリを割り当てる
  for(i=0; i<N; i++) scanf("%d", &(array[i]));      // STDINから配列要素を受け取る
  printf("INIT:::::::"); print_array_(array, N);    // 配列の初期状態をSTDOUTに出力
  i = sel_sort(array, N);                           // 配列を並べ替える
  printf("DONE:::::::"); print_array_(array, N);    // 配列の最終状態をSTDOUTに出力
  printf("%d\n", i);                                // comp_が呼んだ合計回数を出力

  free(array);                                      // 配列に割り当てられた動的メモリを解放

  return 0;
}

int sel_sort (int* array, int N) {
  int init_pos, min_pos, cur_pos, comp_count;

  comp_count = 0;                                            // comp_countは、comp_が呼び出された回数
  for(init_pos=0; init_pos<N-1; init_pos++) {                // init_posは配列の先頭から始まり、配列全体を通過
    min_pos = init_pos;                                      // この反復でこれまでに見つかった最小の要素はinit_posにある
    for(cur_pos=init_pos+1; cur_pos<N; cur_pos++) {          // cur_posは、init_posの次の要素に始まり、配列の残りの部分を通過
      comp_count++;                                          // comp_はここで一度呼び出す
      if(comp_(array, cur_pos, min_pos)) min_pos = cur_pos;  // cur_posの要素がmin_posの要素より小さい場合は、min_posを更新
    }
    if(min_pos != init_pos) {                                // min_posとinit_posが異なる場合、より小さな要素が見つかった
      func_swap_(array, init_pos, min_pos);                  // 最小の要素をinit_posに交換
      print_array_(array, N);                                // 配列の中間状態を出力
    }
    // この時点で、0からinit_posまでのすべての要素が並べ替えられる
  }

  return comp_count;                                         // comp_が呼び出された回数を返す
}
