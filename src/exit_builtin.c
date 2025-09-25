#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

static int	is_numeric(const char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && ft_isdigit((unsigned char)*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

void	cleanup_and_exit(t_data *data, char **args, char *input, int code)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
	free(input);
	while (data->env && data->env[i])
		free(data->env[i++]);
	free(data->env);
	exit(code);
}

void	free_args_and_input(char **args, char *input)
{
	int	i;

	i = 0;
	while (args && args[i])
		free(args[i++]);
	free(args);
	free(input);
}

int	exit_builtin(char **args, t_data *data, char *input)
{
	long	exit_code;

	ft_printf("exit\n");
	if (!args[1])
		cleanup_and_exit(data, args, input, data->last_status);
	else if (!is_numeric(args[1]))
	{
		ft_putendl_fd("exit: numeric argument required\n", 2);
		cleanup_and_exit(data, args, input, 2);
	}
	else if (args[2])
	{
		ft_putendl_fd("exit: too many arguments\n", 2);
		data->last_status = 1;
		return (2);
	}
	else
	{
		exit_code = ft_atol(args[1]) % 256;
		if (exit_code < 0)
			exit_code += 256;
		cleanup_and_exit(data, args, input, (int)exit_code);
	}
	return (1);
}
