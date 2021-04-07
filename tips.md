---
layout: page
title: デバッグのためのTips
---

エラーが出たときや合格にならないときは，質問する前に，以下の項目に当てはまらないか確認して下さい．

# コンパイルエラー（警告含む）
* 宣言されていない変数を使用するとき
   * 最初の使用の行に「変数が宣言されていません」というエラーが出る.
* 宣言されていない関数を使用するとき
   * 使用の行に「関数の暗黙的な宣言です」という警告が出る.
* 宣言されている変数を使用しないとき
   * 全部のプログラムの中にまったく使わなかったら、変数の宣言の行に「使用されない変数です」という警告が出る.
* 設定されている変数を使用しないとき
   * 設定してもまったく使わなかったら、変数の宣言のラインに「 変数が設定されましたが使用されていません」というエラーが出る.
* { と } の数は合わないとき
   * 「expected declaration」や「expected statement」や「expected identifier」など出る.
* ( と ) の数は合わないとき
   * 「expected statement before ‘)’ token」や「expected ‘)’ before ‘;’ token」など文字が欠落している行に出る.
* 「;」が忘れたとき
   * 忘れた行に「expected ‘;’」というエラーが出る.
* 関数が宣言するときの引数の数と使用するときの引数の数が合わないとき
   * 「関数への引数が多すぎます」か「関数への引数が少なすぎます」というエラーが関数を使用の行に出る.

# 実行時エラー
* タイムオーバーになっているとき
    * 無限ループになっていないか．ループの終了条件がおかしい，初期化していない，インクリメント／デクリメントしていない，など．
    * 問題によっては実行時間を厳しく設定しているので，その場合もタイムオーバーが出ます．
* 配列インデックスオーバー（例：`int a[100]; a[100] = 1;`）
    * Segmentation Faultで落ちる．
    * Segmentation Faultはないが，他の変数が上書きされて挙動不審になる．
* 0，‘0’，’\0’の違い
    * 0はint型で，整数としてのゼロ．
    * ‘0’はchar型で，文字としてのゼロ．printf文などでゼロを出力したいときなどに使う．十進数では48（ASCIIコード表を参照）．
    * ’\0’はchar型で，NULL（ヌル）文字と呼ばれる．文字列の終了十進数では0（ASCIIコード表を参照）．
    * 数字をchar型cとして入力したとき，int型iに変換するときには，`i = c-‘0’;`のようにする．
    * NULL文字の判定で‘0’を使ってしまうと無限ループになったりする．
* 配列確保のとき，NULL文字（’\0’）分もカウントに入れないと，配列インデックスオーバーになる可能性あり．
* ループで文字列を作るときなどは，NULL文字（’\0’）を最後に入れないと，挙動不審になる可能性あり．

# 合格にならない
* 仕様をもう一度確認しましょう．例えば…
    * 範囲外の結果（例：0<x<100）に対してエラー出力等していない．
    * 最終行の改行を出力していない．
    * 余計なスペースを出力している（特に行の先頭／末尾）．