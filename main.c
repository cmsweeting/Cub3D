//HEADER

#include "raycasting.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	**create_map(void)
{
	char	**map;
	int		i;
	int		j;

	i = 0;
	map = malloc(sizeof(char *) * 5);
	if (!map)
		return (NULL);
	while (i < 4)
	{
		j = 0;
		map[i] = malloc(sizeof(char) * 9);
		if (!map[i])
		{
			free_map(map);
			return (NULL);
		}
		if (i == 0 || i == 3)
		{
			while (j < 8)
				map[i][j++] = '1';
		}
		else
		{
			map[i][0] = '1';
			map[i][7] = '1';
			j++;
			while (j < 7)
				map[i][j++] = '0';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
	map[i] = NULL;
	return (map);
}

int	main()
{
	char	**map;

	//parsing;
	map = create_map();
	if (!map)
		return (1);
	int i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
	printf("\n");
	if (init_display(map))
	{
		free_map(map);
		return (1);
	}
	free_map(map);
	return (0);
}