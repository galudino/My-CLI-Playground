# My-CLI-Playground

## About
This "playground" is for my own personal use,<br>
for when I want to program C, C++, or Swift in a command-line environment.

## Table of contents
* [Prerequisites](#prerequisites)
* [How to use](#how-to-use)
* [Creating and using a new target](#creating-and-using-a-new-target)
* [Removing a target](#removing-a-target)
* [Script usage](#script-usage)

## Prerequisites
This repository uses `cmake`. The `CMakeLists.txt` file requires <b>3.17.3</b>.
`make` is also required - `cmake` will create the Makefiles for building your targets.
- A C/C++ compiler, `clang` or `gcc` for C and C++ compilation
- A Swift compiler, `swiftc`, for Swift compilation

## How to use:

There are some scripts provided in this repository:
- `./add_target` creates a subdirectory with a client source file, additional source file, and a header file (if applicable).<br>
    It will also add the subdirectory to the top-level `CMakeLists.txt`, and `makebuilds` will be run to update the build system.

- `./remove_target` does the opposite of `./add_target` -<br>
    it removes a specified subdirectory from this parent directory, as well as the `CMakeLists.txt` file.<br>
    `makebuilds` will be run to update the build system.

- `./makebuilds` runs CMake and creates a `./build/make` subdirectory, with the following configurations:
    - `Debug`
    - `Release`
    - `MinSizeRel`
    - `RelWithDebInfo`
    These configurations each have their own subdirectory in `./build/make`.

- `./run` runs a target of your choice with a desired configuration.

## Creating and using a new target

A <b>target</b> is a complete program.<br>

Let's say we want to add a new target, called `MyNewTarget`, written in C++.

`% ./add_target MyNewTarget cpp` will create a new target named `MyNewTarget`, with C++ sources.
- A new directory, `./MyNewTarget` will be created, containing the following:
    - `main.cpp`, source file with `main()` function
    - `header.hpp`, header file for declarations, inline functions, directives, etc.
    - `source.cpp`, source file for implementation details
    - `CMakeLists.txt`, instructions local to this subdirectory
    - The top-level `CMakeLists.txt` file will also be modified to add this new target.

Then,<br>
`cd` into `MyNewTarget` and code away...<br>

To build and run `MyNewTarget`, invoke `% ./run MyNewTarget`<br>
This will run `MyNewTarget` in the `Debug` configuration.

You may specify one of the optional arguments after `./run MyNewTarget`:<br>
    - `Debug`,  i.e. `./run MyNewTarget Debug`<br>
    - `Release`, i.e. `./run MyNewTarget Release`<br>
    - `MinSizeRel`, i.e. `./run MyNewTarget MinSizeRel`<br>
    - `RelWithDebInfo`<br>, i.e. `./run MyNewTarget RelWithDebInfo`<br>

## Removing a target

You could remove `MyNewTarget` yourself, and revise the `CMakeLists.txt` file --<br>
or you can run `% ./remove_target MyNewTarget`.

## Script usage

### `add_target`
`./add_target [target-name] [language-file-extension]`
- Creates a new directory titled `target-name` and appends directory to top-level `CMakeLists.txt`
- i.e. `./add_target MyProgram cpp`
- Supported arguments for `[language-file-extension]`: 
    - `c`
    - `cpp`
    - `swift`
### `remove_target`
`./remove_target [target-name]`
- Removes directory `target-name` from this directory and runs `sed` on `./CMakeLists.txt` to remove the `target-name` subdirectory.
### `makebuilds`
`./makebuilds`
- Runs `cmake` and creates a `build/make` directory, with `Debug`, `Release`, `MinSizeRel`, and `RelWithDebInfo` subdirectories.<br>
  The subdirectories above will have folders containing a `Makefile` for each target in this repository.
### `./run`
`./run [target-name] [configuration]`
- Runs `make -C ./build/make/[configuration]/[target-name]`, then runs the executable for `target-name`.
