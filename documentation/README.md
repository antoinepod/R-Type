# R-Type

**The goal of this project :**

# Game

# Compilation

It is a cross-platform built system:

- **Linux**: it must generate a `Makefile` to be able to build the project

```
mkdir build && cd build
cmake .. -G "Unix Makefiles"
cmake --build .
./bomberman
```

- **Windows**: it must generate a Visual Studio solution `.sln` (will be tested with Visual Studio 2022)

```
mkdir build && cd build
cmake .. -G "Visual Studio 17"
cmake --build .
bomberman.exe
```

