---
layout: page
title: gnuplotの使い方
---
グラフ表示ソフトgnuplotの使い方の簡単な説明です。
詳細な情報を知りたいときは以下のホームページを参照してください。

[Gnuplotの第一歩](http://lagendra.s.kanazawa-u.ac.jp/ogurisu/manuals/gnuplot-intro/)


## 起動と終了

端末で 

`% gnuplot`

と入力すると、gnuplotが起動します。起動後の表示 

`gnuplot> `

が、gnuplotのコマンドプロンプトです。 
終了するには gnuplot のコマンドプロンプトで、

`gnuplot> quit`

と入力します。

## 関数のプロット
まず，関数$y=sin(x)$をプロットしてみましょう。
gnuplot のコマンドプロンプトで、

`gnuplot> plot sin(x)`

と入力すると画面に$y=sin(x)$のグラフが表示されます。
次に2次関数$y=x+3x^2$をプロットしてみましょう。

`gnuplot> plot x + 3*x**2`

と入力すると画面に$y=x+x^2$のグラフが表示されます。
$x$の$n$乗は `x**n` と入力します。

## データのプロット

ファイルに保存されているデータをプロットする場合には

`gnuplot> plot 'filename'`

と入力します。(`filename`はプロットしたいファイルの名前です。)
データファイルには1行目に$x$座標、2行目に$y$座標が保存されて
いなければなりません。

試しに`/opt/local/enshu/data-2002/saisyou.dat`をプロットしてみましょう。
まず、gnuplot を起動する前に

`% cp /opt/local/enshu/data-2002/saisyou.dat .`

と入力してデータファイルを自分のディレクトリにコピーします。
次に gnuplot を起動して

`gnuplot> plot 'saisyou.dat'`

と入力するとデータが点でプロットされます。
折れ線グラフでプロットする場合には

`gnuplot> plot 'saisyou.dat' with lines`

と入力します。

## 複数のグラフのプロット

複数のグラフを同時にプロットする場合にはコンマで区切って入力します。
$y=sin(x)$と$y=cos(x)$をプロットするには

`gnuplot> plot sin(x), cos(x)`

と入力します。
$y=sin(x)$を点で、$y=cos(x)$を線でプロットするには

`gnuplot> plot sin(x) with points, cos(x) with lines`

と入力します。
ファイルに保存されたデータをプロットする場合も同様に

`gnuplot> plot 'filename1' with points, 'filename2 with lines`

などと入力します。


## グラフの印刷

プロットしたグラフをプリンタで印刷するには、まず

`gnuplot> plot sin(x)`

などのコマンドでグラフを画面上にプロットします。
画面上のグラフが印刷したいグラフであることを確認してから

`gnuplot> set terminal postscript`

`gnuplot> set output 'plot.ps'`

`gnuplot> replot`

と入力します。すると自分のディレクトリに`plot.ps`という名前のファイル
が作成されます。
次にgnuplotを終了して

`% lpr plot.ps`

と入力するとプリンターに出力されます。

## カンマ区切りのファイルの利用

`gnuplot> set datafile separator ","`

入力することにより、カンマ区切りのデータファイルをplotできます。

