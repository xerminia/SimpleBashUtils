#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

int s21_getopt(int *fe, int *fi, int *fv, int *fc, int *fl, int *fn, int *error,
               char **cln, char *buf_argc, int flag, int *fs, int *ff, int *fh, int *fo);
int flag_handling(int *fe, int *fi, int *fv, int *fc, int *fl, int *fn,
                  int *error, char **cln, char *buf_argc, int flag, int *fs,
                  int *ff, int *fh, int *fo);
void s21_grep(int fi, int fv, int fc, int fl, int fn, char *buf_argc,
              char name_file[256][256], int num_file, int fs, int fh, int fo);
void out(int flag, char *name_file, char *line, int fc, int count, int fl,
         int fn, int num_line);
void pars_flag(int argc, int *fe, int *fi, int *fv, int *fc, int *fl, int *fn,
               int *error, char **cln, char *buf_argc, int *fs, int *ff,
               int *fh, int *fo);
void pars_file(int tmp, char **argv, int fe, char *buf_argc,
               char name_file[256][256], int *num_file);
char *s21_strcat(char *dest, const char *src);
char *s21_strcpy(char *dest, const char *src);
void open_file(char *buf_argc, FILE *fp, int fv, int fc, int fl, int fi, int fn,
               char *name_file, int flag, int fo);

#endif  // SRC_GREP_S21_GREP_H_
