---
layout: post
title:  "Mac OS X 環境で C 言語を書くために"
date:   2016-03-31 16:29:55 +0900
---

## はじめに

この記事は，皆さんが自身の Mac OS X 環境で C 言語を書くためにどのような準備をすれば良いかを説明するものです．
OS X でバリバリ開発してるよという方にはこの記事は必要ありません．

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

## 環境構築が終わったら

環境構築が終わったら後はプログラムを書くだけですが，皆さんは演習室の計算機でどんなエディタを使用しているでしょうか．
本講義で推奨されているエディタである Emacs は，実は OS X に付属しています．
試しにターミナルで `emacs` と入力してみましょう．演習室で見慣れた画面になると思います．
UNIX 環境での開発になれるために，OS X でもまずはこの Emacs をしばらく使ってみることをおすすめします．

他に UNIX 環境でよく使われるエディタとして Vim があります．
こちらも OS X に付属していますので，ターミナルで `vim` と入力し，ファイルの編集をしてみてください．
Vim を触るのが初めてな方であれば，おそらく文字の入力すら困難なことでしょう．
こんな一見使いづらいと思われるようなエディタですが，沢山練習して十分に習熟することで他のエディタでは得られないような編集速度を手に入れることができます．
詳しくは参考資料に譲りますが，UNIX 環境でプログラミングをするなら，このような世界があることを知っておくことも重要です．

ターミナル上で古めかしいエディタを使いたくないという方もいることでしょう．
OS X には沢山のテキスト編集アプリが存在しますが，C 言語を書くならそれを支援してくれるプログラミング用のエディタを使いましょう．
筆者は次のようなエディタを推奨します．

- [Atom](https://atom.io/)
- [Sublime Text](https://www.sublimetext.com/)

公式サイトは英語ですが，日本語で使い方を解説する記事は多数存在します．もし興味を持ったら自分で検索してみてください．

## 参考資料

- [Xcode Command Line Tools - Yosemite - Install](http://railsapps.github.io/xcode-command-line-tools.html)
- [Vim 101: A Beginner's Guide to Vim | Linux.com](https://www.linux.com/learn/tutorials/228600-vim-101-a-beginners-guide-to-vim)
- 『新しいLinuxの教科書』（大角，SBクリエイティブ）
    - 7 章で Vim の基本操作を解説しています
