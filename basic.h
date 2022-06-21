/*
 * File:   basic.h
 *         - basic definitions and declarations
 *
 * Author: Hermann Stamm-Wilbrandt
 *         Institut fuer Informatik III
 *         Roemerstr. 164 
 *         Bonn University
 *         D-53117 Bonn 
 *         Germany
 * email:  hermann@holmium.informatik.uni-bonn.de
 * phone:  0228-550-260  internal: x260 or x28, Fax: 0228-550-382
 *
 * For my safety:
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef def_basic_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifndef CLK_TCK
#define CLK_TCK 1000000
#endif

#ifdef __GNUC__
#ifndef __linux__
int fread(char *ptr, int size, int nitems, FILE *stream);
int fwrite(char *ptr, int size, int nitems, FILE *stream);
int fseek(FILE *stream, long offset, int ptrname);
int fprintf(FILE *stream, char *format,...);
int sscanf(char *s, char *format,...);
int fclose(FILE *stream);
int fflush(FILE *stream);
int printf(char *format,...);
int fgetc(FILE *);
int ungetc(char, FILE *);
int fscanf(FILE *,char *,...);
int rewind(FILE *);
long random();
void srandom(int);
long clock();
int system(char *);
#endif
#endif

#define CAT(A,B)	A##B
#define _(A,B)		CAT(A,B)
#define USING(X) X=X;


void *MALLOC(size_t n);

void FREE(void *p);

void statistics();

void err_handler(int no,char *mesg);

typedef unsigned int num;

num MIN(num x, num y);
num MAX(num x, num y);
void SWAP(num *a, num *b);

typedef num bool;

#define undef 0

#define before 0
#define after 1
#define false 0
#define true 1

#define newline (void) printf("\n")

#define def_basic_h
#endif


