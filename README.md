# Mini Shell Implementation

## Project Overview
The **Mini Shell** project is a custom shell, developed in C, that replicates key functionalities of the Bash shell. It allows users to execute command lines, manage system resources, and seamlessly interact with the operating system. The shell implements several core features that provide a simplified yet powerful command-line interface.

## Key Features

- **Command Line Execution**: 
  - Execute commands inputted by users.
  - Parses and handles built-in commands as well as external executables.

- **Resource Management**: 
  - Launch processes and manage them.
  - Supports input/output redirection and background jobs.

- **Command Parsing**: 
  - A robust parser breaks down commands into tokens and identifies options and arguments.

- **Job Control**: 
  - Supports both foreground and background process execution for efficient task management.

- **Environment Variables**: 
  - Set, modify, and unset environment variables to customize the shell environment.

- **Error Handling**: 
  - Comprehensive error handling for invalid commands and execution errors with clear feedback.

- **Command History**: 
  - Maintains a history of previously executed commands, allowing users to recall and reuse them to improve workflow.

## Technologies Used

- **C**: 
  - Core programming language used to implement the mini shell.

## Project Outcome
The Mini Shell successfully emulates the core features of the Bash shell, providing a functional command-line interface. It demonstrates:
- Command-line parsing techniques.
- Process management capabilities.
- Understanding of Unix-like system environments.

This project offers valuable insights into designing and implementing shell environments, enhancing both programming and system-level knowledge.

## How to Run

1. Clone the repository:
   ```bash
   git clone git@github.com:moelkama/minishell.git
   cd minishell
   ./minishell
