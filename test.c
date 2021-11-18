#include <stdio.h>

char* good_night();

int main() {
    char *hello;
    printf("hello, i'm going to bed :(\n");
    hello = good_night();
	hello[0] = 'f';
    printf("%s %c\n", hello, hello[0]);
    return 0;
}

char* good_night() {
    return "good night";
}
