/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vjean <vjean@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 09:47:53 by vjean             #+#    #+#             */
/*   Updated: 2023/05/26 14:39:37 by vjean            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "Libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define W 1920
# define H 1080
# define TEXWIDTH 64
# define TEXHEIGHT 24

static const char *g_side_tab[7] = {"NO ", "SO ", "WE ", "EA ", "F ", "C ",
	NULL};
static const char *g_dir_tab[5] = {"N", "E", "S", "W", NULL};

enum e_error_code	{GOOD, PATH, COLOR, MAP, PLAYER, CUB_FILE};

struct	t_parse;

typedef struct s_map {
	bool	first_line;
	bool	last_line;
	char	player;
	char	**map;
	char	direction;
	int		player_x;
	int		player_y;
	int		nb_lines;
}	t_map;

typedef struct s_tex{
	int		**tab;
	int		width;
	int		height;
}	t_tex;

typedef struct s_xpm{
	xpm_t	*NO;
	xpm_t	*SO;
	xpm_t	*EA;
	xpm_t	*WE;
	t_tex	*tab_no_tex;
	t_tex	*tab_so_tex;
	t_tex	*tab_ea_tex;
	t_tex	*tab_we_tex;
}	t_xpm;

typedef struct s_raycast {
	double	pos_X;
	double	pos_Y;
	double	dir_playerX;
	double	dir_playerY;
	double	plane_X;
	double	plane_Y;
	double	cameraX;
	double	ray_dirX;
	double	ray_dirY;
	double	sideX_dist;
	double	sideY_dist;
	double	delta_X;
	double	delta_Y;
	double	perpendicular_wallDist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start_pt;
	int		draw_end_pt;
	int		map_x;
	int		map_y;
	double	move_speed;
	int		tex_x;
}	t_raycast;

typedef struct s_parse {
	char				*no;
	char				*so;
	char				*we;
	char				*ea;
	mlx_t				*mlx;
	mlx_image_t			*image;
	unsigned int		floorcolor;
	unsigned int		ceilingcolor;
	bool				treat_floor;
	bool				treat_ceiling;
	int					mapbeg;
	t_map				*map;
	t_raycast			*ray;
	t_xpm				*xpm;
	enum e_error_code	error;
}	t_parse;

/*      PARSING_INFO    */
void			parseline(char *line, t_parse *MapCheck);
t_parse			*parseinfo(char *map);
void			parsepath(t_parse *MapCheck, char *line, int j);
void			parsecolor(t_parse *data, char *line, int j);
void			parse_color_util(t_parse *data, char *line, int j);

/*      GET             */
char			*getpath(char *line);
void			gettmpmap(t_parse *data, int fd);

/*      INIT_DATA       */
t_parse			*initcheck(void);
int				first_parse(int fd, t_parse *data);
void			clear_data(t_parse *data);
unsigned int	ft_uatoi(const char *str, t_parse *data);

/*      CLEAR           */
void			clear_data(t_parse *data);

/*      ERROR           */
void			error_handler(t_parse *data);
void			check_parseinfo(t_parse *data);

/*      PARSING_MAP     */
void			parsemap(char *line, t_parse *parse);
void			map_space_handler(char *line, int *i, t_parse *parse);
void			gettmpmap(t_parse *data, int fd);
void			print_double_tab(char **tab);
char			*ez_gnl(int fd);
void			flood_fill(t_parse *data, int y, int x);
void			print_info(t_parse *data);

/*      INIT_GAME       */
void			start_mlx(t_parse *data);
void			put_ceiling(t_parse *data, int index);
void			put_floor(t_parse *data, int index);

/*      RAYCAST         */
void			start_raycast(t_parse *data);
void			go_raycast(t_parse *data);
void			init_player_pos(t_parse *data);
void			init_plane(t_parse *data);
void			init_struct(t_parse *data);
void			setup_struct(t_parse *data);

/*      PREP ALGO       */
void			mesure_delta(t_parse *data);
void			prep_dda(t_parse *data);
void			get_perpendicular(t_raycast *ray);
void			draw_line(t_raycast *ray);

/*      TEXTURE         */
void			add_texture(t_parse *data);
void			prepare_tex(t_parse *data, t_tex *text, int *i);
void			put_texture(t_parse *data, t_tex *text, int *i);
void			transform_xpm(t_parse *data);

/*		KEY_EVENT		*/
void			key_event(struct mlx_key_data key, void *data);

/*      MOVES           */
void			go_ahead(t_parse *data);
void			go_back(t_parse *data);
void			go_left(t_parse *data);
void			go_right(t_parse *data);

/*      FREE STUFF      */
void			ft_free_null(void *ptr);
void			ft_free_tab(void **tab);
void			free_everything(t_parse *data);

#endif
