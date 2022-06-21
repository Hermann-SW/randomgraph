/*
 * File:   ugraph.h
 *         - implementation of datatype undirected graph
 *           (see report for short description).
 *           This implementation follows the lines of the nice
 *           package LEDA (Library of Efficient Datatypes
 *           and Algorithms) , which is implemented in C++
 *           (anonymous ftp on  ftp.cs.uni-sb.de  in directory
 *            /pub/LEDA  files  INFO  and  LEDA-<version>.tar.Z ).
 *           Here we only have to write G_new_edge(u,v) when
 *           using the equivalent to LEDA's G.new_edge(u,v).
 *           The price to be paid for the flavour of classes in
 *           ANSI-C is the use of (really) big #define's 
 *           (~ 860 lines) and the non-existence of a variable
 *           for a graph, which forces the graph to be global
 *           (UGRAPH(G) declares ugraph G global for the whole file).
 *           The only differences to the datatype ugraph in LEDA 
 *           are the use of datatype "vertex" instead of the LEDA
 *           datatype "node" and the use of
 *           "forall_incident_edges(e,v,G)" instead of LEDA's
 *           "forall_adj_edges(e,v)".
 *           Additional features in this implementation are the
 *           removal/reinsertion of vertices and edges from/into 
 *           the graph and the fixing of some bugs of LEDA methods.
 *           This implementation was checked by Objectcenter 2.0
 *           under SunOs 4.1.3; the detected errors were removed
 *           and therefore this implementation should work fine.
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

#ifndef def_ugraph_h

#include "ugraph.def"


#define UGRAPH(N)							\
UGRAPH1(N)								\
UGRAPH1a(N)								\
UGRAPH2(N)								\
UGRAPH3(N)								\


#define UGRAPH1(N)							\
									\
num _(N,_vertices),_(N,_edges);						\
num _(N,__max_vertices),_(N,__max_edges);				\
num _(N,__vertices_sofar),_(N,__edges_sofar);				\
									\
array_of_vertex _(N,__source);						\
array_of_vertex _(N,__target);						\
									\
array_of_edge _(N,_Ssucc);						\
array_of_edge _(N,_Spred);						\
									\
array_of_edge _(N,_Tsucc);						\
array_of_edge _(N,_Tpred);						\
									\
array_of_edge _(N,_Esucc);						\
array_of_edge _(N,_Epred);						\
									\
array_of_edge _(N,_first);						\
array_of_edge _(N,_last);						\
									\
									\
array_of_vertex _(N,_Vsucc);						\
array_of_vertex _(N,_Vpred);						\
									\
array_of_edge _(N,_it);							\
									\
array_of_num _(N,__degree);						\
									\
vertex _(N,_first_vertex)(void);					\
vertex _(N,_succ_vertex)(vertex v);					\
edge _(N,_first_incident_edge)(vertex v);				\
edge _(N,_incident_succ)(edge e, vertex v);				\
vertex _(N,_first_edge)(void);						\
vertex _(N,_succ_edge)(edge e);						\
									\
									\
edge_array_of_double _(N,_new_edge_array_of_double)()			\
  {									\
  return new_array_of_double(_(N,__max_edges)+1);			\
  }									\
									\
void _(N,_delete_edge_array_of_double)(edge_array_of_double A) 		\
  { 									\
  delete_array_of_double(A);						\
  }									\
									\
									\
edge_array _(N,_new_edge_array)()					\
  {									\
  return new_array(_(N,__max_edges)+1);					\
  }									\
									\
void _(N,_delete_edge_array)(edge_array A) { delete_array(A); }		\
									\
vertex_array_of_double _(N,_new_vertex_array_of_double)()		\
  {									\
  return new_array_of_double(_(N,__max_vertices)+1);			\
  }									\
									\
void _(N,_delete_vertex_array_of_double)(vertex_array_of_double A) 	\
  { 									\
  delete_array_of_double(A); 						\
  }									\
									\
vertex_array _(N,_new_vertex_array)()					\
  {									\
  return new_array(_(N,__max_vertices)+1);				\
  }									\
									\
void _(N,_delete_vertex_array)(vertex_array A) 				\
  { 									\
  delete_array(A); 							\
  }									\
									\
void _(N,_init_vertex_array)(vertex_array A, num x)			\
  {									\
  vertex v;								\
  forall_vertices(v,N)  A[v] = x;					\
  }									\
									\
void _(N,_init_edge_array)(edge_array A, num x)				\
  {									\
  edge e;								\
  forall_edges(e,N)  A[e] = x;						\
  }									\


#define UGRAPH1y(N)							\
									\
void _(N,_init_edge_array_by_function)(edge_array A, num (*f)(edge,...),...)\
  {									\
  }									\
									\

/*
#define UGRAPH1x(N)							\
									\
void _(N,_init_edge_array_by_function)(edge_array A, num (*f)(edge,...),...)\
  {									\
  va_list ap;								\
  edge e;								\
									\
  va_start(ap,f);							\
									\
    {									\
    num arg1 = va_arg(ap,num);						\
    									\
    if (arg1!=EOAL)							\
      {									\
      num arg2 = va_arg(ap,num);					\
    									\
      if (arg2!=EOAL)							\
        {								\
        num arg3 = va_arg(ap,num);					\
    									\
        if (arg3!=EOAL)							\
          {								\
	  err_handler(301,"at most 2 optional arguments supported");	\
          }								\
        else								\
          forall_edges(e,N)  A[e] = f(e,arg1,arg2);			\
        }								\
      else								\
        forall_edges(e,N)  A[e] = f(e,arg1);				\
      }									\
    else								\
      forall_edges(e,N)  A[e] = f(e);					\
    }									\
									\
  va_end(ap);								\
  }									\
									\

*/


#define UGRAPH1a(N)							\
									\
									\
num  _(N,_vertices_sofar)() { return _(N,__vertices_sofar); }		\
num  _(N,_vertices_max)()   { return _(N,__max_vertices); }		\
									\
num  _(N,_edges_sofar)() { return _(N,__edges_sofar); }			\
num  _(N,_edges_max)()   { return _(N,__max_edges); }			\
									\
void _(N,_resize_copy)(num **p, int n, int k)				\
  {									\
  num *q = new_array(n+1);						\
  /*int i;								\
  for(i=0; i<=k; i++)  q[i]=(*p)[i];	*/				\
  memcpy((char*) q, (char*) (*p),(k+1)*sizeof(num));			\
  delete_array(*p);							\
  (*p)=q;								\
  }									\
									\
void _(N,_resize)(num n, num m)						\
  {									\
  if ((n<_(N,__vertices_sofar)) || (m<_(N,__edges_sofar)))		\
    err_handler(33,"ilegal resize");					\
									\
  _(N,__max_vertices)=n;						\
  _(N,__max_edges)=m;							\
									\
  _(N,_resize_copy)(&_(N,__source),m,_(N,__edges_sofar));		\
  _(N,_resize_copy)(&_(N,__target),m,_(N,__edges_sofar));		\
  _(N,_resize_copy)(&_(N,_Ssucc)  ,m,_(N,__edges_sofar));		\
  _(N,_resize_copy)(&_(N,_Spred)  ,m,_(N,__edges_sofar));		\
  _(N,_resize_copy)(&_(N,_Tsucc)  ,m,_(N,__edges_sofar));		\
  _(N,_resize_copy)(&_(N,_Tpred)  ,m,_(N,__edges_sofar));		\
  _(N,_resize_copy)(&_(N,_Esucc)  ,m,_(N,__edges_sofar));		\
  _(N,_resize_copy)(&_(N,_Epred)  ,m,_(N,__edges_sofar));		\
									\
  _(N,_resize_copy)(&_(N,_Vsucc)  ,n,_(N,__vertices_sofar));		\
  _(N,_resize_copy)(&_(N,_Vpred)  ,n,_(N,__vertices_sofar));		\
  _(N,_resize_copy)(&_(N,__degree),n,_(N,__vertices_sofar));		\
  _(N,_resize_copy)(&_(N,_first)  ,n,_(N,__vertices_sofar));		\
  _(N,_resize_copy)(&_(N,_last)   ,n,_(N,__vertices_sofar));		\
  _(N,_resize_copy)(&_(N,_it)     ,n,_(N,__vertices_sofar));		\
  }									\
									\
void _(N,_compress_vertices)(void (*CV)(vertex,vertex))			\
  {									\
  int i,j;								\
  vertex_array P;							\
  vertex v;								\
  edge e;								\
									\
  P = _(N,_new_vertex_array)();						\
									\
  for(i=1; i<=_(N,__vertices_sofar); i++)  P[i]=false;			\
  forall_vertices(v,N)  P[v]=true;					\
									\
  i=1; j=_(N,__vertices_sofar);						\
									\
  do									\
    {									\
    while ((i<j) &&   (P[i]))  i++;					\
    while ((i<j) && (! P[j]))  j--;					\
    if (i<j)								\
      {									\
      _(N,_Vpred)[i]		  = _(N,_Vpred)[j];			\
      _(N,_Vsucc)[i]		  = _(N,_Vsucc)[j];			\
      _(N,_Vsucc)[_(N,_Vpred)[i]] = i;					\
      _(N,_Vpred)[_(N,_Vsucc)[i]] = i;					\
									\
      _(N,__degree)[i]		  = _(N,__degree)[j];			\
      _(N,_first)[i]		  = _(N,_first)[j];			\
      _(N,_last)[i]		  = _(N,_last)[j];			\
      _(N,_it)[i]		  = _(N,_it)[j];			\
									\
      forall_incident_edges(e,j,N)					\
	if (_(N,__source)[e]==j)  _(N,__source)[e]=i;			\
	else			  _(N,__target)[e]=i;			\
									\
      if (CV!=NULL)  CV(i,j);						\
									\
      P[i]=true; P[j]=false;						\
      }									\
    }									\
  while (i<j);								\
									\
  _(N,__vertices_sofar) = _(N,_vertices);				\
  _(N,_delete_vertex_array)(P);						\
  }									\
									\
void _(N,_compress_edges)(void (*CE)(edge,edge))			\
  {									\
  int i,j;								\
  edge_array P;								\
  edge e;								\
									\
  P = _(N,_new_edge_array)();						\
									\
  for(i=1; i<=_(N,__edges_sofar); i++)  P[i]=false;			\
  forall_edges(e,N)  P[e]=true;						\
									\
  i=1; j=_(N,__edges_sofar);						\
									\
  do									\
    {									\
    while ((i<j) &&   (P[i]))  i++;					\
    while ((i<j) && (! P[j]))  j--;					\
    if (i<j)								\
      {									\
      _(N,__source)[i]		  = _(N,__source)[j];			\
      _(N,__target)[i]		  = _(N,__target)[j];			\
									\
      _(N,_Spred)[i]		  = _(N,_Spred)[j];			\
      _(N,_Ssucc)[i]		  = _(N,_Ssucc)[j];			\
      if (_(N,_first)[_(N,__source)[j]]==j)				\
	_(N,_first)[_(N,__source)[i]]=i;				\
      if (_(N,_last)[_(N,__source)[j]]==j)				\
	_(N,_last)[_(N,__source)[i]]=i;					\
      *PRED_(_(N,_Ssucc)[i],_(N,__source)[i],N) = i;			\
      *SUCC_(_(N,_Spred)[i],_(N,__source)[i],N) = i;			\
									\
      _(N,_Tpred)[i]		  = _(N,_Tpred)[j];			\
      _(N,_Tsucc)[i]		  = _(N,_Tsucc)[j];			\
      if (_(N,_first)[_(N,__target)[j]]==j)				\
	_(N,_first)[_(N,__target)[i]]=i;				\
      if (_(N,_last)[_(N,__target)[j]]==j)				\
	_(N,_last)[_(N,__target)[i]]=i;					\
      *PRED_(_(N,_Tsucc)[i],_(N,__target)[i],N) = i;			\
      *SUCC_(_(N,_Tpred)[i],_(N,__target)[i],N) = i;			\
									\
      _(N,_Epred)[i]		  = _(N,_Epred)[j];			\
      _(N,_Esucc)[i]		  = _(N,_Esucc)[j];			\
      _(N,_Esucc)[_(N,_Epred)[i]] = i;					\
      _(N,_Epred)[_(N,_Esucc)[i]] = i;					\
									\
      if (CE!=NULL)  CE(i,j);						\
									\
      P[i]=true; P[j]=false;						\
      }									\
    }									\
  while (i<j);								\
									\
  _(N,__edges_sofar) = _(N,_edges);					\
  _(N,_delete_edge_array)(P);						\
  }									\
									\
void _(N,_compress)(void (*CV)(vertex,vertex),void (*CE)(edge,edge))	\
  {									\
  _(N,_compress_vertices)(CV);						\
  _(N,_compress_edges)(CE);						\
  }									\
									\
void _(N,_new)(num n, num m) 						\
  { 									\
  _(N,_vertices)=0;  							\
  _(N,_edges)=0; 							\
  _(N,__max_vertices)=n;  						\
  _(N,__max_edges)=m; 							\
  _(N,__vertices_sofar)=0; 						\
  _(N,__edges_sofar)=0; 						\
  _(N,__source) = new_array(m+1); 					\
  _(N,__target) = new_array(m+1); 					\
  _(N,_Ssucc)   = new_array(m+1); 					\
  _(N,_Spred)   = new_array(m+1);  					\
  _(N,_Tsucc)   = new_array(m+1);  					\
  _(N,_Tpred)   = new_array(m+1);  					\
  _(N,_Esucc)   = new_array(m+1); 					\
  _(N,_Epred)   = new_array(m+1); 					\
 									\
  _(N,_Vsucc)   = new_array(n+1); 					\
  _(N,_Vpred)   = new_array(n+1); 					\
  _(N,__degree) = new_array(n+1); 					\
  _(N,_first)   = new_array(n+1); 					\
  _(N,_last)    = new_array(n+1); 					\
  _(N,_it)      = new_array(n+1); 					\
  } 									\
 									\
void _(N,_delete)() 							\
  {									\
  delete_array(_(N,__source));						\
  delete_array(_(N,__target));						\
  delete_array(_(N,_Ssucc));						\
  delete_array(_(N,_Spred));						\
  delete_array(_(N,_Tsucc));						\
  delete_array(_(N,_Tpred));						\
  delete_array(_(N,_Vsucc));						\
  delete_array(_(N,_Vpred));						\
  delete_array(_(N,_Esucc));						\
  delete_array(_(N,_Epred));						\
  delete_array(_(N,__degree));						\
  delete_array(_(N,_first));						\
  delete_array(_(N,_last));						\
  delete_array(_(N,_it));						\
  }									\
									\


#define UGRAPH2(N)							\
num  _(N,_degree)(vertex v)  { return ((v==0) ? 0 : _(N,__degree)[v]); }\
									\
vertex _(N,_source)(edge e)  { return ((e==0) ? 0 : _(N,__source)[e]); }\
edge _(N,_target)(edge e)    { return ((e==0) ? 0 : _(N,__target)[e]); }\
									\
vertex _(N,_opposite)(vertex v, edge e)					\
  { 									\
  if ((v=OPPOSITE(v,e,N))==0)						\
    err_handler(77,"v not in e during opposite call");			\
  return v;								\
  }									\
									\
num  _(N,_number_of_vertices)()	{ return _(N,_vertices); }		\
num  _(N,_number_of_edges)()	{ return _(N,_edges); }			\
									\
vertex _(N,_first_vertex)()	    { return _(N,_Vsucc)[0]; }		\
vertex _(N,_last_vertex)()	    { return _(N,_Vpred)[0]; }		\
vertex _(N,_succ_vertex)(vertex v)  { return ((v==0) ? 0 : _(N,_Vsucc)[v]); } \
vertex _(N,_pred_vertex)(vertex v)  { return ((v==0) ? 0 : _(N,_Vpred)[v]); } \
									\
set_of_vertex _(N,_all_vertices)() { set_of_vertex S = new_set(_(N,_vertices));\
			  	     vertex v;				\
				     forall_vertices(v,N)		\
				       _append(v,S);			\
				     return S;				\
				   }					\
		          						\
edge _(N,_first_edge)()		{ return _(N,_Esucc)[0]; }		\
edge _(N,_last_edge)()		{ return _(N,_Epred)[0]; }		\
edge _(N,_succ_edge)(edge e)  { return ((e==0) ? 0 : _(N,_Esucc)[e]); }	\
edge _(N,_pred_edge)(edge e)  { return ((e==0) ? 0 : _(N,_Epred)[e]); }	\
									\
set_of_edge _(N,_all_edges)()	{ set_of_edge S = new_set(_(N,_edges)); \
				  edge e;				\
				  forall_edges(e,N)			\
				    _append(e,S);			\
				  return S;				\
				}					\
									\
edge _(N,_first_incident_edge)(vertex v)				\
	{ return ((v==0) ? 0 : _(N,_first)[v]); }			\
									\
edge _(N,_last_incident_edge)(vertex v)					\
	{ return ((v==0) ? 0 : _(N,_last)[v]); }			\
									\
edge _(N,_incident_succ)(edge e, vertex v)				\
	{ return ((e==0) ? 0 : SUCC(e,v,N)); }				\
									\
edge _(N,_incident_pred)(edge e, vertex v)				\
	{ return ((e==0) ? 0 : PRED(e,v,N)); }				\
									\
edge _(N,_cyclic_incident_succ)(edge e, vertex v)  { return (e==0) ? 0 : \
     (((e=_(N,_incident_succ)(e,v))==0) ? _(N,_first_incident_edge)(v) : e); } \
									\
edge _(N,_cyclic_incident_pred)(edge e, vertex v)  { return (e==0) ? 0 : \
     (((e=_(N,_incident_pred)(e,v))==0) ? _(N,_last_incident_edge)(v) : e); } \
									\
set_of_edge _(N,_incident_edges)(vertex v)				\
	{ 								\
	set_of_edge S = new_set(_(N,__degree)[v]);			\
	edge e;								\
	forall_incident_edges(e,v,N)					\
	  _append(e,S);							\
	return S;							\
	}								\
									\
set_of_vertex _(N,_adjacent_vertices)(vertex v)				\
	{ 								\
	set_of_vertex S = new_set(_(N,__degree)[v]);			\
	edge e;								\
	forall_incident_edges(e,v,N)					\
	  _append(_(N,_opposite)(v,e),S);				\
	return S;							\
	}								\
									\
vertex _(N,_choose_vertex)()	{ return _(N,_Vsucc)[0]; }		\
edge _(N,_choose_edge)()	{ return _(N,_Esucc)[0]; }		\
									\
									\
									\
void _(N,_app_edges)(edge g)						\
  {									\
  _(N,_Epred)[g]=_(N,_Epred)[0];					\
  _(N,_Esucc)[g]=0;							\
  _(N,_Epred)[0]=g;							\
  _(N,_Esucc)[_(N,_Epred)[g]]=g;					\
  _(N,_edges)++;							\
  }									\
									\
void _(N,_ins_edge)(edge g, vertex u, edge e, bool diru)		\
  {									\
  if (e==0)								\
    {									\
    if (diru==after)							\
      {									\
      if (_(N,_last)[u]==0)	*SUCC_(_(N,_last)[u]=g,u,N)=0;		\
      else    *SUCC_(*PRED_(_(N,_first)[u],u,N)=g,u,N)=_(N,_first)[u];	\
      _(N,_first)[u]=g;							\
      *PRED_(g,u,N)=0;							\
      }									\
    else								\
      {									\
      if (_(N,_first)[u]==0)	*PRED_(_(N,_first)[u]=g,u,N)=0;		\
      else    *PRED_(*SUCC_(_(N,_last)[u],u,N)=g,u,N)=_(N,_last)[u];	\
      _(N,_last)[u]=g;							\
      *SUCC_(g,u,N)=0;							\
      }									\
    }									\
  else									\
   {									\
   if (diru==after)							\
     {									\
     if (SUCC(e,u,N)==0)  *SUCC_(_(N,_last)[u]=g,u,N)=0;		\
     else		  *PRED_(*SUCC_(g,u,N)=SUCC(e,u,N),u,N)=g;	\
     *PRED_(g,u,N)=e;							\
     *SUCC_(e,u,N)=g; 							\
     }									\
   else									\
     {									\
     if (PRED(e,u,N)==0)  *PRED_(_(N,_first)[u]=g,u,N)=0;		\
     else		  *SUCC_(*PRED_(g,u,N)=PRED(e,u,N),u,N)=g;	\
     *PRED_(e,u,N)=g; 							\
     *SUCC_(g,u,N)=e;							\
     }									\
   }									\
  _(N,__degree)[u]++;							\
  }									\
									\
edge _(N,_old_edge2)(vertex u, vertex v, edge g, edge e, edge f, 	\
		     bool diru, bool dirv) 				\
  {									\
  if (u==v)								\
    {									\
    err_handler(0,"self loop not inserted!");				\
    return 0;								\
    }									\
  if (g>_(N,__max_edges))						\
    err_handler(5,"too much edges created");				\
  _(N,_app_edges)(g);							\
  _(N,__source)[g]=u;							\
  _(N,__target)[g]=v;							\
  _(N,_ins_edge)(g,u,e,diru);						\
  _(N,_ins_edge)(g,v,f,dirv);						\
  return g;								\
  }									\
									\
edge _(N,_new_edge2)(vertex u, vertex v, edge e, edge f, bool diru, bool dirv) \
  {									\
  edge g=++_(N,__edges_sofar);						\
  return _(N,_old_edge2)(u,v,g,e,f,diru,dirv);				\
  }									\
									\
edge _(N,_new_edge)(vertex u, vertex v)					\
  {									\
  return _(N,_new_edge2)(u,v,_(N,_last)[u],_(N,_last)[v],after,after);	\
  }									\
									\
void _(N,_rem_edge)(edge e)						\
  { 									\
  _(N,_Epred)[_(N,_Esucc)[e]]=_(N,_Epred)[e];				\
  _(N,_Esucc)[_(N,_Epred)[e]]=_(N,_Esucc)[e];				\
  _(N,_edges)--;							\
  }									\
									\
void _(N,_remove_edge_)(edge e, vertex v)				\
  { 									\
  if (_(N,_first)[v]==e)						\
    {									\
    if (_(N,_last)[v]==e)						\
      {									\
      _(N,_first)[v]=_(N,_last)[v]=0;					\
      }									\
    else								\
      {									\
      _(N,_first)[v]=SUCC(e,v,N);					\
      *PRED_(SUCC(e,v,N),v,N)=0;					\
      }									\
    }									\
  else									\
    {									\
    if (_(N,_last)[v]==e)						\
      {									\
      _(N,_last)[v]=PRED(e,v,N);					\
      *SUCC_(PRED(e,v,N),v,N)=0;					\
      }									\
    else								\
      {									\
      *SUCC_(PRED(e,v,N),v,N)=SUCC(e,v,N);				\
      *PRED_(SUCC(e,v,N),v,N)=PRED(e,v,N);				\
      }									\
    }									\
  _(N,__degree)[v]--;							\
  }									\
									\
edge _(N,_remove_edge1)(edge e, vertex v)				\
  {									\
  _(N,_remove_edge_)(e,v);						\
  _(N,_rem_edge)(e);							\
  return e;								\
  }									\
									\
edge _(N,_remove_edge)(edge e)						\
  {									\
  _(N,_remove_edge_)(e,_(N,__source)[e]);				\
  _(N,_remove_edge_)(e,_(N,__target)[e]);				\
  _(N,_rem_edge)(e);							\
  return e;								\
  }									\
									\
void _(N,_delete_edge)(edge e)						\
  {									\
  (void) _(N,_remove_edge)(e);						\
  _(N,_Esucc)[e]=0;							\
  _(N,_Epred)[e]=0;							\
  _(N,__source)[e]=0;							\
  _(N,__target)[e]=0;							\
  _(N,_Ssucc)[e]=0;							\
  _(N,_Spred)[e]=0;							\
  _(N,_Tsucc)[e]=0;							\
  _(N,_Tpred)[e]=0;							\
  }									\
									\
void _(N,_re_ins_edge)(edge e)	{ _(N,_Epred)[_(N,_Esucc)[e]]=e;	\
				  _(N,_Esucc)[_(N,_Epred)[e]]=e;	\
				  _(N,_edges)++;			\
				}					\
									\
void _(N,_old_edge_)(edge e, vertex v)					\
  {									\
  if (SUCC(e,v,N)==0)							\
    {									\
    if (PRED(e,v,N)==0)							\
      {									\
      _(N,_first)[v]=_(N,_last)[v]=e;					\
      }									\
    else								\
      {									\
      *SUCC_(_(N,_last)[v],v,N)=e;					\
      _(N,_last)[v]=e;							\
      }									\
    }									\
  else									\
    {									\
    if (PRED(e,v,N)==0)							\
      {									\
      *PRED_(_(N,_first)[v],v,N)=e;					\
      _(N,_first)[v]=e;							\
      }									\
    else								\
      {									\
      *PRED_(SUCC(e,v,N),v,N)=e;					\
      *SUCC_(PRED(e,v,N),v,N)=e;					\
      }									\
    }									\
  _(N,__degree)[v]++;							\
  }									\
									\
void _(N,_old_edge1)(edge e, vertex v)					\
  {									\
  _(N,_old_edge_)(e,v);							\
  _(N,_re_ins_edge)(e);							\
  }									\
									\
void _(N,_old_edge)(edge e)						\
  {									\
  _(N,_old_edge_)(e,_(N,__source)[e]);					\
  _(N,_old_edge_)(e,_(N,__target)[e]);					\
  _(N,_re_ins_edge)(e);							\
  }									\
									\
void _(N,_app_vertices)(vertex g)					\
  {									\
  _(N,_Vpred)[g]=_(N,_Vpred)[0];					\
  _(N,_Vsucc)[g]=0;							\
  _(N,_Vpred)[0]=g;							\
  _(N,_Vsucc)[_(N,_Vpred)[g]]=g;					\
  _(N,_vertices)++;							\
  }									\
 									\
vertex _(N,_new_vertex)() { vertex v=++_(N,__vertices_sofar); 		\
			  if (v>_(N,__max_vertices))			\
			    err_handler(5,"too much vertices created");	\
			  _(N,_app_vertices)(v);			\
			  _(N,_first)[v]=_(N,_last)[v]=0;		\
			  _(N,__degree)[v]=0;				\
			  return v;					\
			}						\
									\
void _(N,_rem_vertex)(vertex v)						\
  { 									\
  _(N,_Vpred)[_(N,_Vsucc)[v]]=_(N,_Vpred)[v];				\
  _(N,_Vsucc)[_(N,_Vpred)[v]]=_(N,_Vsucc)[v];				\
  _(N,_vertices)--;							\
  }									\
									\
vertex _(N,_remove_vertex)(vertex v)					\
  { 									\
  set_of_edge S = _(N,_incident_edges)(v);				\
  edge e = 0;								\
  _forall(e,S)								\
    (void) _(N,_remove_edge1)(e,_(N,_opposite)(v,e));			\
  delete_set(S);							\
  _(N,_rem_vertex)(v);							\
  return v;								\
  }									\
									\
void _(N,_delete_vertex)(vertex v)					\
  { 									\
  set_of_edge S = _(N,_incident_edges)(v);				\
  edge e=0;								\
  _forall(e,S)								\
    _(N,_delete_edge)(e);						\
  delete_set(S);							\
  _(N,_rem_vertex)(v);							\
  _(N,_Vsucc)[v]=0;							\
  _(N,_Vpred)[v]=0;							\
  _(N,_it)[v]=0;							\
  }									\
									\
void _(N,_ins_vertex)(vertex v)	{ _(N,_Vpred)[_(N,_Vsucc)[v]]=v;	\
				  _(N,_Vsucc)[_(N,_Vpred)[v]]=v;	\
				  _(N,_vertices)++;			\
				}					\
									\
void _(N,_old_vertex)(vertex v)						\
  { 									\
  set_of_edge S = _(N,_incident_edges)(v);				\
  edge e = 0;								\
  _forall(e,S)								\
    (void) _(N,_old_edge1)(e,_(N,_opposite)(v,e));			\
  delete_set(S);							\
  _(N,_ins_vertex)(v);							\
  }									\
									\
void _(N,_Move_vertex)(vertex v, vertex w, bool dir)			\
  {									\
    if ((dir==before) && (_(N,_Vpred)[w]!=v))				\
      {									\
      _(N,_Vpred)[_(N,_Vsucc)[v]]=_(N,_Vpred)[v];			\
      _(N,_Vsucc)[_(N,_Vpred)[v]]=_(N,_Vsucc)[v];			\
      _(N,_Vpred)[v]=_(N,_Vpred)[w];					\
      _(N,_Vsucc)[v]=w;							\
      _(N,_Vsucc)[_(N,_Vpred)[w]]=v;					\
      _(N,_Vpred)[w]=v;							\
      }									\
    else if ((dir==after) && (_(N,_Vsucc)[w]!=v))			\
      {									\
      _(N,_Vpred)[_(N,_Vsucc)[v]]=_(N,_Vpred)[v];			\
      _(N,_Vsucc)[_(N,_Vpred)[v]]=_(N,_Vsucc)[v];			\
      _(N,_Vsucc)[v]=_(N,_Vsucc)[w];					\
      _(N,_Vpred)[v]=w;							\
      _(N,_Vpred)[_(N,_Vsucc)[w]]=v;					\
      _(N,_Vsucc)[w]=v;							\
      }									\
  }									\
									\
void _(N,_Move_edge)(edge e, edge f, bool dir)				\
  {									\
    if ((dir==before) && (_(N,_Epred)[f]!=e))				\
      {									\
      _(N,_Epred)[_(N,_Esucc)[e]]=_(N,_Epred)[e];			\
      _(N,_Esucc)[_(N,_Epred)[e]]=_(N,_Esucc)[e];			\
      _(N,_Epred)[e]=_(N,_Epred)[f];					\
      _(N,_Esucc)[e]=f;							\
      _(N,_Esucc)[_(N,_Epred)[f]]=e;					\
      _(N,_Epred)[f]=e;							\
      }									\
    else if ((dir==after) && (_(N,_Esucc)[f]!=e))			\
      {									\
      _(N,_Epred)[_(N,_Esucc)[e]]=_(N,_Epred)[e];			\
      _(N,_Esucc)[_(N,_Epred)[e]]=_(N,_Esucc)[e];			\
      _(N,_Esucc)[e]=_(N,_Esucc)[f];					\
      _(N,_Epred)[e]=f;							\
      _(N,_Epred)[_(N,_Esucc)[f]]=e;					\
      _(N,_Esucc)[f]=e;							\
      }									\
  }									\
									\
void _(N,_move_edge)(edge e, vertex v, edge f, bool dir)		\
  { 									\
  if (e!=f)								\
  {									\
  if (_(N,_first)[v]==e)						\
    {									\
    if (_(N,_last)[v]==e)						\
      {									\
      _(N,_first)[v]=_(N,_last)[v]=0;					\
      }									\
    else								\
      {									\
      _(N,_first)[v]=SUCC(e,v,N);					\
      *PRED_(SUCC(e,v,N),v,N)=0;					\
      }									\
    }									\
  else									\
    {									\
    if (_(N,_last)[v]==e)						\
      {									\
      _(N,_last)[v]=PRED(e,v,N);					\
      *SUCC_(PRED(e,v,N),v,N)=0;					\
      }									\
    else								\
      {									\
      *SUCC_(PRED(e,v,N),v,N)=SUCC(e,v,N);				\
      *PRED_(SUCC(e,v,N),v,N)=PRED(e,v,N);				\
      }									\
    }									\
    									\
  if (f==0)								\
    {									\
    if (dir==after)							\
      {									\
      if (_(N,_last)[v]==0)	*SUCC_(_(N,_last)[v]=e,v,N)=0;		\
      else    *SUCC_(*PRED_(_(N,_first)[v],v,N)=e,v,N)=_(N,_first)[v];	\
      _(N,_first)[v]=e;							\
      *PRED_(e,v,N)=0;							\
      }									\
    else								\
      {									\
      if (_(N,_first)[v]==0)	*PRED_(_(N,_first)[v]=e,v,N)=0;		\
      else    *PRED_(*SUCC_(_(N,_last)[v],v,N)=e,v,N)=_(N,_last)[v];	\
      _(N,_last)[v]=e;							\
      *SUCC_(e,v,N)=0;							\
      }									\
    }									\
  else									\
   {									\
   if (dir==after)							\
     {									\
     if (SUCC(f,v,N)==0)  *SUCC_(_(N,_last)[v]=e,v,N)=0;		\
     else		  *PRED_(*SUCC_(e,v,N)=SUCC(f,v,N),v,N)=e;	\
     *PRED_(e,v,N)=f;							\
     *SUCC_(f,v,N)=e; 							\
     }									\
   else									\
     {									\
     if (PRED(f,v,N)==0)  *PRED_(_(N,_first)[v]=e,v,N)=0;		\
     else		  *SUCC_(*PRED_(e,v,N)=PRED(f,v,N),v,N)=e;	\
     *PRED_(f,v,N)=e; 							\
     *SUCC_(e,v,N)=f;							\
     }									\
   }									\
  }									\
  }									\


#define UGRAPH3(N)							\
void _(N,_bucket_sort_edges)(int a, int b, edge_array M)		\
  {									\
  array_of_edge Esucc,Epred,bucket;					\
  int i;								\
  edge e,last;								\
									\
  Esucc = new_array(_(N,__max_edges)+1);				\
  Epred = new_array(_(N,__max_edges)+1);				\
									\
  bucket = new_array(b-a+1);						\
									\
  for(i=0; i<=b-a; i++)  bucket[i]=0;					\
									\
  forall_edges(e,N)							\
    {									\
    i = M[e] - a;							\
    if (bucket[i]==0)							\
      {									\
      Esucc[e]=Epred[e]=e;						\
      bucket[i]=e;							\
      }									\
    else								\
      {									\
      Esucc[e]=bucket[i];						\
      Epred[e]=Epred[bucket[i]];					\
      Esucc[Epred[e]]=e;						\
      Epred[Esucc[e]]=e;						\
      }									\
    }  									\
									\
  for(i=0; i<=b-a; i++)							\
    if (bucket[i]!=0)							\
      {									\
      last = Epred[bucket[i]];						\
      Epred[bucket[i]]=Epred[0];					\
      Esucc[Epred[0]]=bucket[i];					\
      Epred[0]=last;							\
      Esucc[last]=0;							\
      }  								\
									\
  delete_array(_(N,_Epred));						\
  delete_array(_(N,_Esucc));						\
  _(N,_Epred)=Epred;							\
  _(N,_Esucc)=Esucc;							\
  delete_array(bucket);							\
  }									\
									\
									\
void _(N,_bucket_sort_vertices)(int a, int b, vertex_array M)		\
  {									\
  array_of_vertex Vsucc,Vpred,bucket;					\
  int i;								\
  vertex v,last;							\
									\
  Vsucc = new_array(_(N,__max_vertices)+1);				\
  Vpred = new_array(_(N,__max_vertices)+1);				\
									\
  bucket = new_array(b-a+1);						\
									\
  for(i=0; i<=b-a; i++)  bucket[i]=0;					\
									\
  forall_vertices(v,N)							\
    {									\
    i = M[v] - a;							\
    if (bucket[i]==0)							\
      {									\
      Vsucc[v]=Vpred[v]=v;						\
      bucket[i]=v;							\
      }									\
    else								\
      {									\
      Vsucc[v]=bucket[i];						\
      Vpred[v]=Vpred[bucket[i]];					\
      Vsucc[Vpred[v]]=v;						\
      Vpred[Vsucc[v]]=v;						\
      }									\
    }  									\
									\
  for(i=0; i<=b-a; i++)							\
    if (bucket[i]!=0)							\
      {									\
      last = Vpred[bucket[i]];						\
      Vpred[bucket[i]]=Vpred[0];					\
      Vsucc[Vpred[0]]=bucket[i];					\
      Vpred[0]=last;							\
      Vsucc[last]=0;							\
      }  								\
									\
  delete_array(_(N,_Vpred));						\
  delete_array(_(N,_Vsucc));						\
  _(N,_Vpred)=Vpred;							\
  _(N,_Vsucc)=Vsucc;							\
  delete_array(bucket);							\
  }									\
									\
									\
bool _(N,_SAME)(edge e, edge f) 					\
  { 									\
  if ((e==0) || (f==0)) return false;					\
									\
  return ( ( (_(N,__source)[e]==_(N,__source)[f]) 			\
           && (_(N,__target)[e]==_(N,__target)[f]) ) || 		\
           ( (_(N,__source)[e]==_(N,__target)[f]) 			\
           && (_(N,__target)[e]==_(N,__source)[f]))			\
	 );								\
  }									\
									\
bool _(N,_simple)()							\
  {									\
  edge e;								\
  edge_array M;								\
									\
  /* redundant since self loops cannot be created */			\
  forall_edges(e,N)							\
    if (_(N,__source)[e]==_(N,__target)[e])				\
      return false;							\
									\
  M = _(N,_new_edge_array)();						\
									\
  forall_edges(e,N)  M[e] = MIN(_(N,__source)[e],_(N,__target)[e]); 	\
									\
  _(N,_bucket_sort_edges)(1,_(N,_vertices_sofar)(),M);			\
									\
  forall_edges(e,N)  M[e] = MAX(_(N,__source)[e],_(N,__target)[e]);	\
									\
  _(N,_bucket_sort_edges)(1,_(N,_vertices_sofar)(),M);			\
									\
  _(N,_delete_edge_array)(M);						\
									\
  forall_edges(e,N)							\
    if ( _(N,_SAME)( e,_(N,_succ_edge(e)) ) )				\
      return false;							\
									\
  return true;								\
  }									\
									\
void _(N,_eliminate_parallel_edges_and_self_loops)()			\
  {									\
  edge e;								\
  edge_array M;								\
  set_of_edge S;							\
									\
  M = _(N,_new_edge_array)();						\
									\
  forall_edges(e,N)  M[e] = MIN(_(N,__source)[e],_(N,__target)[e]); 	\
									\
  _(N,_bucket_sort_edges)(1,_(N,_vertices_sofar)(),M);			\
									\
  forall_edges(e,N)  M[e] = MAX(_(N,__source)[e],_(N,__target)[e]);	\
									\
  _(N,_bucket_sort_edges)(1,_(N,_vertices_sofar)(),M);			\
									\
  _(N,_delete_edge_array)(M);						\
									\
  S = new_set(_(N,_edges));						\
									\
  forall_edges(e,N)							\
    if (( _(N,_SAME)( e,_(N,_succ_edge(e)) ) )	||			\
	(_(N,__source)[e]==_(N,__target)[e])   )			\
      _append(e,S);							\
									\
  _forall(e,S)								\
    _(N,_delete_edge)(e);						\
									\
  delete_set(S);							\
  }									\
									\
									\
void _(N,_read)(char *fname)						\
  {									\
  char line[250];							\
  FILE *source = fopen(fname,"r");					\
  int n,m,i,s,t;							\
									\
  if (source==NULL) 							\
    err_handler(2,"file not found");					\
									\
  (void) fgets(line,249,source);					\
  (void) fgets(line,249,source);					\
  (void) fgets(line,249,source);					\
									\
									\
  (void) fgets(line,249,source);					\
  n=atoi(line);								\
  for(i=1; i<=n; i++) 							\
    {									\
    (void) fgets(line,249,source);					\
    }									\
									\
  (void) fgets(line,249,source);					\
  m=atoi(line);								\
									\
  _(N,_new)(n,m);							\
									\
  for(i=1; i<=n; i++) 							\
    {									\
    (void) _(N,_new_vertex)();						\
    }									\
									\
  for(i=1; i<=m; i++)							\
    {									\
    (void) fgets(line,249,source);					\
    (void) sscanf(line,"%d %d",&s,&t);					\
    (void) _(N,_new_edge)(s,t);						\
    }									\
  (void) fclose(source);						\
  }									\
									\
void _(N,_readP)(char *fname, void (*IV)(int), void (*IE)(int),		\
		void (*RV)(vertex,char *), void (*RE)(edge,char *))	\
  {									\
  char line[250];							\
  FILE *source = fopen(fname,"r");					\
  int n,m,i,s,t;							\
									\
  if (source==NULL) 							\
    err_handler(2,"file not found");					\
									\
  (void) fgets(line,249,source);					\
  (void) fgets(line,249,source);					\
  (void) fgets(line,249,source);					\
									\
									\
  (void) fgets(line,249,source);					\
  n=atoi(line);								\
  IV(n);								\
  for(i=1; i<=n; i++) 							\
    {									\
    (void) fgets(line,249,source);					\
    RV(i,line);								\
    }									\
									\
  (void) fgets(line,249,source);					\
  m=atoi(line);								\
  IE(m);								\
									\
  _(N,_new)(n,m);							\
									\
  for(i=1; i<=n; i++) 							\
    {									\
    (void) _(N,_new_vertex)();						\
    }									\
									\
  for(i=1; i<=m; i++)							\
    {									\
    (void) fgets(line,249,source);					\
    (void) sscanf(line,"%d %d",&s,&t);					\
    (void) RE(_(N,_new_edge)(s,t),line);				\
    }									\
  (void) fclose(source);						\
  }									\
									\
void _(N,_read_simple)(char *fname)					\
  {									\
  _(N,_read)(fname);							\
  _(N,_eliminate_parallel_edges_and_self_loops)();			\
  }									\
									\
void _(N,_write)(char *fname)						\
  {									\
  FILE *target = fopen(fname,"w");					\
  int i,n=_(N,_vertices),m=_(N,_edges);					\
  vertex_array M;							\
  vertex v;								\
  edge e;								\
									\
  M = _(N,_new_vertex_array)();						\
  i=0;									\
  forall_vertices(v,N)							\
    M[v]=++i;								\
									\
  if (target==NULL) 							\
    err_handler(2,"file can not be created");				\
									\
  (void) fprintf(target,"LEDA.GRAPH\npoint\nint\n%d\n",n);		\
  for(i=1; i<=n; i++)  							\
    (void) fprintf(target,"(%.2f,%.2f)\n",				\
	50.0+40.0*sin((i-1.0)*6.286/n),50.0+40.0*cos((i-1.0)*6.286/n));	\
									\
  (void) fprintf(target,"%d\n",m);					\
									\
  forall_edges(e,N)							\
    (void) fprintf(target,"%d %d 0\n",M[_(N,__source)[e]],M[_(N,__target)[e]]);\
									\
  (void) fclose(target);						\
									\
  _(N,_delete_vertex_array)(M);						\
  }									\
									\
void _(N,_writeP)(char *fname, char * (*WV)(vertex), char * (*WE)(edge))\
  {									\
  FILE *target = fopen(fname,"w");					\
  int i,n=_(N,_vertices),m=_(N,_edges);					\
  vertex_array M;							\
  vertex v;								\
  edge e;								\
									\
  M = _(N,_new_vertex_array)();						\
  i=0;									\
  forall_vertices(v,N)							\
    M[v]=++i;								\
									\
  if (target==NULL) 							\
    err_handler(2,"file can not be created");				\
									\
  (void) fprintf(target,"LEDA.GRAPH\npoint\nint\n%d\n",n);		\
  forall_vertices(v,N) { fprintf(target,"%s\n",WV(v)); } 		\
									\
  (void) fprintf(target,"%d\n",m);					\
									\
  forall_edges(e,N)							\
    (void) fprintf(target,"%d %d %s\n",					\
			 M[_(N,__source)[e]],M[_(N,__target)[e]],WE(e));\
									\
  (void) fclose(target);						\
									\
  _(N,_delete_vertex_array)(M);						\
  }									\
									\
void _(N,_print_vertex)(vertex v)					\
  { 									\
  (void) printf("[%d]",v); (void) fflush(stdout); 			\
  }									\
									\
void _(N,_print_edge)(edge e)						\
  { 									\
  (void) _(N,_print_vertex)(_(N,_source)(e));				\
  (void) printf("--{%d}--",e); (void) fflush(stdout);			\
  (void) _(N,_print_vertex)(_(N,_target)(e));				\
  }									\
									\
void _(N,_print)()							\
  { 									\
  vertex v;								\
  edge e;								\
  (void) printf("\nn: %d  m: %d\n",					\
	_(N,_number_of_vertices)(),_(N,_number_of_edges)());		\
  forall_vertices(v,N)							\
    {									\
    _(N,_print_vertex)(v);						\
    (void) printf(":"); (void) fflush(stdout);				\
    forall_incident_edges(e,v,N)					\
      {									\
      (void) printf(" "); (void) fflush(stdout);			\
      _(N,_print_edge)(e);						\
      }									\
    (void) printf("\n"); (void) fflush(stdout);				\
    }									\
  }									\
									\
void _(N,_use)()							\
  {									\
  _(N,_new)(0,0);							\
  (void) _(N,_source)(0);						\
  (void) _(N,_target)(0);						\
  (void) _(N,_number_of_vertices)();					\
  (void) _(N,_number_of_edges)();					\
  (void) _(N,_all_vertices)();						\
  (void) _(N,_last_vertex)();						\
  (void) _(N,_pred_vertex)(0);						\
  (void) _(N,_all_edges)();						\
  (void) _(N,_last_edge)();						\
  (void) _(N,_pred_edge)(0);						\
  (void) _(N,_cyclic_incident_succ)(0,0);				\
  (void) _(N,_cyclic_incident_pred)(0,0);				\
  (void) _(N,_incident_edges)(0);					\
  (void) _(N,_choose_vertex)();						\
  (void) _(N,_choose_edge)();						\
  (void) _(N,_new_edge)(0,0);						\
  (void) _(N,_new_vertex)();						\
  (void) _(N,_remove_edge)(0);						\
  (void) _(N,_remove_vertex)(0);					\
  (void) _(N,_delete_vertex)(0);					\
  (void) _(N,_simple)();						\
  _(N,_old_vertex)(0);							\
  _(N,_old_edge)(0);							\
  _(N,_read)(0);							\
  _(N,_print)();							\
  (void) _(N,_vertices_sofar)();					\
  (void) _(N,_vertices_max)();						\
  (void) _(N,_edges_sofar)();						\
  (void) _(N,_edges_max)();						\
/*  _(N,_resize_copy)(0,0,0);	*/					\
/*  _(N,_resize)(0,0);	*/						\
  _(N,_delete)();							\
  _(N,_use)();								\
  }

#define def_ugraph_h
#endif

		
