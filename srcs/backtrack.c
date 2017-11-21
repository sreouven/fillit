#include "libft.h"
#include "fillit.h"

int		ft_map_creator(t_data *data)
{
		int		i;
		int		j;

    	if(!(data->result = malloc(sizeof(char*) * data->size)))
					return (0);
		i = -1;
		while(++i < data->size)
		{
				if (!(data->result[i] = malloc(sizeof(char) * data->size)))
				{
						while (--i >= 0)
								free(data->result[i]);
						free(data->result);
						return (0);
				}
				j = -1;
				while (++j < data->size)
						data->result[i][j] = '.';
		}
		return(1);
}

static void		ft_mapoverside(int *i, int *j)
{
		*i += 1;
		*j = 0;
}

static int		ft_oversize(t_data *data, int id)
{
		if(id == 0)
		{
				ft_map_cleaner(data);
				data->size++;
				return (ft_fillit(data, 0, 0, 0));
		}
		return (0);
}

int		ft_fillit(t_data *data, int id, int	j, int i)
{
		if(!ft_map_creator(data))
				return (0);
		while (id < data->nb_tetri)
		{
				if(j == data->size)
						ft_mapoverside(&i, &j);
				if(i == data->size)
						return (ft_oversize(data, id));
				if(data->result[j][i] == '.' && ft_is_free(data, id, j, i))
						if (ft_fillit(data, id + 1, 0, 0))
								return(1);
						else
								ft_remove_last(data, id, i, j++);
				else
						j++;
		}
		if(id  == data->nb_tetri)
				ft_put_map(data);
		return (1);
}

int		ft_is_free(t_data *data, int id, int j, int i)
{
		int		x;
		int		y;
		int		b;
		int		ok;

		b = -1;
		ok = 1;
		while (++b < 4 && ok)
		{
				x = data->map[id][b][0];
				y = data->map[id][b][1];
				if (i + x < 0 || j + y < 0 || i + x >= data->size || j + y >= data->size
								|| data->result[j + y][x + i] != '.')
						ok = 0;
		}
		if (ok)
		{
				while (--b >= 0)
				{
						x = data->map[id][b][0];
						y = data->map[id][b][1];
						data->result[j + y][i + x] = id + 'A';
				}
		}
		return (ok);
}

void	ft_map_cleaner(t_data *data)
{
		int		i;

		i = -1;
		while(++i < data->size)
				free(data->result[i]);
		free(data->result);
}

void	ft_remove_last(t_data *data, int id, int j, int i)
{
		int		x;
		int		y;
		int		b;

		b = -1;
		while (++b < 4)
		{
				x = data->map[id][b][0];
				y = data->map[id][b][1];
				data->result[j + y][i + x] = '.';
		}
}


void	ft_put_map(t_data *data)
{
		int		i;
		int		j;

		j = 0;
		while (j < data->size)
		{
				i = 0;
				while(i <= data->size)
				{
					write(1, &data->result[j][i], 1);
					i++;
				}
				write(1, "\n", 1);
				j++;
		}
}
