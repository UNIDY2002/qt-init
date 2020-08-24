# qt-init: A CLI application for initializing CMake Qt projects

## Dependencies

- Windows
- Qt SDK
- Compatible MinGW
- CMake

## Usage

```
qt-init <ProjectName> <QtSDKPath> <MinGWBinPath>
```

### How to find the `QtSDKPath` and `MinGWBinPath`?

For instance, the structure of my Qt installation directory is as follows:

```
Qt
 |- 5.15.0
 |   |- mingw81_64
 |   |- sha1s.txt
 |
 |- Tools
     |- mingw810_64
     |- QtCreator
```

where `Qt` is located at `C:\ `.

Then the `QtSDKPath` should be `C:/Qt/5.15.0/mingw81_64` while the `MinGWBinPath` should be `C:/Qt/Tools/mingw810_64/bin`.

And a possible example of the command could be:

```
qt-init QtTest C:/Qt/5.15.0/mingw81_64 C:/Qt/Tools/mingw810_64/bin
```

Furthermore, you can now simply open the generated project with CLion and have fun!

## FAQ

### The code simply won't compile

Please make sure you have set the compatible MinGW.

### `Process finished with exit code -1073741701` or `libgcc_s_seh-1.dll not found`

Please make sure you have `${QtSDKPath}/bin` added to your PATH.