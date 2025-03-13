/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:25:16 by aouichou          #+#    #+#             */
/*   Updated: 2022/12/12 18:30:35 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOSPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <errno.h>
# include <string.h>
# include <limits.h>

# define RED	       		"\033[1;31m"
# define GREEN	       		"\033[1;32m"
# define CYAN	       		"\033[1;36m"
# define BLUE	       		"\033[1;34m"
# define YELLOW	       		"\033[1;33m"
# define BLANK	       		"\033[0m"

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
	pthread_t		philosopher;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	int				philo_id;
	int				meals;
	int				stop;
	time_t			last_meal;
	struct s_main	*ptr;

}					t_philo;

typedef struct s_main
{
	t_philo			*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	writing_mutex;
	long			phils_nb;
	time_t			start_time;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	long			meal_amount;
	int				end;
}					t_main;

int					ft_error(t_main *ptr, char *error, int mod_exit, int rno);
void				ft_free_ptr(t_main *ptr, int i);
time_t				get_time(void);
void				ft_sleep(t_main *ptr, time_t sleep_time);
void				print(t_philo *philosopher, char *action);

long				ft_atoi(const char *str);
size_t				ft_strlen(const char *str);
void				ft_putstr_fd(const char *s, int fd);
int					ft_isdigit(int c);

void				init_philo(t_main *ptr);
int					init_ptr(t_main *ptr, char **av);

t_main				*ft_get_ptr(void);
int					check_overflow(t_main *ptr, int ac, char **av);
int					check_args(t_main *ptr, int ac, char **av);

int					creat_philosophers(t_main *ptr);
void				*routine(void *ph);
int					actions(t_philo *philosopher, int action);
int					check_meal_nbr(t_main *ptr);
void				check_death(t_main *ptr);

int					eating(t_philo *philosopher);
int					lock_forks(t_philo *philosopher);
void				unlock_forks(t_philo *philosopher);

#endif