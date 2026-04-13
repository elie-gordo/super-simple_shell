CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic

PROGRAMS=ppid av prompt run5 shell whichpath printenv_env env_addr
FUNC_OBJECTS=2-commandline.o 8-getenv_custom.o 9-path_print_dirs.o 10-path_linked_list.o 11-setenv_custom.o 12-unsetenv_custom.o

all: programs functions

programs: $(PROGRAMS)

functions: $(FUNC_OBJECTS)

ppid: 0-getppid.c
	$(CC) $(CFLAGS) $< -o $@

av: 0-av.c
	$(CC) $(CFLAGS) $< -o $@

prompt: 1-readline.c
	$(CC) $(CFLAGS) $< -o $@

run5: 3-fork_wait_execve_5.c
	$(CC) $(CFLAGS) $< -o $@

shell: 4-super_simple_shell.c
	$(CC) $(CFLAGS) $< -o $@

whichpath: 5-which_path.c
	$(CC) $(CFLAGS) $< -o $@

printenv_env: 6-printenv_environ.c
	$(CC) $(CFLAGS) $< -o $@

env_addr: 7-env_vs_environ.c
	$(CC) $(CFLAGS) $< -o $@

2-commandline.o: 2-commandline.c
	$(CC) $(CFLAGS) -c $< -o $@

8-getenv_custom.o: 8-getenv_custom.c
	$(CC) $(CFLAGS) -c $< -o $@

9-path_print_dirs.o: 9-path_print_dirs.c
	$(CC) $(CFLAGS) -c $< -o $@

10-path_linked_list.o: 10-path_linked_list.c
	$(CC) $(CFLAGS) -c $< -o $@

11-setenv_custom.o: 11-setenv_custom.c
	$(CC) $(CFLAGS) -c $< -o $@

12-unsetenv_custom.o: 12-unsetenv_custom.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(PROGRAMS) $(FUNC_OBJECTS)

re: clean all

.PHONY: all programs functions clean re
