#include "../pipex.h"

static void	_closefds(t_data *data, int *fd)
{
	close(fd[0]);
	close(fd[1]);
	close(data->fd_inp);
	close(data->fd_out);
}

void	pipex(t_data *data, char **env, int *fd)
{
	data->pid1 = fork();
	if (data->pid1 < 0)
		error_handler("fork failed", errno);
	if (data->pid1 == 0)
	{
		dup2(data->fd_inp, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		_closefds(data, fd);
		execve(data->cmd1_path, data->cmd1, env);
	}
	data->pid2 = fork();
	if (data->pid2 < 0)
		error_handler("fork failed", errno);
	if (data->pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		dup2(data->fd_out, STDOUT_FILENO);
		_closefds(data, fd);
		execve(data->cmd2_path, data->cmd2, env);
	}
	_closefds(data, fd);
	waitpid(data->pid1, NULL, 0);
	waitpid(data->pid2, NULL, 0);
}
