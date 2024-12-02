/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 14:32:07 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/01 17:39:40 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// movements
//convert 
// while (pressed)
// {
	//convert player direction to vector
	//convert coordenate to vector direction
	//calc vector * speed
	//calc position + move_vector // if not in wall chunk update position

	//move player in that direction
	//check if player is in a wall
	//if player is in a wall, move player back
// }

//mouse movement
//mo
//cilindric coordinates
//mouse movement 


///// ALL THIS WAS FRACTOL COPIED!!!!! //////////


void	reset_fractol(t_fractol *f)
{
	t_info	*info;

	change_int(f, 117);
	info = f->info.backup;
	info->array = f->info.array;
	info->step_array = f->info.step_array;
	f->info = *info;
	f->info.backup = info;
	f->info.update = 1;
}

int	handle_close(void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	free_struct(f);
	exit(0);
}

int	handle_mouse(int button, int x, int y, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (button == 4 || button == 5)
		mouse_zoom(button, x, y, f);
	if (button == 3)
	{
		f->info.pos.x += f->info.step.x * (x - WIDTH / 2);
		f->info.pos.y += f->info.step.y * (y - HEIGHT / 2);
		f->info.update = 1;
		recalc_vals(f);
	}
	return (0);
}

int	handle_key(int key, void *param)
{
	t_fractol	*f;

	f = (t_fractol *)param;
	if (key == 65307)
		handle_close(f);
	if (key == 102)
		change_fractol(f);
	if (key == 65361 || key == 65363 || key == 65362 || key == 65364)
		move_img(key, f);
	if (key == 114)
		reset_fractol(f);
	if (key == 44 || key == 46)
		zoom_times(key, f);
	if (key == 121 || key == 117 || key == 105)
		change_int(f, key);
	if (key == 99)
		change_colour(f);
	if (key == 108)
		change_loop(f);
	if (key == 112)
		change_palete(f);
	recalc_vals(f);
	return (0);
}


void	mouse_zoom(int button, int x, int y, t_fractol *f)
{
	t_complex	val;

	button = (4 - button);
	val.x = f->info.step_array[x];
	val.y = f->info.step_array[WIDTH + y];
	if (button == 0)
		f->info.s_zoom *= 1.2f;
	else if (button < 0)
		f->info.s_zoom /= 1.2f;
	recalc_vals(f);
	f->info.pos.x = val.x + (WIDTH / 2 - x) * f->info.step.x;
	f->info.pos.y = val.y + (HEIGHT / 2 - y) * f->info.step.y;
	f->info.update = 1;
	recalc_vals(f);
	return ;
}
