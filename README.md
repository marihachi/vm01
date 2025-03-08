# vm01
An experiment for stack machine based VM 01.

## for Linux

### System required
- cmake
- clang or gcc

### Build
Run:
```bash
./build.sh
```

Clean up for the build directory:
```bash
./clean.sh
```

### Run vm01
```shell
./build/vm01 ./program.bin
```

## for Windows

### System required
- Visual Studio

### Build
Use the Developer Command Prompt of Visual Studio.\
You can build an binary by calling `build.bat` in the console.

### Run vm01
Open an Command Prompt.\
Go to the directory where vm01.exe was generated, And execute the following command:
```shell
vm01.exe ../../../program.bin
```

## License
MIT
