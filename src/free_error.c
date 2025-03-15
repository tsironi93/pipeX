#include "../pipex.h"

void	error_handler(char *error, int exit_flag)
{
	perror(error);
	exit(exit_flag);
}

void	free2d(char **a)
{
	while (*a)
	{
		free(*a);
		a++;
	}
	free(a);
}

void	freedata(t_data *data)
{
	free2d(data->cmd1);
	free2d(data->cmd2);
	free(data->cmd1_path);
	free(data->cmd2_path);
}
