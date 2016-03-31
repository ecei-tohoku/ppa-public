---
layout: post
title:  "Mac OS X 環境で C 言語を書くために"
date:   2016-03-31 16:29:55 +0900
---

## はじめに

この記事は，皆さんが自身の Mac OS X 環境で C 言語を書くためにどのような準備をすれば良いかを説明するものです．
Windows 環境の方は [Windows環境でC言語を書くために]({{site.baseurl}}{% post_url 2016-03-24-gcc_for_windows %}) を参照してください．
また，OS X でバリバリ開発してるよという方にはこの記事は必要ありません．

## 環境構築

OS X は UNIX をベースとしているので，演習室の計算機と同じような感覚で使えますが，
残念なことに，C 言語のコンパイルに必要な gcc を含む開発者向けのツールが付属していません．
この節では，それらをインストールする手順を説明します．

と言っても，OS X で開発者向けのツールをインストールする方法はとても簡単です（Windows と違って！）．
まず，App Store で Xcode をインストールしてください．
インストールが完了したら，ターミナルを起動します（ターミナルは Finder を開いて「アプリケーション」→「ユーティリティ」→「ターミナル」で起動できます）．
そして，次のコマンドを入力してください．

```
$ xcode-select --install
```

インストールするかどうか尋ねられるので，インストールを選択します．
後はしばらく待てば gcc などのインストールが完了します．
終わったら，試しに次のコマンドを入力してみましょう．

```
$ gcc -v
```

おそらく次のような出力が得られるでしょう．

```
Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk/usr/include/c++/4.2.1
Apple LLVM version 7.0.2 (clang-700.1.81)
Target: x86_64-apple-darwin15.3.0
Thread model: posix
```

筆者の環境とはバージョン番号などの細かい違いがあるかもしれませんが，このように表示されたら gcc を正常にインストールできたことになります．

## 参考資料

- [Xcode Command Line Tools - Yosemite - Install](http://railsapps.github.io/xcode-command-line-tools.html)
