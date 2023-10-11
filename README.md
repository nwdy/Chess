# Chess
An implementation of Chess game using SFML framework and Minimax & Alpha-Beta-pruning algorithm.

## Introduction
SFML (Simple and Fast Multimedia Library) is a versatile multimedia library widely used for developing multimedia applications and games. This guide will help you install SFML on both Windows and Linux operating systems.

## Installation on Windows


### Requirements

1. **SFML**: You need to install the SFML library before running this project. Visit the official SFML website to download the Windows installation package: [SFML Downloads](https://www.sfml-dev.org/download.php).

2. **GNU Make**: Install GNU Make to use the Makefile. You can use MinGW to get GNU Make. Download MinGW-w64 from the official website: [MinGW-w64 Downloads](https://mingw-w64.org/doku.php).

3. **MinGW**: Install MinGW to get the GCC (GNU Compiler Collection) compiler on Windows. You may choose the x86_64 version for 64-bit support.

### Compilation and Execution

**Install SFML**: Unpack the SFML installation package and copy the files into your project directory. Ensure that the `SFML-x.x.x` directory (version of SFML you downloaded) contains the `include` and `lib` directories.

2. **Edit Makefile**: Open the `Makefile` and update the path to your SFML directory. Replace `SFML_DIR` with the path to the folder containing SFML on your computer.

3. **Make Sure you set the SFML_PATH variable to the root path of the SFML library**: 
    ```
    set SFML_PATH=C:\path\to\sfml
    ```

4. **Compile the Project**: Open Command Prompt or PowerShell and navigate to the project directory:

    ```bash
    cd /path/to/MySFMLProject
    ```

    Then run the make command:

    ```bash
    make
    ```

    This command will compile the source code and create the executable program.

5. **Run the Program**:

    ```bash
    ./chess
    ```

    Alternatively, you can run the program by executing the generated executable file.

### Directory Structure

- `src/`: Contains C++ source files.
- `include/`: Contains header files.
- `build/`: Build directory, where object files and executable files are stored.
- `Makefile`: Makefile.




## Installation on Linux (Ubuntu)
1. Open the Terminal.
2. Use the following command to install the SFML package from the official Ubuntu repository:

```bash
sudo apt-get install libsfml-dev
```

**Note**: The Makefile in the provided source code is configured for macOS and may not run correctly on Windows or Linux. Please select an suitable makefile in the ./guide directory and replace the makefile in the folder which include source code to ensure the program runs on Windows and Linux.

### Build via Makefile and run
```bash
make
./chess
```