#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 505
#define INF INT_MAX

// --- PROVIDED UTILITIES (Hidden in HackerRank Footer) ---
typedef struct { int time, r, c; } Node;
Node heap[MAX * MAX];
int heapSize = 0;

void push(int t, int r, int c) {
    int i = ++heapSize;
    while (i > 1 && heap[i / 2].time > t) {
        heap[i] = heap[i / 2]; i /= 2;
    }
    heap[i].time = t; heap[i].r = r; heap[i].c = c;
}

Node pop() {
    Node top = heap[1], last = heap[heapSize--];
    int i = 1, child;
    while (i * 2 <= heapSize) {
        child = i * 2;
        if (child + 1 <= heapSize && heap[child + 1].time < heap[child].time) child++;
        if (last.time <= heap[child].time) break;
        heap[i] = heap[child]; i = child;
    }
    heap[i] = last; return top;
}

int get_cost(char ch) {
    if (ch == 'W') return 50; if (ch == 'S') return 30;
    if (ch == 'C') return 20; if (ch == 'G') return 10;
    return 1;
}

// write your code here
void find_treasure(int N, int M, int T, char grid[MAX][MAX]) {
    // Initialize distance array
    int dist[MAX][MAX];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dist[i][j] = INF;
        }
    }
    
    // Start at (0,0) with cost of entering that cell
    dist[0][0] = get_cost(grid[0][0]);
    push(dist[0][0], 0, 0);
    
    // Direction vectors: up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    
    // Dijkstra's algorithm
    while (heapSize > 0) {
        Node u = pop();
        int r = u.r, c = u.c;
        
        // Skip if we've already found a better path
        if (u.time > dist[r][c]) continue;
        
        // Try moving in all 4 directions
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            
            // Check if within bounds
            if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
                int cost = get_cost(grid[nr][nc]);
                int new_time = dist[r][c] + cost;
                
                // Update if we found a shorter path
                if (new_time < dist[nr][nc]) {
                    dist[nr][nc] = new_time;
                    push(new_time, nr, nc);
                }
            }
        }
    }
    
    // Check if we reached the destination within the time limit
    if (dist[N-1][M-1] != INF && dist[N-1][M-1] <= T) {
        printf("%d\n", dist[N-1][M-1]);
    } else {
        printf("FAIL\n");
    }
}

int main() {
    int N, M, T;
    scanf("%d %d %d", &N, &M, &T);
    char grid[MAX][MAX];
    for (int i = 0; i < N; i++) scanf("%s", grid[i]);
    find_treasure(N, M, T, grid);
    return 0;
}