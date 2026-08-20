/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knajmech <knajmech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 14:04:55 by dstumpf           #+#    #+#             */
/*   Updated: 2026/08/18 14:21:43 by knajmech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>

typedef struct s_node
{
	void			*content;
	struct s_node	*next;
}				t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
	size_t	len;
}			t_list;

int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
bool	ft_is_numeric(char *input);
int		ft_islower(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_atoi(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_itoa_buff(int n, char *buff, size_t size);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_lstadd_back(t_list *lst, t_node *new);
void	ft_lstadd_front(t_list *lst, t_node *new);
void	ft_lstclear(t_list *lst, void (*del)(void *));
void	ft_lstdelone(t_node *node, void (*del)(void *));
void	ft_lstmid_rm(t_list *l, t_node *rm, t_node *pre, void (*d)(void *));
bool	ft_lstswitch(t_list *lst, t_node *dst, t_node *src, t_node *pre_src);
t_list	*ft_lstnew(void);
t_node	*ft_nodenew(void *content);
void	ft_lstprint(t_list *lst, void (*print_fn)(void *content));
bool	in_charset(char c, const char *charset);
size_t	count_words(const char *s, const char *sep);
size_t	count_nums(const char *s);
int		ft_atoi_multi(char **nptr);
int		ft_iswhitespace(const char c);
int		ft_atoi_hex_multi(char **nptr);
int		ft_strlen_char(char *str, char delimitter);
char	*ft_strndup(const char *s, char delimitter);
t_node	*ft_nodeadd_back(t_node **lst, t_node *new, t_node *tail);
t_node	*ft_nodelast(t_node *lst);
size_t	ft_count_2d(char **argv);
long	ft_atol(const char *nptr);

#endif
