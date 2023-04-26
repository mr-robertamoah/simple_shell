#include "shell.h"

/**
* close_exit - close
* @fd: pointer to file descriptor
* @dir_p: pointer to DIR
* @err: char pointer
*
* Description: close files and directories and exit
*
* Return: void
*/
void close_exit(int *fd, DIR *dir_p, char *err)
{
	if (fd)
		close(*fd);

	if (dir_p)
		closedir(dir_p);

	if (err)
	{
		perror(err);
		exit(EXIT_FAILURE);
	}
}

/**
* _cd_dash - change directory
* @cwd: char pointer
*
* Description: handle cd - and update OLDPWD
*
* Return: int
*/
int _cd_dash(char *cwd)
{
	char *old_pwd;

	old_pwd = get_env("OLDPWD");
	if (old_pwd == NULL)
	{
		_setenv("OLDPWD", cwd);
		return (1);
	}
	if (chdir(old_pwd) < 0)
	{
		return (1);
	}
	_puts(old_pwd);
	_setenv("OLDPWD", cwd);

	return (1);
}

/**
* _cd - change directory
* @arv: pointer of char pointers
*
* Description: handle cd commands and update OLDPWD
*
* Return: void
*/
void _cd(char **arv)
{
	DIR *dir_p = opendir(".");
	struct dirent *dp;
	struct stat filestat;
	char cwd[BUF], absolute_path[BUF], *dir_name = arv[1];
	int fd;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		close_exit(NULL, NULL, "getcwd() error");
	if (_strcmp(dir_name, "-") == 0 && _cd_dash(cwd))
		return;
	while ((dp = readdir(dir_p)) != NULL)
	{
		if (_strcmp(dp->d_name, dir_name) == 0)
		{
			_strcpy(absolute_path, cwd);
			_strcat(absolute_path, "/");
			_strcat(absolute_path, dir_name);
			fd = open(absolute_path, O_DIRECTORY);
			if (fd < 0)
				close_exit(NULL, dir_p, "Error opening directory");
			if (fstat(fd, &filestat) < 0)
				close_exit(&fd, dir_p, "Error getting file status");
			if ((filestat.st_mode & S_IFMT) == S_IFDIR)
			{
				if (chdir(absolute_path) < 0)
					close_exit(&fd, dir_p, "Error changing directory");

				_setenv("OLDPWD", cwd);
				_setenv("PWD", absolute_path);
				close_exit(&fd, dir_p, NULL);
				return;
			}
			else
				close_exit(&fd, dir_p, "Not a directory");
		}
	}
	close_exit(NULL, dir_p, "Directory not found");
}
