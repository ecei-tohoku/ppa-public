---
layout: page
title: Valgrindでメモリに関するデバッグ
---

## メモリの初期化忘れ

以下の [sum.c](sum.c) は$1$から$10$までの整数の和を求めることを意図したプログラムです．
一見すると正しそうですが，変数`sum`が初期化されていないため，意図した動作になる保証はありません．

```
#include <stdio.h>

int main()
{
  int i, sum;

  for (i = 1; i <= 10; ++i) {
    sum += i;
  }
  printf("sum = %d\n", sum);
  return 0;
}
```

実際に動かしてみると，**偶然**正しい結果が表示されますが，別の環境（たとえば自動採点システム等）でも同じ結果が得られるとは限りません．

```
$ gcc -Wall program.c
$ ./a.out
sum = 55
```

## Valgrind

メモリの初期化忘れなど，メモリの使い方を間違えた場合，実行結果が不可解になるため，デバッグが難しいです．
これを自動的に検出してくれるのが，Valgrindというツールです．
使い方は，デバッグ情報付きでコンパイルして，`valgrind`から実行するだけです．

```
$ gcc -g -O0 program.c
```

```
$ valgrind --leak-check=full ./a.out
[enshu01@eiw03 ~]$ valgrind --leak-check=full ./a.out
==25190== Memcheck, a memory error detector
==25190== Copyright (C) 2002-2012, and GNU GPL'd, by Julian Seward et al.
==25190== Using Valgrind-3.8.1 and LibVEX; rerun with -h for copyright info
==25190== Command: ./a.out
==25190==
==25190== Use of uninitialised value of size 8
==25190==    at 0x3297C43A9B: _itoa_word (in /lib64/libc-2.12.so)
==25190==    by 0x3297C46652: vfprintf (in /lib64/libc-2.12.so)
==25190==    by 0x3297C4F189: printf (in /lib64/libc-2.12.so)
==25190==    by 0x4004FB: main (program.c:10)
==25190==
==25190== Conditional jump or move depends on uninitialised value(s)
==25190==    at 0x3297C43AA5: _itoa_word (in /lib64/libc-2.12.so)
==25190==    by 0x3297C46652: vfprintf (in /lib64/libc-2.12.so)
==25190==    by 0x3297C4F189: printf (in /lib64/libc-2.12.so)
==25190==    by 0x4004FB: main (program.c:10)
==25190==
==25190== Conditional jump or move depends on uninitialised value(s)
==25190==    at 0x3297C450E3: vfprintf (in /lib64/libc-2.12.so)
==25190==    by 0x3297C4F189: printf (in /lib64/libc-2.12.so)
==25190==    by 0x4004FB: main (program.c:10)
==25190==
==25190== Conditional jump or move depends on uninitialised value(s)
==25190==    at 0x3297C45101: vfprintf (in /lib64/libc-2.12.so)
==25190==    by 0x3297C4F189: printf (in /lib64/libc-2.12.so)
==25190==    by 0x4004FB: main (program.c:10)
==25190==
sum = 55
==25190==
==25190== HEAP SUMMARY:
==25190==     in use at exit: 0 bytes in 0 blocks
==25190==   total heap usage: 0 allocs, 0 frees, 0 bytes allocated
==25190==
==25190== All heap blocks were freed -- no leaks are possible
==25190==
==25190== For counts of detected and suppressed errors, rerun with: -v
==25190== Use --track-origins=yes to see where uninitialised values come from
==25190== ERROR SUMMARY: 6 errors from 4 contexts (suppressed: 6 from 6)
```

このレポートによると，プログラムの10行目で初期化されていない（uninitialised）変数が使われたと指摘されています．
