#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#define INF INT_MAX

// the point
typedef struct point {
	int x;
	int y;
} point_t;

// the adj node
typedef struct adj_node {
	// the point id
	int pt_id;
	struct adj_node *next;
} adj_node_t;

// the graph
typedef struct graph {
	int num_vertex;
	int num_edge;

	point_t *pts;
	adj_node_t **adj_list;

} graph_t;

// // the heap node
// typedef struct set_node {	
// 	int pt_id;
// 	// the distance
// 	int dist;
// } set_node_t;


// typedef struct set {
// 	// the item in the heap
// 	int size;
// 	// the size of the heap
// 	int capcity;
// 	// all the nodes in the heap
// 	set_node_t *node;

// } set_t;



// the heap node
// typedef struct heap_node {	
// 	int pt_id;
// 	// the distance
// 	int dist;
// } heap_node_t;


// typedef struct heap {
// 	// the item in the heap
// 	int size;
// 	// the size of the heap
// 	int capcity;
// 	// all the nodes in the heap
// 	heap_node_t *node;

// } heap_t;



graph_t* loadMap(const char *filename);
void freeGraph(graph_t *g);

// set_t* createSet(int cap);
// void freeSet(set_t *s);

// heap_t* createHeap(int cap);
// void freeHeap(heap_t *h);


void minHeapify(int *heap, int *dist, int idx, int len);

void buildMinHEAP(int *heap, int *dist, int len);





void solveQuery(graph_t *g, const char *queryfilename);


int main(int argc, char *argv[]) {


	graph_t *g = loadMap(argv[1]);


	solveQuery(g, argv[2]);


	freeGraph(g);

	return 0;
}



graph_t* loadMap(const char *filename) {

	int i, idx, x, y;
	int u, v;
	adj_node_t *n;
	FILE *fp = fopen(filename, "r");

	graph_t *g = (graph_t *)malloc(sizeof(graph_t));

	fscanf(fp, "%d %d", &g->num_vertex, &g->num_edge);

	g->pts = (point_t *)malloc(g->num_vertex * sizeof(point_t));
	g->adj_list = (adj_node_t **)malloc(g->num_vertex * sizeof(adj_node_t *));

	for (i = 0; i < g->num_vertex; i++) {
		fscanf(fp, "%d %d %d", &idx, &x, &y);
		g->pts[idx].x = x;
		g->pts[idx].y = y;
		g->adj_list[i] = NULL;
	}


	for (i = 0; i < g->num_edge; i++) {

		fscanf(fp, "%d %d", &u, &v);
		n = (adj_node_t *)malloc(sizeof(adj_node_t));
		n->pt_id = v;
		n->next = g->adj_list[u];
		g->adj_list[u] = n;

		n = (adj_node_t *)malloc(sizeof(adj_node_t));
		n->pt_id = u;
		n->next = g->adj_list[v];
		g->adj_list[v] = n;

	}

	fclose(fp);
	return g;
}


void freeGraph(graph_t *g) {

	int i;
	adj_node_t *n, *temp;

	if (g == NULL) {
		return;
	}

	free(g->pts);

	for (i = 0; i < g->num_vertex; i++) {
		n = g->adj_list[i];
		// printf("%d: ", i);
	

		while (n != NULL) {
			temp = n;
			// printf("%d ", temp->pt_id);
			n = n->next;
			free(temp);
		}

	}



	free(g->adj_list);
	free(g);

}

int euclideanDistance(point_t p1, point_t p2) {


	return (int)sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));

}



void minHeapify(int *heap, int *dist, int idx, int len) {

	int l = 2 * idx + 1;
	int r = 2 * idx + 2;
	int min, temp;


	if (l < len && dist[heap[l]] < dist[heap[idx]]) {
		min = l;
	} else {
		min = idx;
	}

	if (r < len && dist[heap[r]] < dist[heap[idx]]) {
		min = r;
	}

	if (idx != min) {
		temp = heap[idx];
		heap[idx] = heap[min];
		heap[min] = temp;
		minHeapify(heap, dist, min, len);
	}
}

void buildMinHEAP(int *heap, int *dist, int len) {

	int i;
	for (i = len/2; i >= 0; i--) {
		minHeapify(heap, dist, i, len);
	}
}

void solveQuery(graph_t *g, const char *queryfilename) {

	int num_query;
	int i, src, dst, alt;
	int u, v, min, len;

	adj_node_t *node = NULL;

	FILE *fp = fopen(queryfilename, "r");




	int *dist = (int *)malloc(g->num_vertex * sizeof(int));
	
	int *prev = (int *)malloc(g->num_vertex * sizeof(int));

	int *heap = (int *)malloc(g->num_vertex * sizeof(int));

	int *mark = (int *)malloc(g->num_vertex * sizeof(int));


	fscanf(fp, "%d", &num_query);



	while(num_query--) {



		fscanf(fp, "%d %d", &src, &dst);

		for (i = 0; i < g->num_vertex; i++) {
			dist[i] = INF;
			prev[i] = i;
			heap[i] = i;
			mark[i] = 0;

		}

		len = g->num_vertex;


		dist[src] = 0;

		buildMinHEAP(heap, dist, len);
		
		// do the dijstra algorithm
		// printf("%d %d\n", src, dst);
		
		while (1) {


			// min = -1;

			

			// for (u = 0; u < g->num_vertex; u++) {
			// 	if (heap[u] == 0 && (min == -1 || dist[u] < dist[min])) {
			// 		min = u;
			// 	}
			// }
			
			min = heap[0];
			heap[0] = heap[len-1];
			len--;

			// printf("%d\n", min);

			// find the dst
			if (min == dst || dist[min] == INF) {
				// heap[min] = 1;
				
				break;
			}

			mark[min] = 1;

			// heap[min] = 1;
			// printf("min: %d\n", min);
			// getchar();
			node = g->adj_list[min];

			while (node != NULL) {

				v = node->pt_id;
				if (!mark[v]) {
					alt = dist[min] + euclideanDistance(g->pts[min], g->pts[v]);
					if (alt < dist[v]) {
						dist[v] = alt;
						prev[v] = min;
						//minHeapify(heap, dist, len);
					}
				}

				node = node->next;
			}

			buildMinHEAP(heap, dist, len);


		}

		if (dist[dst] == INF || dst >= g->num_vertex) {

			printf("INF\n");
			printf("%d %d\n", src, dst);
		} else {
			printf("%d\n", dist[dst]);
			len = 0;
			u = dst;
			while (prev[u] != u) {
				heap[len++] = u;
				u = prev[u];
			}
			heap[len++] = u;
			len--;
			while (len >= 0) {
				printf("%d", heap[len]);
				if (len == 0) {
					printf("\n");
				} else {
					printf(" ");
				}
				len--;
			}


		}
		
		
	}


	free(dist);
	free(prev);
	free(mark);
	free(heap);

	fclose(fp);

}


