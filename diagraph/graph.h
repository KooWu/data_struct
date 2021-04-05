#ifndef GRAPH_H
#define GRAPH_H

typedef enum {
	UNDISCOVERED,
	DISCOVERED,
	VISITED
} VertexStatus;

typedef struct {
	int val;
	int inDegree;
	int outDegree;
	VertexStatus status;
	int dtime;
	int ftime;
	int priority;
} VertexInfo;

typedef enum {
	UNDETERMINED,
	TREE,
	CROSS,
	FORWARD,
	BACKWARD
} EdgeStatus;

typedef struct {
	int val;
	int weight;
	EdgeStatus status;
} EdgeInfo;

#define VERTEX_MAX_CNT 100
#define EDGE_MAX_CNT 100

typedef struct {
	int vertexCnt;
	VertexInfo vertex[VERTEX_MAX_CNT];
	int edgeCnt;
	EdgeInfo *edge[EDGE_MAX_CNT][EDGE_MAX_CNT];
} GraphInfo;

#endif