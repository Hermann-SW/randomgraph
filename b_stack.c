/*
 * File:   b_stack.c
 *         - implementation of bounded stack datatype
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

#include "b_stack.h"

num *new_b_stack(num k)			{ return new_array(k+1); }

void delete_b_stack(b_stack S) 		{ delete_array(S); }

num	top(b_stack S)			{ return S[S[0]]; }
num	pop(b_stack S)			{ return S[S[0]--]; }
void	push(num x,b_stack S)		{ S[++S[0]]=x; }
void	clear_b_stack(b_stack S)	{ S[0]=0; }
num	size_b_stack(b_stack S)		{ return S[0]; }
bool	empty_b_stack(b_stack S)	{ return (S[0]==0); }

void USE7()
  {
  (void) new_b_stack(0);
  delete_b_stack(0);
  (void) top(0);
  (void) pop(0);
  push(0,0);
  clear_b_stack(0);
  (void) size_b_stack(0);
  (void) empty_b_stack(0);
  USE7();
  }

