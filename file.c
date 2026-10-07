#include <stdio.h>
#include <string.h>

#define INF 99999
#define MAX 20

int graph[MAX][MAX], dist[MAX], parent[MAX], visited[MAX];
int n, source;
char name[MAX][50];

void enterGraph() {
    int i, j;

    printf("Enter number of locations: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter location %d: ", i + 1);
        scanf(" %[^\n]", name[i]);
    }

    printf("\nEnter distance (0 if no direct road):\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else {
                printf("%s to %s: ", name[i], name[j]);
                scanf("%d", &graph[i][j]);

                if (graph[i][j] == 0)
                    graph[i][j] = INF;
            }
        }
    }
}

void displayMatrix() {
    int i, j;

    printf("\nAdjacency Matrix:\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

void dijkstra() {
    int i, j, min, u;

    for (i = 0; i < n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        visited[i] = 0;
    }

    dist[source] = 0;

    for (i = 0; i < n - 1; i++) {
        min = INF;
        u = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }

        if (u == -1)
            break;

        visited[u] = 1;

        for (j = 0; j < n; j++) {
            if (!visited[j] && graph[u][j] != INF &&
                dist[u] + graph[u][j] < dist[j]) {
                dist[j] = dist[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }
}

void printPath(int v) {
    if (v == -1)
        return;

    printPath(parent[v]);

    if (parent[v] != -1)
        printf(" -> ");

    printf("%s", name[v]);
}

void displayPaths() {
    int i;

    dijkstra();

    printf("\nDestination\tDistance\tPath\n");

    for (i = 0; i < n; i++) {
        if (i == source)
            continue;

        printf("%s\t\t", name[i]);

        if (dist[i] == INF)
            printf("INF\t\tNo Path\n");
        else {
            printf("%d\t\t", dist[i]);
            printPath(i);
            printf("\n");
        }
    }
}

void displayDistances() {
    int i;

    dijkstra();

    printf("\nSource: %s\n", name[source]);

    for (i = 0; i < n; i++) {
        printf("%s : ", name[i]);

        if (dist[i] == INF)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }
}

int main() {
    int choice;

    do {
        printf("\n--- Campus Shortest Route Finder ---\n");
        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                enterGraph();
                break;

            case 2:
                displayMatrix();
                break;

            case 3:
                printf("\n");
                for (int i = 0; i < n; i++)
                    printf("%d. %s\n", i + 1, name[i]);

                printf("Enter source: ");
                scanf("%d", &source);
                source--;
                printf("Source selected: %s\n", name[source]);
                break;

            case 4:
                dijkstra();
                printf("\nShortest distances calculated successfully.\n");
                break;

            case 5:
                displayPaths();
                break;

            case 6:
                displayDistances();
                break;

            case 7:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 7);

    return 0;
}
