#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

void	update_pwd_and_oldpwd(char *oldpwd, char *pwd, char ***env)
{
	set_env_var(env, "OLDPWD", oldpwd);
	set_env_var(env, "PWD", pwd);
}

void	handle_invalid_path(char *cmd)
{
	ft_putendl_fd(ft_strjoin3("minishell: ", cmd,
			": command not found"), 2);
	exit(127);
}

int	cd_to_home(t_data *data)
{
	char	*home;
	char	*pwd;
	char	*oldpwd;

	oldpwd = safe_getcwd();
	if (!oldpwd)
		return (1);
	home = get_env_value(data->env, "HOME");
	if (!home)
	{
		ft_printf("cd: HOME not set\n");
		free(oldpwd);
		return (1);
	}
	if (chdir(home) == -1)
		return (handle_chdir_error(oldpwd));
	pwd = getcwd(NULL, 0);
	if (!pwd)
		free(oldpwd);
	update_pwd_and_oldpwd(oldpwd, pwd, &data->env);
	free(oldpwd);
	free(pwd);
	return (0);
}

int	cd_to_path(char *path, t_data *data)
{
	char	*pwd;
	char	*oldpwd;

	oldpwd = safe_getcwd();
	if (!oldpwd)
		return (1);
	if (chdir(path) == -1)
	{
		perror("cd");
		if (oldpwd)
			free(oldpwd);
		return (1);
	}
	pwd = safe_getcwd();
	if (!pwd)
	{
		free(oldpwd);
		return (1);
	}
	update_pwd_and_oldpwd(oldpwd, pwd, &data->env);
	free(oldpwd);
	free(pwd);
	return (0);
}

int	cd_builtin(char **args, t_data *data)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (args[1] == NULL)
		return (cd_to_home(data));
	else if (args[1][0] == '\0')
		return (0);
	else
		return (cd_to_path(args[1], data));
}
