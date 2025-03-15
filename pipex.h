#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "./libft/libft.h"
# include <errno.h>

typedef struct s_data
{
	int		fd_inp;
	int		fd_out;
	char	**cmd1;
	char	**cmd2;
	char	*env_path;
	char	*cmd1_path;
	char	*cmd2_path;
	int		pid1;
	int		pid2;
}			t_data;

void	error_handler(char *error, int exit_flag);
void	pipex(t_data *data, char **env, int *fd);
void	free2d(char **a);
void	freedata(t_data *data);

#endif
