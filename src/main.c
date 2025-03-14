/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: turmoil <jtsiros93@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:51:14 by turmoil           #+#    #+#             */
/*   Updated: 2025/03/13 13:31:31 by turmoil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
    Parse Arguments: Extract file1, cmd1, cmd2, and file2 from argv.
    Open Files:
        Open file1 for reading. O_RDONLY
        Open file2 for writing. O_WRONLY | O_CREAT | O_TRUNC, 0644)
    Create a Pipe using pipe().
    Fork Two Processes:
        Child 1:
            Redirect file1 to stdin.
            Redirect pipe write-end (fd[1]) to stdout.
            Execute cmd1 using execve().
        Child 2:
            Redirect pipe read-end (fd[0]) to stdin.
            Redirect file2 to stdout.
            Execute cmd2 using execve().
    Close Unused File Descriptors.
    Wait for Both Child Processes.

3. Required System Calls

You'll need:

    open(), close(), read(), write() → For file handling.
    pipe(), dup2(), fork() → For creating pipes and handling processes.
    execve() → To execute commands.
    waitpid() → To wait for child processes.		*/


#include "../pipex.h"

int	main(int ac, char **av, char **env)
{
	int		fd1[2];
	int		fd2[2];
	pid_t	pid;


	while (**env)
	{
		printf("%s\n", *env);
		env++;
	}


	if (ac < 5)
		exit(perror("wrong parameters"), EXIT_FAILURE);

	if (!fd[0] = open(av[1], O_RDONLY))
		exit(perror("Error opening reading file"), EXIT_FAILURE);
	if (!fd[1] = open(av[5], O_WRONLY | O_CREAT | O_APPEND, 0644)
		exit(perror("Error creating output file"), EXIT_FAILURE);

	if (pipe(fd) == -1)
        exit(perror("pipe failed"), EXIT_FAILURE);
	
    if (pid = fork() == -1)
        exit(perror("fork failed"), EXIT_FAILURE);

	if (pid == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
		{
			perror("Error redirecting file to stdin");
			close(fd[0]);
			exit(EXIT_FAILURE);
		}
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("Error redirecting file to stdin");
			close(fd[1]);
			exit(EXIT_FAILURE);
		}
	}

	close(fd[0]);
	close(fd_[1]);
}
