# vm01
An experiment for stack machine based VM (01).

## 推奨環境
- Windows 10
- Visual Studio 2022

主にWindowsを対象としていますが、cmakeだけなんとかすれば他のOSでも動かせるはずです。

## ビルド(Windows)
コンソールはVisual Studio付属のDeveloper Command Promptを使用してください。\
コンソールから`build.bat`を呼び出すことでビルドできます。

## 実行
コマンドプロンプトを開きます。\
vm01.exeが生成された場所に移動し、以下のコマンドを実行します。
```shell
vm01.exe ../../../program.bin
```
リポジトリ直下のプログラムが実行され、実行結果が表示されます。

## License
MIT
