/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 17:38:21 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:30:35 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOSPHERS_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

# define RED				"\033[1;31m"
# define GREEN				"\033[1;32m"
# define CYAN				"\033[1;36m"
# define BLUE				"\033[1;34m"
# define YELLOW				"\033[1;33m"
# define BLANK				"\033[0m"

# define USAGE	"Usage: ./philo [number_of_philosophers] [time_to_die] \
[time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]"

enum	e_bool
{
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK
};

typedef struct s_philo
{
	pthread_t		death_monitor;
	sem_t			*rights;
	long			philo_id;
	long			meals;
	time_t			last_meal;
	long			meal_amount;
}					t_philo;

typedef struct s_main
{
	pthread_t		repletion_monitor;
	t_philo			philosopher;
	pid_t			*philo_pid;
	sem_t			*forks;
	sem_t			*writing_sem;
	sem_t			*repletion;
	long			phils_nb;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	long			meal_amount;
	sem_t			*end;
}					t_main;

void				print(t_main *ptr, t_philo *philosopher, char *action);
void				ft_error(t_main *ptr, char *error, int mod_exit, int rno);
time_t				get_time(void);
void				ft_sleep(t_main *ptr, time_t sleep_time);
char				*naming_semaphores(int philo_id);

void				kill_philosophers(t_main *ptr);
void				ft_free_ptr(t_main *ptr);

long				ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
void				ft_putstr_fd(const char *s, int fd);
int					ft_isdigit(int c);

void				init_ptr(t_main	*ptr, char **av);
void				init_semaphores(t_main *ptr);
void				init_thread(t_main *ptr);
void				init_philosopher(t_main *ptr);

void				creat_philosopher(t_main *ptr);
void				routine(t_main *ptr);
void				actions(t_main *ptr, int action);
void				*check_repletion(void *tmp);
void				*check_death(void *tmp);

#endif