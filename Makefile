CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic

TARGETS=ppid av prompt split run5 shell _which printenv_env env_addr my_getenv path_dirs path_list my_setenv my_unsetenv

all: $(TARGETS)

ppid: pid_ppid_getppid.c
	$(CC) $(CFLAGS) $< -o $@

av: args_av.c
	$(CC) $(CFLAGS) $< -o $@

prompt: read_line.c
	$(CC) $(CFLAGS) $< -o $@

split: split_line.c
	$(CC) $(CFLAGS) $< -o $@

run5: fork_wait_execve_5.c
	$(CC) $(CFLAGS) $< -o $@

shell: super_simple_shell.c
	$(CC) $(CFLAGS) $< -o $@

_which: which_path.c
	$(CC) $(CFLAGS) $< -o $@

printenv_env: printenv_environ.c
	$(CC) $(CFLAGS) $< -o $@

env_addr: env_vs_environ.c
	$(CC) $(CFLAGS) $< -o $@

my_getenv: getenv_custom.c
	$(CC) $(CFLAGS) $< -o $@

path_dirs: path_print_dirs.c
	$(CC) $(CFLAGS) $< -o $@

path_list: path_linked_list.c
	$(CC) $(CFLAGS) $< -o $@

my_setenv: setenv_custom.c
	$(CC) $(CFLAGS) $< -o $@

my_unsetenv: unsetenv_custom.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
