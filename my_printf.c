#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int my_strlen (char* str) {
    int m = 0;
    while (str[m] != 0) {
        m++;
    }
    return m;
}

void reverse (char* str) {
    for (int i = 0; i < my_strlen(str)/2; i++) {
        char temp = str[i];
        str[i] = str[my_strlen(str)-1-i];
        str[my_strlen(str)-1-i] = temp;
    }
}

char* my_itoa (char* line, long num, int base) {
    int k = 0;
    _Bool neg = 0;
    if (num<0) {
        line[k] = '-';
        k++;
        num *= -1;
        neg = 1;
    }
    while (num > 0) {
        if (num%base>9) {
            line[k] = num%base - 10 + 'a';
        } else {
            line[k] = num%base + '0';
        }
        num /= base;
        k++;
    }
    line[k] = '\0';
    if (neg) {
        reverse(&line[1]);
        return line;
    }
    reverse(line);
    return line;
}

void my_putchar (char c) {
    write(1, &c, 1);
}

void my_putstr(char* line) {
    int i = 0;
    while (line[i] != 0) {
        write(1, &line[i], 1);
        i++;
    }
}

int my_printf(char* format, ...) {
    char a;
    long d;
    char* s;
    char* number_buffer = malloc(sizeof(char)*65);
    va_list argptr;
    va_start(argptr, format);
    int count = 0;
    for(char *c = format;*c; c++)
    {
        if(*c!='%')
        {
            my_putchar(*c);
            count++;
            continue;
        }
        switch(*++c)
        {
            case 'd': 
                d = va_arg(argptr, int);
                my_putstr(my_itoa(number_buffer, d, 10));
                count += my_strlen(number_buffer);
                break;
            case 'o':
                d = va_arg(argptr, int);
                my_putstr(my_itoa(number_buffer, d, 8));
                count += my_strlen(number_buffer);
                break;
            case 'x':
                d = va_arg(argptr, long);
                my_putstr(my_itoa(number_buffer, d, 16));
                count += my_strlen(number_buffer);
                break;
            case 's':
                s = va_arg(argptr, char*);
                my_putstr(s);
                count += my_strlen(s);
                break;
            case 'c':
                a = va_arg(argptr, int);
                my_putchar(a);
                count++;
                break;
            case 'u':
                d = va_arg(argptr, unsigned int);
                my_putstr(my_itoa(number_buffer, d, 10));
                count += my_strlen(number_buffer);
                break;
            case 'p':
                d = va_arg(argptr, unsigned long);
                my_putstr("0x");
                count += 2;
                my_putstr(my_itoa(number_buffer, d, 16));
                count += my_strlen(number_buffer);
                break;
            case '%':
                my_putstr("%%");
                count += 2;
                break;
            default:
                my_putchar('%');
                my_putchar(*c);
                count += 2;
                break;
        }  
    }
    va_end(argptr);
    free(number_buffer);
    return count;
};

int main() {
    return 0;
}