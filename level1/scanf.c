#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
	int get ;
	while((get=fgetc(f))!=EOF && isspace(get));
	if(get==EOF)
		return -1;
	ungetc(get,f);
	return 1;
}
int match_char(FILE *f, const char c)
{
	int get =fgetc(f);
	if(get==EOF)
		return -1;
	if(get==c)
		return 1;
	ungetc(get,f);
	return 0;
}

int scan_char(FILE *f, va_list ap)
{
	int get =fgetc(f);
	char *str=va_arg(ap,char *);
	if(get==EOF)
		return -1;
	*str=get;
	return 1;
}

int scan_int(FILE *f, va_list ap)
{
	int *arg=va_arg(ap,int *);
	int get=fgetc(f);
	int s=1;
	int r=0;
	if(get =='-'||get =='+')
	{
		if(get=='-')
			s=-1;
		int getnext=fgetc(f);
		if(!isdigit(getnext))
		{
			ungetc(getnext,f);
			ungetc(get,f);
			return -1;
		}
		get=getnext;
	}
	else if(!isdigit(get))
	{
		ungetc(get,f);
		return -1;
	}
	while (isdigit(get))
	{
		r= r*10+(get -'0');
		get=fgetc(f);
	}
	ungetc(get,f);
	*arg=r*s;
	return 1;
}

int scan_string(FILE *f, va_list ap)
{
	int get =fgetc(f);
	char *str=va_arg(ap,char *);
	int i=0;
	if(get==EOF)
		return -1;
	while(!isspace(get) && get!=EOF)
	{
		str[i++]=get;
		get=fgetc(f);
	}
	str[i]='\0';
	ungetc(get,f);
	return 1;
}

int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	// int c = fgetc(f);
	// if (c == EOF)
	// 	return EOF;
	// ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	if (nconv == 0 && feof(f))
		return -1;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main(void)
{
	int a = 0;
	int b = 1;
	char c[100] = "g";

	printf("Enter a:\n");
	ft_scanf("%d %s %d", &a, c, &b);

	printf("\na: %d", a);
	printf("\nc: %s", c);
	printf("\nb: %d\n", b);
	return 0;
}
