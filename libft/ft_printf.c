/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltournie <ltournie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 15:18:59 by ltournie          #+#    #+#             */
/*   Updated: 2026/05/07 17:02:55 by ltournie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_shortarg(va_list arg, int print_char, char c)
{
	if (c == '%')
		print_char = ft_putchar('%', print_char);
	else if (c == 'c')
		print_char = ft_putchar(va_arg(arg, int), print_char);
	else if (c == 's')
		print_char = ft_putstr(va_arg(arg, char *), print_char);
	else if (c == 'd' || c == 'i')
		print_char = ft_putnbr(va_arg(arg, int), print_char);
	else if (c == 'u')
		print_char = ft_putnbru(va_arg(arg, unsigned int), print_char);
	else if (c == 'x')
		print_char = ft_putnbrhex(va_arg(arg, unsigned int), print_char, 'l');
	else if (c == 'X')
		print_char = ft_putnbrhex(va_arg(arg, unsigned int), print_char, 'U');
	else if (c == 'p')
		print_char = ft_putpoint((unsigned long)va_arg(arg, void *),
				print_char);
	return (print_char);
}

int	ft_printf(const char *str, ...)
{
	int			i;
	va_list		arg;
	int			print_char;

	va_start(arg, str);
	i = -1;
	print_char = 0;
	if (!str)
		return (0);
	while (str[++i] != '\0')
	{
		if (str[i] == '%')
		{
			print_char = ft_shortarg(arg, print_char, str[i + 1]);
			if (ft_strchr("csdiuxXp%%", str[i + 1]) != NULL)
				i++;
			else
				print_char = ft_putchar(str[i], print_char);
		}
		else
			print_char = ft_putchar(str[i], print_char);
	}
	va_end(arg);
	return (print_char);
}
