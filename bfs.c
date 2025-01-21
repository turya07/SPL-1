#include<stdio.h>
#include<stdlib.h>


#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF -1

typedef struct Queue{
    int *num_vertex;
    int front;
    int rear;
    int size;
}Queue;

Queue* creat_queue(int size){
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->num_vertex = (int *)malloc(size* sizeof(int));
    queue->front = 0;
    queue->rear = -1;
    queue->size = size;
    return queue;
} 

int isEmpty(Queue *queue){
    return queue->rear < queue->front;
}

void enqueue(Queue *queue, int value){
    queue->num_vertex[++queue->rear] = value;
}

int dequeue(Queue *queue){
    return queue->num_vertex[queue->front++];
}

void BFS(int **adjM, int num_v, int start, int *prev, int *des){
    int *color = (int*)malloc(num_v * sizeof(int));
    Queue *QUE = creat_queue(num_v);

    for(int i = 0; i < num_v; i++){
        color[i] = WHITE;
        prev[i] = -1;
        des[i] = INF;
    }
    color[start] = GRAY;
    des[start] = 0;
    prev[start] = -1;
    enqueue(QUE,start);

    while (!isEmpty(QUE)){
       int i = dequeue(QUE);
       for(int j = 0; j < num_v ; j++){
            if(adjM[i][j] == 1 && color[j] == WHITE){
                color[j] = GRAY;
                des[j] = des[i] +1;
                prev[j] = i;
                enqueue(QUE,j);
            }
        }
        color[i] = BLACK;
    }

    free(color);
    free(des);
    free(QUE->num_vertex);
    free(QUE);
}

void printPath(int *prev, int start, int last){
    if(start == last)
        printf("%d ",start);
    else if(prev[last] == -1)
        printf("no path from %d to %d\n",start,last);
    else{
        printPath(prev, start, prev[last]);
        printf("%d ",last);
    }
}

int main(){
    int num_v;
    printf("enter the size\n");
    scanf("%d",&num_v);

    int **adjMatrix = (int **)malloc(num_v * sizeof(int*));
    for (int i = 0; i < num_v; i++) 
        adjMatrix[i] = (int*) malloc(num_v * sizeof(int));

    printf("Enter the adjacency matrix (1 for connection, 0 for no connection):\n");
    for (int i = 0; i < num_v; i++)
    {
        for (int j = 0; j < num_v; j++)
        {
            scanf("%d", &adjMatrix[i][j]);
        }
    }

    int searchIn,destination;
    printf("enter the sourch & destination:");
    scanf("%d %d",&searchIn,&destination);
    int *prev = (int *)malloc(num_v * sizeof(int));
    int *des = (int *)malloc(num_v * sizeof(int));

    BFS(adjMatrix, num_v, searchIn, prev, des);

    printf("path from %d to %d :",searchIn,destination);
    printPath(prev,searchIn,destination);
    printf("\n");

    printf("Distances from vertex %d:\n", searchIn);
    for (int i = 0; i < num_v; i++) {
        printf("Distance to %d: %d\n", i, des[i]);
    }

    for (int i = 0; i < num_v; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);
    free(prev);

}