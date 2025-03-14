#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include "./libft/libft.h"

typedef struct s_data
{
	int		fd_inp;
	int		fd_out;
	char	**cmd1;
	char	**cmd2;
	char	*env_path;
	char	*cmd1_path;
	char	*cmd2_path;
}			t_data;

void	error_handler(char *error);

#endif
