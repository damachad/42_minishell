# Minishell 🐚
A simple shell implementation that takes bash as a reference.

## Features 🚀

- **Prompt:** Displays a prompt when waiting for a new command.
- **History:** Has a working command history.
- **Command Execution:** Searches and launched the right executable based on the PATH variable or using an absolute path.
- **Single Quotes:** Handles single quotes to prevent interpretation of meta-characters in the quoted sequence.
- **Double Quotes:** Handles double quotes to prevent interpretation of meta-characters, except for `$` (dollar sign).
- **Redirections:** Implements various redirections, such as `<`, `>`, `<<`, and `>>`.
- **Pipes:** Implements pipes (`|`) for command pipelines.
- **Environment Variables:** Handles expansion of environment variables (`$`) to their values.
- **$?:** Handles `$?` to expand to the exit status of the most recently executed foreground pipeline.
- **Ctrl-C, Ctrl-D, Ctrl-\:** Implements behavior similar to bash for these control signals.
- **Builtins:** Implements several built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.   
   
**Note:** It does not interpret unclosed quotes or special characters that are not mentioned above.

## Getting Started 🛠️

To get started with Minishell, follow these steps:

1. Clone the repository: `git clone https://github.com/damachad/42_minishell.git`
2. Navigate to the project directory: `cd minishell`
3. Build the project: `make`
4. Run Minishell: `./minishell`

## Usage Example 📝

```sh
$ ls -l
$ echo "Hello, Minishell!"
$ << EOF cat | wc
$ export MY_VARIABLE="42"
$ echo $MY_VARIABLE
```

### Documentation
- [Lexer](https://spicy-dirigible-2b6.notion.site/Lexer-5a3b48397dda4492a2c4364f710255aa?pvs=4)
- [Parser](https://www.notion.so/Parser-7b271a7bd7e549269bb571e692bf7637)
