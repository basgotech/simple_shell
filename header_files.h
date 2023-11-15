#ifndef HEADER_FILES_H
#define HEADER_FILES_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct separated_Items_s
{
	char separator;
	struct separated_Items_s *next;
} separated_Items;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_Collection_S
{
	char *line;
	struct line_Collection_S *next;
} line_Collection;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct registry_Of_Variables
{
	int len_var;
	char *val;
	int len_val;
	struct registry_Of_Variables *next;
} reg_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/* lists_logI.c */
separated_Items *add_Separation_At_End(separated_Items **head, char sep);
void release_Separated_List(separated_Items **head);
line_Collection *insert_Line_End_Node(line_Collection **head, char *line);
void release_Line_List(line_Collection **head);

/* lists_logII.c */
reg_var *insert_Variable_Node(reg_var **head, int sc_var, char *in_Var, int varLcl);
void relase_Variable_list(reg_var **head);

/* string_loggerI.c functions */
char *str_Merge(char *destination, const char *origin);
char *str_Copy(char *destination, char *origin);
int string_Comparator(char *string1, char *string2);
char *locate_Char(char *string, char ch);
int string_Span(char *string, char *processInput);

/* memcpy_logs.c */
void memory_Copy(void *ptrInstance, const void *pointer, unsigned int size);
void *reallocate_Memory(void *ptr, unsigned int os, unsigned int ns);
char **reallocateDPtr(char **ptr, unsigned int os, unsigned int ns);

/* string_loggeerII.c */
char *clone_String(const char *string);
int str_Length(const char *string);
int char_Compare(char string[], const char *divider);
char *tokenize_String(char string[], const char *divider);
int is_Number(const char *string);

/* string_loggerIII.c */
void mirror_String(char *string);

/* error_checker.c */
int recurring_Char(char *dataIn, int y);
int Separator_Error(char *dataIn, int y, char end);
int primary_Char(char *dataIn, int *y);
void show_Syntax_error(data_shell *datashell, char *dataIn, int y, int istrue);
int validate_Syntax_Error(data_shell *datashell, char *dataIn);

/* shell_loop.c */
char *uncaptioned(char *get);
void shell_iteration(data_shell *data_shell);

/* line_grapper.c */
char *read_Input_Line(int *endOfFileInput);

/* line_segmenter.c */
char *char_Exchange(char *dataIn, int isTrue);
void insert_Nodes(separated_Items **head_sl, line_Collection **head_ll, char *dataIn);
void moveForward(separated_Items **list_sl, line_Collection **list_ll, data_shell *datashell);
int separatedCom(data_shell *datashell, char *dataIn);
char **divideLine(char *dataIn);

/* variavle_env.c */
void verifyEnv(reg_var **head, char *input, data_shell *d);
int validateVar(reg_var **head, char *dataIn, char *s, data_shell *data_shell);
char *substituted_Input(reg_var **head, char *dataIn, char *new_dataIn, int len);
char *changedVar(char *dataIn, data_shell *datashell);

/* get_statments.c */
void acquire_Line(char **acq_line, size_t *num, char *buf, size_t y);
ssize_t fetch_Line(char **fetch_line, size_t *num, FILE *io);

/* excute_statment */
int run_Line(data_shell *datashell);

/* excute_cmd.c */
int verify_Current_Location(char *path, int *x);
char *which_Executable(char *cmd, char **env);
int is_Runnable(data_shell *data_shell);
int validate_cmd_Error(char *directory, data_shell *data_shell);
int invoke_Command(data_shell *data_shell);

/* shell_envI.c */
char *get_Env_Value(const char *name, char **env);
int environment(data_shell *data_shell);

/* shell_envII.c */
char *clone_Data(char *name, char *val);
void configure_Env(char *name, char *val, data_shell *data_shell);
int _set_env(data_shell *data_shell);
int _un_set_env(data_shell *data_shell);

/* cd.c */
void navigateParentDirectory(data_shell *dataShell);
void navigate_To(data_shell *dataShell);
void navigate_Back(data_shell *dataShell);
void navigate_Home(data_shell *dataShell);

/* cd changer files */
int cd_changer(data_shell *dshel);

/* get_builtin */
int (*get_builtin(char *cmd))(data_shell *datash);

/* quite_shell.c */
int end_Shell(data_shell *data_shell);

/* stdlib_logger.c */
int get_length(int x);
char *int_To_Str(int x);
int parseToInt(char *string);

/* error_logsI.c */
char *concatenateCd(data_shell *, char *, char *, char *);
char *getAndHandleCdError(data_shell *datash);
char *missing_Error(data_shell *datashell);
char *terminateShellOnError(data_shell *datashell);

/* error_logsII.c */
char *error_get_alias(char **args);
char *envIssue(data_shell *datashell);
char *error_syntax(char **args);
char *error_permission(char **args);
char *pathIssue126(data_shell *datashell);


/* grab_erros.c */
int fetchError(data_shell *datashell, int eval);

/* get_com_ident.c */
void getsigint(int si);

/* help_logsI.c */
void supportEnvHelp(void);
void supportSetenvHelp(void);
void supportUnsetenvHelp(void);
void supportGeneralHelp(void);
void supportExitHelp(void);

/* help_logsII.c */
void supportHelp(void);
void supportAliasHelp(void);
void supportCdHelp(void);

/* need_help.c */
int fetchHelp(data_shell *datashell);

#endif /*END SHELL_H*/
