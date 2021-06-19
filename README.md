# My-CLI-Playground

## About
This "playground" is for my own personal use, 
for when I want to program C, C++, or Swift in a command-line environment.

## How to use:

There are some scripts provided in this repository:
- `./add_target` creates a subdirectory with a client source file, additional source file, and a header file (if applicable).<br>
    It will also add the subdirectory to the top-level `CMakeLists.txt`, and `makebuilds` will be run to update the build system.

- `./remove_target` does the opposite of `./add_target` -<br>
    it removes a specified subdirectory from this parent directory, as well as the `CMakeLists.txt` file.<br>
    `makebuilds` will be run to update the build system.

- `./makebuilds` runs CMake and creates a `build/make` subdirectory, with the following configurations:
    - `Debug`
    - `Release`
    - `MinSizeRel`
    - `RelWithDebInfo`

- `./run` runs a target of your choice with a desired configuration.

## Creating and using a new C++ target

`% ./add_target MyNewTarget cpp` will create a new target named `MyNewTarget`, with C++ sources.<br>

`cd` into `MyNewTarget` and code away...<br>

To build and run `MyNewTarget`, do `% ./run MyNewTarget`<br>
No argument after `MyNewTarget` means it will run the `Debug` configuration.

You may specify the following arguments after `MyNewTarget`:<br>
    - `Debug`
    - `Release`
    - `MinSizeRel`
    - `RelWithDebInfo`

## Removing the target

You could remove `MyNewTarget` yourself, and revise the `CMakeLists.txt` file --<br>
or you can run `% ./remove_target MyNewTarget`.

