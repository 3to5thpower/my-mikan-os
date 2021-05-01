# my-mikan-os

## 環境構築
### プロジェクト外部に必要なディレクトリ
 - `$HOME/edk2`
 - `$HOME/osbook`

osbookディレクトリは[このリポジトリ](https://github.com/uchan-nos/mikanos-build)をそのまま配置する。  
edk2は同リポジトリのREADMEに従って導入する。
なお、edk2内のMikanLoaderPkgのシンボリックリンク先はこのプロジェクトの同フォルダにする。

## 実行手順
kernelディレクトリ内のMakefileを利用する。
 - QEMUで実行：`make run`
 - USB(Eドライブ)にインストールする: `make install`
 
