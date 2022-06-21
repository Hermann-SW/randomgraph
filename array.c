/*
 * File:   array.c
 *         - implementation of array datatype
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
#include "array.h"

/*----------------------------------------------------------------------------*/

num *new_array(num k) 
  { 
  num *p=(num *) MALLOC(k*sizeof(num)); 
  if (p==NULL) 
    err_handler(1,"out of memory during array allocation");
  p[0]=0;
  return p;
  }

void delete_array(num *A) { FREE(A); }

void init_array(num low, num high, num x, num *A) 
  { num i; for(i=low; i<=high; i++)  A[i]=x; }


double *new_array_of_double(num k) 
  { 
  double *p=(double *) MALLOC(k*sizeof(double)); 
  if (p==NULL) 
    err_handler(1,"out of memory during array allocation");
  p[0]=0;
  return p;
  }

void delete_array_of_double(double *A) { FREE(A); }

void print_array(num low, num high, num *A)
  {
  num i;

  for(i=low; i<=high; i++)  printf("+---");
  printf("+\n");
  for(i=low; i<=high; i++)  printf("|%3d",i);
  printf("|\n");
  for(i=low; i<=high; i++)  printf("+---");
  printf("+\n");
  for(i=low; i<=high; i++)  printf("|%3d",A[i]);
  printf("|\n");
  for(i=low; i<=high; i++)  printf("+---");
  printf("+\n");
  }

void print_array_of_double(num low, num high, double *A)
  {
  num i;

  for(i=low; i<=high; i++)  printf("+------");
  printf("+\n");
  for(i=low; i<=high; i++)  printf("|%6d",i);
  printf("|\n");
  for(i=low; i<=high; i++)  printf("+------");
  printf("+\n");
  for(i=low; i<=high; i++)  printf("|%6.2f",A[i]);
  printf("|\n");
  for(i=low; i<=high; i++)  printf("+------");
  printf("+\n");
  }

void USE2()
  {
  (void) new_array(0);
  delete_array(0);
  (void) new_array_of_double(0);
  delete_array_of_double(0);
  USE2();
  }

