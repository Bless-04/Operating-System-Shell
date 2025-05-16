# Operating System Shell

A basic shell that targets both Windows And Ubuntu written in C++ for COSC 439 - Operating Systems course.

## Features

This shell implements the following commands:

- **cd**: Change directory
- **clear**: Clear the terminal
- **environ**: Display environment variables
- **echo**: Display a line of text
- **help**: Display help information
- **pause**: Pause the shell
- **quit**: Quit the shell
- **ls**: List directory contents
- **pwd**: Print working directory
- **cat**: Display file contents
- **mkdir**: Create directories
- **rmdir**: Remove empty directories
- **rm**: Remove files
- **cp**: Copy files
- **mv**: Move/rename files
- **touch**: Create empty files or update timestamps
- **wc**: Word count (lines, words, characters)
- **grep**: Search text patterns in files

## Building the Project

The project is built using C++. To build the shell:

1. Ensure you have a C++ compiler installed like g++
2. Navigate to the project directory
3. Compile the main file:
```bash
g++ 439shell.cpp -o 439shell
```

## Usage

### Interactive Mode
Run the compiled shell:
```bash
./439shell
```

The shell will start with a prompt where you can enter commands. 
```
>> [command] [arguments...]
```

### Command Line Mode
You can also run individual commands directly from the command line without actually starting the shell.
```bash
./439shell [command] [arguments...]
```

Example:
```bash
./439shell help
./439shell ls
./439shell mkdir new_directory
./439shell cat file.txt
```

## Command Reference

### Directory Operations
- `mkdir <directory>`: Create a new directory
- `rmdir <directory>`: Remove an empty directory
- `ls`: List directory contents
- `pwd`: Print current working directory

### File Operations
- `touch <file>`: Create an empty file or update timestamp
- `rm <file>`: Remove a file
- `cp <source> <destination>`: Copy files
- `mv <source> <destination>`: Move or rename files

### File Content Operations
- `cat <file>`: Display file contents
- `wc <file>`: Count lines, words, and characters
- `grep <pattern> <file>`: Search for text patterns

## Project Structure

- `src/`: Contains implementation files for each command
- `src/Windows/`: Windows-specific command implementations
- `src/Unix/`: Unix-specific command implementations
- `src/Models/`: Shell model classes. Also holds functions that should work no matter the platform
- `439shell.cpp`: Main shell implementation

## System Requirements

- C++11 or later
- Unix-like system (Linux, macOS, or WSL)
- Windows
- Standard C++ libraries



