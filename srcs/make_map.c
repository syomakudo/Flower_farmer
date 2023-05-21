#include "include.h"

/*初期化*/
void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->x_now = 0;
	data->y_now = 0;
	data->x_start = 0;
	data->y_start = 0;
	data->x_goal = 0;
	data->y_goal = 0;
	data->items = 0;
	data->x_max = 0;
	data->y_max = 0;
	data->col = 0;
	data->row = 0;
}

/*gnlを使用する*/
void	read_map(t_data *data, char *file_name)
{
	int	fd;
	int	j;
	int	row;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error(-2);
	j = 0;
	row = data->row;
	while (row-- > 0)
	{
		data->map[j] = get_next_line(fd);
		if (data->map[j] == NULL)
			ft_error(-5);
		j++;
	}
	data->map[j] = NULL;
	if (close(fd) == -1)
		ft_error(-4);
}

/*ファイルの行数を返す
**rowに行数を代入
*/
int	count_read_row(char *file_name)
{
	int		fd;
	int		count;
	char	buf[1];
	ssize_t		k;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error(-2);
	k = -2;
	while (1)
	{
		k = read(fd, buf, 1);
		if (k == 0)
			break ;
		else if (k == -1)
			ft_error(-3);
		if (buf[0] == '\n')
			count++;
	}
	if (close(fd) == -1)
		ft_error(-4);
	if (count == 0)
		return (0);
	return (count + 1);
}

/*mapを作成する*/
t_data	make_map(char *file_name)
{
	t_data data;
	init_data(&data);
	data.row = count_read_row(file_name);
	if (data.row == 0)
		ft_error(0);
	data.map = malloc(sizeof(char *) * (data.row + 1));
	if (data.map == NULL)
		ft_error(-1);
	read_map(&data, file_name);
	return (data);
}