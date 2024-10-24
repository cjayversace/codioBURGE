Quash: A Custom Command Line Shell

Charlie J. Seigler
Sydney Stokes

---

Introduction

The Quash (Quick Shell) project implements a custom command-line shell, designed to replicate key features of widely-used UNIX shells like `bash` and `sh`. Quash supports various functionalities including built-in commands, process management, signal handling, background task execution, I/O redirection, and command piping. These features were developed incrementally with a modular design approach to ensure the shell remains clear, robust, and scalable. This document provides an overview of the design decisions, explanations of core components, and documentation of the shell’s key functionalities.

---

Design Choices

1. Modular Design and Helper Functions
Each major feature—such as command parsing, built-in commands, piping, and redirection—is implemented as a dedicated function. This modularity ensures code organization, making each function focused and improving readability. Functions like `changeDir`, `getWorkingDir`, and `echoFunc` manage specific built-in commands, while `cmd_exec` handles simple commands as well as complex pipeline executions.  

Advantages: This structure allows for easy maintenance, testing, and debugging, as each function operates independently. Adding new features, like additional built-in commands, is straightforward and can be done with minimal disruption to existing code.

2. Input Parsing and Tokenization
User input is split into tokens using the `strtok` function, with whitespace as delimiters. Tokenization enables the identification of commands and arguments, the separation of piped commands, and detection of special symbols like `&`, `<`, `>`, and `|`.  

Special Symbol Handling: Input (`<`) and output (`>`) redirection, as well as piping (`|`), are detected during parsing, allowing for their proper handling within the corresponding functions.  
Quoted Strings: The `parseQuotes` function manages quoted strings (e.g., `"Hello World"`), stripping the quotes to ensure commands like `echo "Hello World"` work as expected.

3. Built-in Commands
The shell implements several built-in commands (`cd`, `pwd`, `env`, `echo`, `setenv`, and `exit`), which are managed through specific functions. The `cmd_exec` function checks whether a command is built-in and, if so, calls the respective function without creating a new process.  

Environment Variables: The `getEnv` and `setEnv` functions allow users to retrieve and modify environment variables using the standard `getenv` and `setenv` functions.

4. Process Management via Forking
For external (non-built-in) commands, the shell forks a child process through `cmd_exec`, where `execvp` replaces the process image with the requested command. If `execvp` fails, an error is displayed using `perror`.

Background Processes: Commands with the `&` symbol at the end are executed in the background. `cmd_exec` sets a background flag and skips waiting for the child process to finish, allowing the shell to accept new commands immediately.

5. Signal Handling and Timeout
SIGINT Handling: The `signal_handler` function catches the `SIGINT` signal (e.g., Ctrl+C). Instead of terminating both the shell and child processes, `SIGINT` only affects the foreground child process, letting users interrupt commands without exiting the shell.  
Process Timeout: A secondary child process serves as a timer, monitoring the duration of a running process. If the process exceeds a predefined time limit (e.g., 10 seconds), the timer terminates it by sending a `SIGINT` signal.

6. I/O Redirection
Input (`<`) and output (`>`) redirection is handled by the `handleIO` function, which redirects input and output to the specified files using `dup2`. For example, `cat < input.txt` directs input from `input.txt` into `stdin`, while `echo Hello > output.txt` writes output to `output.txt`.

Error Handling: If a file cannot be opened for reading or writing, `handleIO` prints an error message and exits.

7. Command Piping
Piping Implementation (`|`): Piped commands are detected and split into subcommands using `executePipedCommands`, which creates the necessary pipes between commands. Each command runs in its process, with `dup2` connecting the output of one process to the input of the next.

Error Handling and Resource Management: Pipe file descriptors are closed after use in both child and parent processes. Each child process in the pipeline is awaited by the parent to ensure proper cleanup and resource management.

---

Function Documentation

Main Functions
- `main`: This is the shell's main loop. It prints the prompt, reads user input, tokenizes commands, and calls either `cmd_exec` for external commands or appropriate built-in functions.
- `cmd_exec`: Manages command execution. For non-built-in commands, it forks a child process, handles background processing, I/O redirection, and process timeouts. When pipes are present, `executePipedCommands` is used.
- `executePipedCommands`:*Sets up command pipelines using multiple pipes. `dup2` is used to connect input/output between processes, allowing smooth data flow across commands.

Built-in Command Functions
- `changeDir`: Changes the current working directory.
- `getWorkingDir`: Prints the current working directory.
- `getEnv`: Displays environment variables or retrieves a specific one when given an argument.
- `echoFunc`: Prints arguments or retrieves environment variables if the argument starts with `$`.
- `setEnv`: Sets or updates an environment variable.
- `exitShell`: Terminates the shell session.

Utility Functions
- `parseQuotes`: Strips quotes from command arguments, allowing string literals to be processed correctly (e.g., `echo "Hello World"`).
- `timeout_process`: Monitors processes and terminates them if they exceed the allowed runtime.
- `handleIO`: Detects and manages input/output redirection symbols using `dup2` to handle file descriptors.

Signal Handling
- `signal_handler`: Manages `SIGINT` signals, directing them to the current foreground process to prevent the shell from terminating.
