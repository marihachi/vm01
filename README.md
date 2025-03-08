# vm01
An experiment for stack machine based VM 01.

## Build (Linux)
System required:
- cmake
- clang or gcc

Run:
```bash
./build.sh
```

Clean up for the build directory:
```bash
./clean.sh
```

## Run vm01 (Linux)
```shell
./build/vm01 ./program.bin
```

## Build (Windows)
コンソールはVisual Studio付属のDeveloper Command Promptを使用してください。\
コンソールから`build.bat`を呼び出すことでビルドできます。

## Run vm01 (Windows)
コマンドプロンプトを開きます。\
vm01.exeが生成された場所に移動し、以下のコマンドを実行します。
```shell
vm01.exe ../../../program.bin
```
リポジトリ直下のプログラムが実行され、実行結果が表示されます。

## License
MIT
