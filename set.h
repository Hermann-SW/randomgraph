/*
 * File:   set.h
 *         - header file for datatype set
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

#ifndef def_set_h

#include "array.h"

extern num set_aux;

typedef num *set_of_num;

typedef num iterator;

#define _forall_items(it,S)  for( (it) = _first(S); (it); (it) = _succ(it,S))


#define _forall(x,S)	for(set_aux=_first(S); 				     \
			    x=set_aux?S[set_aux]:x,set_aux;		     \
			    set_aux=_succ(set_aux,S))

#define _forall_rev(x,S) for(set_aux=_last(S); 			     \
			    x=set_aux?S[set_aux]:x,set_aux;		     \
			    set_aux=_pred(set_aux,S))


set_of_num	new_set(num k);
void 		delete_set(set_of_num S);

num		_size(set_of_num S);
bool		_empty(set_of_num S);
iterator 	_first(set_of_num S);
iterator 	_last(set_of_num S);


iterator 	_succ(iterator it, set_of_num S);
iterator 	_pred(iterator it, set_of_num S);


bool 		_search(num x, set_of_num S);


bool 		_duplicates(set_of_num S);


void		_append(num x, set_of_num S);

void 		_bucket_sort(num low, num high, array_of_num Map, set_of_num S);

#define def_set_h
#endif

