---
layout: page
title: ファイルからのデータ読込方法
---

ファイルからデータを読み込む場合は，FILE，fopen，fscanf，fcloseと
いったものを使います．以下に示す例は，一つのファイルに記載されてい
るデータを終りまで読み込んで，読み込まれたデータの個数とデータを出力するというものです．

複数のファイルを開く場合には，それぞれのファ
イルに対して，fopen，fscanf，fcloseを行い，格納用配列にデータを格
納して下さい．FILE，fopen，fscanf，fcloseの詳細な使用法については，
C言語に関する書籍を参考にして下さい．

## サンプルプログラム(ファイル名を固定する場合)
プログラムの中で，読み込むファイルを直接指定したい場合は，こちらのプログラムを参考にすると良いでしょう．

```
#include <stdio.h>

#define N 100    /* データの個数を定義 */

int main(void){
    int  data[N];            /* ファイルからのデータを格納する変数 */
    int  count = 0;          /* 入力したデータ数を数える変数 */
    FILE *fp;                /* ファイルポインタ */
    int  result;             /* データの入力数を確認する変数 */
    int  i;

    /* 指定したファイルを開く */
    fp = fopen("/opt/local/enshu/data/score.dat", "rt");
    if (fp==NULL){
        printf("Error: File not found.\n");
        exit(1);
    }
    /* データの読み込み */
    while(count<N){
        result = fscanf(fp, "%d", &data[count]);   /* データを変数に格納する */
        if (result==EOF)  break;  /* ファイルの終わりに来たら終了 */
        count++;                  /* 読み込んだデータ数を一つ増やす */
    }
    /* ファイルを閉じる */
    fclose(fp);

    /* 読み込んだデータを出力 */
    printf("Size of data: %d\n", count);
    for (i = 0;i < count;i++){
        printf("Data No.%d = %d\n", i+1, data[i]);
    }

    return 0;
}
```


## サンプルプログラム(標準入力を利用する場合)
読み込むファイルを直接指定したくない場合は，標準入力からファイルを読み込む手法が良いでしょう．

```
#include <stdio.h>

#define N 100    /* データの個数を定義 */

int main(void){
    int  data[N];            /* ファイルからのデータを格納する変数 */
    int  count = 0;          /* 入力したデータ数を数える変数 */
    int  result;             /* データの入力数を確認する変数 */
    int  i;

    /* 標準入力からデータの読み込み */
    while(count<N){
        result = scanf("%d", &data[count]);   /* データを変数に格納する */
        if (result==EOF)  break;  /* ファイルの終わりに来たら終了 */
        count++;                  /* 読み込んだデータ数を一つ増やす */
    }

    /* 読み込んだデータを出力 */
    printf("Size of data: %d\n", count);
    for (i = 0;i < count;i++){
        printf("Data No.%d = %d\n", i+1, data[i]);
    }

    return 0;
}
```

上のプログラムを保存，コンパイルし，端末から:

`./a.out < 読み込みたいファイル `

として実行すれば，ファイルが一行ずつ読みこまれます．

