#include "../pipex.h"
#include <unistd.h>

void	error_handler(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

char	*find_exec(char **cmd, char **dirs)
{
	char	*path;
	char	*tmp;

	while (*dirs)
	{
		tmp = ft_strjoin(*dirs, "/");
		path = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		dirs++;
	}
	return (NULL);
}

char	*_get_path(char **envp)
{
	char	*path;

	while (*envp)
	{
		path = ft_strnstr(*envp, "PATH=", 5);
		if (path != NULL)
			break ;
		envp++;
	}
	return (path + 5);
}

static void	_init_files(char **av, t_data *data)
{
	data->fd_inp = open(av[1], O_RDONLY);
	if (!data->fd_inp)
		error_handler("cant open input file");
	data->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!data->fd_out)
		error_handler("error with output file");
}

static void	_init_data(char **av, t_data *data, char **env)
{
	char	**all_env_paths;

	data->cmd1 = ft_split(av[2], ' ');
	data->cmd2 = ft_split(av[3], ' ');
	data->env_path = _get_path(env);
	all_env_paths = ft_split(data->env_path, ':');
	data->cmd1_path = find_exec(data->cmd1, all_env_paths);
	data->cmd2_path = find_exec(data->cmd2, all_env_paths);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		fd[2];
	int		pid1;
	int		pid2;

	if (ac != 5)
		error_handler("wrong parameters");
	_init_files(av, &data);
	_init_data(av, &data, env);
	if (pipe(fd) == -1)
		error_handler("pipe failed");
	pid1 = fork();
	if (pid1 < 0)
		error_handler("fork failed");
	if (pid1 == 0)
	{
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			close(fd[0]);
			close(fd[1]);
			error_handler("error redirecting to stdout");
		}
		execve(data.cmd1_path, data.cmd1, env);
	}
	pid2 = fork();
	if (pid2 < 0)
		error_handler("fork failed");
	if (pid2 == 0)
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			close(fd[0]);
			close(fd[1]);
			error_handler("error redirecting to stdin");
		}
		execve(data.cmd2_path, data.cmd2, env);
	}
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close(fd[0]);
	close(fd[1]);
	close(data.fd_inp);
	close(data.fd_out);
}
