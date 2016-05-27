---
layout: page
title: 課題１の解答例と解説
---

## 1-1. 和差算

```
#include <stdio.h>

int main()
{
  int a, b, x, y;
  scanf("%d %d", &a, &b);
  x = a + b;
  y = b - a;
  if (x % 2 != 0 || y % 2 != 0) {
    printf("ERROR\n");
  } else {
    printf("%d %d\n", x / 2, y / 2);
  }
  return 0;
}
```

## 1-2. コラッツの問題

```
#include <stdio.h>

int main()
{
  int i, x;

  scanf("%d", &x);
  for (i = 0; i < 100; ++i) {
    printf("%d\n", x);
    if (x % 2 == 0) {
      x /= 2;
    } else {
      x *= 3;
      ++x;
    }
    if (x == 1) {
      printf("%d\n", x);
      printf("OK\n");
      break;
    }
  }
  return 0;
}
```

`while`文を使った繰り返し処理でもよい．ただ，`for`文を使ったほうが「100回繰り返す」という仕様が一目瞭然になるので，後からプログラムを読み返したときに理解しやすくなる．

## 1-3. トリム平均

```
#include <stdio.h>

int main()
{
  int i;
  double v, s = 0., min = 20., max = 0.;

  for (i = 0; i < 7; ++i) {
    scanf("%lf", &v);
    if (v < min) {
      min = v;
    }
    if (max < v) {
      max = v;
    }
    s += v;
  }

  printf("%.2f\n", (s - min - max) / 5.);
  return 0;
}
```

入力された数値を配列に格納してから処理をしてもよい．ただ，最大値，最小値，和を求める処理は，入力された値を全て保持しなくても，逐次処理で求めることができる．

## 1-4. 単純移動平均

```
#include <stdio.h>

int main()
{
  int i, j;
  double v[1246];

  for (i = 1; i <= 1245; ++i) {
    scanf("%lf", &v[i]);
  }

  for (i = 20; i <= 1245; ++i) {
    double sma5 = 0., sma20 = 0.;
    for (j = 0; j < 5; ++j) {
      sma5 += v[i-j];
    }
    for (j = 0; j < 20; ++j) {
      sma20 += v[i-j];
    }
    printf("%d %.2f %.2f %.2f\n", i, v[i], sma5 / 5, sma20 / 20);
  }

  return 0;
}
```

SMA5やSMA20を`for`文を使わず，和の計算を書き下す解答が意外と多かった．ぜひ`for`文の便利さを感じて欲しい．

## 1-5. Luhnアルゴリズム

```
#include <stdio.h>
#include <string.h>

int main()
{
  int i, s = 0;
  char digits[101];
  int table[10] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};

  scanf("%s", digits);

  for (i = 1; i <= strlen(digits); ++i) {
    int v = digits[strlen(digits)-i] - '0';
    if (i % 2 == 1) {
      s += v;
    } else {
      s += table[v];
    }
  }

  if (s % 10 == 0) {
    printf("true\n");
  } else {
    printf("false\n");
  }

  return 0;
}
```

文字列の終端にはヌル文字（`'\0'`）が挿入されるため，100桁（100文字）の文字列を格納するには，101個の要素を保持できる`char`型の配列が必要（100個の要素では足りない）．

文字の逆順を求めてから左から`i`番目の文字にアクセスしようとする解答もあったが，長さ`n`の文字列（文字の配列）`s`があるとき，右から`i`番目の文字は`s[n-i]`で表される．文字列`s`の長さは`strlen(s)`で求めることができる．

右から数えて偶数桁の数字では，元の数$v$と足される数の関係は以下のようになる．

|   元の数 $v$  | 足される数 |
|:-----------|:------------|
| 0 | 0 ($2v$) |
| 1 | 2 ($2v$) |
| 2 | 4 ($2v$) |
| 3 | 6 ($2v$) |
| 4 | 8 ($2v$) |
| 5 | 1 ($2v - 9$) |
| 6 | 3 ($2v - 9$) |
| 7 | 5 ($2v - 9$) |
| 8 | 7 ($2v - 9$) |
| 9 | 9 ($2v - 9$) |
{: .table .table-bordered}

この変換表をそのままC言語で実装したのが，以下の配列`table`である．

```
int table[10] = {0, 2, 4, 6, 8, 1, 3, 5, 7, 9};
```

この配列`table`を使うと，元の数`v`に対して足すべき数は常に`table[v]`で求まるため，プログラムが簡潔になる．もちろん，$v < 5$と$5 \leq v$に場合分けして計算式を実装してもよい．

## 1-6. カプレカー変換

```
#include <stdio.h>

int main()
{
  int i, x, d[3];

  scanf("%d", &x);
  do {
    // Extract three digits d[2]d[1]d[0] from x.
    for (i = 0; i < 3; ++i) {
      d[i] = x % 10;
      x /= 10;
    }

    // Find the maximum and minimum of the digits.
    int max = d[0], min = d[0];
    for (i = 1; i < 3; ++i) {
      if (max < d[i]) max = d[i];
      if (d[i] < min) min = d[i];
    }

    // Find the middle of the digits.
    int mid = d[0] + d[1] + d[2] - max - min;

    // Compute high - low.
    int high = 100*max + 10*mid + min;
    int low = 100*min + 10*mid + max;
    x = high - low;
    printf("%3d - %3d = %3d\n", high, low, x);
  } while (x != 495);

  return 0;
}
```

自然数`x`の1の位（右から1桁目），10の位（右から2桁目），100の位（右から3桁目）を，それぞれ，`d[0]`, `d[1]`, `d[2]`で表すように剰余の計算を繰り返している．

配列の要素の最大値と最小値を求めるのは容易だが，中間値を求めるのには工夫が要る．多かった解答は以下の通り．

+ 条件分岐をすべて書いて求める
+ 課題2を先取りして配列の要素を整列する

これらを実装するのは少し手間だが，「最小値 + 中間値 + 最大値 = 各桁の数字の和」という関係を使えば，中間値を簡単に求めることができる．

## 1-7. 三目並べ

```
#include <ctype.h>
#include <stdio.h>

int main()
{
  int i, j, x;
  char states[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  int patterns[8][3] = {
    {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
    {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    {0, 4, 8}, {2, 4, 6}
  };

  for (i = 0; i < 10; ++i) {
    // The mark of this turn.
    char m = (i % 2 == 0) ? 'o' : 'x';

    // Show the current state.
    printf("%c|%c|%c\n", states[6], states[7], states[8]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", states[3], states[4], states[5]);
    printf("-+-+-\n");
    printf("%c|%c|%c\n", states[0], states[1], states[2]);

    // Judge the state.
    for (j = 0; j < 8; ++j) {
      int a = patterns[j][0];
      int b = patterns[j][1];
      int c = patterns[j][2];
      if (states[a] == 'o' && states[b] == 'o' && states[c] == 'o') {
        printf("o win!\n");
        return 0;
      }
      if (states[a] == 'x' && states[b] == 'x' && states[c] == 'x') {
        printf("x win!\n");
        return 0;
      }
    }

    // Print a prompt and read a number (at most nine times).
    if (i < 9) {
      // Loop until the user enters a valid number.
      do {
        printf("%c> ", m);
        scanf("%d", &x);
        printf("\n");
        if (x < 1 || 9 < x || !isdigit(states[x-1])) {
          printf("ERROR\n");
          x = 0;
        }
      } while (x == 0);

      // Mark the position #x with c.
      states[x-1] = m;
    }
  }

  printf("even.\n");
  return 0;
}
```

盤面上のマス目の番号`x`に対し，そのマス目で表示すべき文字を`state[x-1]`で管理している（配列`state`のインデックスは`0`から始まるので，`x-1`としている）．マス目の文字を表示するには，書式`%c`を用いればよい．

三項演算子（` ? : `）を使った行にビックリするかもしれない．

```
char m = (i % 2 == 0) ? 'o' : 'x';
```

これは，以下の処理をコンパクトに書いたもの．

```
char m;
if (i % 2 == 0)
  m = 'o';
else
  m = 'x';
```

横一列，縦一列，斜めに関して，配列`state`の文字がすべて`'o'`または`'x'`になった時に勝敗がつく．これを，配列`state`のインデックス番号で表すと，次のようになる．

* 横一列: (0, 1, 2), (3, 4, 5), (6, 7, 8)
* 縦一列: (0, 3, 6), (1, 4, 7), (2, 5, 8)
* 斜め: (0, 4, 8), (2, 4, 6)

このテストすべきインデックス番号のパターンを2次元配列`pattern`に格納しておき，そのパターンに従って勝敗判定を行うことで，大量の条件式を書かなくても済む．

`isdigit(c)`関数は，引数`c`が数字の文字であれば真，それ以外ならば偽を返す関数で，ヘッダファイル`ctype.h`で宣言されている．`isdigit(state[x-1])`が真ということは，番号`x`のマス目に数字が書かれている（＝マス目が空いている）ということになる．したがって，その否定`!isdigit(state[x-1])`は「マス目が空いていない」という状態を表す．少し長くなるが，`!isdigit(state[x-1])`よりも`state[x-1] == 'o' || state[x-1] == 'x'`と書くほうが，分かりやすいかもしれない．