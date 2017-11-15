#ifndef FILLIT_H
# define FILLIT_H

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>

void	ft_error_msg(void);
int		open_file(char **argv, char *buf);

#endif
