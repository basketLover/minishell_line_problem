#define _POSIX_C_SOURCE 200809L
#define _GNU_SOURCE
#include "minishell.h"
#include "libft/libft.h"

int	handle_chdir_error(char *oldpwd)
{
	perror("cd");
	free(oldpwd);
	return (1);
}

char	*safe_getcwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("cd: getcwd failed");
	return (cwd);
}
