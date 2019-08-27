#include <stdio.h>

void printstring(const char *frm, const char *to) {
  fputc('<', stdout);  // <...>\n Added for output clarity
  while (frm < to) {
    fputc(*frm++, stdout);
  }
  fputc('>', stdout);
  fputc('\n', stdout);
}

void split_space_not_quote(const char *s) {
  const char *start;
  int state = ' ';
  while (*s) {
    switch (state) {
      case '\n': // Could add various white-space here like \f \t \r \v
      case ' ': // Consuming spaces
        if (*s == '\"') {
          start = s;
          state = '\"';  // begin quote
        } else if (*s != ' ') {
          start = s;
          state = 'T';
        }
        break;
      case 'T': // non-quoted text
        if (*s == ' ') {
          printstring(start, s);
          state = ' ';
        } else if (*s == '\"') {
          state = '\"'; // begin quote
        }
        break;
      case '\"': // Inside a quote
        if (*s == '\"') {
          state = 'T'; // end quote
        }
        break;
    }
    s++;
  } // end while
  if (state != ' ') {
    printstring(start, s);
  }
}

int main(void) {
  split_space_not_quote("Insert \"hello world\" to dbms");
  return 0;
}
