#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#include <stdio.h>

void raycasting(t_map *map, t_player *player, t_ray *ray)
{
	//calculate how many rays to cast
	//find intesection over each ray
	//pixellize the intersection

	//raycasting algorithm
	//i will need to check if the ray hit a wall
	//and if it did i will need to check the distance
	//and the dir of the wall
	//i will need to check the dir of the player
	//and the dir of the wall
	//and the distance of the player to the wall

}

/////// ALL THIS WAS GPT GENERATED!!!! ////

typedef struct {
    double x;
    double y;
} Vector2D;

typedef struct {
    Vector2D pos;
    double dir; // dir in degrees
} Player;

typedef struct {
    int **map;
    int width;
    int height;
} Chunk;

typedef struct {
    int chunk_x;
    int chunk_y;
    Chunk *chunk;
} LoadedChunk;

typedef struct {
    int map_width;
    int map_height;
    LoadedChunk **loaded_chunks;
    int loaded_chunk_count;
    void *mlx;
    void *win;
    struct {
        void *img;
        char *addr;
        int bpp;
        int len_line;
        int endian;
    } img;
    Player player;
} Game;

Game *ft_game(void) {
    static Game game;
    return &game;
}

void my_mlx_pixel_put(void *img, int x, int y, int color) {
    Game *game = ft_game();
    char *dst;

    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    dst = game->img.addr + (y * game->img.len_line + x * (game->img.bpp / 8));
    *(unsigned int *)dst = color;
}

Chunk *load_chunk(int chunk_x, int chunk_y) {
    // Simulate loading a chunk (in a real application, this would load from a file or generate procedurally)
    Chunk *chunk = malloc(sizeof(Chunk));
    chunk->width = CHUNK_SIZE;
    chunk->height = CHUNK_SIZE;
    chunk->map = malloc(chunk->height * sizeof(int *));
    for (int i = 0; i < chunk->height; i++) {
        chunk->map[i] = malloc(chunk->width * sizeof(int));
        for (int j = 0; j < chunk->width; j++) {
            chunk->map[i][j] = (i + j) % 2; // Example pattern
        }
    }
    return chunk;
}

Chunk *get_chunk(Game *game, int chunk_x, int chunk_y) {
    // Check if the chunk is already loaded
    for (int i = 0; i < game->loaded_chunk_count; i++) {
        if (game->loaded_chunks[i]->chunk_x == chunk_x && game->loaded_chunks[i]->chunk_y == chunk_y) {
            return game->loaded_chunks[i]->chunk;
        }
    }

    // Load the chunk if not already loaded
    Chunk *chunk = load_chunk(chunk_x, chunk_y);
    LoadedChunk *loaded_chunk = malloc(sizeof(LoadedChunk));
    loaded_chunk->chunk_x = chunk_x;
    loaded_chunk->chunk_y = chunk_y;
    loaded_chunk->chunk = chunk;
    game->loaded_chunks[game->loaded_chunk_count++] = loaded_chunk;
    return chunk;
}

typedef struct {
    double distance;
    int hit_x;
    int hit_y;
    char face; // 'N', 'S', 'E', 'W'
} RayHit;

RayHit cast_ray(Game *game, double ray_angle) {
    RayHit hit;
    hit.distance = -1;
    hit.hit_x = -1;
    hit.hit_y = -1;
    hit.face = ' ';

    // Convert ray angle to radians
    double ray_angle_rad = ray_angle * PI / 180.0;

    // Calculate ray dir
    double ray_dir_x = cos(ray_angle_rad);
    double ray_dir_y = sin(ray_angle_rad);

    // Player pos
    double pos_x = game->player.pos.x;
    double pos_y = game->player.pos.y;

    // Distance to the next x and y side
    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);

    // Which box of the map we're in
    int map_x = (int)pos_x;
    int map_y = (int)pos_y;

    // Length of ray from current pos to next x or y-side
    double side_dist_x;
    double side_dist_y;

    // What dir to step in x or y-dir (either +1 or -1)
    int step_x;
    int step_y;

    int hit_wall = 0; // Was there a wall hit?
    int side; // Was a NS or a EW wall hit?

    // Calculate step and initial side_dist
    if (ray_dir_x < 0) {
        step_x = -1;
        side_dist_x = (pos_x - map_x) * delta_dist_x;
    } else {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - pos_x) * delta_dist_x;
    }
    if (ray_dir_y < 0) {
        step_y = -1;
        side_dist_y = (pos_y - map_y) * delta_dist_y;
    } else {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - pos_y) * delta_dist_y;
    }

    // Perform DDA
    while (hit_wall == 0) {
        // Jump to next map square, either in x-dir, or in y-dir
        if (side_dist_x < side_dist_y) {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            side = 0;
        } else {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            side = 1;
        }

        // Determine the chunk coordinates
        int chunk_x = map_x / CHUNK_SIZE;
        int chunk_y = map_y / CHUNK_SIZE;

        // Get the chunk
        Chunk *chunk = get_chunk(game, chunk_x, chunk_y);

        // Check if ray has hit a wall
        if (chunk->map[map_y % CHUNK_SIZE][map_x % CHUNK_SIZE] > 0) hit_wall = 1;
    }

    // Calculate distance projected on camera dir (Euclidean distance will give fisheye effect!)
    if (side == 0) hit.distance = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x;
    else hit.distance = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y;

    // Determine the face of the wall hit
    if (side == 0) {
        if (ray_dir_x > 0) hit.face = 'W';
        else hit.face = 'E';
    } else {
        if (ray_dir_y > 0) hit.face = 'N';
        else hit.face = 'S';
    }

    hit.hit_x = map_x;
    hit.hit_y = map_y;

    return hit;
}

void raycasting(Game *game) {
    // Cast rays over the 120-degree FOV
    double start_angle = game->player.dir - FOV / 2;
    double end_angle = game->player.dir + FOV / 2;
    double angle_step = FOV / WIDTH;

    for (int x = 0; x < WIDTH; x++) {
        double ray_angle = start_angle + x * angle_step;
        RayHit hit = cast_ray(game, ray_angle);

        // Calculate line height
        int line_height = (int)(HEIGHT / hit.distance);

        // Draw the line (simplified example)
        int draw_start = -line_height / 2 + HEIGHT / 2;
        int draw_end = line_height / 2 + HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        if (draw_end >= HEIGHT) draw_end = HEIGHT - 1;

        for (int y = draw_start; y < draw_end; y++) {
            my_mlx_pixel_put(game->img.img, x, y, 0xFFFFFF); // Draw white line for walls
        }
    }
}

int main() {
    Game *game = ft_game();

    // Initialize MiniLibX
    game->mlx = mlx_init();
    if (game->mlx == NULL) {
        fprintf(stderr, "Failed to initialize MiniLibX\n");
        return 1;
    }

    // Create a window
    game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Raycasting Example");
    if (game->win == NULL) {
        fprintf(stderr, "Failed to create window\n");
        return 1;
    }

    // Create an image
    game->img.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.len_line, &game->img.endian);

    // Initialize player pos and dir
    game->player.pos.x = WIDTH / 2;
    game->player.pos.y = HEIGHT / 2;
    game->player.dir = 0.0; // Facing right (0 degrees)

    // Initialize loaded chunks array
    game->loaded_chunks = malloc(100 * sizeof(LoadedChunk *)); // Example size
    game->loaded_chunk_count = 0;

    // Perform raycasting
    raycasting(game);

    // Display the image
    _image_to_window(game->mlx, game->win, game->img.img, 0, 0);

    // Enter the main loop
    mlx_loop(game->mlx);

    // Free loaded chunks
    for (int i = 0; i < game->loaded_chunk_count; i++) {
        for (int j = 0; j < game->loaded_chunks[i]->chunk->height; j++) {
            free(game->loaded_chunks[i]->chunk->map[j]);
        }
        free(game->loaded_chunks[i]->chunk->map);
        free(game->loaded_chunks[i]->chunk);
        free(game->loaded_chunks[i]);
    }
    free(game->loaded_chunks);

    return 0;
}