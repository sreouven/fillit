#include "libft.h"
#include "fillit.h"

#define BUF_SIZE 545

/*
   OPEN_FILE ouvre le .fillit et remplit le buffer de travail.
   return len(char) du buffer
 */
int		open_file(char **argv, char *buf)
{
		int		ret;
		int		fd;

		if ((fd = open(*argv, O_RDONLY)) == -1)
				return (0);
		ret = read(fd, buf, BUF_SIZE);
		if (ret > 545 || ret == -1)
				return (0);
		buf[ret] = '\0';
		if (close(fd) == -1)
				return (0);
		return (ret);
}

/*
   CHECK_CHAR verifie l'integrite du buffer au niveau des char . # \n
0: erreur, 1: reussite
 */
int		check_char(char *buf, int size_buf)
{
		while(*buf)
		{
				if (*buf != '.' && *buf != '#' && *buf != '\n')
						return (0);
				buf++;
		}
		return (1);
}

/*
   CHECK_FORMAT verifie le format du fichier : bloc de 4.\n et \n
 */
int		check_format(char *buf, int	size_buf)
{
		int		x;
		int		y;

		size_buf--;
		while (size_buf > 0)
		{
				y = 0;
				while(y < 4)
				{
						x = 0;
						while(x < 4)
						{
								size_buf--;
								if(size_buf < 0 || buf[size_buf] == '\n')
										return (0);
								x++;
						}
						size_buf--;
						if(size_buf > 0 && buf[size_buf] != '\n')
								return(0);
						y++;
				}
				size_buf--;
		}
		return (1);
}

/*
   FT_OPEN_CHECK_FILE ouvre et verifie integrite du format du fichier
0: error, 1: reussite
 */
char		*ft_open_check_file(char **argv)
{
		char	buf[BUF_SIZE + 1];
		char	*buf_work;
		int		len_buffer;

		if ((len_buffer = open_file(argv, buf)) == 0)
				return (0);
		if (!(check_char(buf, len_buffer)))
				return (0);
		if (!(check_format(buf, len_buffer)))
				return(0);
		if(!(buf_work = malloc(sizeof(char) * len_buffer)))
				return (NULL);
		ft_strcpy(buf_work, buf);
		return (buf_work);
}

/*************************************************************************************************************/
int		check_piece(int	ligne, int colonne, char tetri[][colonne])
{
		int		i;
		int		j;
		int		ok;
		int		nbh;

		ok = 0;
		j = 0;
		nbh = 0;
		while (j <= ligne - 1)
		{
				i = 0;
				while (i <= colonne - 2)
				{
						if (tetri[j][i] == '#')
						{
								ok += check_link(j, i, tetri);
								nbh++;
						}
						i++;
				}
				j++;
		}
		return ((ok < 6 || nbh != 4) ? 0 : 1);
}

int		check_link(int j, int i, char tetri[][5])
{
		int		link;

		link = 0;
		if(tetri[j][i - 1] == '#' && (i - 1 >= 0))
				link++;
		if(tetri[j][i + 1] == '#' && (i + 1 < 4))
				link++;
		if(tetri[j + 1][i] == '#' && (j + 1 < 4))
				link++;
		if(tetri[j - 1][i] == '#' && (j - 1 >= 0))
				link++;
		return(link);
}

t_tetri		*new_piece(char *buffer, int ipiece)
{
		t_tetri	*new;
		int		i;
		int		j;
		int		k;

		j = 0;
		k = 21 * ipiece;
		if(!(new = malloc(sizeof(t_tetri))))
				return (NULL);
		while(j < 4)
		{
				i = 0;
				while(i < 5)
				{
						new->block[j][i] = buffer[k];
						k++;
						i++;
				}
				j++;
		}
		new->index = ipiece;
		new->next = NULL;
		return (new);
}

void	ft_listadd(t_tetri **alst, t_tetri *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_tetri		*fill_list(char *buffer, int sizebuf)
{
		t_tetri		*list;
		int			ipiece;
		int			max;

		ipiece = 0;
		max = (sizebuf / 21 + 1);
		if(!(list = malloc(sizeof(t_tetri*) * max)))
						return (NULL);
		list = NULL;
		while (ipiece < max)
		{
				ft_listadd(&list, new_piece(buffer, ipiece));
				if (!(check_piece(4, 5, list->block)))
				{
						return (NULL);
				}
				ipiece++;
		}
		return (list);
}
/*************************************************************************************************************/
/* backtracking + print_resulst */

char	**init_tab(int sqrt)
{
		char	tab[][];

		while(j < sqrt)
		{
				while(i < sqrt)
				{
						tab[j][i] = '.';
						i++;
				}
				tab[j][i] = '\0';
				j++;
		}
		return(tab);
}

void	print_tab(char ***tab)
{

}
/*************************************************************************************************************/

void	ft_error(void)
{
		write(2, "error\n", 6);
}

/***************** MAIN ************************************/

int		main(int argc, char **argv)
{
		t_tetri		*ptr_list;
		char		*buffer;

		if (argc != 2)
		{
				write(2, "usage : ./fillit file_name\n", 27);
				return (1);
		}
		if(!(buffer = ft_open_check_file(&argv[1])))
		{
				ft_error();
				return (1);
		}
		ptr_list = fill_list(buffer, ft_strlen(buffer));
		if(ptr_list == NULL)
		{
				ft_error();
				return (1);
		}
		return (0);
}
