#include <stdio.h>
#include <unistd.h>
int	main()
{
		char	tab[4][5] = {{'#','#','.','.','\n'},{'.','.','.','.','\n'},{'.','.','.','.','\n'},{'.','.','.','.','\n'}};

		int		i;
		int		j;

		j = 0;
		i = 0;
		printf("%c", tab[j + 15][i + 16]);
/*		while (j < 4)
		{
				i = 0;
				while(i < 5)
				{
					printf("%c", tab[j][i]);
					i++;
				}
				j++;
		}*/
		return (0);
}
