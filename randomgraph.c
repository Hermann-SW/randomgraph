/*
 * File:   randomgraph.c
 *         - implementation of some algorithms for generation
 *           of random graphs.
 *         - "randomgraph" called without arguments gives short
 *           usage information.
 *           Types of random graphs created are:
 *           > maximal planar
 *           > cubic Halin (= cubic tree + cycle through leafs)
 *           > dual of cubic Halin (= maximal planar with one
 *                                    vertex of degree |V|-1)
 *           > cubic 
 *           The default type is maximal planar.
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

#include "basic.h"
#include "b_urn.h"
#include "ugraph.h"

#include "is_embedding.h"

UGRAPH(G)
UGRAPH(D)

b_urn(INNER)
b_urn(OUTER)

#include "randomgrapho.h"

/*****************************************************************************/


/* 
 *  generates random cubic (multi-)graph by collecting 
 *  3 random perfect matchings 
 */
void random_cubic_ugraph(int n)   
  {
  int i;
  vertex u,v;

  if ((n%2==1) || (n<0)) 
    err_handler(88,"number of vertices must be even and positive");

  U_new(n);
  G_new(n,3*n/2); 

  for(i=0; i<n; i++)
    G_new_vertex();

  for(i=0; i<3; i++)
    {
    forall_vertices(v,G)            /* fill up urn with all vertices */
      U_put(v);

    while (! U_empty())             /* while there are some vertices left */
      {
      u=U_draw();
      v=U_draw();
      G_new_edge(u,v);              /* build new perfect matching edge */
      }
    }

  U_delete();
  }

/*****************************************************************************/


/*
 *  generation of random cubic Halin graph  
 * (planar embedded tree with inner degree 3 and 1 cycle through all leaves)
 */
enum {nothing,outer,inner,updated};

void random_cubic_Halin_graph(int n)
  {                                 
  vertex		u,v,w;
  edge			e;
  int			i,leafs;
  vertex_array		N,Left,Right;
  edge_array		E;

  if ((n%2==1) || (n<0)) 
    err_handler(88,"number of vertices must be even and positive");

  G_new(n,2*n);

  N = G_new_vertex_array();
  E = G_new_edge_array();

  Left = G_new_vertex_array();
  Right = G_new_vertex_array();

  INNER_new(n);
  OUTER_new(n);

  for(i=0; i<n; i++)
    N[G_new_vertex()]=nothing;

  forall_vertices(v,G)         	/* initially left and right border of */
    {                          	/* vertex v is itself 	              */
    Left[v]=v;
    Right[v]=v;
    INNER_put(v);
    }

  leafs=(n>>1)+1;

  for(i=0; i<leafs; i++)       	/* put leaf-vertices in OUTER-urn */   
    {
    v=INNER_draw();
    N[v]=outer;               	/* label outer vertices		*/
    OUTER_put(v);
    }

  while (! INNER_empty())	/* while there exist inner vertices */
    {
    v=INNER_draw();             /* get one inner ...             */

    N[v]=inner;                 /* label inner vertex 		 */

    u=OUTER_draw();             /* ... and two  outer vertices   */
    w=OUTER_draw();

    Left[v]=Left[u];            /* actualize borders of v        */
    Right[v]=Right[w];

    E[G_new_edge(v,u)]=inner;     	   /* add 2 inner and 1 outer edge */
    E[G_new_edge(Right[u],Left[w])]=outer; /* in correct order		   */
    E[G_new_edge(v,w)]=inner;

    OUTER_put(v);                 	/* now v is an outer vertex	*/
    }

  v=OUTER_draw();                 	/* take the last two outer vertices */
  w=OUTER_draw();

  E[G_new_edge(v,w)]=inner;             /* and add the last three edges     */
  if (N[v]==outer)
    E[G_new_edge(Right[v],Left[w])]=outer;
  E[G_new_edge(Right[w],Left[v])]=outer;
  if (N[v]==inner)
    E[G_new_edge(Right[v],Left[w])]=inner;

  forall_vertices(v,G)		/* all incidence lists of inner vertices are */
    {				/* directed clockwise, thus reorder them!    */
    if (N[v]==inner)		/* Size of G.incident_edges(v) always 3!     */
      {
      e=G_first_incident_edge(v);
      w=G_opposite(v,e);

      if (N[w]==inner)
        { 
        E[G_new_edge2(v,w,G_cyclic_incident_succ(e,v),G_cyclic_incident_succ(e,w),after,after)]
          =inner;
        N[w]=updated;
        }
      else
        E[G_new_edge2(v,w,G_cyclic_incident_succ(e,v),e,after,after)]=inner;
      G_delete_edge(e);
      N[v]=updated;
      }      
    }

  G_delete_vertex_array(N);
  G_delete_edge_array(E);
  G_delete_vertex_array(Left);
  G_delete_vertex_array(Right);

  INNER_delete();
  OUTER_delete();

  G_compress(NULL,NULL);
  }


/*****************************************************************************/

#define LEFT(e,v,Left,Right)   ((G_source(e)==v) ? Left[e] : Right[e])
#define RIGHT(e,v,Left,Right)  ((G_source(e)==v) ? Right[e] : Left[e])

#define LEFT_(e,v,Left,Right)  ((G_source(e)==v) ? &Left[e] : &Right[e])
#define RIGHT_(e,v,Left,Right) ((G_source(e)==v) ? &Right[e] : &Left[e])


bool dual_left_face(edge e, vertex d, edge_array Left, edge_array Right)
  {
  vertex v=G_target(e);
  edge f=G_cyclic_incident_pred(e,v);

  Left[e]=d;

  while (LEFT(f,v,Left,Right)==0)  
    {
    *LEFT_(f,v,Left,Right)=d;
    v = G_opposite(v,f);
    f = G_cyclic_incident_pred(f,v);
    }
    
  return (e==f);
  }

bool dual_right_face(edge e, vertex d, edge_array Left, edge_array Right)
  {
  vertex v=G_target(e);
  edge f=G_cyclic_incident_succ(e,v);

  Right[e]=d;

  while (RIGHT(f,v,Left,Right)==0)  
    {
    *RIGHT_(f,v,Left,Right)=d;
    v = G_opposite(v,f);
    f = G_cyclic_incident_succ(f,v);
    }
    
  return (e==f);
  }

/*
 *  generates the topological embedding D dual to the topological embedding
 *  in the planar graph G. It returns true on success and false if G is not
 *  a topological embedding.
 */
bool dual_graph()
  {
  int n,m,f;
  edge_array	Left,Right;
  edge e;

  n = G_number_of_vertices();
  m = G_number_of_edges();

  if (m>3*n-6)  return false;

  Left  = G_new_edge_array();
  Right = G_new_edge_array();

  f = m + 2 - n;

  D_new(f,m);

  forall_edges(e,G)  { Left[e]=0; Right[e]=0; }

  forall_edges(e,G)
    {
    if (Left[e]==0)
      if (! dual_left_face(e,D_new_vertex(),Left,Right))
        {
        D_delete();
        G_delete_edge_array(Left);
        G_delete_edge_array(Right);
        }
    if (Right[e]==0)
      if (! dual_right_face(e,D_new_vertex(),Left,Right))
        {
        D_delete();
        G_delete_edge_array(Left);
        G_delete_edge_array(Right);
        }
    }

  forall_edges(e,G)
    D_new_edge(Left[e],Right[e]);

  G_delete_edge_array(Left);
  G_delete_edge_array(Right);

  return true;
  }

/*****************************************************************************/

void make_non_planar(void)
  {
  edge e,f,g,h;
  vertex u,v,w,x,y;
  if ((G_number_of_edges()+6)!=3*G_number_of_vertices())
    err_handler(77,"make_non_planar() called with non-maximal planar graph");

  if (! is_embedding())
    err_handler(77,"make_non_planar() called with non-embedding");

  U_new(G_number_of_edges());

  forall_edges(e,G)  U_put(e);

  e = U_draw();

  U_delete();

  u = G_source(e);  if (G_degree(u)==3)  u = G_target(e);

  f = G_cyclic_incident_pred(e,u);

  v = G_opposite(u,f);

  g = G_cyclic_incident_succ(e,u);

  w = G_opposite(u,g);

  h = G_cyclic_incident_succ(g,u);

  x = G_opposite(u,h);

  y = G_opposite(u,e);

  G_remove_edge(e);

  G_old_edge2(x,y,e,h,G_cyclic_incident_pred(f,v),after,before);

  forall_edges(f,G)
    if ((f!=e) && (G_SAME(e,f)))
      {
      printf("parallel edge generated! (%d)\n",is_embedding());

      G_print();

      G_print_edge(e); printf("   "); G_print_edge(f); newline;
      exit(1);
      }

  printf("modified to non-embedding! (%d)\n",is_embedding());
  }

/*****************************************************************************/

enum { cubic, cubic_Halin, dual_of_cubic_Halin, maximal_planar };

int main(int argc, char *argv[])
  {
  int i,n,eremove=0,gen_type=maximal_planar;
  bool file_out=false;
  bool nonplanar=false;
  char fname[100];

  if (argc<2)  err_handler(3,"Format: randomgraph n [-t type] [-o file.[u/bit/bit8]] \
[-s seed] [-no] [-r edges] [-n]\
( type in {cubic,cubic_Halin,maximal_planar,dual_of_cubic_Halin} ) ");

  n = atoi(argv[1]);

  for(i=2; i<argc; i++)
    {
    char arg[100];
    strcpy(arg,argv[i]);
    if (arg[0]!='-')
      err_handler(77,"non option found");
    else
      switch (arg[1])
        {
	case 'n': if (arg[2]=='o') { fname[0]=0; file_out=false; }
                  else if (arg[2]=='\0') nonplanar=true;
                  break;
        case 'o': strcpy(fname,argv[++i]); file_out=true; 
		  break;
        case 'r': eremove = atoi(argv[++i]); break;
        case 's': srandom(atoi(argv[++i])); break;
	case 't': strcpy(arg,argv[++i]);
		  if (strncmp(arg,"cubic",5)==0)
                    {
		    if (strlen(arg)==5)
		      gen_type=cubic;
		    else if (strncmp(arg,"cubic_Halin",11)==0)
		      gen_type=cubic_Halin;
		    else err_handler(77,"unknown gen_type");
                    }
		  else
		    if (strncmp(arg,"maximal_planar",14)==0)
		      gen_type=maximal_planar;
		    else if (strncmp(arg,"dual_of_cubic_Halin",19)==0)
		      gen_type=dual_of_cubic_Halin;
		    else err_handler(77,"unknown gen_type");
		  break;                      
	default: err_handler(77,"unknown option");
        }
    }

  switch (gen_type)
    {
    case               cubic: random_cubic_ugraph(n); break;
    case         cubic_Halin: random_cubic_Halin_graph(n); break;
    case      maximal_planar: random_maximal_planar_graph(n); 
			      if ((nonplanar) && (n>4))
				make_non_planar();
			      break;
    case dual_of_cubic_Halin: random_cubic_Halin_graph(2*n-4);
			      if (dual_graph())  UGRAPH_ASSIGN(G,D)
	   		      else err_handler(77,"cubic_Halin not embedded");
	   		      break;
    default: err_handler(77,"wrong type");
    }

  if (eremove!=0)
    {
    U_new(G_number_of_edges());

    Apply_forall_edges(e,G,  U_put(e); )

    while (eremove>0)
      {
      edge e=U_draw();

      G_delete_edge(e);

      eremove--;
      }

    U_delete();
    }

  if (! file_out)
    G_print();
  else
    {
    if (strlen(fname)>0)  
        G_write(fname);
    }

  G_delete();

  if (!getenv("NOSTAT")) statistics();  return 0;
  }

