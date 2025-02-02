/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fandre-b <fandre-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 19:52:20 by fandre-b          #+#    #+#             */
/*   Updated: 2024/12/11 15:38:51 by fandre-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct s_bucket
{
	int				entry;
	void			*content;
	struct s_bucket	*next;
}	t_bucket;

typedef struct s_hash_table
{
	t_bucket	**buckets;
	int			size;
}	t_hashtable;

t_hashtable	*ft_hash_table(void)
{
	static t_hashtable	hash_table;

	return (&hash_table);
}

static t_bucket	*index_bucket(int key)
{
	t_bucket	*curr_buck;

	curr_buck = ft_hash_table()->buckets[key % ft_hash_table()->size];
	if (curr_buck == NULL)
		printf ("No bucket found\n");
	return (curr_buck);
}

static void	add_hash_entry(int key, bool value)
{
	t_bucket	*curr_buck;

	curr_buck = index_bucket(key);
	while (curr_buck)
		curr_buck = curr_buck->next;
	if (!curr_buck) //if the key is not found, create a new entry
	{
		curr_buck = (t_bucket *) my_calloc(1, sizeof(t_bucket));
		ft_hash_table()->buckets[key % ft_hash_table()->size] = curr_buck;
		// index_bucket(key) = curr_buck;
	}
	else
	{
		curr_buck->next = (t_bucket *) my_calloc(1, sizeof(t_bucket));
		curr_buck = curr_buck->next;
	}
	curr_buck->entry = key;
	curr_buck->content = (void *) my_calloc(1, sizeof(bool)); //is set to false
	curr_buck->next = NULL;
	*(bool *)curr_buck->content = value;
}

int	hash_find(int key)
{
	t_bucket	*curr_buck;

	curr_buck = index_bucket(key);
	while (curr_buck) //for coliisions
	{
		if (curr_buck->entry == key)
			return ((bool) curr_buck->content); //key is pressed
		curr_buck = curr_buck->next;
	}
	return (-1); //the key has no entry
}

void	hash_update(int key, bool value)
{
	t_bucket	*curr_buck;

	curr_buck = index_bucket(key);
	while (curr_buck) //for coliisions
	{
		if (curr_buck->entry == key)
		{
			*(bool *)curr_buck->content = value; //key is pressed
			return ;
		}
		curr_buck = curr_buck->next;
	}
	add_hash_entry(key, value);
}
