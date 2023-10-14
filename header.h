#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define BUF_SIZE 1024
#define BUF_FLUSH -1
#define NORM	0
#define OR		1
#define AND		2
#define CHAIN	3
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int rfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* am_strings1.c */
char *_strdup(const char *str);
char *_strcat(char *, char *);
char *start_to(const char *haystack, const char *needle);
int _strcmp(char *str1, char *str2);

/* am_strings2.c */
char *_strcpy(char *dst, char *src);
int _strlen(char *str);
int _putchar(char a);
void _puts(char *str);

/*am_storage.c*/
char *_memset(char *c, char b, unsigned int n);
int rep_string(char *nw, char **ol);
void *_realloc(void *ptr, unsigned int old, unsigned int neww);
void _free(char **c);

/*_a_ati.c*/
int inter(info_t *);
int s_dlm(char ch, char *dlm);
int _alpha(int in);
int _ati(char *str);

/*am_stings3.c*/
char *sstrncpy(char *dst, char *src, int n);
char *sstrchr(char *str, char ch);
char *sstrncat(char *dst, char *src, int n);


/*To erorrs files*/

void am_eputs(char *);
int am_eputchar(char);
int am_putfd(char c, int fd);
int am_putsfd(char *str, int fd);

/*To errors1.c */
int am_erratoi(char *);
void am_print_error(info_t *, char *);
int am_print_d(int, int);
char *am_convert_number(long int, int, int);
void am_remove_comments(char *);

/*To am_memory.c */
int am_bfree(void **);

/*To am_list.c*/
list_t *am_add_node(list_t **, const char *, int);
list_t *am_add_node_end(list_t **, const char *, int);
size_t am_print_list_str(const list_t *);
int am_delete_node_at_index(list_t **, unsigned int);
void am_free_list(list_t **);


/*To am_list1.c*/
size_t am_list_len(const list_t *);
char **am_list_to_strings(list_t *);
size_t am_print_list(const list_t *);
list_t *am_node_starts_with(list_t *, char *, char);
ssize_t am_get_node_index(list_t *, list_t *);

/*To am_history file*/
char *am_get_history_file(info_t *info_t);
int am_write_history(info_t *info_t);
int am_read_history(info_t *info_t);
int am_build_history_list(info_t *info_t, char *buf, int linecount);
int am_renumber_history(info_t *info_t);

/*To am_parser.c*/

int am_is_cmd(info_t *, char *);
char *am_dup_chars(char *, int, int);
char *am_find_path(info_t *, char *, char *);
/* toem_shloop.c */
int am_hsh(info_t *, char **);
int am_find_builtin(info_t *);
void am_find_cmd(info_t *);
void am_fork_cmd(info_t *);
/*To am_tokenizer.c */
char **am_strtow(char *, char *);
char **am_strtow2(char *, char);
/*To am_vars.c */
int am_is_chain(info_t *, char *, size_t *);
void am_check_chain(info_t *, char *, size_t *, size_t, size_t);
int am_replace_alias(info_t *);
int am_replace_vars(info_t *);
int am_replace_string(char **, char *);

/*am_envn.c*/
int _prt_env(info_t *inf);
char *get_val_env(info_t *inf, const char *name);
int _init_setv(info_t *inf);
int _rm_setv(info_t *inf);
int pop_env_linklist(info_t *);


/*am_bult_in.c*/
int _shell_exit(info_t *inf);
int _this_is_cd(info_t *inf);
int _shell_help(info_t *inf);

/*am_bult_in1.c*/
int _this_is_hist(info_t *inf);
int uns_ali_str(info_t *inf, char *strg);
int s_ali_str(info_t *inf, char *str);
int print_ali_str(list_t *node);
int _my_ali_str(info_t *inf);

/*envgit.c*/
char **get_env_str(info_t *inf);
int _another_setv(info_t *inf, char *var);
int _rell_setenv(info_t *inf, char *var, char *val);

/*am_infget.c*/
void rm_inf(info_t *inf);
void put_inf(info_t *inf, char **av);
void freeStr_inf(info_t *inf, int all);

/*am_lineget.c*/
ssize_t input_buf(info_t *inf, char **buff, size_t *leng);
ssize_t am_get_inp(info_t *);
ssize_t rd_buffer(info_t *inf, char *buff, size_t *i);
int _get_nextline(info_t *inf, char **ptr, size_t *);
int _getline(info_t *, char **, size_t *);
void Handler(__attribute__((unused))int sig_num);

#endif
