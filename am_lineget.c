#include "header.h"

/**
 * inp_buffer - buffers chained commands
 * @inf: parameter struct
 * @buff: address of buffer
 * @leng: address of length variable
 *
 * Return: bytes
 */
ssize_t input_buf(info_t *inf, char **buff, size_t *leng)
{
	ssize_t e = 0;
	size_t len_p = 0;

	if (!*leng)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, Handler);
#if USE_GETLINE
			e = getline(buff, &len_p, stdin);
#else
			e = _getline(inf, buff, &len_p);
#endif
		if (e > 0)
		{
			if ((*buff)[e - 1] == '\n')
			{
				(*buff)[e - 1] = '\0';
				e--;
			}
			inf->linecount_flag = 1;
			am_remove_comments(*buff);
			am_build_history_list(inf, *buff, inf->histcount++);
			/*if (sstrchr(*buff, ';'))*/
			{
				*leng = e;
				inf->cmd_buf = buff;
			}
		}
	}
	return (e);
}

/**
 * am_get_inp - gets a newline
 * @inf: parameter struct
 *
 * Return: bytes read
 */
ssize_t am_get_inp(info_t *inf)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(inf->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(inf, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		am_check_chain(inf, buf, &j, i, len);
		while (j < len)
		{
			if (am_is_chain(inf, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			inf->cmd_buf_type = NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (r);
}

/**
 * rd_buffer - reads a buffer
 * @inf: parameter struct
 * @buff: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t rd_buffer(info_t *inf, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(inf->rfd, buff, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _get_nextline - gets the next line of input from STDIN
 * @inf: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _get_nextline(info_t *inf, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = rd_buffer(inf, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = sstrchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
	{
		sstrncat(new_p, buf + i, k - i);
	}
	else
	{
		sstrncpy(new_p, buf + i, k - i + 1);
	}

	s += k - i;
	i = k;
	p = new_p;

	if (length)
	{
		*length = s;
	}
	*ptr = p;
	return (s);
}

/**
 * Handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}


