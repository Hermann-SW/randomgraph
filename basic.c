/*
 * File:   basic.c
 *         - error handler
 *         - memory management
 *         - ...
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

#include "basic.h"

void err_handler(int no,char *mesg)
  {
  (void) fprintf(stderr,"[%d] %s\n",no,mesg);
  if (no!=0)
    exit(no);
  }

static int _malloc=0;
static int _free=0;

void *MALLOC(size_t n)
  {
  void *p = malloc(n);
  _malloc++;
  return p;
  }

void FREE(void *p)
  {
  (void) free(p);
  _free++;
  }

void statistics()
  {
  (void) fprintf(stderr,"\n");
  (void) fprintf(stderr,"-------------------------------------\n");
  (void) fprintf(stderr,"malloc: %d   malloc-free: %d\n",_malloc,_malloc-_free);
  }

num MIN(num x, num y) { return (x<y) ? x : y; }
num MAX(num x, num y) { return (x>y) ? x : y; }

void SWAP(num *a, num *b) { num h=*a; *a=*b; *b=h; }


void USE1()
  {
  (void) MALLOC(MIN(0,1)+MAX(2,3));
  FREE(0);
  statistics();
  err_handler(7,"da");
  USE1();
  }

