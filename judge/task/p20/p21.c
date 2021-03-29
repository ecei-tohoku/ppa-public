#include <stdio.h>
#include <stdlib.h>

void func_swap_(  // 配列内の2つの要素を交換し、操作をSTDOUTに出力
    int* const array,  // 要素が交換される配列
    const int pos_a,   // 1番目の交換対象の要素番号
    const int pos_b    // 2番目の交換対象の要素番号
) {
  int tmp = array[pos_a];       // array[pos_a]の値をtmpに退避
  array[pos_a] = array[pos_b];  // array[pos_a]にarray[pos_b]を代入
  array[pos_b] = tmp;           // 退避したarray[pos_a]の値をarray[pos_b]に代入
  printf("SWAP(%2d,%2d)", pos_a, pos_b);
}

int comp_(             // 配列内の2つの要素を比較する関数
    int* const array,  // 要素の比較を行う配列
    const int pos_a,   // 1つ目の比較対象の要素番号
    const int pos_b    // 2つ目の比較対象の要素番号
) {
  if (array[pos_a] < array[pos_b]) return 1;  // 1つ目の要素が2つ目の要素より小さい場合に信号
  return 0;                                   // 他のすべての可能性で信号無し
}

void print_array_(           // 配列をSTDOUTに表示する関数
    const int* const array,  // 表示する配列
    const int N              // 配列の要素数
) {
  for (int i = 0; i < N; ++i) {
    printf(" %2d", array[i]);
  }
  printf("\n");
}

int* func_mallocation_(  // 配列の動的メモリ確保をおこなう関数
    const int N          // 配列の要素数
) {
  int* data = (int*)malloc(N * sizeof(int));  // dataはN個の整数に割り当てられたメモリスペースへに指し示す
  if (data == NULL) { // メモリ確保に失敗した際のエラー処理
    printf("Can not allocate memory. 'data' is NULL.\n");
    exit(EXIT_FAILURE);
  }
  return data;  // 確保した配列のポインタを戻り値として返す
}


int reverse_array(int*, int);

int main() {
  int N;       // 入力配列の要素数
  scanf("%d", &N);               // STDINから要素数を受け取る
  int* array = func_mallocation_(N);  // 配列に動的メモリを割り当てる
  for (int i = 0; i < N; i++)
    scanf("%d", &(array[i]));  // STDINから配列要素を受け取る
  printf("INIT:::::::");
  print_array_(array, N);             // 配列の初期状態をSTDOUTに出力
  int cnt = reverse_array(array, N);  // 入力配列を逆順
  printf("DONE:::::::");
  print_array_(array, N);  // 配列の最終状態をSTDOUTに出力
  printf("%d\n", cnt);     // comp_が呼んだ合計回数を出力

  free(array);  // 配列に割り当てられた動的メモリを解放
  return 0;     // プログラムがエラーなしで終了した場合は0を返す
}

int reverse_array(  // 配列を逆順
    int* array,     // 逆順される配列
    int N           // 配列の要素数
) {
  int pos_a = 0;       // pos_aは配列の最初から始まる
  int pos_b = N - 1;   // pos_bは配列の最後から始まる
  int comp_count = 0;  // comp_countには、comp_が呼んだ合計回数が含まれる

  while (pos_a < pos_b) {  // 配列のすべての要素が表示されるまでループを繰り返す
    comp_count += 2;       // 反復ごとにcomp_が呼ばれる

    if ((comp_(array, pos_a, pos_b) +   // pos_aの要素がpos_bの要素よりも小さいかどうかを確認
        comp_(array, pos_b, pos_a))	// pos_bの要素がpos_aの要素よりも小さいかどうかを確認
    == 1) {   			// いずれかが1の場合にのみ、両方の要素が異なり、変更する必要す
      func_swap_(array, pos_a, pos_b);  // pos_aとpos_bの要素を交換
      print_array_(array, N);           // 配列の中間状態を出力
    }
    pos_a++;  // pos_aは配列の次の要素に移動
    pos_b--;  // pos_bは配列の前の要素に移動
  }
  return comp_count;  // comp_が呼んだ合計回数を返す
}
