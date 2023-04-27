#include "shell.h"


/**
 * change_directory - changes the curren
 *  working directory of the shell
 * @content: struct parameter
 * Desc: getcwd gets the current working directory and
 *	stores it in the buffer. If it is empty, it sets the dir
 *	variable to the value of the HOME environment variable,
 *	and if that fails, it sets dir to the value of the PWD
 *	environment variable. It then calls the chdir function to
 *	change the current working directory to the value of dir.
 *	If the first argument is not empty, the function checks if
 *	it is equal to "-". If it is, it prints the current working
 *	directory to standard output and sets the dir variable to the
 *	value of the OLDPWD. If the first argument is not empty and
 *	not equal to "-", the function simply calls chdir to change
 *	the current working directory to the value of the first argument.
 *	Then it sets OLDPWD and PWD to the shell's environment variable table
 *
 * Return: 0 (success), 1 (error)
 */
int change_directory(sh_args *content)
{
    const int buf_size = 1024;
    int cd_success;
    char *buff = malloc(buf_size * sizeof(char));
    char *wrkin_dir = getcwd(buff, buf_size);
    char *err_msg, *dir = NULL;

    if (!buff)
    {
        _puts("Error: could not allocate memory\n");
        return (1);
    }
    if (!wrkin_dir)
    {
        err_msg = strerror(errno);
        _puts("Error: ");
        _puts(err_msg);
        _putchar('\n');
        return (1);
    }
    if (!content->argv[1])
        dir = get_default_directory(content);
    else if (cmpare_strs(content->argv[1], "-") == 0)
    {
        dir = get_previous_directory(content, wrkin_dir);
        if (!dir)
        {
            _puts(wrkin_dir);
            _putchar('\n');
            return (1);
        }
        _puts(dir);
        _putchar('\n');
    }
    else
        dir = content->argv[1];
    cd_success = change_directory_helper(content, dir, buff, buf_size);
    free(buff);
    return (cd_success);
}

char* get_default_directory(sh_args *content)
{
    char *dir = getenv_clone(content, "HOME=");
    if (!dir)
        dir = getenv_clone(content, "PWD=");
    return dir;
}

char* get_previous_directory(sh_args *content, char *wrkin_dir)
{
    char *dir = getenv_clone(content, "OLDPWD=");
    if (!dir)
    {
        _puts(wrkin_dir);
        _putchar('\n');
        return NULL;
    }
    return dir;
}

int change_directory_helper(sh_args *content, char *dir, char *buff, int buf_size)
{
    int cd_success = chdir(dir);
    if (cd_success == -1)
    {
        print_err_mesg(content, "can't cd to ");
        write_with_buffer('\n');
    }
    else
    {
        env_setter(content, "OLDPWD", getenv_clone(content, "PWD="));
        env_setter(content, "PWD", getcwd(buff, buf_size));
    }
    return cd_success;
}
