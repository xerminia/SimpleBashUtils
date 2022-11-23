#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void s21_cat(int fb, int fe, int fn, int fs, int ft, int fv, char **argv,
             int error);
void open_file(int fb, int fe, int fn, int fs, int ft, int fv, char **argv);
int flag_s(int fs, int temp, char now);
int flag_b(int fb, int count, char now, char prev);
int flag_n(int fn, int fb, int count, char prev);
void flag_e(int fe, char now);
int flag_v(int fv, char now, int tmpv);
int flag_t(int ft, int tmpv, char now);
int s21_getopt(int *fb, int *fe, int *fn, int *fs, int *ft, int *fv, int error,
               char **cln);
int getoptlong(char **cln, int *fb, int *fn, int *fs, int error);
int getopt(char **cln, int *fe, int *ft, int *fb, int *fv, int *fn, int *fs,
           int error);

#endif  // SRC_CAT_S21_CAT_H_
