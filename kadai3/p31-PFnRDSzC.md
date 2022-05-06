---
layout: page
title: 3-1. 課題３導入問題【初歩】
---

この問題では，以降の問題で使用する文字配列，整数の二次元配列，整数の最大／最小に関する関数群の一部を実装してもらう．

---
## <font color="red">！！重要！！　課題全体を通しての仕様</font>
---

課題を通しての仕様を説明する (各設問で追加の仕様や注意書きがある場合はそちらを優先する)．

- グローバル変数や静的変数を使用してはいけない．
- `include`するファイルは`<stdio.h>`および`<stdlib.h>`のみとする．
- プログラム全体の構成を以下に従うようにする．
  - `main`関数の正常終了時の戻り値を0にする．
  - 関数の前方宣言を用い，関数本体は`main`関数の下に記述する．
    ```
      #include <stdio.h>
      #include <stdlib.h>

        ... 事前に与えられる関数の定義 ...

      //////

        ... 課題ごとの関数前方宣言 ...

      int main()
      {

        ...（main関数本体）...

        return 0;
      }

        ... 課題ごとの関数本体 ...
      ```
  - ただし，課題ごとに与えられるコードを記載する場所は，それぞれの指示に従う．

- 入力データの読み込み
  - 入力データの読み込は`main` 関数内で行うこと．
  + 入力用の文字列$X$や$Y$とその要素数は標準入力から与えられる．
  + 各文字列は空白文字（スペースや改行）で区切られる．

- 事前に定義されている関数(基本的に関数名の最後に`_`がついているもの)の中身を書き換えてはいけない．これらの関数は例えば，`printf`や`scanf`と同様に中身を書き換えられない関数として扱うこと．

- 表示例の`⊔` は半角スペース，`↩︎`は改行を表す．
- 表示(出力)
  - 全ての表示は標準出力にすること．ただし，標準エラー出力への表示が必要な場合は各課題の仕様に記載する．
  - 全ての出力には改行文字 `\n` を付けること．特に最後の行の改行の有無に注意すること．
  - 各要素の間には空白文字を一つ入れる．
  - 改行前の空白文字などの表示されない文字を出力しないこと．

---
## 問題
---
以下に説明する関数群を実装し，それらの動作確認を行なうプログラムを書け．

---
### 整数引数の大小を判定する関数群
---

+ 2つの値のうち小さい方の値を取得する関数`vmin_`：

  ```
  int vmin_(int a, int b);
  ```
    
  例：`vmin_(1, 3)` なら戻り値は`1`
+ 2つの値のうち大きい方の値を取得する関数`vmax_`：
  
  ```
  int vmax_(int a, int b);
  ```
    
  例：`vmax_(2, 3)` なら戻り値は`3`
+ 3つの値のうち最も小さい値を取得する関数`vmin3_`：
  
  ```
  int vmin3_(int a, int b，int c);
  ```
    
  例：`vmin3_(2, 1, 3)` なら戻り値は`1`
+ 3つの値のうち最も大きい値を取得する関数`vmax3_`：
  
  ```
  int vmax3_(int a, int b，int c);
  ```
    
  例：`vmax3_(3, 2 ,1)` なら戻り値は`3`

---
### 文字配列処理の関数群
---

+ 文字配列専用でメモリ確保する関数`func_mallocation_char_`：

    ```
    char* func_mallocation_char_(int N);
    ```
  
    引数は文字列の長さNで，ヌル文字分を足してN+1の長さの文字配列を確保する．
    戻り値は，配列の先頭を指すポインタ．
    ※動的に確保したメモリ領域は，処理が完了した後に`free`関数で解放すること．

  + 標準入力から決められた長さの文字列を読み込む関数 `read_string_`を用いること
  
    ```
    char* read_string_(int N);
    ```
    
    引数は，読み込む文字列の長さ．
    戻り値は，読み込んだ文字列の先頭を指すポインタ．

  + 文字列用の配列を`\0`で初期化する関数`zeros_`：
 
     ```
     void zeros_(char* X,  int N);
     ```
     
     引数は，初期化したい文字列$X$と文字列＄X$の長さ


---
### 二次元配列を動的メモリ確保／解放する関数群
---
`func_mallocation_2d_`関数と`func_free_2d_`関数の中身は，それぞれ以下の通りである．

```
int** func_mallocation_2d_(const int len_x, const int len_y){
  int** array_2d = (int **)malloc(sizeof(int *) * len_x);
    if(array_2d == NULL){
        printf("Can not allocate memory. 'array_2d' is NULL.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < len_x; ++i){
        array_2d[i] = (int*)malloc(sizeof(int) * len_y);
        if(array_2d[i] == NULL){
            printf("Can not allocate memory. 'array_2d[i]' is NULL.\n");
            exit(EXIT_FAILURE);
        }
    }
    return array_2d;
}
```

```
void func_free_2d_(int **array_2d, int len_x){
  for(int i = 0; i < len_x; ++i) free(array_2d[i]);
 free(array_2d);
}
```

---
### 仕様
---
+ 上述した課題全体の仕様．

＋ 以下のプログラムを必ず用いてプログラムを完成させること．
  + コメント文が`???`となっている箇所は，書かれているコードに対するコメントを書くこと．
  + コードが`???`となっている箇所は，コメント文で書かれた処理を行なうコードを書くこと．
  + すでに書いてあるコメント文は書き写さなくてよい．

```
#include <stdio.h>
#include <stdlib.h>
#include "ppa_extra_h/p3_1.h"

int vmax_(int x, int y) { return x > y ? x : y; }                  // ???
int vmax3_(int a, int b, int c) { return vmax_(a, vmax_(b, c)); }  // ???
int vmin_(int x, int y) { return x < y ? x : y; }                  // ???
int vmin3_(int a, int b, int c) { return vmin_(a, vmin_(b, c)); }  // ???

void zeros_(     // 文字列用の配列を\0で初期化する関数
    char* data,  // 文字列を格納する配列
    int N        // 文字列の長さ
) {
  for (int i = 0; i < N; ++i) {
    data[i] = ‘\0’;  // 配列のi番目の要素を\0で初期化
  }
}

char* func_mallocation_char_(  // 文字列用の配列を確保する関数
    const int len_x            // 文字列の長さ
) {
  char* data  = (char*)malloc( (len_x+1) * sizeof(char));  // 配列に動的メモリを割り当てる
  if (data == NULL) {                                  // メモリ確保に失敗した際のエラー処理
    printf(“Can not allocate memory. ‘data’ is NULL.\n”);
    exit(EXIT_FAILURE);  // メモリ確保に失敗したら、プログラムを終了（EXIT_FAILUREはstdlib.h内で定義されている）
  }
  zeros_(data, len_x+1);   // 配列dataを関数zeros_で初期化
  return data;       // 配列dataの先頭のポインタを返す
}

char* read_string_(  // 文字列用のメモリ確保と、標準入力からの文字列読み込みを行う関数
    const int N      // 文字列の長さ
) {
  char* data = func_mallocation_char_(N);
  scanf(“%s”, data);          // 文字列を読み込む
  if (data[N ] != ‘\0’) {  // 文字列がN以上の場合のエラー処理
    printf(“Reading invalid string\n”);
    exit(1);  // プログラムを終了
  }
  return data;  // 配列dataの先頭のポインタを返す
}

//////////
int find_matching(char* X, int M, char* Y, int N, char* buf);
void sort_buf(char* buf, int N);


int main() {
  int len_x, len_y ;                      // 入力文字列の要素数を記録する
  scanf(“%d”, &len_x);               // 1つ目の文字列の要素数を受け取る
  scanf(“%d”, &len_y);               // 2つ目の文字列の要素数を受け取る
  char* data_x = read_string_(len_x);  // 1つ目の文字列をdata_xに格納
  char* data_y = read_string_(len_y);  // 2つ目の文字列をdata_yに格納
  char* buf =  func_mallocation_char_(len_x * len_y);   // マッチングした文字を保存する配列bufの宣言
  
  // find_matching関数を実行して、data_x, data_yの共通文字を取得
  int cnt = find_matching(data_x, len_x, data_y, len_y, buf); 
  
  // sort_buf関数を実行して、辞書順に並べ替え
  sort_buf(buf, cnt);
  
  printf(“%s %d\n”, data_x, len_x);  // data_xに格納した文字列とその長さをSTDOUTに出力
  printf(“%s %d\n”, data_y, len_y);  // data_yに格納した文字列とその長さをSTDOUTに出力
  
  // 重複した文字をスキップして出力するループ
  char prev = ‘\0’;                // 変数prevを'\0'で初期化
  for (int i = 0; i < cnt; ++i) {  // i=0からi=cnt-1まで繰り返す
    ???;  // prev == buf[i]ならばスキップ
    printf(“%c\n”, buf[i]);        // buf[i]を出力
    prev = buf[i];                 // prevにbuf[i]を代入
  }
  
  ???;  // 動的に確保された配列data_xの開放
  ???;  // 動的に確保された配列data_yの開放
  ???;  // 動的に確保された配列bufの開放
  return 0;      // プログラムの正常終了
} 


int find_matching(  // 文字列XとYの中からマッチした文字を重複込みで配列bufに保存する関数
    char* X,        // ???
    int len_x,      // ???
    char* Y,        // ???
    int len_y,      // ???
    char* buf       // ???
) {
  int cnt = 0;  // ???
  for (int i = 0; i < len_x; ++i) {
    for (int j = 0; j < len_y; ++j) {
      if (X[i] == Y[j]) {  // ???
        buf[cnt] = X[i];   // ???
        cnt++;             // ???
      }
    }
  }
  return cnt;  // ???
}


void sort_buf(  // 交換ソートの考え方に基づき、文字列を辞書順に並び替える関数
    char* buf,  // ???
    int N       // ???
) {
  for (int i = 0; i < N; ++i) {
    for (int j = 1; j < N - i; ++j) {
      if (buf[j] < buf[j - 1]) {   // ASCIIコードに従い，文字に対応する整数の大小を比較（問題1-5のASCIIコードの説明を参照せよ）
      
        // buf[j]とbuf[j-1]を交換
        ???;
        ???;
        ???;
      }
    }
  }
}
```


---
## 実行例
---

---
### 例（1）
---

+ 入力
```
3 3 eat ate
```

+ 出力
```
eat 3
ate 3
a
e
t
```

---
### 例（2）
---

+ 入力
```
8 7 abababab abababc
```

+ 出力
```
abababab 8
abababc 7
a
b
```


---
## 参考情報
---
- 関数`vmax_`等で用いられている`(条件式) ? (真式) : (偽式)`という記法は，三項演算子と呼ばれ，(条件式)が真であれば(真式)を，偽であれば(偽式)を評価して値を返す．例えば`vmax_`は以下と等価である：

  ```
  int vmax_(int x, int y){
   if( x > y ){
     return x;
   }
    else {
      return y;
    }
  }
  ```
 
- 簡単な式であればよいが，カッコ書きや三項演算子を入れ子にするような複雑な式の場合は，if文を使用した方が見やすい：

  ```
  d = (a>b) ? ((b>c) ? c : b) : ((a>c) ? c : a );
  
  if( a > b ){
    if( b > c ) d = c;
    else d = b;
  }
  else {
    if( a > c ) d = c;
    else d = a;
  }
  ```
  
- 「真偽判定の結果に応じて異なる値を代入する」という処理はわりと登場頻度が高いので，C言語では演算子としてサポートされている．（もともと導入された経緯としては，Intelプロセッサなどで提供している"conditional move"などの条件付き命令を積極的に用いるためというのも一つある．）
