#include "../includes/fractol.h"

//문자열을 double형으로 변환하는 함수
double  a2f(char *str)
{
    double	temp;
	double	minus;
	int		depth;

	minus = 1;
	if (str[0] == '-')
	{
		minus = -1;
		str++;
	}
    temp = ft_atoi(str);
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		depth = 1;
		while (ft_isdigit(*(++str)))
			temp += (double)(*str - '0') / pow(10, depth++);
	}
    return (temp * minus);
}
