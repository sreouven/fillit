#include "libft.h"
#include "fillit.h"


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

t_tetri		*new_piece(char *buffer, int id)
{
		t_tetri	*new;
		int		i;
		int		j;
		int		k;

		j = 0;
		k = 21 * id;
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
		ft_xy(new);
		new->index = id;
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

t_tetri		*reverse(t_tetri *liste)
{
		t_tetri *new_list;
		t_tetri *tmp;

		new_list = NULL;
		while (liste)
		{
				tmp = liste->next;
				liste->next = new_list;
				new_list = liste;
				liste = tmp;
		}
		return (new_list);
}

void	ft_xy(t_tetri *piece)
{
		int		x;
		int		j;
		int		i;

		x = -1;
		j = -1;
		while(++j < 4)
		{
				i = -1;
				while(++i < 4)
				{
						if(++x > 0 && piece->block[j][i] == '#')
						{
								piece->map[x][0] = i - piece->map[0][0];
								piece->map[x][1] = j - piece->map[0][1];
						}
						if(x == 0 && piece->block[j][i] == '#')
						{
								piece->map[x][0] = i;
								piece->map[x][1] = j;
						}
				}
		}
		piece->map[0][0] = 0;
		piece->map[0][1] = 0;
}

t_tetri		*fill_list(char *buffer, int sizebuf)
{
		t_tetri		*list;
		int			id;
		int			max;

		id = 0;
		max = (sizebuf / 21 + 1);
		if(!(list = malloc(sizeof(t_tetri*) * max)))
				return (NULL);
		list = NULL;
		while (id < max)
		{
				ft_listadd(&list, new_piece(buffer, id));
				if (!(check_piece(4, 5, list->block)))
						return (NULL);
				id++;
		}
		return (reverse(list));
}
