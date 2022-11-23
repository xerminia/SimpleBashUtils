#include "s21_grep.h"

int main(int argc, char **argv) {
  int fe = 0, fi = 0, fv = 0, fc = 0, fl = 0, fn = 0, error = 0, num_file = 0,
      fs = 0, ff = 0, fh = 0, fo = 0;
  argv++, argc--;
  char *buf_argc = (char *)malloc(8096);
  char name_file[256][256];
  s21_strcpy(buf_argc, "(");
  char **cln = argv;
  int tmp = argc;
  pars_flag(argc, &fe, &fi, &fv, &fc, &fl, &fn, &error, cln, buf_argc, &fs, &ff,
            &fh, &fo);
  pars_file(tmp, argv, fe, buf_argc, name_file, &num_file);
  for (int i = 0; buf_argc[i] != '\0'; i++) {
    argc = i;
  }
  buf_argc[argc] = ')';
  if (!error) {
    s21_grep(fi, fv, fc, fl, fn, buf_argc, name_file, num_file, fs, fh, fo);
  }
  free(buf_argc);
  return error;
}

void pars_flag(int argc, int *fe, int *fi, int *fv, int *fc, int *fl, int *fn,
               int *error, char **cln, char *buf_argc, int *fs, int *ff,
               int *fh, int *fo) {
  while (argc) {
    int flag;
    flag = 0;
    flag = s21_getopt(fe, fi, fv, fc, fl, fn, error, cln, buf_argc, flag, fs,
                      ff, fh, fo);
    if (*error == 1) break;
    if (flag == 1) {
      *cln = NULL, cln++, argc--;
    }
    cln++, argc--;
  }
}

void pars_file(int tmp, char **argv, int fe, char *buf_argc,
               char name_file[256][256], int *num_file) {
  while (tmp) {
    if (*argv != NULL) {
      if (!fe) {
        s21_strcat(buf_argc, *argv);
        s21_strcat(buf_argc, "|");
        fe++;
      } else {
        s21_strcat(name_file[*num_file], *argv);
        *num_file += 1;
      }
    }
    tmp--, argv++;
  }
}

int s21_getopt(int *fe, int *fi, int *fv, int *fc, int *fl, int *fn, int *error,
               char **cln, char *buf_argc, int flag, int *fs, int *ff, int *fh,
               int *fo) {
  if (**cln == '-') {
    *cln += 1;
    while (**cln != '\0') {
      int tmp1 = *fe;
      flag = flag_handling(fe, fi, fv, fc, fl, fn, error, cln, buf_argc, flag,
                           fs, ff, fh, fo);
      if (tmp1 != *fe || *error == 1) break;
      *cln += 1;
    }
    *cln = NULL;
  }
  return flag;
}

int flag_handling(int *fe, int *fi, int *fv, int *fc, int *fl, int *fn,
                  int *error, char **cln, char *buf_argc, int flag, int *fs,
                  int *ff, int *fh, int *fo) {
  if (**cln == 'e' || **cln == 'i' || **cln == 'v' || **cln == 'c' ||
      **cln == 'l' || **cln == 'n' || **cln == 's' || **cln == 'h' ||
      **cln == 'f' || **cln == 'o') {
    if (**cln == 'i') *fi = 1;
    if (**cln == 'v') *fv = 1;
    if (**cln == 'c') *fc = 1;
    if (**cln == 'l') *fl = 1;
    if (**cln == 'n') *fn = 1;
    if (**cln == 's') *fs = 1;
    if (**cln == 'o') *fo = 1;
    if (**cln == 'h') *fh = 1;
    if (**cln == 'f') {
      *ff = 1;
      *cln += 1;
      if (**cln == '\0') {
        flag = 1;
        *cln = NULL;
        cln++;
      }
      FILE *fp;
      if ((fp = fopen(*cln, "r")) != NULL) {
        char ch;
        // int tmp;
        while (*buf_argc != '\0') buf_argc++;
        while ((ch = getc(fp)) != EOF) {
          if (ch == '\n') {
            *buf_argc++ = ch;
            *buf_argc++ = '|';
          } else {
            *buf_argc++ = ch;
          }
        }
        fclose(fp);
      }
      *fe += 1;
      *cln = NULL;
    } else if (**cln == 'e') {
      *cln += 1;
      if (**cln == '\0') {
        flag = 1;
        *cln = NULL;
        cln++;
      }
      s21_strcat(buf_argc, *cln);
      s21_strcat(buf_argc, "|");
      *fe += 1;
      *cln = NULL;
    }
  } else {
    if (!fs) printf("grep: unknown --directories option\n");
    *error = 1;
  }
  return flag;
}

void s21_grep(int fi, int fv, int fc, int fl, int fn, char *buf_argc,
              char name_file[256][256], int num_file, int fs, int fh, int fo) {
  int flag = 0;
  if (name_file[1][0] != '\0' && !fh) {
    flag = 1;
  }
  for (int i = 0; i < num_file; i++) {
    FILE *fp;
    if ((fp = fopen(name_file[i], "r")) != NULL) {
      open_file(buf_argc, fp, fv, fc, fl, fi, fn, name_file[i], flag, fo);
    } else if (!fs) {
      printf("grep: %s : No such file of directory\n", name_file[i]);
    }
  }
}

void open_file(char *buf_argc, FILE *fp, int fv, int fc, int fl, int fi, int fn,
               char *name_file, int flag, int fo) {
  int count = 0, num_line = 0;
  regex_t regex;
  if (fi)
    regcomp(&regex, buf_argc, REG_EXTENDED | REG_ICASE);
  else
    regcomp(&regex, buf_argc, REG_EXTENDED);
  char *line = NULL;
  size_t len;
  size_t nmatch = 2;
  regmatch_t pmatch[2];
  while (getline(&line, &len, fp) != EOF) {
    num_line++;
    int isMatch = regexec(&regex, line, nmatch, pmatch, 0);
    if (isMatch != REG_NOMATCH && !fv) {
      if (!fc && !fl) {
        if (fo) {
          while (isMatch != REG_NOMATCH) {
            char *tmp_line = line;
            printf("%.*s\n", (int)(pmatch[1].rm_eo - pmatch[1].rm_so),
                   tmp_line + pmatch[1].rm_so);
            tmp_line += pmatch[1].rm_eo;
            isMatch = regexec(&regex, tmp_line, 0, pmatch, 0);
          }
        } else {
          out(flag, name_file, line, fc, count, fl, fn, num_line);
        }
      }
      count++;
    } else if (isMatch == REG_NOMATCH && fv) {
      if (!fc && !fl) {
        out(flag, name_file, line, fc, count, fl, fn, num_line);
      }
      count++;
    }
  }
  if (fc || fl) out(flag, name_file, line, fc, count, fl, fn, num_line);
  if (line) {
    free(line);
  }
  regfree(&regex);
  fclose(fp);
}

void out(int flag, char *name_file, char *line, int fc, int count, int fl,
         int fn, int num_line) {
  if (flag && fc && fl && count) {
    printf("%s:1\n", name_file);
  } else if (!flag && fc && fl && count) {
    printf("1\n");
  }
  if (flag && fc != 1 && !fl && !fn)
    printf("%s:%s", name_file, line);
  else if (!flag && !fc && !fl && !fn)
    printf("%s", line);
  else if (flag && fc && !fl && !fn)
    printf("%s:%d\n", name_file, count);
  else if (!flag && fc && !fl && !fn)
    printf("%d\n", count);
  else if (fl && count > 0)
    printf("%s\n", name_file);
  else if (fn && flag)
    printf("%s:%d:%s", name_file, num_line, line);
  else if (fn && !flag)
    printf("%d:%s", num_line, line);
}

char *s21_strcat(char *dest, const char *src) {
  char *cln = dest;
  while (*dest) {
    dest++;
  }
  while (*src) {
    *dest++ = *src++;
  }
  *dest++ = '\0';
  return cln;
}

char *s21_strcpy(char *dest, const char *src) {
  char *cln = dest;
  while (*src) {
    *dest++ = *src++;
  }
  *dest++ = '\0';
  return cln;
}
