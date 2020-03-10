/* ************************************************************************** */
/*                                                                            */
/*   Project: custom_libc                                 ::::::::            */
/*   Members: dvoort, prmerku                           :+:    :+:            */
/*   Copyright: 2020                                   +:+                    */
/*                                                    +#+                     */
/*                                                   +#+                      */
/*                                                  #+#    #+#                */
/*   while (!(succeed = try()));                   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_UTILS_H
# define PRINTF_UTILS_H

# include <stddef.h>
# include <stdarg.h>

enum				e_length
{
	none,
	hh,
	h,
	l,
	ll,
	j,
	t,
	z,
	q,
};

typedef struct		s_buf_fd
{
	int				fd;
	size_t			printed;
	size_t			offset;
	char			buf[128];
	size_t			buf_size;
	size_t			total_written;
}					t_buf_fd;

typedef struct		s_buf_str
{
	size_t			offset;
	char			*out;
	size_t			buf_size;
}					t_buf_str;

struct				s_col_combo
{
	char			key;
	char			*code;
};

typedef void		(*t_buf_reset)(void *buf);
typedef void		(*t_buf_putstr)(void *buf, char *s);
typedef void		(*t_buf_putstri)(void *buf, char *s, size_t n);
typedef void		(*t_buf_putchar)(void *buf, char c);
typedef void		(*t_buf_flush)(void *buf);
typedef void		(*t_buf_putchars)(void *buf, char c, size_t n);
typedef int			(*t_buf_cprinted)(void *buf);

typedef struct		s_buf
{
	void			*metadata;
	t_buf_reset		reset;
	t_buf_putstr	putstr;
	t_buf_putstri	putstri;
	t_buf_putchar	putchar;
	t_buf_flush		flush;
	t_buf_putchars	putchars;
	t_buf_cprinted	chars_printed;
}					t_buf;

typedef struct		s_ft_fmt
{
	char			specifier;
	char			left_justify;
	char			force_nbr_sign;
	char			whitespace_sign;
	char			hashtag;
	char			leftpad_zeroes;
	int				precision;
	char			precision_set;
	int				orig_precision;
	int				width;
	enum e_length	length;
}					t_ft_fmt;

typedef struct		s_ft_printf
{
	t_buf			*buf;
	va_list			*args;
}					t_ft_printf;

typedef void		(*t_spec)(t_ft_printf *pf, t_ft_fmt *fmt);

/*
** The internal printf that does all the printf
*/
int					ft_inner_printf(t_ft_printf *printf, const char *fmt);

/*
** Buffers
*/
void				buf_reset(t_buf *buf);
void				buf_putstr(t_buf *buf, char *s);
void				buf_putstri(t_buf *buf, char *s, size_t n);
void				buf_putchar(t_buf *buf, char c);
void				buf_flush(t_buf *buf);
void				buf_putchars(t_buf *buf, char c, size_t n);
int					buf_chars_printed(t_buf *buf);

/*
** File-descriptor buffer implementation
*/
void				buf_fd_create(t_buf *buf, t_buf_fd *fd_buf, int fd);
void				buf_fd_reset(void *buf);
void				buf_fd_putstr(void *buf, char *s);
void				buf_fd_putstri(void *buf, char *s, size_t n);
void				buf_fd_putchar(void *buf, char c);
void				buf_fd_putchars(void *buf, char c, size_t n);
void				buf_fd_flush(void *buf);
int					buf_fd_chars_printed(void *buf);

/*
** String buffer implementation
*/
void				buf_str_create(t_buf *buf, t_buf_str *str_buf, char *str,
		size_t buf_size);
void				buf_str_reset(void *buf);
void				buf_str_putstr(void *buf, char *s);
void				buf_str_putstri(void *buf, char *s, size_t n);
void				buf_str_putchar(void *buf, char c);
void				buf_str_putchars(void *buf, char c, size_t n);
void				buf_str_flush(void *buf);
int					buf_str_chars_printed(void *buf);

/*
** Format reading
*/
void				fmt_read(char **str, va_list *args, t_ft_fmt *fmt);

/*
** Specifiers
*/
t_spec				spec_get(char spec);
void				spec_default(t_ft_printf *pf, t_ft_fmt *fmt);
void				spec_string(t_ft_printf *pf, t_ft_fmt *fmt);
void				spec_signed_int(t_ft_printf *pf, t_ft_fmt *fmt);
void				spec_unsigned_int(t_ft_printf *pf, t_ft_fmt *fmt);
void				spec_base(t_ft_printf *pf, t_ft_fmt *fmt);
void				spec_ptr(t_ft_printf *pf, t_ft_fmt *fmt);
void				spec_char(t_ft_printf *pf, t_ft_fmt *fmt);
void				spec_charsprinted(t_ft_printf *pf, t_ft_fmt *fmt);

/*
** Private number conversions
*/
int					ft_pf_atoi(char **str);
char				ft_lltoa(char *out, long long value);
void				ft_ulltoa(char *out, unsigned long long value);
void				ft_ulltoa_base(char *out, char *base,
									unsigned long long value);

#endif
