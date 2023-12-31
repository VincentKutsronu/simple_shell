#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	if (!path || stat(path, &st)) {
		return 0;
	}

	if (S_ISREG(st.st_mode) && access(path, X_OK) == 0) {
		return 1;
	}

	return 0;
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++) {
		if (pathstr[i] != ':') {
			buf[k++] = pathstr[i];
		}
	}

	buf[k] = '\0';
	return buf;
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr) {
		return NULL;
	}

	// Check if the command is already a full path.
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./")) {
		if (is_cmd(info, cmd)) {
			return cmd;
		}
	}

	// Split the PATH string into individual paths.
	while (1) {
		if (!pathstr[i] || pathstr[i] == ':') {
			// Create a full path for the command using the current path.
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path) {
				_strcat(path, cmd);
			} else {
				_strcat(path, "/");
				_strcat(path, cmd);
			}

			// Check if the command is executable.
			if (is_cmd(info, path)) {
				return path;
			}

			// If we reached the end of the PATH string, stop searching.
			if (!pathstr[i]) {
				break;
			}

			// Move to the next path in the PATH string.
			curr_pos = i + 1;
		}

		i++;
	}

	// If we reached this point, the command was not found in the PATH string.
	return NULL;
}
