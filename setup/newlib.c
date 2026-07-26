extern int (* _stdout_putchar)(char c);

void _putchar(char c) {
    _stdout_putchar(c);
}

