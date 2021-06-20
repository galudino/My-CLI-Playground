# My-CLI-Playground

## About
This "playground" is for my own personal use,<br>
for when I want to program C, C++, Objective-C/C++, or Swift in a command-line environment.

## Table of contents
- [My-CLI-Playground](#my-cli-playground)
  - [About](#about)
  - [Table of contents](#table-of-contents)
  - [Prerequisites](#prerequisites)
  - [How to use](#how-to-use)
  - [Creating and using a new target](#creating-and-using-a-new-target)
  - [Removing a target](#removing-a-target)
  - [Script usage](#script-usage)
    - [`add_target`](#add_target)
    - [`remove_target`](#remove_target)
    - [`makebuilds`](#makebuilds)
    - [`./run`](#run)
  - [Xcode/`xcodebuild` users](#xcodexcodebuild-users)

## Prerequisites
This repository uses `cmake`. The `CMakeLists.txt` file requires <b>3.18</b>.

`make` is also required for Unix Makefiles - <br>`cmake` will create the Makefiles for building your targets.
- A C/C++ compiler, `clang` or `gcc` for C and C++ compilation
- A Swift compiler, `swiftc`, for Swift compilation

Please note: Unix Makefiles do not support Swift.<br>
Swift sources must be built using `xcodebuild`.<br>

You will not be able to use the `makebuilds` or `run` scripts provided,<br>
since those will be using Unix Makefiles.

Please see [Xcode/`xcodebuild` users](#xcodexcodebuild-users) if you are interested in using Xcode.

If you would rather use another build system,<br>
invoke `% cmake -help` in the Terminal to review the build systems available to you<br>
on your platform.

[(return to top)](#table-of-contents)<br>

## How to use

There are some scripts provided in this repository:
- `./add_target` creates a subdirectory in `src` with a client source file, additional source file, header file (if applicable),and a local `CMakeLists.txt` file.<br>
    It will also add the name of the subdirectory to the top-level `CMakeLists.txt`, and `makebuilds` will be run to update the build system.

- `./remove_target` does the opposite of `./add_target` -<br>
    it removes a specified subdirectory from `src`, as well as the its entry from the top-level `CMakeLists.txt` file in `src`.<br>
    `makebuilds` will be run to update the build system.

- `./makebuilds` runs CMake and creates a `./build/make` subdirectory, with the following configurations:
    - `Debug`
    - `Release`
    - `MinSizeRel`
    - `RelWithDebInfo`
    These configurations each have their own subdirectory in `./build/make`.

- `./run` runs a target of your choice with a desired configuration.

[(return to top)](#table-of-contents)<br>

## Creating and using a new target

A <b>target</b> is a complete program.<br>

Let's say we want to add a new target, called `MyNewTarget`, written in C++.

`% ./add_target MyNewTarget cpp` will create a new target named `MyNewTarget`, with C++ sources.
- A new directory, `./src/MyNewTarget` will be created, containing the following:
    - `main.cpp`, source file with `main()` function
    - `header.hpp`, header file for declarations, inline functions, directives, etc.
    - `source.cpp`, source file for implementation details
    - `CMakeLists.txt`, instructions local to this subdirectory
    - The top-level `CMakeLists.txt` in `./src` will also be modified to add this new target.

Then,<br>
`cd` into `MyNewTarget` and code away...<br>

To build and run `MyNewTarget`, invoke `% ./run MyNewTarget`<br>
This will run `MyNewTarget` in the `Debug` configuration.

You may specify one of the optional arguments after `./run MyNewTarget`:<br>
    - `Debug`,  i.e. `./run MyNewTarget Debug`<br>
    - `Release`, i.e. `./run MyNewTarget Release`<br>
    - `MinSizeRel`, i.e. `./run MyNewTarget MinSizeRel`<br>
    - `RelWithDebInfo`<br>, i.e. `./run MyNewTarget RelWithDebInfo`<br>
    
[(return to top)](#table-of-contents)<br>

## Removing a target

You could remove `MyNewTarget` yourself, and revise the `CMakeLists.txt` file --<br>
or you can run `% ./remove_target MyNewTarget`.

[(return to top)](#table-of-contents)<br>

## Script usage

### `add_target`
`./add_target [target-name] [language-file-extension]`
- Creates a new directory titled `target-name` to `./src/ and appends the directory to the top-level `CMakeLists.txt` in `./src`.
- i.e. `./add_target MyProgram cpp`
- Supported arguments for `[language-file-extension]`: 
    - `c`
    - `cpp`
    - `swift`
### `remove_target`
`./remove_target [target-name]`
- Removes directory `target-name` from `src` and runs `sed` on `./src/CMakeLists.txt` to remove the `target-name` subdirectory.
### `makebuilds`
`./makebuilds`
- Runs `cmake` and creates a `build/make` directory, with `Debug`, `Release`, `MinSizeRel`, and `RelWithDebInfo` subdirectories.<br>
  The subdirectories above will have folders containing a `Makefile` for each target in this repository.
### `./run`
`./run [target-name] [configuration]`
- Runs `make -C ./build/make/[configuration]/[target-name]`, then runs the executable for `target-name`.

[(return to top)](#table-of-contents)<br>

## Xcode/`xcodebuild` users

Swift sources are not supported by Unix Makefiles.<br>
If you are on macOS, we can use `xcodebuild` instead to stay in the command line.

- First, use `cmake` to create the Xcode project.
  - `% cmake -S ./src -B ./build/xcode -G "Xcode"`
- Navigate to `./build/xcode`
  - `% cd ./build/xcode`
- We will now use `xcodebuild` to build our targets.
  - To build all targets in `Debug` mode:
    - `% xcodebuild`
  - To build all targets in a chosen configuration:
      - `% xcodebuild -configuration [config-name]`
        - `[config-name]` can be:
          - `Debug`
          - `Release`
          - `MinSizeRel`
          - `RelWithDebInfo`
  - To build a specific target in `Debug` mode:
    - `% xcodebuild -target [target-name]`
  - To build a specific target with a chosen configuration:
    - `% xcodebuild -target [target-name] -configuration [config-name]`

Your executable will be in `./build/xcode/[target-name]/[config-name]/`

Invoke `% xcodebuild -help` for a complete list of valid options.

[(return to top)](#table-of-contents)<br>
