#ifndef _CONSOLESHELL_H_
#define _CONSOLESHELL_H_

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

/* read and write chunk */
#define READ_CHUNK_SIZE 1024
#define WRITE_CHUNK_SIZE 1024
#define FLUSH_THRESHOLD -1

/* truth table */
#define CMD_NORMALIZED	0
#define OR_GATE		1
#define AND_GATE		2
#define CMD_CHAIN	3

/* number exchange*/
#define TO_LOW	1
#define TO_UNSIGNED	2

/* chnage to active is sys use  */
#define ACTIVE_GETLINE 0
#define ACTIVE_USESTROCK 0

#define LOG_FILE	".simple_shell_history"
#define MAX_LOG	4096

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
	int readfd;
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


/* console_loop.c */
int hShell(info_t *, char **);
int search_builtin(info_t *);
void search_command(info_t *);
void launchCmd(info_t *);

/* parsingEngine.c */
int validate_cmd(info_t *context, char *route);
char *cloneChars(char *, int, int);
char *locate_dir(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void error_output(char *);
int put_error_char(char);
int write_descriptor(char c, int fd);
int write_str_to_fd(char *str, int fd);

/* string.c */
int string_size(char *);
int string_equals(char *, char *);
char *is_prefixed(const char *, const char *);
char *join_strings(char *, char *);

/* string2.c */
char *str_clone(char *, char *);
char *string_duplicate(const char *);
void display_string(char *);
int _putchar(char);

/* exits.c */
char *str_sub_copy(char *, char *, int);
char *substring_conca(char *, char *, int);
char *search_for_char(char *, char);

/* tokenizer.c */
char **tokenize_str(char *, char *);
char **tokenize_strad(char *, char);

/* realloc.c */
char *fill_memory(char *, char, unsigned int);
void deallocate_memory(char **);
void *reallocate_memory(void *, unsigned int, unsigned int);

/* memory.c */
int release_blocks(void **);

/* atoi.c */
int real_time_com(info_t *);
int is_delim(char, char *);
int checkalpha(int);
int _atoi(char *);

/* errors1.c */
int _safe_str_to_int(char *);
void show_error_message(info_t *, char *);
int print_debug_info(int, int);
char *convert_numeric(long int, int, int);
void eliminate_comments(char *);

/* builtin.c */
int _custom_exit(info_t *);
int _custom_cd(info_t *);
int _custom_help(info_t *);

/* builtin1.c */
int _custom_history(info_t *);
int _custom_alias(info_t *);

/*getline.c */
ssize_t fetch_input(info_t *);
int _getline(info_t *, char **, size_t *);
void handle_ctrl_d(int);

/* getinfo.c */
void reset_info(info_t *);
void initialize_info(info_t *, char **);
void deallocate_info(info_t *, int);

/* environ.c */
char *env_query(info_t *, const char *);
int retrieve_custom_env(info_t *);
int configure_custom_env(info_t *);
int clear_custom_env(info_t *);
int setup_env_list(info_t *);

/* getenv.c */
char **get_env_data(info_t *);
int _cus_unsetenv(info_t *, char *);
int _cus_setenv(info_t *, char *, char *);

/* history.c */
char *history_file_query(info_t *info);
int save_history(info_t *info);
int get_history(info_t *info);
int construct_history_list(info_t *info, char *buf, int linecount);
int modify_history_order(info_t *info);

/* lists.c */
list_t *generate_node(list_t **, const char *, int);
list_t *generate_node_end(list_t **, const char *, int);
size_t show_string_list(const list_t *);
int erase_node_at_position(list_t **, unsigned int);
void deallocate_list(list_t **);

/* lists1.c */
size_t get_list_size(const list_t *);
char **list_stringify(list_t *);
size_t show_list(const list_t *);
list_t *node_prefix_match(list_t *, char *, char);
ssize_t retrieve_node_index(list_t *, list_t *);

/* vars.c */
int sequence_verification(info_t *, char *, size_t *);
void assure_verification(info_t *, char *, size_t *, size_t, size_t);
int modify_alias(info_t *);
int modify_vars(info_t *);
int modify_string(char **, char *);

#endif
