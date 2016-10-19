#include <stdio.h>
#include <stdarg.h>

int debug(const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  return vprintf(fmt, args);
}

int main(void) {
  debug("pi=%6.2f\n", 3.14159);
}
