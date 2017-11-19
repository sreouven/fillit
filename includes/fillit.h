#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_tetri
{
		char	block[4][5];
		int		index;
		t_tetri	*next;
}				t_tetri;

void			ft_error_msg(void);
int				open_file(char **argv, char *buf);

#endif
