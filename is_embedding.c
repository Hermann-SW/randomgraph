
#include "b_stack.h"

#include "ugraph.def"

/*****************************************************************************/

UGRAPH_PROTO(G)

#define _LEFT(e,v,Left,Right)   ((G_source(e)==v) ? Left[e] : Right[e])
#define _RIGHT(e,v,Left,Right)  ((G_source(e)==v) ? Right[e] : Left[e])

#define _LEFT_(e,v,Left,Right)  ((G_source(e)==v) ? &Left[e] : &Right[e])
#define _RIGHT_(e,v,Left,Right) ((G_source(e)==v) ? &Right[e] : &Left[e])


/*****************************************************************************/


void CONNECTED_COMPONENTS_recursive(vertex v, vertex_array compnum, num no)
  {
  vertex w;

  compnum[v] = no;

  forall_adjacent_vertices(w,v,G)
    if (compnum[w]==0)
      CONNECTED_COMPONENTS_recursive(w,compnum,no);
  }

num CONNECTED_COMPONENTS(vertex_array compnum)
  {
  vertex v;
  num count = 0;

  G_init_vertex_array(compnum,0);

  if (! getenv("NONRECURSIVE"))
    {
    forall_vertices(v,G)
      if (compnum[v]==0)
        CONNECTED_COMPONENTS_recursive(v,compnum,++count);
    } 
  else
    {
    vertex w;
    b_stack S=new_b_stack(2*G_number_of_edges());

    forall_vertices(v,G)
      if (compnum[v]==0)
        {
        ++count;

        push(v,S);

        while (! empty_b_stack(S))
          {
          v = pop(S);

          if (compnum[v]==0)
            {
            compnum[v]=count;

            forall_adjacent_vertices(w,v,G)
              if (compnum[w]==0) 
                push(w,S);
            }
          }
        }

     delete_b_stack(S);
    }

  return count;
  }

void trace_left_pseudo_face(edge e, vertex v, 
                            edge_array Left, edge_array Right, num no)
  {
  edge f = e;

  do
    {
    *_LEFT_(f,v,Left,Right)=no;
    v = G_opposite(v,f);
    f = G_cyclic_incident_pred(f,v);
    }
  while (_LEFT(f,v,Left,Right)==0);
  }

#define for_both_adjacent_vertices(v,e,G,Block)\
  { vertex v=G_source(e); { Block } v=G_target(e); { Block } }


bool is_embedding(void)
  {
  int n,m,f,c;
  edge_array	Left,Right;
  vertex_array  compnum;

  n = G_number_of_vertices();
  m = G_number_of_edges();

  if (m+6>3*n)  
    {
    return (n<3);
    }


  Left  = G_new_edge_array();
  Right = G_new_edge_array();

  f = 0;

  G_init_edge_array(Left,0);
  G_init_edge_array(Right,0);

  Apply_forall_edges
    (e,G,   
      for_both_adjacent_vertices
        (v,e,G,
          if (_LEFT(e,v,Left,Right)==0)
            trace_left_pseudo_face(e,v,Left,Right,++f);
        )
    )

  Apply_forall_vertices(v,G,  if (G_degree(v)==0)  f++; )

  G_delete_edge_array(Left);
  G_delete_edge_array(Right);


  compnum = G_new_vertex_array();

  c = CONNECTED_COMPONENTS(compnum);

  G_delete_vertex_array(compnum);


  return ((n+f)==(m+2*c));
  }

