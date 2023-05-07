#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "../minilibx-linux/mlx.h"

#define ROW 3  // 行数
#define COL 5  // 列数

typedef struct	s_img
{
	void	*img;
	int		width;
	int		height;
}				t_img;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		x_now;
	int		y_now;
	int		x_max;
	int		y_max;
}				t_data;

void init_data(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->x_now = 0;
	data->y_now = 0;
	data->x_max = 0;
	data->y_max = 0;
}

void read_map(t_data *data, char *file_name)
{
	int		fd;
	char	*line;
	int		i;
	int		j;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		printf("file open error\n");
		exit(1);
	}
	i = 0;
	char buf[1];
	while (i < ROW)
	{
		j = 0;
		while (j < COL)
		{
			read(fd, &data->map[i][j], 1);
			j++;
		}
		//改行のために1バイト読み込む
		read(fd, buf, 1);
		i++;
	}
	close(fd);
}

int main() {

	t_data	data;
	int		i;
	int		j;
	char	*file_name = "./maps/test.ber";

	data.map = malloc(sizeof(char *) * ROW);  // ダブルポインタで2次元配列を実現
	for (int i = 0; i < ROW; i++) {
		data.map[i] = malloc(sizeof(char) * COL);
	}
	read_map(&data,file_name);

    char **map = malloc(sizeof(char *) * ROW);  // ダブルポインタで2次元配列を実現
    for (int i = 0; i < ROW; i++) {
        map[i] = malloc(sizeof(char) * COL);
    }

	/*2次元配列の値を代入する*/
    map[0][0] = '1';
    map[0][1] = '1';
    map[0][2] = '1';
    map[0][3] = '1';
    map[0][4] = '1';
    map[1][0] = '1';
    map[1][1] = 'C';
    map[1][2] = 'P';
    map[1][3] = 'E';
    map[1][4] = '1';
    map[2][0] = '1';
    map[2][1] = '1';
    map[2][2] = '1';
    map[2][3] = '1';
    map[2][4] = '1';

	init_data(&data);
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 50 * COL,
			50 * ROW, "Hello");

	t_img	img[5];

	img[0].img = mlx_xpm_file_to_image(data.mlx,
			"./img/snake.xpm", &img[0].width, &img[0].height);
	img[1].img = mlx_xpm_file_to_image(data.mlx,
			"./img/tooth.xpm", &img[1].width, &img[1].height);
	img[2].img = mlx_xpm_file_to_image(data.mlx,
			"./img/bacteria.xpm", &img[2].width, &img[2].height);
	img[3].img = mlx_xpm_file_to_image(data.mlx,
			"./img/trashBox2.xpm", &img[3].width, &img[3].height);
	img[4].img = mlx_xpm_file_to_image(data.mlx,
			"./img/dentist2.xpm", &img[4].width, &img[4].height);


		i = 0;
	while (i < ROW)
	{
		j = 0;
		while (j < COL)
		{
				if (data.map[i][j] == '1')
					mlx_put_image_to_window(data.mlx, data.win,
						img[1].img, j * 50, i * 50);
				else if (data.map[i][j] == 'C')
					mlx_put_image_to_window(data.mlx, data.win,
						img[2].img, j * 50, i * 50);
				else if (data.map[i][j] == 'P')
					mlx_put_image_to_window(data.mlx, data.win,
						img[4].img, j * 50, i * 50);
				else if (data.map[i][j] == 'E')
					mlx_put_image_to_window(data.mlx, data.win,
						img[3].img, j * 50, i * 50);

			j++;
		}
		i++;
	}
	mlx_loop(data.mlx);
	// printf("mlx: %p\n", mlx);
	// printf("win: %p\n", win);

    // 2次元配列の値を出力する
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            printf("%c ", map[i][j]);  // %c で文字を表示
        }
        printf("\n");
    }
    // メモリの解放
    for (int i = 0; i < ROW; i++) {
        free(map[i]);
    }
    free(map);

    return 0;
}
