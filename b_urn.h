/*
 * File:   b_urn.h
 *         - implementation of datatype bounded urn
 *           (see report for description)
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
#ifndef def_b_urn

#include "basic.h"
#include "array.h"

                         
#define b_urn(N)							\
                                                                   	\
num* _(N,_V);								\
num  _(N,_n);								\
num  _(N,_actual);							\
                                                                   	\
void _(N,_new)(int s)							\
  { 									\
  if (s<1) err_handler(88,"b_urn: bad size");                		\
  _(N,_n) = s+1;							\
  _(N,_V) = new_array(s+1);						\
  if (_(N,_V)==0) err_handler(88,"b_urn: out of memory");      		\
  _(N,_actual) = 0;							\
  }                                                     		\
									\
void _(N,_delete)() { delete_array(_(N,_V)); }				\
									\
num _(N,_empty)() { return (_(N,_actual)==0); }                       	\
                                                        		\
num _(N,_size)()  { return _(N,_actual); }				\
									\
void _(N,_put)(num a) 							\
  { 									\
  _(N,_V)[_(N,_actual)++] = a;  					\
  if (_(N,_actual)>_(N,_n))  err_handler(88, "b_urn overflow");		\
  }									\
                                                           		\
num _(N,_draw)()							\
  {									\
  int k,x;								\
  if (_(N,_actual)==0)  err_handler(88, "b_urn underflow");		\
                     							\
  k = (num) random()%_(N,_actual);					\
  x = _(N,_V)[k];        						\
  _(N,_V)[k] = _(N,_V)[--_(N,_actual)];		     			\
									\
  return x; 								\
  }									\
									\
num _(N,_Draw)()							\
  {									\
  int k;								\
  if (_(N,_actual)==0)  err_handler(88, "b_urn underflow");		\
                     							\
  k = (num) random()%_(N,_actual);					\
  return _(N,_V)[k];        						\
  }									\
                                            				\
void _(N,_clear)() { _(N,_actual) = 0; }      				\
									\
void _(N,_print)() 							\
  {									\
  int i;								\
  for(i=0; i<_(N,_actual); i++)						\
    printf(" %d",_(N,_V)[i]);						\
  printf(" urn_size: %d\n",_(N,_actual));				\
  }

#define def_b_urn
#endif
