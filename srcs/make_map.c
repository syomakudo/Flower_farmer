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
	int	i;
	int	row;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error(-2);
	i = 0;
	row = data->row;
	while (row-- > 0)
	{
		data->map[i] = get_next_line(fd);
		if (data->map[i] == NULL)
			ft_error(-5);
		i++;
	}
	data->map[i] = NULL;
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
	int		i;

	count = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_error(-2);
	i = -2;
	while (1)
	{
		i = read(fd, buf, 1);
		if (i == 0)
			break ;
		else if (i == -1)
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
void	make_map(t_data *data, char *file_name)
{
	init_data(data);
	data->row = count_read_row(file_name);
	if (data->row == 0)
		ft_error(0);
	data->map = malloc(sizeof(char *) * (data->row + 1));
	if (data->map == NULL)
		ft_error(-1);
	read_map(data, file_name);
}