#ifndef SHELL_H
#define SHELL_H

char *read_line(void);
char **split_line(char *line);
int execute(char **args);

#endif /* SHELL_H */
