#include "shell.h"

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	// If no arguments are provided, print all aliases.
	if (info->argc == 1) {
		list_t *node = info->alias;
		while (node) {
			print_alias(node);
			node = node->next;
		}
		return 0;
	}

	// Otherwise, iterate over the arguments and set or print aliases.
	for (int i = 1; i < info->argc; i++) {
		char *arg = info->argv[i];
		char *equals_sign = _strchr(arg, '=');

		// If the argument contains an equals sign, set an alias.
		if (equals_sign) {
			*equals_sign = '\0';
			set_alias(info, arg);
			*equals_sign = '=';
		} else {
			// Otherwise, print the alias for the given name.
			print_alias(node_starts_with(info->alias, arg, '='));
		}
	}

	return 0;
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p) {
		return 1;
	}

	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p) {
		return 1;
	}

	if (!*++p) {
		return unset_alias(info, str);
	}

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++) {
			_putchar(*a);
		}

		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *              constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}
