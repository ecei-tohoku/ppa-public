---
layout: page
title: Windows環境でC言語を書くために
---

## はじめに

このドキュメントは，プログラミング演習Aの課題に家で取り組みたいあなたのためのものです．

「家のパソコン(Windows)だとプログラムが書けないから，課題をするために計算機室に行かないといけない」と思っていませんか？
実はそんなことはありません．

このドキュメントに沿って設定をしていけば，家でもプログラミングが出来るようになりますよ．

## なぜ設定が必要なのか
実は，計算機室のマシン(UNIX環境)と違い，Windowsには標準で`gcc`(コンパイラ)が付属していません．
また，Emacsやgeditなどのエディタも付いていません．

そのため，**あなたが**これらをインストールしてやる必要があります．

このドキュメントは，これらのソフトウェアのインストール作業を解説するためのものです．

さあ，それでは設定をしていきましょう．

## MSYS2をインストールする

[MSYS2](https://sourceforge.net/projects/msys2/)というソフトウェアがあります．

これは，Windows環境でUNIX環境のコマンドを利用できるようにするためのものです．
MSYS2をインストール後，これを使ってgccをインストールするのが全体の流れとなっています．

まずはMSYS2を以下のURLからダウンロードしましょう．

URL: [https://msys2.github.io/](https://msys2.github.io/)

![Msys2 Download]({{ site.baseurl }}/images/windows_gcc/msys2.png)

ダウンロード用のリンクが二つありますが，ここでは自分のOSのbit数にあったものをダウンロードすればいいでしょう．
bit数がわからない場合は，[自分のパソコンが 32 ビット版か 64 ビット版かを確認したい](https://support.microsoft.com/ja-jp/kb/958406)を参考に調べてください．

ダウンロードが終わったら，インストール作業に移りましょう．

![Msys2 install 01]({{ site.baseurl }}/images/windows_gcc/01.png)

「次へ」をクリック

![Msys2 install 02]({{ site.baseurl }}/images/windows_gcc/02.png)

特に何も変更する必要はないので，「次へ」をクリックしましょう

![Msys2 install 03]({{ site.baseurl }}/images/windows_gcc/03.png)

ここも「次へ」でいいでしょう．インストールが始まります．

![Msys2 install 04]({{ site.baseurl }}/images/windows_gcc/04.png)

しばらく待ちましょう

![Msys2 install 05]({{ site.baseurl }}/images/windows_gcc/05.png)

「完了」をクリックして，インストールを終えましょう．これであなたのパソコンにMSYS2がインストールされました．

## gcc(コンパイラ)をインストールする

先ほどインストールした`MSYS2 Shell`を起動します．ここからはこのアプリケーションを使って作業をしていきます．

![Msys2 install 06]({{ site.baseurl }}/images/windows_gcc/06.png)

スタートメニューから，`MSYS2 Shell`を選択すればよいでしょう．

すると，計算機室のマシン(UNIX)で見慣れた，あの黒い画面(端末)が立ち上がります．(もしかしたら，計算機室のものは白い画面かもしれませんが）

この画面では，計算機室のマシンのように`ls`や`mkdir`や`cd`や`pwd`を実行することができます．試してみるといいでしょう．

これから，この黒い画面にいくつかコマンドを打ち込んでいきます．
コマンドがよく分からなくても，心配は要りません．
全部コピー&ペーストで済みますよ．

まず，`pacman -Sy`を実行してください．

![Msys2 install 07]({{ site.baseurl }}/images/windows_gcc/07.png)

黒い画面に`pacman -Sy`と打ち込んで，Enterを押すだけです．

コマンドが終了したら，次は`pacman --needed -S bash pacman pacman-mirrors msys2-runtime`を実行してください．

![Msys2 install 08]({{ site.baseurl }}/images/windows_gcc/08.png)

ここでも同じように，コマンドを打ち込んでEnterでOKです．途中，「インストールを行いますか？ [Y/n]」と聞かれたら，yを打ってEnterを押しましょう．

コマンドが終了したら，**一度ウィンドウを閉じて，MSYS2 Shellを終了しましょう**．その後，もう一度スタートメニューから立ち上げてください．(これを怠ると，この次の作業がうまく行きません！)

次に，`pacman -Su`を実行しましょう．

![Msys2 install 09]({{ site.baseurl }}/images/windows_gcc/09.png)

先ほどと同様，ここでもインストールの確認がされますが，yを打ってEnterを押してください．

またコマンドが終了したら，**もう一度ウィンドウを閉じて，MSYS2 Shellを終了しましょう**．その後，もう一度立ち上げてください．(先ほど同様，重要なことです)

最後に，`pacman -S gcc`を実行しましょう．
もう分かるでしょうが，このコマンドでgccをインストールします．

![Msys2 install 10]({{ site.baseurl }}/images/windows_gcc/10.png)

(確認されたら，yを打ってEnterを押しましょう．)

お疲れ様でした．これでgccのインストール作業は終了です．
これであなたのパソコンでC言語をコンパイルすることができるようになりました．

## C言語をコンパイルしてみる

ここでは例として，以下の`hello.c`をコンパイル，実行してみます．

```
#include <stdio.h>

int main(void) {
    printf("Hello, World!");
}
```

(非常に簡単なプログラムですが，例としては十分です)

このファイルを，`C:\msys64\home\(ユーザー名)`(環境によっては`C:\msys32\home\(ユーザー名)`)にコピーします．

![Msys2 install 11]({{ site.baseurl }}/images/windows_gcc/11.png)

こんな風になれば良いでしょう．(`hello.c`がありますね)

その後，`MSYS2 Shell`を開いて，`gcc hello.c -o hello`を実行しましょう．

コンパイルが終わったら，コマンド`./hello.exe`を実行してみます．

![Msys2 install 12]({{ site.baseurl }}/images/windows_gcc/12.png)

無事に**Hello, World!**が出力され，コンパイルと実行がうまく行ったことが確認できましたね．

やっとWindowsでもgccが使えるようになりました．
これであなたのプログラムもコンパイルすることができますね．

さあ，プログラミング演習の課題に取り組みましょう！

## おまけ Windowsで使えるエディタ

計算機室のマシン(UNIX)にはエディタとしてEmacs,Vim,geditなどがインストールされていますが，当然Windowsにはこれらのソフトウェアは付属していません．

幸い，EmacsとVimに関してはWindows版がありますので，これらをインストールすれば良いでしょう．

* [NTEmacs / Emacs for Windows](http://cha.la.coocan.jp/doc/NTEmacs.html)
* [Vim - KaoriYa](http://www.kaoriya.net/software/vim/)

geditに関しては，同等の機能を持つものとして，[サクラエディタ](http://sakura-editor.sourceforge.net/download.html)などがあります．

自分にとって使いやすいものを使いましょう!

## 参考資料

* [MSYS2 installer](https://msys2.github.io/)
    * MSYS2インストーラはここからダウンロードできます
* [MSYS2 installation](https://sourceforge.net/p/msys2/wiki/MSYS2%20installation/)
    * 本文に載せたコマンド(`pacman -Sy`など)の意味が気になる場合は，これを読むと良いでしょう．
