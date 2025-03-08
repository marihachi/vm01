# vm01
An experiment for stack machine based VM 01.

## for Linux

### System required
- cmake
- C compiler (clang recommended)

### Build
1. Configure
```bash
cmake -S src -B build
```

2. use make commands:
```bash
cd build
make clean
make all
```

### Run vm01
```shell
cd build
./vm01 ../program.bin
```

## for Windows

### System required
- Visual Studio

### Build
1. Configure
```shell
cmake -S src -B build
```
2. Open the .sln file in the build directory to start Visual Studio.
3. Rebuild the solution in the Visual Studio.

### Run vm01
Open a Command Prompt.\
Go to the directory where vm01.exe was generated, And execute the following command:
```shell
vm01.exe ../../../program.bin
```

## License
MIT
