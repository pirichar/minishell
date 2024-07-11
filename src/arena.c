#include "arena.h"
#include "../include/libft/libft.h"
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

static size_t align_up(size_t address, size_t alignment)
{
    size_t mask = alignment - 1;
    return (address + mask) & ~mask;
}

/**
 * @brief 
 * 
 * @param arena 
 * @param size 
 * @return t_arena* 
 */
t_arena *arena_init(t_arena *arena, size_t size)
{
    *arena = (t_arena){0};
    arena->block = (char*)ft_calloc(size, sizeof(char));
    arena->size = size;
    return arena;
}

/**
 * @brief 
 * 
 * @param arena the arena map to allocate in
 * @param size how much to allocate
 * @return void* 
 */
void	*arena_alloc(t_arena *arena, size_t size)
{
    char* address = arena->block + arena->index;
    address = (char*)align_up((size_t)address, 16);
    arena->index += size;
    if (arena->index > arena->high_watermark)
        arena->high_watermark = arena->index;
    if (arena->index >= arena->size)
    {
        dprintf(STDERR_FILENO, "Out of memory\n");
        exit(EXIT_FAILURE);
    }
    return address;
}

/**
 * @brief 
 * 
 * @param arena 
 */
void    arena_clear(t_arena *arena)
{
    arena->index = 0;
}

/**
 * @brief 
 * *arena = (t_arena){0} is like a b zero for every variables
 * @param arena 
 */
void    arena_free(t_arena *arena)
{
    free(arena->block);
    *arena = (t_arena){0};
}

/**
 * @brief print in MB, KB or B
 * 
 * @param arena 
 */
void    arena_log_watermark(t_arena *arena)
{
    printf("arena max memory: ");
    if (arena->high_watermark >= 1024 * 1024)
		printf("%.2f MB\n", (float)arena->high_watermark / (1024.f * 1024.f));
    else if (arena->high_watermark >= 1024)
		printf("%.2f KB\n", (float)arena->high_watermark / (1024.f));
    else
        printf("%zu byte\n", arena->high_watermark);
}