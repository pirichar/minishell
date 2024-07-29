/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:46:28 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:46:29 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief 	Make sure next block of memory's address
 			is aligned to the specified boundary.(multiple of 2)
			It calculates the mask as alignment - 1 
			It then adds this mask to the address 
			The bitwise AND with the negated (NOT operator ~)mask clears out
			the lower bits to ensure alignment
			This make sure we get the closest block of memory possible within

			Example:
			Suppose address = 18 and alignment = 16:
			Mask: 15 (00001111)
			Address + Mask: 18 + 15 = 33 (00100001)
			Address & ~mask : 33 & ~15 (the opposite of (00001111)) =
			33(00100001) & 240 (11110000) = 32 (00100000)

 * 
 * @param The memory address to align.
 * @param The alignment boundary.
 * @return The aligned address.
 */
static size_t	align_up(size_t address, size_t alignment)
{
	size_t	mask;

	mask = alignment - 1;
	return ((address + mask) & ~mask);
}

/**
 * @brief Allocate a bloc of memory into the arena alocator
 * 
 * @param arena the arena map to allocate in
 * @param size how much to allocate
 * @return the adress to the block to be used
 */
void	*arena_alloc(t_arena *arena, size_t size)
{
	char	*address;

	arena->index = align_up(arena->index, 16);
	address = arena->block + arena->index;
	arena->index += size;
	if (arena->index > arena->high_watermark)
		arena->high_watermark = arena->index;
	if (arena->index >= arena->size)
	{
		dprintf(STDERR_FILENO, "Out of memory\n");
		exit(EXIT_FAILURE);
	}
	ft_bzero(address, size);
	return (address);
}

/**
 * @brief Reset the index of the block of memory to 0
 * 
 * @param arena to be reset
 */
void	arena_clear(t_arena *arena)
{
	arena->index = 0;
}

/**
 * @brief Free the desired arena
 * 			arena = (t_arena){0} is like a b zero for every variables
 * @param to be freed
 */
void	arena_free(t_arena *arena)
{
	free(arena->block);
	*arena = (t_arena){0};
}

/**
 * @brief print in MB, KB or B, only used at the end
 * 
 * @param arena to print
 */
void	arena_log_watermark(t_arena *arena)
{
	printf("arena max memory: ");
	if (arena->high_watermark >= 1024 * 1024)
		printf("%.2f MB\n", (float)arena->high_watermark / (1024.f * 1024.f));
	else if (arena->high_watermark >= 1024)
		printf("%.2f KB\n", (float)arena->high_watermark / (1024.f));
	else
		printf("%zu byte\n", arena->high_watermark);
}
