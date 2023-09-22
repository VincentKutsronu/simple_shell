#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	/* Open the history file if specified */
	if (ac == 2) {
		fd = open(av[1], O_RDONLY);
		if (fd == -1) {
			if (errno == EACCES) {
				exit(126);
			} else if (errno == ENOENT) {
				fprintf(stderr, "%s: 0: Can't open %s\n", av[0], av[1]);
				exit(127);
			} else {
				return EXIT_FAILURE;
			}
		}

		info->readfd = fd;
	}

	/* Populate the environment list */
	populate_env_list(info);

	/* Read the history file */
	read_history(info);

	/* Run the shell */
	hsh(info, av);

	return EXIT_SUCCESS;
}
