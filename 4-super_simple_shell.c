#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * run_cmd - fork and execute one full path command
 * @cmd: command full path
 * @env: process environment array
 *
 * Return: 0 on success, 1 on failure
 */
int run_cmd(char *cmd, char **env)
{
	pid_t child_pid;
	int status;
	char *argv[2];

	/* Create a child process to run the command safely. */
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return (1);
	}
	if (child_pid == 0)
	{
		/* This shell version supports one full-path command, no arguments. */
		argv[0] = cmd;
		argv[1] = NULL;
		/* Replace child image with target program and inherited env. */
		if (execve(argv[0], argv, env) == -1)
		{
			perror("execve");
			return (1);
		}
	}
	/* Parent waits so execution order stays deterministic. */
	if (wait(&status) == -1)
	{
		perror("wait");
		return (1);
	}
	return (0);
}

/**
 * main - simple shell running full path commands without arguments
 * @ac: argument count
 * @av: argument vector
 * @env: process environment array
 *
 * Return: 0 on success
 */
int main(int ac, char **av, char **env)
{
	char *line;
	size_t len;
	ssize_t nread;

	/* Keep full signature while explicitly ignoring ac and av. */
	(void)ac;
	(void)av;
	/* getline will allocate and resize this buffer automatically. */
	line = NULL;
	len = 0;
	while (1)
	{
		/* Interactive prompt. */
		printf("#cisfun$ ");
		fflush(stdout);
		/* Read one command line from standard input. */
		nread = getline(&line, &len, stdin);
		if (nread == -1)
			break;
		/* Strip trailing newline to obtain a clean command path. */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';
		/* Ignore empty entries and prompt again. */
		if (line[0] == '\0')
			continue;
		/* Execute command via fork/execve/wait pipeline. */
		if (run_cmd(line, env) != 0)
		{
			free(line);
			return (1);
		}
	}
	/* Free getline-managed buffer before normal exit. */
	free(line);
	return (0);
}
