/*
 * File:   set.c
 *         - implementation of datatype set
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

#include "set.h"

num set_aux;

set_of_num	new_set(num k)			{ return new_array(k+1); }
void		delete_set(set_of_num S)	{ delete_array(S); }


num		_size(set_of_num S)		{ return S[0]; }
bool		_empty(set_of_num S)		{ return (S[0]==0); }
iterator 	_first(set_of_num S)		{ return (S[0]==0) ? 0 : 1; }
iterator 	_last(set_of_num S)		{ return S[0]; }
iterator 	_succ(iterator it, set_of_num S)	{ return (it<S[0]) ? it+1 : 0; }
iterator 	_pred(iterator it, set_of_num S)	{ S=S; return it-1; }
bool 		_search(num x, set_of_num S)	{
						iterator it;
						_forall_items(it,S)
						  if (S[it]==x)
						    return true;
						return false;
						}
bool 		_duplicates(set_of_num S)	{
						num i,j;
						for(i=2; i<=S[0]; i++)
						  for(j=1; j<i; j++)
						    if (S[i]==S[j])
						      return true;

						return false;
						}


void		_append(num x, set_of_num S)	{ S[++S[0]]=x; }

void 		_bucket_sort(num low, num high, array_of_num Map, set_of_num S)
  {
  num siz = high-low+2;
  set_of_num Aux = new_set(_size(S));
  set_of_num H   = new_set(siz);
  num x,i;

  H[0]=siz;
  _forall_items(i,H)  H[i]=0;

  _forall(i,S)  
    {
    x = Map[i];

    if ((x<low) || (x>high))  err_handler(77,"Mapping outside bounds");

    H[x-low+2]++;
    }

  _forall_items(i,H)  if (i>1) H[i]+=H[i-1];
 
  Aux[0]=_size(S);
  _forall(i,S)  Aux[++H[Map[i]-low+1]]=i;

  _forall_items(i,Aux)  S[i]=Aux[i];

  delete_set(H);
  delete_set(Aux);
  }


