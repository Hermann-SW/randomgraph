/*
 * File:   list.h
 *         - header file for datatype polymorph list
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

/*
 *      Diagram of datatype list (with items):
 *      ======================================
 *
 *
 *                              +-----+       
 *            +-----------------|first|
 *            |                 +-----+ 
 *            |                 | last|-----------------+
 *            |                 +-----+                 |
 *            |                 | size|                 |
 *            |                 +-----+                 |
 *            |                   list                  |
 *            |                                         |
 *            |                                         |
 *            V                                         V
 *         +----+     +----+              +----+     +----+
 *         |succ|---> |succ|---> ....---> |succ|---> |succ|---> 0
 *         +----+     +----+              +----+     +----+
 *   0 <---|pred| <---|pred| <---.... <---|pred| <---|pred| 
 *         +----+     |____|              |____|     |____|
 *         | inf|     | inf|              | inf|     | inf|
 *         +----+     +----+              +----+     +----+
 *          item       item                item       item
 *          
 *            ^                                         ^
 *            |                                         |
 *            |                                         |
 *     (here Push/Pop)                        (here Append/Remove)
 *
 *      
 *      Push-Pop    or Append-Remove: stack 
 *      Push-Remove or Append-Pop   : queue
 *      alltogether                 : double ended queue
 *
 *
 *                         +----+
 *                     <---|    |--->
 *                         +----+
 *                      ^          ^       
 *                      |          |      
 *                      |          |      
 *      Directions:  before      after
 *
 */ 

#ifndef def_list_h

#include "array.h"

#define t_none      0
#define t_list      1
#define t_num       2
#define t_universe  3
#define t_deleted   4

#define Inf(X) _U_[(X)]
#define _N_(X) _U_[(X)+1]
#define _P_(X) _U_[(X)+2]
#define _T_(X) _U_[(X)+3]


#define ACTEL  _U_[0]
#define SEENEL _U_[1]
#define MAXEL  _U_[2]
#define FREEEL _U_[4]
#define FREESZ _U_[5]

extern num TOPIT,TOPITH,TOPITH1;

#define IS_NUM(X)     (_T_(X)==t_num)
#define IS_LIST(X)    (_T_(X)==t_list)
#define IS_DELETED(X) ((_T_(X)!=t_num) && (_T_(X)!=t_list))

#define IS_DEFINED(X) ((((X)%4)==0) && ((X)<=SEENEL) && (! IS_DELETED(X)))


#define new_IT	TOPITH = new_half_element(TOPIT), _U_[TOPITH]=TOPIT,\
		TOPIT=TOPITH, act_IT

#define act_IT0 _U_[TOPIT+1]
#define act_L   _U_[_U_[TOPIT]+1]

#define act_IT  TOPITH1 = _U_[TOPIT+1], _U_[TOPIT+1]
#define act_IT1 TOPITH1

#define del_IT	TOPITH = _U_[TOPIT], delete_half_element(TOPIT),\
		TOPIT=TOPITH

#define push_ARG(x)	new_IT = (num) (x)

#define top_ARG1()	(_U_[TOPIT+1])
#define top_ARG2()	(_U_[_U_[TOPIT]+1])
#define top_ARG3()	(_U_[_U_[_U_[TOPIT]]+1])
#define top_ARG4()	(_U_[_U_[_U_[_U_[TOPIT]]]+1])

#define pop_ARG()	(TOPITH1 = _U_[TOPIT+1], del_IT, TOPITH1)

extern num uni_aux;
extern num *_U_;

typedef num list;

typedef num item;

typedef list list_of_num;
typedef list list_of_list_of_num;
 
#define Apply_forall_elements(e,L,Block)    { num e=0; forall(e,L) { Block } }

#define forall_items(it,S)  for( (it) = first(S); (it); (it) = succ(it,S))

#define forall(x,L)	for(new_IT = _N_(L);	 			     \
			    x=(act_IT?Inf(act_IT1):(del_IT,x)),act_IT1;	     \
			    act_IT = _N_(act_IT))			     \
/*if (printf("\nforall\n"),1)*/

#define forall_rev(x,L)	for(new_IT = _P_(L);	 			     \
			    x=(act_IT?Inf(act_IT1):(del_IT,x)),act_IT1;	     \
			    act_IT = _P_(act_IT))			     \
/*if (printf("\nforall_rev\n"),1)*/

#define forallH(x)	for(new_IT = _N_(act_L);			     \
			    x=(act_IT?Inf(act_IT1):(del_IT,x)),act_IT1;	     \
			    act_IT = _N_(act_IT))/*if (printf("\nforall\n"),1)*/

#define next1(I,L0,L1)		( (((I)==(L0)) && ((L0)!=(L1))) ? (L1) : 0 )
#define next2(I,L0,L1,L2)	( (((I)==(L0)) && 			       \
				  ((L0)!=(L1))) ? (L1) : next1((I),(L1),(L2)) )

#define next3(I,L0,L1,L2,L3)	( (((I)==(L0)) && ((L0)!=(L1))) ? 	\
				  (L1) : next2((I),(L1),(L2),(L3)) )

#define next4(I,L0,L1,L2,L3,L4)	( (((I)==(L0)) && ((L0)!=(L1))) ? 	\
				  (L1) : next3((I),(L1),(L2),(L3),(L4)) )

#define next5(I,L0,L1,L2,L3,L4,L5)  ( (((I)==(L0)) && ((L0)!=(L1))) ? 	\
				  (L1) : next4((I),(L1),(L2),(L3),(L4),(L5)) )


#define forall1(x,L1)		forall((X),(L1))

#define forall2(x,L1,L2)	for(new_IT = 0;				     \
			act_IT0 = next2(act_IT0,0,(L1),(L2)),\
			(act_IT0 ? 1 : (del_IT,0));\
				   ) \
/*if (printf("\nact_IT0: %d(%d,%d)\n",act_IT0,(L1),(L2)),1)*/\
forallH((x))

#define forall3(x,L1,L2,L3)	for(new_IT = 0;				     \
			act_IT0 = next3(act_IT0,0,(L1),(L2),(L3)),\
			(act_IT0 ? 1 : (del_IT,0));\
				   ) \
/*if (printf("\nact_IT0: %d(%d,%d)\n",act_IT0,(L1),(L2)),1)*/\
forallH((x))

#define forall4(x,L1,L2,L3,L4)	for(new_IT = 0;				\
			act_IT0 = next4(act_IT0,0,(L1),(L2),(L3),(L4)), \
			(act_IT0 ? 1 : (del_IT,0));			\
				   ) 					\
forallH((x))

#define forall5(x,L1,L2,L3,L4,L5) for(new_IT = 0;			\
			act_IT0 = next5(act_IT0,0,(L1),(L2),(L3),(L4),(L5)),\
			(act_IT0 ? 1 : (del_IT,0));			\
				   ) 					\
forallH((x))


void		new_universe(num k);
num		used_in_universe(void);
void		universe_statistics(bool do_abort);
void		delete_universe();
num		new_element(void);
void		delete_element(num e);
num		new_half_element(num e);
void		delete_half_element(num e);

list		new_list(void);
void 		delete_list(list L);

num		length(list L);
num		size(list L);
bool		empty(list L);
item     	first(list L);
item     	last(list L);
item     	succ(item it, list L);
item     	pred(item it, list L);
item     	cyclic_succ(item it, list L);
item     	cyclic_pred(item it, list L);
item    	search(num x, list L);
num 		contents(item it, list L);
num 		inf(item it, list L);
num	 	head(list L);
num	 	tail(list L);
num		rank(num x, list L);
num 		choose(list L);
bool 		duplicates(list L);


item		Insert(num x, item it, bool dir, list L); 
item		Push(num x, list L);	
item		Append(num x, list L);		
item		remove_item(item it, list L);
item		old_item(item it, list L);
num		delete_item(item it, list L);
num		Remove(list L);
num		Top(list L);
num		Pop(list L);
void		assign(item it, num x, list L);
item		conc(list L1, list L);
list		split(item it, list L);
void		swap(item it, item it1, list L);
void		apply(void (*f)(num*), list L);
void 		bucket_sort_F(num low, num high, num (*Map)(num), list L);
void 		bucket_sort(num low, num high, array_of_num Map, list L);

void 		clear(list L);

bool		is_layered_list(num level, list L);

void		print(list L);

item		Append_list(list L1, list L);	

#define def_list_h
#endif
