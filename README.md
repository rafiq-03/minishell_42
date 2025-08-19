# Minishell

This project is a custom implementation of a shell, similar to `bash`. It is written in C and is a project for the 42 school curriculum.

This shell can parse and execute simple commands, including built-in commands, and it supports features like pipes and I/O redirections.

## Features

*   **Command Execution**: Execute simple commands with arguments.
*   **Built-in Commands**:
    *   `echo` with `-n` option
    *   `cd` with relative or absolute path
    *   `pwd`
    *   `export`
    *   `unset`
    *   `env`
    *   `exit`
*   **Pipes (`|`)**: Chain multiple commands together.
*   **I/O Redirections**:
    *   `<` redirect input
    *   `>` redirect output
    *   `<<` here document
    *   `>>` append redirected output
*   **Environment Variables**: Handling of environment variables (`$VAR`).
*   **Signal Handling**: Handles `Ctrl+C` (SIGINT) and `Ctrl+\\` (SIGQUIT) like `bash`.

## How to Use

1.  **Clone the repository and navigate to the directory.**

2.  **Compile the project:**
    ```bash
    make
    ```

3.  **Run the shell:**
    ```bash
    ./minishell
    ```

## Project Structure

The project is divided into the following main components:

*   **`Libft`**: A custom library of C functions used throughout the project.
*   **`lexer`**: Responsible for tokenizing the input string. It breaks the input into a sequence of tokens, such as words, pipes, and redirection operators.
*   **`parser`**: Takes the list of tokens from the lexer and builds a command structure. This includes handling syntax, expanding environment variables, and organizing commands.
*   **`builtin`**: Implements the shell's built-in commands (e.g., `cd`, `echo`, `env`).
*   **`execution`**: Executes the parsed commands. It manages processes, pipes, and I/O redirections.
*   **`minishell.c`**: The main file containing the entry point and the main loop of the shell.
*   **`minishell.h`**: The main header file with all the necessary data structures and function prototypes.

## Authors

*   [**@rmarzouk**](https://github.com/rmarzouk)
*   [**@mskhairi**](https://github.com/mskhairi)
