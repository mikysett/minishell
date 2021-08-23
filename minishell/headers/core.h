#ifndef CORE_H
# define CORE_H

// CORE_UTIL

void	ft_error_exit(t_err_code err);
void	ft_print_err(t_err_code err);

// MEMORY_UTIL

void	*calloc_or_exit(size_t count, size_t size);

#endif
