## Minishell
A small reimplementation of bash in `C`. This was a group project, part of the Codam school
curriculum.

## Installation

Make sure to have `make`, `clang` and `zlib1g-dev` installed

```bash
git clone git@github.com:pmerku/minishell.git
cd minishell
make -j
```

You can now launch minishell with `make exec` or `./minishell`.

## Features
Supported commands:
- `echo` with option `-n`
- `cd` with relative or absolute path
- `pwd` without options
- `export` without options
- `unset` without options
- `env` without options and without arguments
- `exit` without options
- `;` command separation like in bash
- `\'` and `\"` like in bash (no multiline commands)
- `<`, `>` and `>>` redirections (no file descriptor aggregation)
- `|` pipes like in bash
- `$ENV` environmental variables like in bash
- `$?` command exit code like in bash
- `ctr-D`, `ctrl-C` and `ctrl-\` like in bash

## Screenshots
![alt tex](https://github.com/pmerku/minishell/raw/pmerku_branch/images/minishell.gif "minishell gif")

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## Updates
If we will have time one day, we would like to add `<<` redirections, history, line editing, auto-completion,
`&&` and `||` with priority parenthesis and wildcard `*`.
