/*
 * File:   b_stack.h
 *         - headerfile for datatype bounded stack
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

#ifndef def_b_stack_h

#include "array.h"

typedef num *b_stack;

num    *new_b_stack(num k);

void	delete_b_stack(b_stack S);

num	top(b_stack S);
num	pop(b_stack S);
void	push(num x,b_stack S);
void	clear_b_stack(b_stack S);
num	size_b_stack(b_stack S);
bool	empty_b_stack(b_stack S);

#define def_b_stack_h
#endif
