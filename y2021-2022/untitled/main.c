#include <stdio.h>

size_t len_string(const char *start)
{
  size_t len = 0;
  while(start[len])
  {
    len++;
  }
// for (size_t x = 0; p[x]; x++)
  return len;
}

size_t len_string2(const char *start)
{
  return sizeof(*start) / sizeof (char);
}

int main(void)
{
//    char str[20];
//    str[0] = 'a';
//    str[1] = 'b';
//    str[2] = 'c';
//    printf(len_string2(&str[0]));
    char x[20];
//    while (scanf("%s", x));
//    scanf("%19s", x);
    printf(x);
    return 0;
}
