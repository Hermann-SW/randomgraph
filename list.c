/*
 * File:   list.c
 *         - implementation of datatype polymorph list
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

#include "list.h"

num uni_aux;

num *_U_;

#define LL(it)	_U_[it]



void		new_universe(num k)		{ _U_ = new_array(4*(k+2)); 
						  ACTEL  = 4;
						  SEENEL = 4;
						  MAXEL  = 4*(k+1);
						  FREEEL = 0;
						  FREESZ = 0;
						  TOPIT  = 0;
						  _T_(0) = t_universe;
						  _T_(4) = t_universe;
						}

num		used_in_universe(void)		{ return (ACTEL-4)/4;
						}
void		universe_statistics(bool do_abort){
						if ((ACTEL==4) &&
						    (4*(FREESZ+1)==SEENEL) &&
						    (SEENEL<=MAXEL))
						  printf("universe empty!\n");
						else
						  {
	printf("universe  actual: %d  free: %d  seen: %d  max: %d\n",
		(ACTEL-4)/4,FREESZ,(SEENEL-4)/4,(MAXEL-4)/4);
						  if (do_abort)
						    err_handler(77,"universe abort: non-empty universe");
						  }
						}

void		delete_universe(void)		{ delete_array(_U_);
						}

num		new_element(void)		{ num e; 
						  if (FREESZ)
						    {
						    e = FREEEL;
						    FREEEL = _U_[e];
						    FREESZ--;
						    }
						  else
						    {
						    e = (SEENEL+=4);
						    if (e>MAXEL)
				err_handler(77,"overlow of universe!");
						    }
						  ACTEL+=4;
						  _T_(e) = t_num;
						  return e;
						}

void		delete_element(num e)		{
						  ACTEL-=4;
						  _U_[e] = FREEEL;
						  _T_(e) = t_deleted;
						  FREEEL = e;
						  FREESZ++;
						}

num		new_half_element(num e)		{
						if ((e!=0) && ((e%4)==0))
						  {
						  /* _U_[e+3] = undef;       */
						  /* nicht noetig wegen      */
						  /* _T_(e)=t_num (?)        */
						  /* in new_element          */

						  return e+2;
						  }
						else
						  {
						  num x = new_element();
						  _U_[x+1] = undef;
						  return x;
						  }
						}

void		delete_half_element(num e)	{
						if ((e!=0) && ((e%4)==0))
						  delete_element(e);
						}

list		new_list(void)			{ list L1 = new_element();
						  _U_[L1]  = 0;
						  _N_(L1)  = 0;
						  _P_(L1)  = 0;
						  _T_(L1)  = t_list;
						  return L1;
						}
void		delete_list(list L)		{ clear(L);
						  delete_element(L); 
						}


num		length(list L)			{ return _U_[L]; }
num		size(list L)			{ return _U_[L]; }
bool		empty(list L)			{ return (_U_[L]==0); }
item     	first(list L)			{ return _N_(L) ? _N_(L) : 0; }
item     	last(list L)			{ return _P_(L) ? _P_(L) : 0; }
item     	succ(item     it, list L)	{ return it ? _N_(it) : _N_(L);}
item     	pred(item     it, list L)	{ return it ? _P_(it) : _P_(L);}
item     	cyclic_succ(item     it, list L){ return succ(it,L) ? 
							 succ(it,L) : first(L);}
item     	cyclic_pred(item     it, list L){ return pred(it,L) ? 
							 pred(it,L) : last(L); }
item    	search(num x, list L)		{
						item     it;
						forall_items(it,L)
						  if (_U_[it]==x)
						    break;
						return it;
						}

num 		contents(item     it, list L)	{ L=L; return _U_[it]; }
num 		inf(item     it, list L)	{ L=L; return _U_[it]; }
num	 	head(list L)			{ return _U_[first(L)]; }
num	 	tail(list L)			{ return _U_[last(L)]; }
num		rank(num x, list L)		{ item     it;
						  num i=0;
						  forall_items(it,L)
						    {
						    i++;
						    if (_U_[it]==x)
						      break;
						    }
						  return (it) ? i : 0;
						}
num 		choose(list L) 			{ return head(L); }
bool 		duplicates(list L)		{
						item     it,it1;
						forall_items(it,L)
						  {
						  forall_items(it1,L)
						    if (_U_[it]==_U_[it1])
						      break;
						  if (it!=it1)
						    return true;
						  }

						return false;
						}


item    	Insert(num x, item     it, bool dir, list L) 
						{ num  e;

						  if (! IS_DEFINED(L))
			    err_handler(77,"Insert(_,_,_,undefined)");

                 				  if (! IS_LIST(L))
			    err_handler(77,"Insert(_,_,_,non list)");

						  if (! IS_DEFINED(it))
						    if (it!=0)
			    err_handler(77,"Insert(_,undefined,_,_)");

						  e = new_element();

						  if (it)
						    {
						    if (dir)
						      {
						      _P_(e)  = it;
						      _N_(e)  = _N_(it);
						      _N_(it) = e;
						      if (_N_(e))
							_P_(_N_(e)) = e;
						      else
							_P_(L) = e;
						      }
						    else
						      {
						      _N_(e)  = it;
						      _P_(e)  = _P_(it);
						      _P_(it) = e;
						      if (_P_(e))
							_N_(_P_(e)) = e;
						      else
							_N_(L) = e;
						      }
						    }
						  else
						    {
						    if (dir)
						      {
						      if (_N_(L))
							{
							_P_(e)      = 0;
							_N_(e)      = _N_(L);
							_N_(L)      = e;
							_P_(_N_(e)) = e;
							}
						      else
							{
							_P_(e)      = 0;
							_N_(e)      = 0;
							_N_(L)      = e;
							_P_(L)      = e;
							}
						      }
						    else
						      {
						      if (_P_(L))
							{
							_N_(e)      = 0;
							_P_(e)      = _P_(L);
							_P_(L)      = e;
							_N_(_P_(e)) = e;
							}
						      else
							{
							_P_(e)      = 0;
							_N_(e)      = 0;
							_N_(L)      = e;
							_P_(L)      = e;
							}
						      }
						    }
						  _U_[L]++;
						  _U_[e] = x;
						  return e;
						}

item    	Push(num x, list L)		{ return Insert(x,0,after,L); }
item    	Append(num x, list L)		{ return Insert(x,0,before,L); }

item		remove_item(item it, list L)	
		  { 
		  if (! it)
		    err_handler(77,"del_item(0)");

		  if (_P_(it))
		    {
		    if (_N_(it))
		      {
		      _P_(_N_(it)) = _P_(it);
		      }
		    else
		      {
		      _P_(L) = _P_(it);
		      }
		    _N_(_P_(it)) = _N_(it);
		    }
		  else
		    {
		    if (_N_(it))
		      {
		      _P_(_N_(it)) = _P_(it);
		      }
		    else
		      {
		      _P_(L) = _P_(it);
		      }
		    _N_(L) = _N_(it);
		    }
		  _U_[L]--;	  
		  return it;
		  }

item		old_item(item it, list L)
		  {
		  if (! it)
		    err_handler(77,"del_item(0)");

		  if (_P_(it))
		    {
		    if (_N_(it))
		      {
		      _P_(_N_(it)) = it;
		      }
		    else
		      {
		      _P_(L) = it;
		      }
		    _N_(_P_(it)) = it;
		    }
		  else
		    {
		    if (_N_(it))
		      {
		      _P_(_N_(it)) = it;
		      }
		    else
		      {
		      _P_(L) = it;
		      }
		    _N_(L) = it;
		    }
		  _U_[L]++;	  
		  return it;
		  }

num		delete_item(item     it, list L)	{ num x = _U_[it];
							  remove_item(it,L);
							  delete_element(it);
							  return x;
							}

num		Top(list L)		{ return head(L); }
num		Pop(list L)		{ return delete_item(first(L),L); }
num		Remove(list L)		{ return delete_item(last(L),L); }

void		assign(item     it, num x, list L)	{ L=L; _U_[it]=x; }
item		conc(list L1, list L)	
		  {
		  item it,it1;

		  if (! IS_DEFINED(L))
		    err_handler(77,"conc(_,undefined)");

		  if (! IS_DEFINED(L1))
		    err_handler(77,"conc(undefined,_)");

                  if (! IS_LIST(L))
		    err_handler(77,"conc(_,non list)");

                  if (! IS_LIST(L1))
		    err_handler(77,"conc(non list,_)");

		  it=first(L1);
		  if (it)
		    {
		    _P_(it)  = (it1=last(L));
		    _N_(it1 ? it1 : L) = it;
		    _P_(L)   = _P_(L1);
		    Inf(L)  += Inf(L1);    /* sizes */
		    Inf(L1)  = 0;
		    _P_(L1)  = 0;
		    _N_(L1)  = 0;
		    }

		  return it;
		  }

list		split(item it1, list L)
		  {
		  item it;
		  list L1 = new_list();
                  num i;

		  if (it1)
		    {
		    if (it1==first(L))
		      {
		      Inf(L1) = Inf(L);
		      _N_(L1) = _N_(L);
		      _P_(L1) = _P_(L);
		      Inf(L)  = 0;
		      _N_(L)  = 0;
		      _P_(L)  = 0;
		      }
		    else
		      {
		      it       = pred(it1,L);
		      _P_(it1) = 0;
		      _N_(L1)  = it1;
		      _P_(L1)  = _P_(L);
		      _N_(it)  = 0;
		      _P_(L)   = it;

		      i = 0;
		      while ((it!=0) && (it1!=0))
			{
			i++;
			it  = pred(it,L);
			it1 = succ(it1,L1);
			}

		      if (it1!=0)  i=Inf(L)-i;

		      Inf(L1) = i;
		      Inf(L)  = Inf(L) - i;
		      }
		    }

		  return L1;
		  }
					
void		swap(item     it, item     it1, list L)	{ num x=_U_[it]; L=L;
							  _U_[it]=_U_[it1];
							  _U_[it1]=x;
							}
void		apply(void (*f)(num*), list L)		{ item     it;
							  forall_items(it,L)
							    f(&(_U_[it]));
							}



void 		bucket_sort_F(num low, num high, num (*Map)(num), list L)
  {
  array_of_num first_it   = new_array(high-low+1);
  array_of_num last_it    = new_array(high-low+1);
  num x,i,j;
  item     it;

  if (size(L)<=1)  return;


  for(i=0; i<=high-low; i++)  first_it[i]=last_it[i]=0;

  forall_items(it,L)  
    {
    x = Map(_U_[it]);

    if ((x<low) || (x>high))  err_handler(77,"Mapping outside bounds");

    x-=low;

    if (first_it[x]==0) 
      last_it[x] = first_it[x] = it;
    else 
      {
      _P_(it)          = last_it[x];
      _N_(last_it[x])  = it;
      last_it[x]       = it;
      }
    }

  for(i=0; i<=high-low; i++) 
    if (first_it[i]!=0)
      break;

  _P_(first_it[i]) = 0;
  _N_(L)           = first_it[i];

  do
    {
    for(j=i+1; j<=high-low; j++)
      if (first_it[j]!=0)
	break;

    if (j<=high-low)
      {
      _N_(last_it[i])  = first_it[j];
      _P_(first_it[j]) = last_it[i];
      i = j;
      }
    }
  while (j<=high-low);

  _N_(last_it[i]) = 0;
  _P_(L)          = last_it[i];

  delete_array(first_it);
  delete_array(last_it);
  }

void 		bucket_sort(num low, num high, array_of_num Map, list L)
  {
  array_of_num first_it   = new_array(high-low+1);
  array_of_num last_it    = new_array(high-low+1);
  num x,i,j;
  item     it;

  if (size(L)<=1)  return;


  for(i=0; i<=high-low; i++)  first_it[i]=last_it[i]=0;

  forall_items(it,L)  
    {
    x = Map[_U_[it]];

    if ((x<low) || (x>high))  err_handler(77,"Mapping outside bounds");

    x-=low;

    if (first_it[x]==0) 
      last_it[x] = first_it[x] = it;
    else 
      {
      _P_(it)          = last_it[x];
      _N_(last_it[x])  = it;
      last_it[x]       = it;
      }
    }

  for(i=0; i<=high-low; i++) 
    if (first_it[i]!=0)
      break;

  _P_(first_it[i]) = 0;
  _N_(L)           = first_it[i];

  do
    {
    for(j=i+1; j<=high-low; j++)
      if (first_it[j]!=0)
	break;

    if (j<=high-low)
      {
      _N_(last_it[i])  = first_it[j];
      _P_(first_it[j]) = last_it[i];
      i = j;
      }
    }
  while (j<=high-low);

  _N_(last_it[i]) = 0;
  _P_(L)          = last_it[i];

  delete_array(first_it);
  delete_array(last_it);
  }

bool		check(list L)		{ item it;
					  if (! IS_DEFINED(L))
					    err_handler(77,"check(undef.list)");
					  if (! IS_LIST(L))
					    err_handler(77,"check(non list)");
					  forall_items(it,L)
					    {
					    if (IS_NUM(it))
					      it=it;
					    else if (IS_LIST(it))
					      {
					      if (! check(_U_[it]))
					        return false;
					      }
					    else
					      return false;
					    }

					  return true;
					}

void		clear_internal(list L)	{ item it;

					  forall_items(it,L)
					    {
					    if (IS_LIST(it))
					      if (IS_LIST(_U_[it]))
					        delete_list(_U_[it]);
					    delete_item(it,L);
					    }
					}

void		clear(list L)		{ if (! check(L))
					    err_handler(77,"clear(wrong list)");

					  clear_internal(L);
					}

bool		is_layered_list(num level, list L)
				{
				item it;

				forall_items(it,L)
				  {
				  if ((level==0) && (! IS_NUM(it)))
				    return false;

				  else if (level>0)
				    {
				    if (! IS_LIST(it))
				      return false;

				    if (! is_layered_list(level-1,LL(it))) 
				      return false;
				    }
				  }

				return true;
				}


void		print(list L)		{ item it;
					  if (! IS_DEFINED(L))
					    err_handler(77,"print(undef.list)");
					  if (! IS_LIST(L))
					    err_handler(77,"print(non list)");
					  printf("\n[");
					  forall_items(it,L)
					    {
					    if (IS_NUM(it))
					      printf("%d",_U_[it]);
					    else if (IS_LIST(it))
					      print(_U_[it]);
					    else
					      err_handler(77,"bad print-type");
					    if (it!=last(L))  printf(",");
					    }
					  printf("]\n");
					}


item		Append_list(list L1, list L)	
		  { 
		  item it;

		  if (! IS_DEFINED(L1))
		    err_handler(77,"Append_list(undefined,_)");

                  if (! IS_LIST(L1))
		    err_handler(77,"Append_list(non list,_)");

		  if (! IS_DEFINED(L))
		    err_handler(77,"Append_list(_,undefined)");

                  if (! IS_LIST(L))
		    err_handler(77,"Append_list(_,non list)");

		  it = Append(L1,L);
		  _T_(it) = t_list;

		  return it;
		  }
