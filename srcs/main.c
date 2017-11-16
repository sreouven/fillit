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
   CHECK_CHAR verifie l'integrite du buffer au niveau des char . # \n et %4#
0: erreur, 1: reussite
 */
int		check_char(char *buf, int size_buf)
{
		int		nbh;

		nbh = 0;
		while(*buf)
		{
				if (*buf != '.' && *buf != '#' && *buf != '\n')
						return (0);
				if (*buf == '#')
						nbh++;
				buf++;															//pas forcement neilleur endroit
		}
		return ((nbh % 4 == 0) ? 1 : 0);
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
int		ft_open_check_file(char **argv)
{
		char	buf[BUF_SIZE + 1];
		int		len_buffer;


		if ((len_buffer = open_file(argv, buf)) == 0)
				return (0);
		if (!(check_char(buf, len_buffer)))
				return (0);
		if (!(check_format(buf, len_buffer)))
				return(0);
		ft_putstr(buf); 																			// debug
		return (1);
}

/*************************************************************************************************************/
int		check_piece(char **tetri)  // ne gere pas 5 cas
{
		int		i;
		int		j;
		int		nbh;
		int		ok;

		nbh = 0;
		ok = 0;
		j = 0;
		while (j < 3)
		{
				i = 0;
				while (i < 3)
				{
						if (tetri[j][i] == '#')
						{
								nbh++;
								if ((tetri[j][i + 1] == '#') || (tetri[j + 1][i] == '#'))
										ok++;
						}
						i++;
				}
				j++;
		}
		return ((nbh == 4 && ok == 3) ? 1 : 0);
}

t_tetri		add_piece(t_tetri *piece, char *block, int ipiece)
{
		t_tetri		*newpiece;

		if(!(newpiece = malloc(sizeof(t_tetri))))
				return (NULL);
		newpiece->block = block;
		newpiece->index = ipiece;

}

t_tetri		*fill_list(char *buffer, int sizebuf)
{
		t_tetri		*piece;
		int			ipiece;
		int			max;

		ipiece = 0;
		piece = NULL;
		max = (sizebuf / 21 + 1);
		while (ipiece < max)
		{
			add_piece(piece, ft_strsub(buffer -= 20, 20), (max - 1));
			check_piece();
			buffer--;
			ipiece++;
		}
		return (ptr_list);
}
/*************************************************************************************************************/
/* backtracking + print_resulst */
/*************************************************************************************************************/

/*
   MESSAGE ERREUR
 */
void	ft_error(void)
{
		write(2, "error\n", 6);
}

/***************** MAIN ************************************/

int		main(int argc, char **argv)
{
		t_tetri		*ptr_list;

		if (argc != 2)
		{
				write(2, "usage : ./fillit file_name\n", 27);
				return (1);
		}
		if (!(ft_open_check_file(&argv[1])))
		{
				ft_error();
				return (1);
		}
		ptr_list = fill_list(
		return (0);
}
