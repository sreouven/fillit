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
   CHECK_FORMAT verifie le format du fichier
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
		ft_putstr(buf); // debug
		return (1);
}

/*
   MESSAGE ERREUR
 */
void	ft_error(void)
{
		ft_putendl_fd("error", 2);
}

int		main(int argc, char **argv)
{

		if (argc != 2)
		{
				ft_putendl_fd("usage : ./fillit file.fillit", 2);
				return (1);
		}
		if (!(ft_open_check_file(&argv[1])))
		{
				ft_error();
				return (1);
		}
		return (0);
}