/*
 * File:   array.h
 *         -  header file for datatype array
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

#ifndef def_array_h

#include "basic.h"

num *new_array(num k);

void delete_array(num *A);

void init_array(num low, num high, num x, num *A);

typedef num *array_of_num;

double *new_array_of_double(num k);

void delete_array_of_double(double *A);

typedef double *array_of_double;

void print_array(num low, num high, num *A);

void print_array_of_double(num low, num high, double *A);

#define def_array_h
#endif
