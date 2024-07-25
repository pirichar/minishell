/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pirichar <pirichar@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:45:28 by pirichar          #+#    #+#             */
/*   Updated: 2024/07/25 11:45:30 by pirichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stddef.h>

typedef struct s_arena
{
	char	*block;
	size_t	size;
	size_t	index;
	size_t	high_watermark;
}	t_arena;

/**
 * @brief 
 * 
 * @param arena 
 * @param size 
 * @return t_arena* 
 */
t_arena	*arena_init(t_arena *arena, size_t size);

/**
 * @brief 
 * 
 * @param arena the arena map to allocate in
 * @param size how much to allocate
 * @return void* 
 */
void	*arena_alloc(t_arena *arena, size_t size);

/**
 * @brief 
 * 
 * @param arena 
 */
void	arena_clear(t_arena *arena);

/**
 * @brief 
 * *arena = (t_arena){0} is like a b zero for every variables
 * @param arena 
 */
void	arena_free(t_arena *arena);

void	arena_log_watermark(t_arena *arena);