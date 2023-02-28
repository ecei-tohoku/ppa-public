---
layout: page
title: 4-2. 編集距離(再帰+メモ化)【基本】
---


---
## メモ化
---
問題 4-1 のプログラムでは，文字列 $X$ と $Y$ の編集距離 $c_{m,n}$ を，与えられた文字列長から順に遡って再帰的に計算した．しかし，この方法では，同じ値を複数回計算してしまう可能性があるため，効率面で問題がある．
本問題では，再帰処理を効率的に行う手法として**メモ化(memoization)**について学ぶ.

メモ化の考えは非常に単純であり,

  + $c_{m,n}$ を求める過程で，一度計算した $c_{i,j}$の値をメモリに保存する.
  + 再び必要になった時は再帰呼び出しを行わず，以前求めて保存してあった $c_{i,j}$ の値を再利用する.
  
このような処理をメモ化と呼ぶ.
これにより，一度計算したものを再び計算する必要がないため，計算量は指数関数的に改善される.



---
## 問題
---


問題4-1で実装したプログラムにメモ化を導入し，メモ化ありの場合とメモ化なしの場合の再帰関数の呼び出し回数を求めよ.

なお，メモ化あり場合は，再帰関数の呼び出し回数が最小となるように実装せよ．


---
### 仕様
---
+ `include`するファイルは`<stdio.h>`,`<stdlib.h>`および`ppa_extra_h/p3_header.h`のみとする．

+ 問題4-1に提示してある関数を`ppa_extra_h/p3_header.h`というファイルにおいてある．`#include "ppa_extra_h/p3_header.h"`という宣言を通して含め、以下の関数を必要に応じて用いること．
  + `vmax_`
  + `vmax3_`
  + `vmin_`
  + `vmin3_`
  + `zeros_`
  + `malloc_string_`
  + `read_string_`
  + `malloc_2d_`
  + `free_2d_`

+ 事前に定義されている関数(基本的に関数名の最後に`_`がついているもの)の中身を書き換えてはいけない．これらの関数は例えば，`printf`や`scanf`と同様に中身を書き換えられない関数として扱うこと．

+ プログラム全体の構成を以下に従うようにする．
  + `main`関数の正常終了時の戻り値を0にする．
  + 関数は前方宣言を用い，関数本体は`main`関数の下に記述する（後方定義）．
 
    ```
    #include <stdio.h>
    #include <stdlib.h>

    ... 関数の前方宣言 ...

    int main(){

      ...（main関数本体）...

      return 0;
    }

      ... 関数の定義 ...
    ```


+ 問題4-1で実装した再帰関数をベースに，メモ化を導入せよ．関数名は`ldmemo`とする．この関数は，文字列$X$，文字列$X$の先頭から$m$文字目の場所を表すインデックス$m$，文字列$Y$，文字列$Y$の先頭から$n$文字目の場所を表すインデックス$n$，メモを格納する2次元配列用テーブル `memo` の5つを引数にとり，編集距離を返すものとする．
  + 例：
  ```	
  int ldmemo(char *X, int m, char *Y, int n, int** memo);
  ```

+ 2次元配列の確保と開放には，問題4-1に提示してある関数`malloc_2d_`関数と`free_2d_`関数をそれぞれ用いよ．
  + `malloc_2d_`関数は，整数iと整数jを引数に取り，整数型の2次元配列（i行j列）を返す関数である．例えば，以下のように書くと，2次元配列arrayが確保出来る．
  ```	
  int** array = malloc_2d_(i, j);　
  ```
  + `free_2d_`関数は，2次元配列arrayと配列の行数iを引数に取るvoid型の関数である．例えば，以下のように書くと，2次元配列arrayの開放を行う．
  ```	
  free_2d_(array, i);
  ```
  + `memo`の大きさは，文字列の長さに合わせて必要十分な大きさとすること．

+ `ld`と`delta`は問題4-1と同じものを使ってよい．

+ <font color="red">この問題に限り,再帰関数を呼び出した回数を求めるために,グローバル変数を用いること</font>（グローバル変数の説明は[こちら](#global_and_local_variables)）.

+ 呼び出し回数を求めるためのグローバル変数は,各再帰関数の中で一回だけ使用し,インクリメント演算子あるいは1を足す演算のみを行うこと.

+ 入力データの読み込み
  + 入力データの読み込みは`main` 関数内で行うこと．
  + 入力用の文字列$X$や$Y$とその要素数は標準入力から与えられる．文字列はスペースを除く可読文字（アルファベット，数字，記号）のみで構成されていると仮定してよい．
  + 各文字列はスペースや改行で区切られる．

+ 表示：以下を標準出力に書き出せ.
  + 一行目：文字列$X$ とその長さ
  + 二行目：文字列$Y$ とその長さ
  + 三行目：メモ化なしの再帰関数`ld`で求めた $c_{m,n}$ の値とメモ化なしの再帰関数の呼び出し回数
  + 四行目：メモ化ありの再帰関数`ldmemo`で求めた $c_{m,n}$ の値とメモ化ありの再帰関数の呼び出し回数
  + 全ての出力には改行文字 `\n` を付けること．特に最後の行の改行の有無に注意すること．
  + 各要素の間には空白文字を一つ入れる．
  + 改行前の空白文字などの表示されない文字を出力しないこと．
  + 全体的な出力例は以下のステップ3/3の実行例を参照せよ．
  + 出力例の`⊔` は半角スペース，`↩︎`は改行を表す．


+ 以下のプログラムを必ず用いてプログラムを完成させること．
  + `???` の部分は適宜補完すること.適宜コメント文を入れること.
  
```
#include <stdio.h>
#include <stdlib.h>

#include "ppa_extra_h/p3_header.h"

int count = 0;     // メモ化なしの再帰関数の呼び出し回数をカウントするグローバル変数
int countm = 0;    // メモ化ありの再帰関数の呼び出し回数をカウントするグローバル変数

int delta(char *X, int a, char *Y, int b);  // ???
int ld(char *X, int m, char *Y, int n);     // ???
int ldmemo(char *X, int m, char *Y, int n, int** memo);     // ???

int main() {
  int len_x, len_y ;                     // ???
  scanf(“%d”, &len_x);                   // ???
  scanf(“%d”, &len_y);                   // ???
  char* data_x = malloc_string_(len_x);  // ???
  char* data_y = malloc_string_(len_y);  // ???
  read_string_(data_x, len_x);           // ???
  read_string_(data_y, len_y);           // ???
  int** memo = malloc_2d_(??, ??); // ???
    
  ...(省略)...

  free_2d_(memo, ??);
  free(data_x);  // ???
  free(data_y);  // ???
  return 0;      // ???
}


int delta( ??? ) {

  ...(省略)...

}


int ld( ??? ) {

  ...(省略)...

}


int ldmemo( ??? ) {

  ...(省略)...

}
```

---
### グローバル変数とローカル変数の違い<a name="global_and_local_variables"></a>
---
ここではグローバル変数とローカル変数の違いについて説明する.

ローカル変数は宣言された関数内でのみ利用可能な変数であり,これまでの演習でも自然に用いてきたものである.
例として次のようなコードを考えてみよう.

    ```
    void func1(void){
      int a;
    }
    void func2(void){
      int b;
    }
    ```

ローカル変数`a`は関数`func1`で,ローカル変数`b`は関数`func2`で宣言されている.
これらの二つのローカル変数はそれぞれ,ローカル変数`a`は関数`func1`の中でのみ,ローカル変数`b`は関数`func2`の中でのみ利用することが可能な変数であり,ローカル変数`b`を関数`func1`で利用することは出来ず,ローカル変数`a`を関数`func2`で利用することもできない.次のように両者を同じ名前で宣言したとしても,二つのローカル変数`i`は全くの別物である.

    ```
    void func1(void){
      int i;
    }
    void func2(void){
      int i;
    }
    ```

一方で,変数の宣言は必ずしも関数の中で行わなければならないというわけではなく,`main`関数の外で変数を宣言することも出来る.

    ```
    int a;
    
    int main(void){
       ...
    }
    ```

このように,関数の外で宣言した変数をグローバル変数と呼ぶ.ローカル変数とは異なり,グローバル変数はどの関数からでも利用することが可能である.例えば,次のようなコードを考えると,

    ```
    int a = 0;
    
    int main(void){
       func1();
       func2();
    }
    
    void func1(void){
      a++;
    }
    void func2(void){
      a++;
    }
    ```

グローバル変数`a`は関数`func1`と関数`func2`でそれぞれ+1されるので,実行後は`a=2`となる.


---
### ステップに分けてプログラミング
---
この問題では，「グローバル変数を用いた再帰関数の呼び出し回数のカウント」「メモ化の実装」「メモ化を実装した場合のグローバル変数を用いた再帰関数の呼び出し回数のカウント」の3ステップに分けてプログラミングしてもらう．ステップごとに"動作確認"に成功しなければ，"TAに提出"が出来ないようになっている．以下では，各ステップをさらに細分化して説明する．

---
### ステップ1/3　「グローバル変数を用いた再帰関数の呼び出し回数のカウント」
---
ここでは、問題4-1で作成した`ld`関数の呼び出し回数をグローバル変数を用いてカウントする方法を実装する.


#### 1-1. 準備
- 問題4-1で作成したプログラムを利用するので,まずはそのまま書き写す.

#### 1-2. グローバル変数の定義
- `main`関数の外で整数型のグローバル変数`count`を定義する.

- `ld`関数を呼び出すたびに,`count`の値を+1するように`ld`関数を修正する.


#### 1-3. グローバル変数の値を確認
- ここでは`count`が`ld`関数の再帰による呼び出し回数を正しくカウントしていることを確認するために,`count`の値を出力させるようにしておく.問題4-1のステップ2/2の出力を改良して,以下の書式で表示すること.

- 入力データは,1,2列目が配列の要素数,3,4列目が配列の要素であるとする．

- 出力の3行目に`ld`関数の呼び出し回数も表示すること.

- 出力を目視で確認せよ.

  - 入力データ
    ```
    3 3 eat ate
    ```
  - 出力例
    ```
    eat⊔3↩︎
    ate⊔3↩︎
    2⊔94↩︎
    ```

  - 入力データ
    ```
    8 7 abababab abababc
    ```
  - 出力例
    ```
    abababab⊔8↩︎
    abababc⊔7↩︎
    2⊔162817↩︎
    ```

#### 1-4. 自動採点システムで動作確認


---
### ステップ2/3　「メモ化の実装」
---

このステップでは`ld`関数を改良することにより,メモ化の機能を実装した`ldmemo`関数を作成する.


#### 2-1. 準備
- ステップ1/3で作成したプログラムはそのままに、`ld`関数のコピーを作成し,`ldmemo`関数と名づける. ただし、引数に二次元配列も追加すること. 以下では,`ldmemo`関数にメモ化の機能を実装させるが,`ldmemo`関数の呼び出し回数を一意に定めるために,必ず下記の手順に従いメモ化を実装すること.

#### 2-2. メモ化の実装
- まず,二次元配列`memo`を定義し,`ldmemo(X,i,Y,j)`で計算した編集距離$c_{i,j}$の値を`memo[i][j]`に格納させるように`ldmemo`関数を修正する.

- 次に,`ldmemo`関数を呼び出す際,すでに計算済みである場合は`ldmemo`関数を呼び出さずに,`memo`を呼び出すことにより計算コスト削減する. 三つの操作それぞれに対して,`ldmemo`関数を呼び出す前に`memo`を参照するようにせよ.

- 計算済みかどうかを判別するためにはどうしたらいいだろうか？編集距離$c_{i,j}$は必ず0以上の値をとるため,`memo`の値が0以上かどうかで計算済みかを判断すれば良い.そのために、`memo`の初期化を工夫する必要がある.

- また,$i=0$ または $j=0$ の場合,編集距離 $c_{i,j}$ は自明なので`memo[i][j]`の初期値に代入すること.


#### 2-3. `ldmemo`関数による編集距離の値を確認
- ここでは`memo`を用いて`ldmemo`関数が編集距離を正しく計算できていることを確認する(`ldmemo`関数の呼び出し回数はステップ3/3で計算する).ステップ1/3の出力を改良して,以下の書式で表示すること.

- 入力データは,1,2列目が配列の要素数,3,4列目が配列の要素であるとする．

- 出力の4行目に`ldmemo`関数によって計算した編集距離を表示すること.

- 出力を目視で確認せよ.

  - 入力データ
    ```
    3 3 eat ate
    ```
  - 出力例
    ```
    eat⊔3↩︎
    ate⊔3↩︎
    2⊔94↩︎
    2↩︎
    ```

  - 入力データ
    ```
    8 7 abababab abababc
    ```
  - 出力例
    ```
    abababab⊔8↩︎
    abababc⊔7↩︎
    2⊔162817↩︎
    2↩︎
    ```

#### 2-4. 自動採点システムで動作確認

---
### ステップ3/3　「メモ化を実装した場合のグローバル変数を用いた再帰関数の呼び出し回数のカウント」
---
このステップではメモ化により,`ldmemo`関数の呼び出し回数が削減されていることを確認する.

#### 3-1. グローバル変数の定義
- ステップ2/3で作成したプログラムはそのままに,`main`関数の外で整数型のグローバル変数`countm`を定義する.

- `ldmemo`関数を呼び出すたびに,`countm`の値を+1するように`ldmemo`関数を修正する.

#### 3-2. グローバル変数の値を確認
- ここでは`countm`が`ldmemo`関数の呼び出し回数を正しくカウントしていることを確認する.ステップ2/3の出力を改良して,以下の書式で表示すること

- 入力データは,1,2列目が配列の要素数,3,4列目が配列の要素であるとする．

- 出力の4行目に`ldmemo`関数の呼び出し回数も表示すること.

- 出力を目視で確認せよ.

  - 入力データ
    ```
    3 3 eat ate
    ```
  - 出力例
    ```
    eat⊔3↩︎
    ate⊔3↩︎
    2⊔94↩︎
    2⊔9↩︎
    ```

  - 入力データ
    ```
    8 7 abababab abababc
    ```
  - 出力例
    ```
    abababab⊔8↩︎
    abababc⊔7↩︎
    2⊔162817↩︎
    2⊔56↩︎
    ```
    
#### 3-3. 自動採点システムで動作確認