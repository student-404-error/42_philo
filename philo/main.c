/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 19:28:15 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/18 19:46:50 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/time.h>

int	main(int ac, char *av[])
{
	struct timeval tv;
	time_t	current_time;

	gettimeofday(&tv, NULL);
	current_time = tv.tv_sec;
	if (ac != 5 && ac != 6)
		printf("%d %d %d\n", tv.tv_hour, );
}
