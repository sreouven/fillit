#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>


# include <stdio.h>

# define BUF_SIZE 545

typedef struct	s_tetri
{
		char			block[4][5];
		int				map[4][2];
		int				index;
		struct s_tetri	*next;
}						t_tetri;

typedef struct 	s_data
{
		int 	map[27][4][2];
		int		nb_tetri;
		int		size;
		char	**result;
}				t_data;
char		*ft_open_check_file(char **argv);
void    ft_xy(t_tetri *piece);
void			ft_error_msg(void);
int				open_file(char **argv, char *buf);
int		check_link(int j, int i, char tetri[j][i]);
int		ft_sqrt(int nb);
int		ft_is_free(t_data *data, int c_tetri, int i, int j);
void	ft_map_cleaner(t_data *data);
int				ft_fillit(t_data *data, int tetri, int i, int j);
int		ft_map_creator(t_data *data);
void	ft_remove_last(t_data *data, int c_tetri, int i, int j);
void	ft_put_map(t_data *data);
t_tetri		*fill_list(char *buffer, int sizebuf);

#endif
