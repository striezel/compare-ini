# Building for Windows with MSYS2

Currently, compare-ini does not support native Windows builds with Microsoft
Visual Studio. However, it can be built on Windows systems with
[MSYS2](https://www.msys2.org/). MSYS2 provides some typical GNU / Linux tools
on Windows operating systems. Those can be used to build botvinnik.

## Prerequisites

### MSYS2

First, download the MSYS2 installer from <https://www.msys2.org/#installation>
and run it. After that is done, open "MSYS2 MinGW x64" from the start menu. This
will open a command prompt window. All following steps are done there.

If you haven't done it yet, update any existing base packages by typing

```bash
pacman -Syu
```

into the prompt, then press enter.

### Build tools

To build the botvinnik from source you need a C++ compiler, CMake, and the Ninja
build system.

It also helps to have Git, a distributed version control system, on your build
system to get the latest source code directly from the Git repository.

All of that can usually be installed be typing

```bash
pacman -S git mingw-w64-x86_64-cmake mingw-w64-x86_64-gcc mingw-w64-x86_64-ninja
```

into the MSYS2 command prompt.

### Getting the source code

Get the source directly from Git by cloning the Git repository and change to
the directory after the repository is completely cloned:

```bash
git clone https://github.com/striezel/compare-ini.git
cd compare-ini
```

That's it, you should now have the current source code on your machine.

### Build process

The build process is relatively easy, because CMake does all the preparations.
Starting in the root directory of the source, you can do the following steps:

```bash
mkdir build
cd build
cmake ../
cmake --build . -j4
```

It may take a moment to build.

After the build is finished, the executable will be available as
`compare-ini.exe` inside the `build` directory.
