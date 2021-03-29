#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p2_header.h"

int bub_sort(int *, int);

int main () {
  int N, *array, i;

  scanf("%d", &N);                                  // 入力配列の要素数
  array = func_mallocation_(N);                     // 配列に動的メモリを割り当てる
  for(i=0; i<N; i++) scanf("%d", &(array[i]));      // STDINから配列要素を受け取る
  printf("INIT:::::::"); print_array_(array, N);    // 配列の初期状態をSTDOUTに出力
  i = bub_sort(array, N);                           // 配列を並べ替える
  printf("DONE:::::::"); print_array_(array, N);    // 配列の最終状態をSTDOUTに出力
  printf("%d\n", i);                                // omp_が呼んだ合計回数を出力

  free(array);                                      // 配列に割り当てられた動的メモリを解放

  return 0;
}

int bub_sort (int* array, int N) {
  int cur_pos, end_pos, comp_count;

  comp_count = 0;                                   // comp_countは、comp_が呼び出された回数
  for(end_pos=N-1; end_pos>0; end_pos--) {          // end_posは配列の最後から始まり、配列の最初まで通過
    for(cur_pos=0; cur_pos<end_pos; cur_pos++) {    // cur_posは配列の先頭から始まり、end_posまで通過
      comp_count++;                                 // comp_は反復ごとに一度呼び出す
      if(comp_(array, cur_pos+1, cur_pos) {         // cur_posの要素がその次の要素よりも高い場合、順序が狂っている
        func_swamp_(array, cur_pos, cur_pos+1);     // cur_posの要素をその次の要素と交換
        print_array_(array, N);                     // 配列の中間状態を出力
      }
    }
    // この時点で、end_posから配列の最後までのすべての要素が並べ替えられる
  }

  return comp_count;                                // comp_が呼び出された回数を返す
}
