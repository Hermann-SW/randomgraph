

#include "ugraph.def"
#include "is_embedding.h"

/*****************************************************************************/

UGRAPH_PROTO(G)

#define _LEFT(e,v,Left,Right)   ((G_source(e)==v) ? Left[e] : Right[e])
#define _RIGHT(e,v,Left,Right)  ((G_source(e)==v) ? Right[e] : Left[e])

#define _LEFT_(e,v,Left,Right)  ((G_source(e)==v) ? &Left[e] : &Right[e])
#define _RIGHT_(e,v,Left,Right) ((G_source(e)==v) ? &Right[e] : &Left[e])

void tr_stat(vertex_array Left, vertex_array Right)
  {
  printf("actual embedding\n");
  G_print();

  Apply_forall_edges(e,G, { G_print_edge(e); 
			    printf("\t(%d,%d)\n",Left[e],Right[e]); } )
  }

/*****************************************************************************/

void triangulate_left_face(edge e, vertex v,
			   edge_array Left, edge_array Right,
			   vertex_array active,
			   list_of_edge A)
  {
  vertex w,u;
  edge f,g,h;


  w = G_opposite(v,e);                 /* find non-articulation vertex */
  f = G_cyclic_incident_pred(e,w);

  active[v] = true;

  while (! active[w])
    {
    active[w]=true;

    w = G_opposite(w,f);
    f = G_cyclic_incident_pred(f,w);
    }

  e = G_cyclic_incident_succ(f,w);     /* v is non-articulation vertex */
  v = G_opposite(w,e);

/*                           no need for cleaning up! */
/*	yes, need for cleaning up!!! */

  while (active[w])
    {
    active[w]=false;

    f = G_cyclic_incident_succ(f,w);
    w = G_opposite(w,f);
    }



  f = e;
  *_LEFT_(e,v,Left,Right) = true;   

  g = G_cyclic_incident_succ(e,v);
  u = G_opposite(v,g);
  *_LEFT_(g,u,Left,Right) = true;

  w = G_opposite(v,e);
  h = G_cyclic_incident_pred(e,w);
  *_LEFT_(h,w,Left,Right) = true;
  w = G_opposite(w,h);
  
  while (G_cyclic_incident_pred(h,w)!=g)                 /* (w!=u) */
    {
    f = G_new_edge2(v,w,g,h,before,before);
    Left[f] = Right[f] = true;
    Append(f,A);

    h = G_cyclic_incident_pred(f,w);
    *_LEFT_(h,w,Left,Right) = true;
    w = G_opposite(w,h);
    }
  }


/*
 *  generates triangulation of embedding.
 */
void triangulate(list_of_edge A)
  {
  edge_array	Left,Right,M;
  edge          e,f,g,h;
  vertex	u,v,w;
  vertex_array  vnum,active;
  list_of_edge  L;
  num           i;

  Left  = G_new_edge_array();
  Right = G_new_edge_array();

  active = G_new_vertex_array();

  G_init_vertex_array(active,false);

  forall_edges(e,G)  
    { 
    Left[e]=Right[e]=(G_degree(G_source(e))+G_degree(G_target(e))==2);
    }

  forall_edges(e,G)
    {
    if (! Left[e])
      triangulate_left_face(e,G_source(e),Left,Right,active,A);


    if (! Right[e])
      triangulate_left_face(e,G_target(e),Left,Right,active,A);
    }

  G_delete_edge_array(Left);
  G_delete_edge_array(Right);
  G_delete_vertex_array(active);


  L    = new_list();

  vnum = G_new_vertex_array();
  M    = G_new_edge_array();

  forall_edges(e,G)  Append(e,L);

  i = 0;
  Apply_forall_vertices(v,G,  vnum[v]=++i; )

  Apply_forall_edges(e,G,  M[e] = MIN(vnum[G_source(e)],vnum[G_target(e)]); )

  bucket_sort(1,G_number_of_vertices(),M,L);

  Apply_forall_edges(e,G,  M[e] = MAX(vnum[G_source(e)],vnum[G_target(e)]); )

  bucket_sort(1,G_number_of_vertices(),M,L);

  G_delete_vertex_array(vnum);
  G_delete_edge_array(M);


  if (! empty(L))
    {
    e = Pop(L);

    while (! empty(L))
      {
      f = Pop(L);

      if (G_SAME(e,f))
        {
        v = G_source(f);
        g = G_cyclic_incident_pred(f,v);
	u = G_opposite(v,g);
        h = G_cyclic_incident_succ(f,v);
	w = G_opposite(v,h);
	G_remove_edge(f);
	G_old_edge2(u,w,f,g,h,before,after);
        }
      else
        e = f;
      }
    }
    
  delete_list(L);

  if (! is_embedding())
    err_handler(234,"non-embedding at end of triangulate");

  if (! G_simple())
    err_handler(234,"non-simple at end of triangulate");
  }


