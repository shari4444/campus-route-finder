#include <stdio.h>

#define MAX 20
#define INF 99999

int graph[MAX][MAX];
int dist[MAX], visited[MAX], parent[MAX];
char location[MAX][50];
int n, source;

void enterGraph()
{
    int i, j, roads, u, v, w;

    printf("\n===== ENTER CAMPUS GRAPH =====\n");

    printf("Enter number of locations (e.g. 5): ");
    scanf("%d", &n);

    printf("\nEnter location names one by one:\n");

    for(i = 0; i < n; i++)
    {
        printf("Location %d: ", i + 1);
        scanf(" %[^\n]", location[i]);
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }

    printf("\nEnter number of roads (e.g. 6): ");
    scanf("%d", &roads);

    printf("\nEnter each road in this format:\n");
    printf("Source_Number Destination_Number Distance\n");
    printf("Example: 1 2 4\n");
    printf("This means Location 1 is connected to Location 2 with distance 4.\n\n");

    for(i = 0; i < roads; i++)
    {
        printf("Road %d: ", i + 1);
        scanf("%d %d %d", &u, &v, &w);

        if(u >= 1 && u <= n && v >= 1 && v <= n && w >= 0)
        {
            graph[u-1][v-1] = w;
            graph[v-1][u-1] = w;
        }
        else
        {
            printf("Invalid input! Enter again.\n");
            i--;
        }
    }

    printf("\nCampus graph created successfully!\n");
}

void displayMatrix()
{
    int i, j;

    printf("\n===== ADJACENCY MATRIX =====\n\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(graph[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", graph[i][j]);
        }
        printf("\n");
    }
}

void dijkstra()
{
    int i, j, min, u;

    for(i = 0; i < n; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[source] = 0;

    for(i = 0; i < n; i++)
    {
        min = INF;
        u = -1;

        for(j = 0; j < n; j++)
        {
            if(!visited[j] && dist[j] < min)
            {
                min = dist[j];
                u = j;
            }
        }

        if(u == -1)
            break;

        visited[u] = 1;

        for(j = 0; j < n; j++)
        {
            if(graph[u][j] != INF &&
               !visited[j] &&
               dist[u] + graph[u][j] < dist[j])
            {
                dist[j] = dist[u] + graph[u][j];
                parent[j] = u;
            }
        }
    }
}

void printPath(int v)
{
    if(parent[v] != -1)
    {
        printPath(parent[v]);
        printf(" -> ");
    }

    printf("%s", location[v]);
}

void displayPaths()
{
    int i;

    printf("\n===== SHORTEST PATHS =====\n");
    printf("Source: %s\n\n", location[source]);

    printf("%-25s %-10s %s\n",
           "Destination", "Distance", "Path");

    printf("-------------------------------------------------------------\n");

    for(i = 0; i < n; i++)
    {
        if(i == source)
            continue;

        if(dist[i] == INF)
        {
            printf("%-25s %-10s No Path\n",
                   location[i], "INF");
        }
        else
        {
            printf("%-25s %-10d ",
                   location[i], dist[i]);

            printPath(i);
            printf("\n");
        }
    }
}

void displayDistances()
{
    int i;

    printf("\n===== DISTANCES FROM SOURCE =====\n");
    printf("Source: %s\n\n", location[source]);

    for(i = 0; i < n; i++)
    {
        if(dist[i] == INF)
            printf("%s : Not Reachable\n", location[i]);
        else
            printf("%s : %d\n", location[i], dist[i]);
    }
}

int main()
{
    int choice;
    int graphEntered = 0;
    int sourceSelected = 0;

    do
    {
        printf("\n============================================\n");
        printf("       CAMPUS SHORTEST ROUTE FINDER\n");
        printf("          DIJKSTRA'S ALGORITHM\n");
        printf("============================================\n");

        printf("1. Enter Campus Graph\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Select Source Location\n");
        printf("4. Find Shortest Distance\n");
        printf("5. Display Shortest Paths\n");
        printf("6. Display Distance from Source\n");
        printf("7. Exit\n");

        printf("\nEnter your choice (1-7): ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                enterGraph();
                graphEntered = 1;
                sourceSelected = 0;
                break;

            case 2:
                if(!graphEntered)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else
                {
                    displayMatrix();
                }
                break;

            case 3:
                if(!graphEntered)
                {
                    printf("\nPlease enter the campus graph first.\n");
                    break;
                }

                printf("\n===== CAMPUS LOCATIONS =====\n");

                for(int i = 0; i < n; i++)
                {
                    printf("%d. %s\n", i + 1, location[i]);
                }

                printf("\nEnter source location number (e.g. 1): ");
                scanf("%d", &source);

                if(source >= 1 && source <= n)
                {
                    source--;
                    sourceSelected = 1;

                    printf("Source selected: %s\n",
                           location[source]);
                }
                else
                {
                    printf("Invalid location number!\n");
                }

                break;

            case 4:
                if(!graphEntered)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else if(!sourceSelected)
                {
                    printf("\nPlease select a source location first.\n");
                }
                else
                {
                    dijkstra();

                    printf("\nShortest distances calculated successfully!\n");
                }

                break;

            case 5:
                if(!graphEntered)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else if(!sourceSelected)
                {
                    printf("\nPlease select a source location first.\n");
                }
                else
                {
                    dijkstra();
                    displayPaths();
                }

                break;

            case 6:
                if(!graphEntered)
                {
                    printf("\nPlease enter the campus graph first.\n");
                }
                else if(!sourceSelected)
                {
                    printf("\nPlease select a source location first.\n");
                }
                else
                {
                    dijkstra();
                    displayDistances();
                }

                break;

            case 7:
                printf("\nThank you for using Campus Shortest Route Finder!\n");
                break;

            default:
                printf("\nInvalid choice! Please enter a number from 1 to 7.\n");
        }

    } while(choice != 7);

    return 0;
}
