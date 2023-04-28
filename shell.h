#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>


/* when using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0


/* Command Chaining sequence */
#define CMD_AND		2
#define CMD_OR		1
#define CMD_NORM	0
#define CMD_CHAIN	3


/* File History Specifiers */
#define HIST_MAX	4096
#define HIST_FILE	".simple_shell_history"


/* Number Converters */
#define CONVERT_UNSIGNED	2
#define CONVERT_LOWERCASE	1


/* Buffer sizes for Read-Write */
#define WRITE_BUF_SIZE 1024
#define READ_BUF_SIZE 1024
#define BUF_FLUSH -1


extern char **environ;


/**
 * struct l_list - singly linked list
 * @str: string
 * @num: number field
 * @link: points to the next node
 */
typedef struct l_list
{
	int num;
	char *str;
	struct l_list *link;
} l_list;

/**
 *struct shell_args - stores arguments and environment variables for a shell
 * @arg: command to be executed
 * @argv: array of pointers to the arguments for the command
 * @path: path to the command
 * @argc: number of arguments for the command
 * @line_count: number of lines in the command
 * @err_num: error number if the command fails
 * @linecount_flag: flag indicating if the command is a line count command
 * @fname: name of the file for the command
 * @env: array of pointers to the environment variables
 * @environ: linked list of environment variables
 * @history: linked list of previous commands
 * @alias: linked list of aliases
 * @env_changed: flag show if the environment variables have been changed
 * @status: exit status of the command
 * @cmd_buf: pointer to a buffer that stores the command chain
 * @cmd_buf_type: type of the command chain
 * @readfd: file descriptor for the command
 * @histcount: number of commands in the history
 */
typedef struct shell_args
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	l_list *env;
	l_list *history;
	l_list *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} sh_args;

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
	int (*func)(sh_args *);
} builtin_table;


/* PROTOTYPE DEFINATIONS */

/* alias */
int alias_to_str(sh_args *content, char *str);
int remv_alias(sh_args *content, char *str);
int alias_printer(l_list *node);
int alias_clone(sh_args *);


/* buffer_handlers */
int write_with_buffer(char);
void write_string_with_buffer(char *);


/* dym_mem_allocator */
void *mem_alloc(void *, unsigned int, unsigned int);
char *memset_clone(char *, char, unsigned int);
void multi_free(char **);
int free_n_NULL(void **);


/* env_getter */
int env_setter(sh_args *, char *, char *);
int unsetenv_clone(sh_args *, char *);
char **environ_getter(sh_args *);


/* environment_handlers */
int check_env_setter(sh_args *);
int check_env_unsetenv(sh_args *);
int populat_listof_env(sh_args *);
int env_clone(sh_args *);
char *getenv_clone(sh_args *, const char *);


/* error_handlers1 */
void print_err_mesg(sh_args *, char *);
int exit_str_to_int(char *);


/* exit_checker */
int change_directory(sh_args *);
int help_command(sh_args *);
int shell_exit(sh_args *);


/* file-descriptor_handlers */
int write_string_to_fd(char *str, int fd);
int write_car_to_fd(int fil_des, char car);
int prnt_decim_int(int, int);


/* history_getter */
int load_history(sh_args *content);
int write_shel_histry(sh_args *content);
int add_to_history(sh_args *content, char *buf, int linecount);
char *get_hist_file_path(sh_args *content);
int update_hist_node_numbrs(sh_args *incontentfo);


/* history_list */
int print_command_hist(sh_args *);


/* hsh_handlers */
int custom_shell(sh_args *, char **);
void findAndExecCommand(sh_args *);
void custom_fork(sh_args *);
int search_and_exec_builtin(sh_args *);


/* hsh_handlers1 */
int is_interactive(sh_args *);
int is_delimiter(char, char *);


/* info_getter */
void fill_sh_args(sh_args *, char **);
void reset_sh_args(sh_args *);
void free_sh_args(sh_args *, int);


/* l_list_handler */
size_t prnt_l_list_str(const l_list *);
l_list *new_end_node(l_list **, const char *, int);
int delete_node_index(l_list **, unsigned int);
void free_l_list(l_list **);


/* l_list_handler1 */
ssize_t find_node_index(l_list *, l_list *);
l_list *get_first_node_with_prefix(l_list *, char *, char);
size_t list_len(const l_list *);
size_t prnt_l_list_with_index(const l_list *);
char **conv_list_to_strings(l_list *);


/* line_getter */
ssize_t process_input(sh_args *);
ssize_t read_into_buffer(sh_args *content, char *buf, size_t *i);
ssize_t get_input_from_stdin(sh_args *content, char **buf, size_t *len);
int read_input_line(sh_args *, char **, size_t *);
void handle_sigInt(int);


/* parse_handlers */
char *find_exec_path(sh_args *, char *, char *);
int is_file_exec(sh_args *, char *);
char *copy_chars_without_delimiter(char *, int, int);


/* string_handlers */
char *car_finder(char *, char);
char *string_concat(char *, char *, int);
char *cpy_str(char *, char *, int);
void coments_remover(char *);
char *custom_itoa(long int, int, int);


/* string_handlers1 */
char *find_substr_at_start(const char *, const char *);
int len_of_str(char *);
char *concat_str(char *, char *);
int cmpare_strs(char *, char *);


/* string_handlers2 */
int _putchar(char);
void _puts(char *);
char *str_cpy(char *, char *);
char *str_dup(const char *);


/* token_handlers */
char **custom_strtow(char *, char *);


/* token_handlers */
void evaluate_command_chain(sh_args *, char *, size_t *, size_t, size_t);
int detect_command_chaining(sh_args *, char *, size_t *);
int replaceStr_Contnt(char **, char *);
int replace_alias_with_value(sh_args *);
int replace_var_values(sh_args *);


#endif /* MAIN_H */
