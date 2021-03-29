#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p2_header.h"

int mrg_sort(int*, int, int, int);
int merge(int*, int, int, int, int);

int main () {
  int N, *array, i;

  scanf("%d", &N);                                  // 入力配列の要素数
  array = func_mallocation_(2*N);                   // 配列とN個の整数をコピーバッファに動的メモリを割り当てる
  for(i=0; i<N; i++) scanf("%d", &(array[i]));      // STDINから配列要素を受け取る
  printf("INIT:::::::"); print_array_(array, N);    // 配列の初期状態をSTDOUTに出力
  i = mrg_sort(array, N, 0, N-1);                   // 配列を並べ替える
  printf("DONE:::::::"); print_array_(array, N);    // 配列の最終状態をSTDOUTに出力
  printf("%d\n", i);                                // comp_が呼んだ合計回数を出力

  free(array);                                      // 配列に割り当てられた動的メモリを解放

  return 0;
}

int mrg_sort (int* array, int N, int p, int q) {
  int comp_count, mid_pos, num_elem;

  comp_count = 0;                                   // comp_countは、comp_が呼び出された回数

  if(p != q) {                                      // p！= qの場合、この配列の部分には1個より要素がある
    num_elem = q - p + 1;                           // 配列の部分の要素数を計算
    mid_pos = p + (int)(num_elem/2);                // 配列の部分の中央（ピボット）位置を計算
    if(num_elem%2) mid_pos++;
    comp_count += mrg_sort(array, N, p, mid_pos-1); // 配列の部分の前半を並べ替える
    comp_count += mrg_sort(array, N, mid_pos, q);   // 配列の部分の後半を並べ替える
    comp_count += merge(array, N, p, q, mid_pos);   // 配列の部分の2つの並べ替えれた半分をマージ
  }

  return comp_count;                                // comp_が呼び出された回数を返す
}

int merge (int* array, int N, int p, int q, int r) {
  int comp_count, i1, i2, iT;

  comp_count = 0;                     // comp_countは、comp_が呼び出された回数
  i1 = p;                             // i1は、配列の部分の前半の最初から始まり、配列の部分の中間点まで進む
  i2 = r;                             // i2は、配列の部分の中間点から始まり、配列の部分の終わりまで進む
  iT = N+p;                           // iTは、配列の部分の先頭に対応するコピーバッファ位置から開始します

  // i1またはi2が最小の要素を指しているかどうかを識別し、要素をコピーバッファにコピーし、変数を更新
  // 配列の部分の1つの半分が完全にチェックされるまで繰り返す
  while(i1<r && i2<=q) {              // i1またはi2のいずれかが配列の部分の半分を通過するまでループを繰り返す
    comp_count++;                     // comp_は反復ごとに一度呼び出す
    if(comp_(array, i1, i2)) {        // array[i1] < array[i2]　の場合
      func_copy_val_(array, i1, iT);  // i1の要素をコピーバッファにコピー
      i1++; iT++;                     // 配列の部分内でi1を前方に移動し、コピーバッファ内でiTを前方に移動
    }
    else {                            // array[i1] >= array[i2]　の場合
      func_copy_val_(array, i2, iT);  // i2の要素をコピーバッファにコピー
      i2++; iT++;                     // 配列の部分内でi2を前方に移動し、コピーバッファ内でiTを前方に移動
    }
  }

  // i1<r の場合、配列の部分の前半にコピーバッファにコピーされていない要素がまだある
  // これらの要素をすべてコピーバッファにコピー
  while(i1<r) {
    func_copy_val_(array, i1, iT);
    i1++; iT++;
  }

  // i2<=q の場合、配列の部分の後半にコピーバッファにコピーされていない要素がまだある
  // これらの要素をすべてコピーバッファにコピー
  while(i2<=q) {
    func_copy_val_(array, i2, iT);
    i2++; iT++;
  }

  // コピーバッファ全体を配列にコピー
  for(iT=p; iT<=q; iT++) {
    func_copy_val_(array, N+iT; iT);
  }

  printf("MERG(%2d,%2d)", p, q);        // 操作を出力します（配列の部分の2つの半分を、pからqにマージ）
  print_array_range_(array, N, p, q);   // 配列の中間状態を出力

  return comp_count;                    // comp_が呼び出された回数を返す
}
