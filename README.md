# An assignment repository
This repository is a C++ workspace supported by a cross-platform Docker-based dev container. The header (`.h`) files should be placed under the `include/` folder, while the implementation (`.cpp`) files should be placed under the `src/` folder.

## Option 1: GitHub Codespaces (Recommended)

Codespaces runs a fully configured development environment in your browser — no installs needed.

1. On your repository page, click the green **Code** button → **Codespaces** tab → **Create codespace on main**.
2. Wait about a minute for the environment to load.
3. You're ready — the terminal, compiler, and debugger are all set up.

> **Free tier:** GitHub gives every account 60 free Codespaces hours per month, which is more than enough for this course. Just remember to **stop your Codespace** when you're done working. You can do this from the bottom-left status bar in VS Code (→ "Stop Current Codespace"), or by visiting [github.com/codespaces](https://github.com/codespaces) and stopping it from there.
>
> **Need more hours?** Apply for the [GitHub Student Developer Pack](https://education.github.com/pack) using your `.edu` email. Once approved, your account is upgraded to Pro, which includes 90 Codespaces hours per month.

## Option 2: Local Development (VS Code + Docker)

If you prefer to work offline or have used up your Codespaces hours, you can run the same environment locally.

**One-time setup:**
1. Install the [Docker desktop application](https://www.docker.com/products/docker-desktop/). You don't need to do anything with Docker other than installing it on your operating system.
2. Install [Visual Studio Code](https://code.visualstudio.com).
3. In VS Code, install the **Dev Containers** extension.

**Opening the project:**
Clone this repository and open its folder in Visual Studio Code. If you see a popup with an option to "Reopen in Container," click that. Otherwise, click on the Dev Containers icon at the bottom left corner and select "Reopen in Container." You can also type F1 to launch VS Code's Command Palette and search for and select "Dev Containers: Reopen in Container." This will reopen this repository in the dev container where all development environment tools (compiler, linker, debugger, etc.) are available.

## Build
Inside the assignment folder created by the command “git clone”, run the following commands:
```
cd build
cmake ..
```
You only need to run these commands once.

**Note:** If your `.cpp` file is in the `src/` folder and its name starts with `alg_`, it will be included automatically. Otherwise, you must add it manually to the correct `add_executable(...)` line in `CMakeLists.txt`, listing it with the other source files (space-separated). Don’t forget to re-run `cmake ..` whenever you change `CMakeLists.txt`.

## Compile and test
From inside the build folder (run `cd build` if needed), run the following commands to compile and test your code:

```
make tester
./tester1
./tester2
```

Make sure all the test cases/assertions pass.

You may run a subset of the test cases by passing an argument tag.

```
./tester1 [tag1]

./tester2 [tag1]
```

This will run all the test cases tagged with `[tag1]`.

## Compile and run
From inside the build folder (run `cd build` if needed), run the following commands to compile and run your programs:

```
make prog1
./prog1  

make prog2
./prog2 
``` 

**NOTE**: All files should be read from or written to the `resources` folder.

## Debugging

This project includes a pre-configured debugger setup in `.vscode/launch.json`, with one entry each for `prog1`, `prog2`, `tester1`, and `tester2`. Before debugging, CMake must be configured with debug symbols enabled. From the `build/` folder, run:

```
cmake -DCMAKE_BUILD_TYPE=Debug ..
```

This replaces the plain `cmake ..` from the Build section above — if you already ran that, re-run this command instead. It only needs to be done once (or after switching build types). Then to debug a program:

1. Open its source file in VS Code and click in the left margin to set breakpoints.
2. Open the **Run and Debug** panel (or press `F5`).
3. Select the configuration matching what you want to debug from the dropdown (e.g., **Debug prog1**).
4. Press the green play button — VS Code will compile and launch the debugger automatically.
