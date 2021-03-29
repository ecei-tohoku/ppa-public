#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p2_header.h"

int ins_sort(int *, int);

int main () {
  int N, *array, i;

  scanf("%d", &N);                                  // 入力配列の要素数
  array = func_mallocation_(N+1);                   // 配列と1つの整数をコピーバッファに動的メモリを割り当てる
  for(i=0; i<N; i++) scanf("%d", &(array[i]));      // STDINから配列要素を受け取る
  printf("INIT:::::::"); print_array_(array, N);    // 配列の初期状態をSTDOUTに出力
  i = ins_sort(array, N);                           // 配列を並べ替える
  printf("DONE:::::::"); print_array_(array, N);    // 配列の最終状態をSTDOUTに出力
  printf("%d\n", i);                                // comp_が呼んだ合計回数を出力

  free(array);                                      // 配列に割り当てられた動的メモリを解放

  return 0;
}

int ins_sort (int* array, int N) {
  int cur_pos, end_pos, comp_count;

  comp_count = 0;                                    // comp_countは、comp_が呼び出された回数
  for(end_pos=1; end_pos<N; end_pos++) {             // end_posは、配列の2番目の要素から始まり、最後の要素まで通過
    for(cur_pos=end_pos-1; cur_pos>=0; cur_pos--) {  // cur_posは、end_posの前の要素から始まり、配列の先頭まで通過
      comp_count++;                                  // comp_は反復ごとに一度呼び出す
      if(comp_(array, end_pos, cur_pos) != 1) break; // ループは、配列の先頭に到達するか、end_posより小さい要素が見つかるまで続く
    }
    cur_pos+=1;                                      // cur_posは、end_posより大きい最初の要素に戻される
                                                     // これは、end_posの要素を挿入する場所

    if(end_pos!=cur_pos) {                           // end_posの要素が正しい場所にない場合にのみ何かをする必要
      printf("INST(%2d,%2d)", end_pos, cur_pos);     // end_posの要素をcur_posの位置に挿入

                                                     // Nをコピーバッファとして使用して、cur_posとend_posの要素を交換し、
      for(; cur_pos<end_pos; cur_pos++) {            // cur_posがend_posに到達するまでcur_posを前方に移動
        func_copy_val_(array, cur_pos, N);
        func_copy_val_(array, end_pos, cur_pos);
        func_copy_val_(array, N, end_pos);
      }
      print_array_(array, N);                        // 配列の中間状態を出力
    }
    // この時点で、0からend_posまでのすべての要素が並べ替えられる
  }

  return comp_count;                               // comp_が呼び出された回数を返す
}
