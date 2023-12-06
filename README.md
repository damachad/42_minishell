# Minishell 🐚
A simple shell implementation that takes bash as a reference.

## Features 🚀

- **Prompt:** Display a prompt when waiting for a new command.
- **History:** Have a working command history.
- **Command Execution:** Search and launch the right executable based on the PATH variable or using a relative or absolute path.
- **Quote Handling:** Do not interpret unclosed quotes or special characters that are not required by the subject.
- **Single Quotes:** Handle single quotes to prevent interpretation of meta-characters in the quoted sequence.
- **Double Quotes:** Handle double quotes to prevent interpretation of meta-characters, except for `$` (dollar sign).
- **Redirections:** Implement various redirections, such as `<`, `>`, `<<`, and `>>`.
- **Pipes:** Implement pipes (`|`) for command pipelines.
- **Environment Variables:** Handle expansion of environment variables (`$`) to their values.
- **$?:** Handle `$?` to expand to the exit status of the most recently executed foreground pipeline.
- **Ctrl-C, Ctrl-D, Ctrl-\:** Implement behavior similar to bash for these control signals.
- **Builtins:** Implement several built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

## Getting Started 🛠️

To get started with Minishell, follow these steps:

1. Clone the repository: `git clone https://github.com/your-username/minishell.git`
2. Navigate to the project directory: `cd minishell`
3. Build the project: `make`
4. Run Minishell: `./minishell`

## Usage Example 📝

```sh
$ ./minishell
$ ls -l
$ echo "Hello, Minishell!"
$ export MY_VARIABLE="42"
$ echo $MY_VARIABLE
```

### Documentation
- [Lexer](https://spicy-dirigible-2b6.notion.site/Lexer-5a3b48397dda4492a2c4364f710255aa?pvs=4)
- [Parser](https://www.notion.so/Parser-7b271a7bd7e549269bb571e692bf7637)
