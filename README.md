# clang-tidy plugin demo

This repository contains the slides for the [Large Scale Refactoring using Clang-Tidy](C++_Refactoring_Using_Clang_Tidy.pdf) presentation that was presented at [Montréal C++ Meetup](https://www.meetup.com/fr-FR/cppmtl/) on November 24th 2022.

The code for the custom Clang-Tidy check is in the [src/custom_check](src/custom_check) folder.

The sample code used during the presentation is in the [src/sample_code_for_presentation](src/sample_code_for_presentation) folder.

The slide deck is available [here](C++_Refactoring_Using_Clang_Tidy.pdf).

## Quick Start

To compile the custom Clang-Tidy check used in the presentation, you need clang-tidy-14 (or more recent) installed on your machine.

### 1a. Easy Setup

On a an OS that packages clang-tidy-14 (like Ubuntu 22.04), you could perform the following commands to install the required packages:

```shell
sudo apt update
sudo apt install cmake clang-14 clang-tidy-14 libclang-14-dev
```

### 1b. More Involved Setup

You could install clang-tidy from the source code. See [https://github.com/coveooss/clang-tidy-plugin-example](https://github.com/coveooss/clang-tidy-plugin-example) for more information on how to do this.

### 2. Compile the custom Clang-Tidy plugin

Use this command if you install Clang-Tidy from packages:

```
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=/usr/bin/clang++-14 -B build -S .
cmake --build build
```

You will have to change the path to the compiler if you built Clang from the source code.

### 3. Check that the custom plugin can be loaded by Clang-Tidy

Enter the following command to see if the custom check is in the list of all checks:

```shell
clang-tidy-14 --checks=* --load build/lib/libReviseLibV2Check.so --list-checks | grep revise
```
 If the plugin is working, you should see `revise-libv2-api` in the console.

### 4. Commands used in the presentation

Clang-Tidy requires a compilation database (a `compile_commands.json` file) to work properly. When building the code step 2 above, we used the `./build` folder. Because of this, we must add the option `-p build` to the clang-tidy command-line options to specify where the `compile_commands.json` file could be found.

In the presentation the full path to the sample files (src/sample_code_for_presentation/) was not given.

In the presentation we removed the `-*,` at the beginning of the `--checks` option. This is needed to disable all other checks.

Here is the detailed list of commands that were used durring the presentation:

```
clang-tidy-14 --checks="-*,bugprone*" -p build src/sample_code_for_presentation/example1.cpp
clang-tidy-14 --checks="-*,modernize-loop-convert" -p build --fix src/sample_code_for_presentation/example2.cpp
clang-tidy-14 --checks="performance-*" -p build --fix src/sample_code_for_presentation/example3.cpp
run-clang-tidy-14 -export-fixes=fixes.yaml -p build
clang-apply-replacements-14 .
clang-14 -cc1 -ast-dump src/sample_code_for_presentation/patate.cpp
clang-query-14 -p build src/sample_code_for_presentation/example4.cpp
clang-tidy-14 --checks=-*,revise-* -p build --load build/lib/libReviseLibV2Check.so src/sample_code_for_presentation/example4.cpp
clang-tidy-14 --checks=-*,revise-* -p build --load build/lib/libReviseLibV2Check.so --fix src/sample_code_for_presentation/example4.cpp
```

## Thanks

Thanks to Stephen Kelly for writing his amazing [Exploring Clang Tooling](https://devblogs.microsoft.com/cppblog/exploring-clang-tooling-part-1-extending-clang-tidy/) blog in 2018. This help a lot demystifying how to write custom Clang-Tidy checks. References to his blog and videos are available at the end of the slide deck.

Thanks to Kevin Lalumière for his work on how to build a Clang-Tidy check in a plugin (dynamic-link library). See his [clang-tidy plugins](https://github.com/coveooss/clang-tidy-plugin-example) project for details.