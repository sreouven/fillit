#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>


# include <stdio.h>
typedef struct	s_tetri
{
		char	block[4][5];
		int		index;
		struct s_tetri	*next;
}				t_tetri;

void			ft_error_msg(void);
int				open_file(char **argv, char *buf);
int		check_link(int j, int i, char tetri[j][i]);

#endif
