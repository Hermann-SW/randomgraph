
#include "basic.h"
#include "b_urn.h"
#include "ugraph.def"

UGRAPH_PROTO(G)
b_urn(U1)

/*****************************************************************************/

/*
 *   generates random maximal planar graph on n vertices.
 *   The resulting ugraph G represents a topological
 *   embedding of the generated random graph.
 */
void random_maximal_planar_graph(int n)
  {
  vertex		u,v,w,x=0,y,z;
  edge			e,f,g,h=0,i=0;
  num			j,typ;

  if (n<4) err_handler(88,"at leat 4 vertices");

  U1_new(5*n);
  G_new(n,5*n);

  u = G_new_vertex();
  v = G_new_vertex();
  w = G_new_vertex();

  U1_put(G_new_edge(u,v));
  U1_put(G_new_edge(u,w));
  U1_put(G_new_edge(v,w));

  for(j=4; j<=n; j++)
    {
    do  { e = U1_draw(); }  while (G_source(e)==0); U1_put(e);

    v = ((random()%2)==1) ? G_source(e) : G_target(e) ;

    switch (G_degree(v))
      {
      case  2: { typ=1; break; }
      case  3: { typ=(num) (1+(random()%2)); break; }
      default: { typ=(num) (1+(random()%3)); break; }
      }

    u=G_opposite(v,e);
    if (typ>1)
      {
      if (typ==3)
	{
	f=G_cyclic_incident_succ(e,v);
	y=G_opposite(v,f);
	h=G_cyclic_incident_pred(f,y);
        G_delete_edge(f);
	}

      f=G_cyclic_incident_succ(e,v);
      x=G_opposite(v,f);
      i=G_cyclic_incident_pred(f,x);
      G_delete_edge(f);
      }

    f=G_cyclic_incident_succ(e,v);
    w=G_opposite(v,f);
    g=G_cyclic_incident_pred(e,u);

    z=G_new_vertex();

    if (typ>1)
      {
      if (typ==3)
	{
	U1_put(G_new_edge2(z,y,G_last_incident_edge(z),h,after,after));
	}
      U1_put(G_new_edge2(z,x,G_last_incident_edge(z),i,after,after));
      }
    U1_put(G_new_edge2(z,w,G_last_incident_edge(z),f,after,after));
    U1_put(G_new_edge2(z,v,G_last_incident_edge(z),e,after,after));
    U1_put(G_new_edge2(z,u,G_last_incident_edge(z),g,after,after));
    }

  U1_delete();

  G_compress(NULL,NULL);
  }



void random_planar_graph(int n, int m)
  {
  random_maximal_planar_graph(n);

  U1_new(G_number_of_edges());

  Apply_forall_edges(e,G,  U1_put(e); )

  while (G_number_of_edges()>m)
    G_delete_edge(U1_draw());

  U1_delete();
  }

