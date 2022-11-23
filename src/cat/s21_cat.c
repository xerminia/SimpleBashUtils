#include "s21_cat.h"

int main(int argc, char **argv) {
  int error = 0, fb = 0, fe = 0, fn = 0, fs = 0, ft = 0, fv = 0;
  char **cln;
  cln = argv;
  cln++;
  argc--;
  while (argc != 0) {
    error = s21_getopt(&fb, &fe, &fn, &fs, &ft, &fv, error, cln);
    if (error == 1) break;
    cln++;
    argc--;
  }
  s21_cat(fb, fe, fn, fs, ft, fv, argv, error);
  return error;
}

int s21_getopt(int *fb, int *fe, int *fn, int *fs, int *ft, int *fv, int error,
               char **cln) {
  if (**cln == '-') {
    *cln += 1;
    if (**cln == '-') {
      error = getoptlong(cln, fb, fn, fs, error);
    } else {
      error = getopt(cln, fe, ft, fb, fv, fn, fs, error);
    }
  }
  return error;
}

int getopt(char **cln, int *fe, int *ft, int *fb, int *fv, int *fn, int *fs,
           int error) {
  while (**cln != '\0') {
    if (**cln == 'E' || **cln == 'T' || **cln == 'b' || **cln == 'v' ||
        **cln == 'n' || **cln == 's' || **cln == 't' || **cln == 'e') {
      if (**cln == 'E') *fe = 1;
      if (**cln == 'T') *ft = 1;
      if (**cln == 'b') *fb = 1;
      if (**cln == 'v') *fv = 1;
      if (**cln == 'n') *fn = 1;
      if (**cln == 's') *fs = 1;
      if (**cln == 't') {
        *ft = 1;
        *fv = 1;
      }
      if (**cln == 'e') {
        *fe = 1;
        *fv = 1;
      }
    } else {
      printf("usage: cat [-benstuv] [file ...]\n");
      error = 1;
      break;
    }
    *cln += 1;
  }
  return error;
}

int getoptlong(char **cln, int *fb, int *fn, int *fs, int error) {
  *cln += 1;
  if (strcmp(*cln, "number-nonblank") == 0 || strcmp(*cln, "number") == 0 ||
      strcmp(*cln, "squeeze-blank") == 0) {
    if (strcmp(*cln, "number-nonblank") == 0) *fb = 1;
    if (strcmp(*cln, "number") == 0) *fn = 1;
    if (strcmp(*cln, "squeeze-blank") == 0) *fs = 1;
  } else {
    printf("usage: cat [-benstuv] [file ...]\n");
    error = 1;
  }
  while (**cln != '\0') {
    *cln += 1;
  }
  return error;
}

void s21_cat(int fb, int fe, int fn, int fs, int ft, int fv, char **argv,
             int error) {
  argv++;
  int tmp = 0;
  while (*argv && error != 1) {
    if (**argv == '\0' && tmp != 1) {
      argv++;
    } else {
      open_file(fb, fe, fn, fs, ft, fv, argv);
      tmp = 1;
      argv++;
    }
  }
}

void open_file(int fb, int fe, int fn, int fs, int ft, int fv, char **argv) {
  FILE *fp;
  if ((fp = fopen(*argv, "r")) == NULL) {
    printf("cat: %s: No such file of directory", *argv);
  } else {
    char now, prev = '\n';
    int count = 1, temp = 0;
    while ((now = getc(fp)) != EOF) {
      temp = flag_s(fs, temp, now);
      if (temp < 3) {
        int tmpv;
        tmpv = 0;
        count = flag_b(fb, count, now, prev);
        count = flag_n(fn, fb, count, prev);
        flag_e(fe, now);
        tmpv = flag_v(fv, now, tmpv);
        tmpv = flag_t(ft, tmpv, now);
        if (!tmpv) printf("%c", now);
      }
      prev = now;
    }
    fclose(fp);
  }
}

int flag_s(int fs, int temp, char now) {
  if (fs) {
    if (now == '\n') temp++;
    if (now != '\n') temp = 0;
  }
  return temp;
}

int flag_b(int fb, int count, char now, char prev) {
  if (fb) {
    if (prev == '\n' && now != '\n') {
      printf("%6d\t", count);
      count++;
    }
  }
  return count;
}

int flag_n(int fn, int fb, int count, char prev) {
  if (fn && !fb) {
    if (prev == '\n') {
      printf("%6d\t", count);
      count++;
    }
  }
  return count;
}

void flag_e(int fe, char now) {
  if (fe && now == '\n') printf("$");
}

int flag_v(int fv, char now, int tmpv) {
  if (fv) {
    if (-1 < now && now != 9 && now != 10 && now < 32) {
      printf("^%c", now + 64);
      tmpv = 1;
    }
  }
  return tmpv;
}

int flag_t(int ft, int tmpv, char now) {
  if (ft) {
    if (now == '\t') {
      printf("^I");
      tmpv = 1;
    }
  }
  return tmpv;
}
