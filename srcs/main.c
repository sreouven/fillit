#include "libft.h"
#include "fillit.h"

void	fill_data(t_tetri *list, t_data *data)
{
		int		i;
		int		x;
		int		z;

		x = 0;
		data->nb_tetri = 0;
		while(list)
		{
				i = 0;
				data->nb_tetri++;
				while(i < 4)
				{
						data->map[x][i][0] = list->map[i][0];
						data->map[x][i][1] = list->map[i][1];
						i++;
				}
				x++;
				list = list->next;
		}
		z = 2;
		while (z * z < data->nb_tetri * 4)
				z++;
		data->size = z;
}

int		main(int argc, char **argv)
{
		t_tetri		*ptr_list;
		char		*buffer;
		int			len_buffer;
		char		**map;
		t_data		data;

		if (argc != 2)
		{
				write(2, "usage : ./fillit file_name\n", 27);
				return (1);
		}
		if(!(buffer = ft_open_check_file(&argv[1])))
		{
				write(1, "error\n", 6);
				return (1);
		}
		len_buffer = ft_strlen(buffer);
		ptr_list = fill_list(buffer, len_buffer);
		if(ptr_list == NULL)
		{
				write(1, "error\n", 6);
				return (1);
		}
		fill_data(ptr_list, &data);
		ft_fillit(&data, 0, 0, 0); 
		return (0);
}
