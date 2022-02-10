#include "../includes/fractol.h"

static int	get_int_len(double n)
{
	int	len;
	int	n2;

	len = 1;
	n2 = (int)(n / 10);
	while (n2 != 0)
	{
		n2 /= 10;
		len += 1;
	}
	return (len);
}

static int	get_decimal_point_len(double n)
{
	int	len;

	len = 1;
	while (1)
	{
		n *= 10.0;
		if (n - (int)(n / 1))
			len += 1;
		else
			break ;
	}
	return (len);
}

char	*f2a(double f)
{
	int		len;
	int		len2;
	int		i;
	char	*temp;
	double	f2;

	len = get_int_len(f);
	len2 = get_decimal_point_len(f);
	temp = (char *)malloc(sizeof(char) * (len + len2 + 2 + (f < 0)));
	if (temp == NULL)
		return (NULL);
	i = len + len2 + 1 + (f < 0);
	temp[i] = '\0';
	if (f < 0)
		temp[0] = '-';
	if (f < 0)
		f *= -1;
	f2 = f;
	while (len2)
		temp[--i] = (int)(f2 * pow(10, len2--)) % 10 + '0';
	temp[--i] = '.';
	while (len)
		temp[--i] = (int)(f / pow(10, --len)) % 10 + '0';
	return (temp);
}

double	a2f(char *str)
{
	double	temp;
	double	minus;
	int		depth;

	minus = 1;
	if (str[0] == '-')
		minus = -1;
	temp = ft_atoi(str);
	if (temp < 0)
		temp *= -1;
	while (*str++ != '.')
		depth = 1;
	depth = 1;
	while (ft_isdigit(*str))
		temp += (*str++ - '0') / pow(10, depth++);
	return (temp * minus);
}
