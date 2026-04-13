CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic

TARGETS=ppid av prompt split run5 shell _which printenv_env env_addr my_getenv path_dirs path_list my_setenv my_unsetenv

all: $(TARGETS)

ppid: 0-getppid.c
	$(CC) $(CFLAGS) $< -o $@

av: 0-av.c
	$(CC) $(CFLAGS) $< -o $@

prompt: 1-readline.c
	$(CC) $(CFLAGS) $< -o $@

split: 2-commandline.c
	$(CC) $(CFLAGS) $< -o $@

run5: 3-fork_wait_execve_5.c
	$(CC) $(CFLAGS) $< -o $@

shell: 4-super_simple_shell.c
	$(CC) $(CFLAGS) $< -o $@

_which: 5-which_path.c
	$(CC) $(CFLAGS) $< -o $@

printenv_env: 6-printenv_environ.c
	$(CC) $(CFLAGS) $< -o $@

env_addr: 7-env_vs_environ.c
	$(CC) $(CFLAGS) $< -o $@

my_getenv: 8-getenv_custom.c
	$(CC) $(CFLAGS) $< -o $@

path_dirs: 9-path_print_dirs.c
	$(CC) $(CFLAGS) $< -o $@

path_list: 10-path_linked_list.c
	$(CC) $(CFLAGS) $< -o $@

my_setenv: 11-setenv_custom.c
	$(CC) $(CFLAGS) $< -o $@

my_unsetenv: 12-unsetenv_custom.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(TARGETS)

.PHONY: all clean
