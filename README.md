# 0x16. C - Simple Shell
A Project done by a team of 2 people (Team: [Victoria Iria](https://github.com/EseVic), [Israel Oyetunji](https://github.com/x9x96))

# List of allowed functions and system calls
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)

# Compilation
## The shell compilation is to be done this way:

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

## Citation
We admit the framework for ```hsh()``` (simple_shell) custom build utilized in this project is sourced from
+ simple_shell (2022) ALX Simple Shell Team Project [[Source code](https://github.com/ehoneahobed/simple_shell)]

## Attribution
High regards to **OBED EHONEAH** and **JUSTICE MENSAH BLAY MEWUBE** for the [solution](https://github.com/ehoneahobed/simple_shell) to this project as we were able to put time into understanding the functionality of the linux bash shell
