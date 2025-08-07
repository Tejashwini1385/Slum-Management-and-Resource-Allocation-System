#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include<limits.h>

#define TARGET_HYGIENE 0.75
#define HASH_SIZE 100
#define MAX_NODES 100
#define INF INT_MAX
#define MAX_MEMBERS 6
#define PRIME 101
#define MAX_SLUMS 5

#define MAX_VERTICES 100


// FOR DIJKTRAS ALGORITHM
int v;
int distance[MAX_VERTICES];
int path[MAX_VERTICES];
int visited[MAX_VERTICES];

// FOR DEPTH FIRST SEARCH

#define MAX 100
int n;
int start;
int graph[MAX][MAX];

// ***************************************Functions of thefts **********************************************************
// The code includes various functions related to sorting and handling theft data.
struct theft
{
    int slumNumber;
    int thefts;
    char date[20];
    char time[10];

};

typedef struct theft* Theft;

Theft node[30];


// Function:     Partition
// Description:  Partition function used in quicksort for sorting theft data based on the number of thefts
// Input param:  arr[] - array of Theft structures, low - starting index, high - ending index
// Return Type:  int - partition index
int Partition(Theft arr[], int low, int high)
{
    int pivot = arr[high]->thefts;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j]->thefts < pivot)
        {
            i++;
            Theft temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }


    Theft temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Function:     quick_sort
// Description:  Quick sort algorithm for sorting theft data based on the number of thefts
// Input param:  arr[] - array of Theft structures, low - starting index, high - ending index
// Return Type:  void
void quick_sort(Theft arr[], int low, int high)
{
    if (low < high)
    {

        int PartitionIndex = Partition(arr, low, high);


        quick_sort(arr, low, PartitionIndex - 1);
        quick_sort(arr, PartitionIndex + 1, high);
    }
}

// **************************************Kruskals function*****************************************************

// making relation between node and area
typedef struct dataNodesNames
{
    int n;
    char name[50];
    struct dataNodesNames* next;
} Node;
Node* data;

// structure to store vertices and weight between them
typedef struct node
{
    int u;
    int v;
    int w;
} NODE;
NODE* edges;

// Function:     fillSpanningFile
// Description:  Fills a file ("spanning.txt") with randomly generated data for Kruskal's algorithm
// Input param:  fp - pointer to the file
// Return Type:  void
void fillSpanningFile(FILE * fp)
{
    fp = fopen("spanning.txt", "w");
    srand(time(NULL));

    for(int i=0; i<300; i++)
    {
        // rand()%100  rand()%100  rand()%1000
        fprintf(fp, "%d %d %d\n",rand()%100, rand()%100,rand()%1000);
    }
    fclose(fp);
    return;
}

// Function:     displayData
// Description:  Displays data stored in the "data" array
// Input param:  n - number of elements, data[] - array of Node structures
// Return Type:  void
void displayData(int n, Node data[])
{
    for(int i=0; i<n; i++)
    {
        printf("%d %s\n",data[i].n, data[i].name);
    }
    return;
}

// Function:     generate_random_string
// Description:  Generates a random string of a given length
// Input param:  length - length of the string to be generated
// Return Type:  char* - pointer to the generated string
char* generate_random_string(int length)
{
    // Seed the random number generator with the current time
    // Define the characters that can be used in the random string
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    // Allocate memory for the string, including space for the null terminator
    char* random_string = (char*)malloc((length + 1) * sizeof(char));
    // Generate random characters and build the string
    for (int i = 0; i < length; i++)
    {
        int index = rand() % (sizeof(charset) - 1);
        random_string[i] = charset[index];
    }

    // Add null terminator to the end of the string
    random_string[length] = '\0';
    return random_string;
}

// Function:     fillKruskalsFile
// Description:  Fills a file ("kruskalsRepresentation.txt") with randomly generated data for Kruskal's algorithm
// Input param:  fp - pointer to the file
// Return Type:  void
void fillKruskalsFile(FILE* fp)
{
    fp = fopen("kruskalsRepresentation.txt", "w");
    char *name;
    for(int i=0; i < 100; i++)
    {
        name = generate_random_string(10);
        fprintf(fp, "%d %s\n", i, name);
    }
    fclose(fp);
    return;
}

// Function:     readKruskals
// Description:  Reads data from the file ("kruskalsRepresentation.txt") and populates the "data" array
// Input param:  fp - pointer to the file, data[] - array of Node structures
// Return Type:  void
void readKruskals(FILE* fp, Node data[])
{
    fp = fopen("kruskalsRepresentation.txt","r");
    int j = 0;
    while(!feof(fp))
    {
        fscanf(fp,"%d %s\n",&data[j].n, &data[j].name);
        j++;
    }
    fclose(fp);
    return;
}

// Function:     swap
// Description:  Swaps two NODE structures
// Input param:  a, b - pointers to NODE structures
// Return Type:  void
void swap(NODE* a, NODE* b)
{
    NODE temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// Function:     partition
// Description:  Partition function used in quicksort for sorting edges based on weight
// Input param:  a[] - array of NODE structures, l - starting index, r - ending index
// Return Type:  int - partition index
int partition(NODE a[], int l, int r)
{
    NODE P = a[l];
    int i = l;
    int j = r+1;

    // Using tonys logic of partition in quick sort
    do
    {
        do
        {
            i++;
        }
        while(P.w > a[i].w);
        do
        {
            j--;
        }
        while(P.w < a[j].w);
        swap(&a[i], &a[j]);
    }
    while(i < j);

    swap(&a[i], &a[j]);
    swap(&a[l], &a[j]);

    return j;

}

// Function:     quickSort
// Description:  Quick sort algorithm for sorting edges based on weight
// Input param:  edges[] - array of NODE structures, l - starting index, r - ending index
// Return Type:  void
void quickSort(NODE edges[], int l, int r)
{
    if(l < r)
    {
        // we can sort
        int p = partition(edges, l, r);

        // calling Quick Sort on both the parts
        quickSort(edges, l, p-1);
        quickSort(edges, p+1, r);
    }
    return;
}

// Function:     find
// Description:  Checks if two vertices belong to the same connected component
// Input param:  arr[] - array representing connected components, u, v - vertices
// Return Type:  int - 1 if u and v are in the same connected component, 0 otherwise
int find(int arr[], int u, int v)
{
    if(arr[u] == arr[v])
        return 1;
    return 0;
}

// Function:     union_
// Description:  Unions two connected components
// Input param:  arr[] - array representing connected components, n - size of arr[], u, v - vertices
// Return Type:  void
void union_(int arr[], int n, int u, int v)
{
    int temp = arr[u];
    for(int i=0; i<n; i++)
    {
        if(arr[i] == temp)
            arr[i] = arr[v];
    }
    return;
}

// Function:     kruskals
// Description:  Kruskal's algorithm for finding a minimal spanning tree
// Input param:  edges[] - array of NODE structures, n - number of edges, arr[] - array representing connected components
// Return Type:  int - total weight of the minimal spanning tree
int kruskals(NODE edges[], int n, int arr[])
{
    int sum = 0;
    for(int i=0; i<n; i++)
    {
        if(!find(arr, edges[i].u, edges[i].v))
        {
            union_(arr, 10, edges[i].u, edges[i].v);
            sum += edges[i].w;
            printf("%d %s  %d %s\n",edges[i].u,data[edges[i].u].name, edges[i].v,data[edges[i].v].name);
        }
    }
    printf("\n");
    return sum;
}

// *******************************************************Shortest path***********************************************************

// creating a structure for storing index {node} and areaName to implement dijktras
typedef struct nodesNames
{
    int index;
    char areaName[50];
} nodesNames;

// Function:     heapify
// Description:  Heapifies an array
// Input param:  h[] - array to be heapified, n - size of h[]
// Return Type:  void
void heapify(int h[], int n)
{
    for (int i = n / 2; i >= 0; i--)
    {
        int k = i;
        int v = h[i];
        bool heap = false;
        while (!heap && k * 2 <= n)
        {
            int j = k * 2;
            if (j < n)
            {
                if (h[j] > h[j + 1])
                {
                    j = j + 1;
                }
            }
            if (v <= h[j])
            {
                heap = true;
            }
            else
            {
                h[k] = h[j];
                k = j;
            }
        }
        h[k] = v;
    }
    return;
}

// Function:     deleteMin
// Description:  Deletes the minimum element from a heap
// Input param:  h[] - array representing the heap, n - size of h[]
// Return Type:  int - minimum element
int deleteMin(int arr[], int* n)
{
    if (*n <= 0)
    {
        printf("Heap is empty\n");
        return -1;
    }
    else
    {
        heapify(arr, *n);
        int r = arr[1];
        arr[1] = arr[*n];
        (*n)--;
        heapify(arr, *n);
        return r;
    }
}

// Function: dijkstras
// Description: Implementation of Dijkstra's algorithm to find the shortest path in a graph
// Input parameters:
//   - cost[MAX_VERTICES][MAX_VERTICES]: adjacency matrix representing the graph
//   - v: number of vertices in the graph
//   - src: source vertex for Dijkstra's algorithm
// Return Type: void
void dijkstras(int cost[MAX_VERTICES][MAX_VERTICES], int v, int src)
{
    int j;
    visited[src] = 1;

    int* arr = (int*)malloc(MAX_VERTICES * sizeof(int));
    if (arr == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    for (j = 0; j < v - 1; j++)
    {
        int u = 0;
        int c = 0;
        for (int i = 0; i < v; i++)
        {
            if (visited[i] == 0)
            {
                arr[++c] = distance[i];
            }
        }
        u = deleteMin(arr, &c);
        int index;
        if (u != -1)
        {
            for (int i = 0; i < v; i++)
            {
                if (visited[i] == 0 && distance[i] == u)
                {
                    index = i;
                }
            }
            visited[index] = 1;
            for (int i = 0; i < v; i++)
            {
                if (visited[i] == 0 && distance[i] > cost[index][i] + distance[index])
                {
                    distance[i] = cost[index][i] + distance[index];
                    path[i] = index;
                }
            }
        }
    }

    free(arr);
    return;
}

// Function: print
// Description: Displays the distance array and corresponding area names
// Input parameters:
//   - v: number of vertices
//   - a[]: array of nodesNames structures
// Return Type: void
void print(int v, nodesNames a[])
{
    printf("\nThe distance array is\n");
    for (int i = 0; i < v; i++)
    {
        printf("%d ", distance[i]);
        printf("%s \n", a[i].areaName);
    }
    printf("\n");
    return;
}

// Function: writeGraphToFile
// Description: Writes the edges of the graph to a file ("dijkstraNodes.txt")
// Input parameter:
//   - cost[MAX_VERTICES][MAX_VERTICES]: adjacency matrix representing the graph
// Return Type: void
void writeGraphToFile(int cost[MAX_VERTICES][MAX_VERTICES])
{
    FILE * fp;
    fp = fopen("dijkstraNodes.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file");
        return;
    }

    for (int i = 0; i < MAX_VERTICES; ++i)
    {
        for (int j = i + 1; j < MAX_VERTICES; ++j)
        {
            if (cost[i][j] != 0)
            {
                fprintf(fp, "%d %d %d\n", i, j, cost[i][j]);
            }
        }
    }

    fclose(fp);
}

// Function: generateRandomEdges
// Description: Generates random edges for the graph and assigns random weights
// Input parameter:
//   - cost[MAX_VERTICES][MAX_VERTICES]: adjacency matrix representing the graph
// Return Type: void
void generateRandomEdges(int cost[MAX_VERTICES][MAX_VERTICES])
{

    // Create a connected graph
    for (int i = 1; i < MAX_VERTICES; ++i)
    {
        int edge1 = i;
        int edge2 = rand() % i;  // Connect to a random node before the current one
        int weight = rand() % 10 + 1;  // Random weight between 1 and 10
        cost[edge1][edge2] = weight;
        cost[edge2][edge1] = weight;  // Assuming an undirected graph
    }
}

// Function: assignCostMatrixValue
// Description: Initializes the cost matrix with default values
// Input parameter:
//   - m[][MAX_VERTICES]: cost matrix to be initialized
// Return Type: void
void assignCostMatrixValue(int m[][MAX_VERTICES])
{
    for(int i= 0; i<MAX_VERTICES; i++)
    {
        for(int j = 0; j < MAX_VERTICES; j++)
        {
            m[i][j] = 9999;
        }
        m[i][i] = 0;
    }
    return;
}

// Function: loadThenodeNames
// Description: Loads node names from a file ("DijktrasNodesAreaRelation.txt") into the array a[]
// Input parameters:
//   - a[]: array of nodesNames structures
//   - fp: pointer to the file
// Return Type: int - number of nodes loaded
int loadThenodeNames(nodesNames a[], FILE* fp)
{
    int i = 0;
    fp = fopen("DijktrasNodesAreaRelation.txt", "r");
    if(fp == NULL)
    {
        printf("Error in opeaning in dijktras.txt\n");
        return -1;
    }
    while(!feof(fp))
    {
        fscanf(fp,"%d %s",&a[i].index, &a[i].areaName);
        i++;
    }
    fclose(fp);
    return i;
}

// Function: BruteForceStringMatch
// Description: Performs a brute-force string match for two strings
// Input parameters:
//   - t[]: target string
//   - p[]: pattern string
//   - n: length of target string
//   - m: length of pattern string
// Return Type: int - 1 if strings match, 0 otherwise
int BruteForceStringMatch(char t[], char p[], int n, int m)
{
    for(int i = 0; i < n; i++)
    {
        if(t[i] != p[i])
        {
            return 0;
        }
    }
    return 1;
}

// Function: findSource
// Description: Finds the index of a source node in the nodesNames array
// Input parameters:
//   - source[]: source node name
//   - a[]: array of nodesNames structures
//   - v: number of nodes
// Return Type: int - index of the source node, -1 if not found
int findSource(char source[], nodesNames a[], int v)
{
    for(int i =0; i < v; i++)
    {
        if(strlen(source) == strlen(a[i].areaName))
        {
            if(BruteForceStringMatch(source, a[i].areaName, strlen(source), strlen(a[i].areaName)))
            {
                return i;
            }
        }
    }
    return -1;
}

// Function: printAreaNames
// Description: Displays area names from the nodesNames array
// Input parameters:
//   - n: number of nodes
//   - a[]: array of nodesNames structures
// Return Type: void
void printAreaNames(int n, nodesNames a[])
{

    for(int i=0; i<n; i++)
    {
        printf("%s\n",a[i].areaName);
    }
    return;
}


// ******************************************************* DFS **********************************************************

// Function: dfs
// Description: Performs depth-first search (DFS) on a graph
// Input parameters:
//   - graph[MAX][MAX]: adjacency matrix representing the graph
//   - n: number of vertices in the graph
//   - start: starting vertex for DFS
//   - a[]: array of DFS_Names structures
// Return Type: void
struct DFS_Names
{
    int number;
    char name[50];
};

typedef struct DFS_Names DFS_Names;

// Define a Node structure for the linked list
struct Node
{
    int data;
    struct Node *next;
};

struct Stack
{
    struct Node *top;
};

// Define a typedef for a pointer to Stack as stack
typedef struct Stack *stack;

void initstack(stack s)
{
    s->top = NULL;
}

// Function to check if the stack is empty
int isempty(stack s)
{
    return s->top == NULL;
}

// Function to push a new element onto the stack
void push(stack s, int data)
{
    // Allocate memory for a new node
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Set data and link the new node to the current top
    newNode->data = data;
    newNode->next = s->top;

    // Update the top pointer to the new node
    s->top = newNode;
}

// Function to pop an element from the stack
int pop(stack s)
{
    // Check for stack underflow
    if (isempty(s))
    {
        printf("Stack underflow!\n");
        exit(EXIT_FAILURE);
    }

    // Save the current top node
    struct Node *temp = s->top;

    // Get data and update the top pointer to the next node
    int data = temp->data;
    s->top = temp->next;

    // Free the memory of the popped node
    free(temp);

    // Return the popped data
    return data;
}

// Function to perform depth-first search (DFS)
void dfs(int graph[MAX][MAX], int n, int start, DFS_Names a[])
{
    // Allocate memory for the stack structure
    stack s = (stack)malloc(sizeof(struct Stack));
    if (s == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Array to track visited nodes
    int visited[MAX] = {0};

    // Initialize the stack
    initstack(s);

    // Push the starting node onto the stack
    push(s, start);

    // Display the initial message
    printf("DFS Order: ");

    // Perform DFS
    while (!isempty(s))
    {
        // Pop a node from the stack
        int node = pop(s);

        // Process the node if not visited
        if (!visited[node])
        {
            printf("%d %s\n", node, a[node].name);
            visited[node] = 1;

            // Push unvisited neighbors onto the stack
            for (int i = 0; i < n; i++)
            {
                if (graph[node][i] && !visited[i])
                {
                    push(s, i);
                }
            }
        }
    }

    // Free the stack memory
    free(s);

    // Display a newline character after DFS completion
    printf("\n");
}

// Function: fillValue
// Description: Fills the adjacency matrix from a file ("DFS_Edges.txt")
// Input parameters:
//   - fp: pointer to the file
//   - m[][MAX]: adjacency matrix to be filled
// Return Type: void
void fillValue(FILE *fp, int m[][MAX])
{
    fp = fopen("DFS_Edges.txt", "r");
    while (!feof(fp))
    {
        int x, y, z;
        fscanf(fp, "%d %d %d", &x, &y, &z);
        m[x][y] = z;
    }
    fclose(fp);
    return;
}

// Function: fillNames
// Description: Fills DFS_Names array from a file ("DijktrasNodesAreaRelation.txt")
// Input parameters:
//   - fp: pointer to the file
//   - a[]: array of DFS_Names structures
// Return Type: void
void fillNames(FILE *fp, DFS_Names a[])
{
    fp = NULL;
    fp = fopen("DijktrasNodesAreaRelation.txt", "r");
    int i=0;
    if(fp == NULL)
    {
        printf("File Not found ");
        exit(0);
    }
    while(!feof(fp))
    {
        fscanf(fp, "%d %s", &a[i].number, &a[i].name);
        i++;
    }
    fclose(fp);
    return;
}

// ***************************************************** BST ****************************************
// Structure to represent a house
struct House
{
    int slumNo;
    int houseNo;
    int numOfMembers;
    char houseName[50];
    struct House* left;
    struct House* right;
};

// Function: createHouse
// Description: Creates a new house node for the BST
// Input parameters:
//   - slumNo: slum number
//   - houseNo: house number
//   - numOfMembers: number of members in the house
//   - houseName: name of the house
// Return Type: struct House* - pointer to the new house node
struct House* createHouse(int slumNo, int houseNo, int numOfMembers, const char* houseName)
{
    struct House* newHouse = (struct House*)malloc(sizeof(struct House));
    newHouse->slumNo = slumNo;
    newHouse->houseNo = houseNo;
    newHouse->numOfMembers = numOfMembers;
    strcpy(newHouse->houseName, houseName);
    newHouse->left = NULL;
    newHouse->right = NULL;
    return newHouse;
}

// Function: insert
// Description: Inserts a new house node into the BST
// Input parameters:
//   - root: root of the BST
//   - slumNo: slum number
//   - houseNo: house number
//   - numOfMembers: number of members in the house
//   - houseName: name of the house
// Return Type: struct House* - pointer to the root of the updated BST
struct House* insert(struct House* root, int slumNo, int houseNo, int numOfMembers, const char* houseName)
{
    if (root == NULL)
    {
        return createHouse(slumNo, houseNo, numOfMembers, houseName);
    }

    if (houseNo < root->houseNo)
    {
        root->left = insert(root->left, slumNo, houseNo, numOfMembers, houseName);
    }
    else if (houseNo > root->houseNo)
    {
        root->right = insert(root->right, slumNo, houseNo, numOfMembers, houseName);
    }

    return root;
}

// Function: displayHousesInSlum
// Description: Displays houses in a specific slum from the BST using in-order traversal
// Input parameters:
//   - root: root of the BST
//   - slumNo: slum number
// Return Type: void
void displayHousesInSlum(struct House* root, int slumNo)
{
    if (root != NULL)
    {
        displayHousesInSlum(root->left, slumNo);

        if (root->slumNo == slumNo)
        {
            printf("Slum No: %d, House No: %d, Members: %d, Name: %s\n", root->slumNo, root->houseNo, root->numOfMembers, root->houseName);
        }

        displayHousesInSlum(root->right, slumNo);
    }
    return;
}

// Function: freeBST
// Description: Frees the memory allocated for the BST
// Input parameter:
//   - root: root of the BST
// Return Type: void
void freeBST(struct House* root)
{
    if (root != NULL)
    {
        freeBST(root->left);
        freeBST(root->right);
        free(root);
    }
}

// Function: findMin
// Description: Finds the minimum value node in a BST
// Input parameter:
//   - node: root of the BST
// Return Type: struct House* - pointer to the minimum value node
struct House* findMin(struct House* node)
{
    struct House* current = node;

    // Keep traversing the left subtree to find the minimum value
    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}

// Function: deleteNode
// Description: Deletes a node with a given house number from the BST
// Input parameters:
//   - root: root of the BST
//   - houseNo: house number to be deleted
// Return Type: struct House* - pointer to the root of the updated BST
struct House* deleteNode(struct House* root, int houseNo)
{
    if (root == NULL)
    {
        return root;
    }

    // If the house number to be deleted is smaller than the root's house number,
    // then it lies in the left subtree
    if (houseNo < root->houseNo)
    {
        root->left = deleteNode(root->left, houseNo);
    }
    // If the house number to be deleted is greater than the root's house number,
    // then it lies in the right subtree
    else if (houseNo > root->houseNo)
    {
        root->right = deleteNode(root->right, houseNo);
    }
    // If the house number to be deleted is the same as the root's house number,
    // then this is the node to be deleted
    else
    {
        // Node with only one child or no child
        if (root->left == NULL)
        {
            struct House* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            struct House* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        // Get the inorder successor (smallest in the right subtree)
        struct House* temp = findMin(root->right);

        // Copy the inorder successor's content to this node
        root->slumNo = temp->slumNo;
        root->houseNo = temp->houseNo;
        root->numOfMembers = temp->numOfMembers;
        strcpy(root->houseName, temp->houseName);

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->houseNo);
    }

    return root;
}

// Function: displayHouses
// Description: Displays houses in the BST using in-order traversal
// Input parameter:
//   - head: root of the BST
// Return Type: void
void displayHouses(struct House* head)
{
    if(head == NULL)
    {
        return;
    }
    else
    {
        displayHouses(head->left);
        printf("House name: %s House number: %d Number of members: %d \n",head->houseName, head->houseNo, head->numOfMembers);
        displayHouses(head->right);
    }
    return;
}
//****************************************heap sort*********************************\\

struct commette {
    char name[20];
    int age;
    float education;
};

struct slum {
    char slumName[10];
    struct commette leader;
    struct commette members[MAX_MEMBERS];
};

struct slum mumbai[5];

void displayCommetteLeader() {
    int i, j;
    for (i = 0; i < 5; i++) {
        printf(" slum name=%s , Leader: name=%s, age=%d ,education=%f\n",
               mumbai[i].slumName, mumbai[i].leader.name, mumbai[i].leader.age, mumbai[i].leader.education);

        for (j = 0; j < MAX_MEMBERS; j++) {
            printf(" Member %d: name=%s, age=%d ,education=%f\n", j + 1,
                   mumbai[i].members[j].name, mumbai[i].members[j].age, mumbai[i].members[j].education);
        }

        printf("\n");
    }
}

void heapify_education(struct commette arr[], int n, int i) {
    int smallest = i;
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    if (leftChild < n && arr[leftChild].education < arr[smallest].education)
        smallest = leftChild;

    if (rightChild < n && arr[rightChild].education < arr[smallest].education)
        smallest = rightChild;

    if (smallest != i) {
        struct commette temp = arr[i];
        arr[i] = arr[smallest];
        arr[smallest] = temp;
        heapify_education(arr, n, smallest);
    }
}

void heapSort_education(struct commette arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_education(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        struct commette temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify_education(arr, i, 0);
    }
}

void select_commette_leader(struct slum *s) {
    s->leader = s->members[0];
}

//*********************************************merge sort*************************\\

struct SubArea {
    char name[50];
    float pop_density;
    float healthRisks;
    float existingFacilities;
    float priority;
};


struct SlumArea {
    char name[50];
    int numSubAreas;
    struct SubArea *subAreas;
    float priority;
};



void merge(struct SlumArea a[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    struct SlumArea L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].priority >= R[j].priority) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(struct SlumArea a[], int l, int r) {
    if (l < r) {

        int m = l + (r - l) / 2;

        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);


        merge(a, l, m, r);
    }
}


float calPriorityScore(struct SlumArea slum) {
    float totalScore = 0;

    for (int i = 0; i < slum.numSubAreas; i++) {
        totalScore += slum.subAreas[i].priority;
    }

    return totalScore;
}

struct SlumArea read_information(FILE *fp) {
    struct SlumArea slum;
    fscanf(fp, "%s %d", slum.name, &slum.numSubAreas);
    slum.subAreas = (struct SubArea *)malloc(slum.numSubAreas * sizeof(struct SubArea));

    for (int i = 0; i < slum.numSubAreas; i++) {
        fscanf(fp, "%s %f %f %f", slum.subAreas[i].name, &slum.subAreas[i].pop_density,
               &slum.subAreas[i].healthRisks, &slum.subAreas[i].existingFacilities);

        slum.subAreas[i].priority = slum.subAreas[i].pop_density * 0.4 +
                                          slum.subAreas[i].healthRisks * 0.3 +
                                          slum.subAreas[i].existingFacilities * 0.3;
    }

    slum.priority = calPriorityScore(slum);

    return slum;
}
//************************************************* Hash table**********************************\\

   struct Slum_Area {
    char name[50];
    float population;
    float hygieneLevel;
    int numToilets;
    struct Slum_Area* next;
};

struct HashTable {
    struct Slum_Area* table[HASH_SIZE];
};

float calculatePriority(struct Slum_Area slum) {
    return slum.population * slum.hygieneLevel / (slum.numToilets + 1);
}

void displaySlumInfo(struct Slum_Area* slum) {
    printf("Slum %s:\n", slum->name);
    printf("  Population Density: %.2f\n", slum->population);
    printf("  Hygiene Level: %.2f\n", slum->hygieneLevel);
    printf("  Number of Toilets: %d\n", slum->numToilets);
    printf("---------\n");
}

struct Slum_Area* readSlumData(const char* fileName, struct HashTable* hashTable) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", fileName);
        return NULL;
    }

    struct Slum_Area* head = NULL;
    struct Slum_Area* current = NULL;

    while (1) {
        struct Slum_Area* newSlum = (struct Slum_Area*)malloc(sizeof(struct Slum_Area));

        if (fscanf(file, "%s %f %f %d", newSlum->name, &newSlum->population,
                   &newSlum->hygieneLevel, &newSlum->numToilets) != 4) {
            free(newSlum);
            break;
        }

        newSlum->next = NULL;


        int hashValue = hashFunction(newSlum->name);
        newSlum->next = hashTable->table[hashValue];
        hashTable->table[hashValue] = newSlum;

        if (head == NULL) {
            head = newSlum;
            current = newSlum;
        } else {
            current->next = newSlum;
            current = newSlum;
        }
    }

    fclose(file);
    return head;
}

struct SlumArea* findSlum(struct HashTable* hashTable, const char* name) {
    int hashValue = hashFunction(name);
    struct Slum_Area* slum = hashTable->table[hashValue];

    while (slum != NULL) {
        if (strcmp(slum->name, name) == 0) {
            return slum;
        }
        slum = slum->next;
    }

    return NULL;
}

void improveHygieneAndToilets(struct SlumArea* slums, struct HashTable* hashTable) {
    struct Slum_Area* current = slums;

    while (current != NULL) {

        if (current->hygieneLevel < TARGET_HYGIENE) {

            int toiletsToAdd = (current->hygieneLevel < TARGET_HYGIENE - 1.0) ? 2 : 1;


            current->numToilets += toiletsToAdd;
            current->hygieneLevel = calculatePriority(*current);

            printf("Improved hygiene level for %s to %.2f and added %d toilets.\n-->>Total toilets now: %d.\n",
                   current->name,
                   current->hygieneLevel,
                   toiletsToAdd,
                   current->numToilets);
        }

        current = current->next;
    }
}

void displayAllSlums(struct SlumArea* slums) {
    struct Slum_Area* current = slums;
    while (current != NULL) {
        displaySlumInfo(current);
        current = current->next;
    }
}

void freeSlumList(struct SlumArea* slums) {
    struct Slum_Area* current = slums;
    while (current != NULL) {
        struct Slum_Area* temp = current;
        current = current->next;
        free(temp);
    }
}

void freeHashTable(struct HashTable* hashTable) {
    for (int i = 0; i < HASH_SIZE; i++) {
        struct Slum_Area* current = hashTable->table[i];
        while (current != NULL) {
            struct Slum_Area* temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int hashFunction(const char* str) {
    int hash = 0;
    while (*str != '\0') {
        hash += *str;
        str++;
    }
    return hash % HASH_SIZE;
}
//************************************************Dijekstras algorithm and bst**************************\\

 typedef struct {
    int id;
    char name[50];
    int cost;
} Node_;

// Structure to represent an edge in the network
typedef struct {
    int src;
    int dest;
    int length;
} Edge;

// Structure for a node in the Binary Search Tree (BST)
typedef struct bstNode {
    Node_  house;
    struct bstNode* left;
    struct bstNode* right;
} BSTNode;

// Function to create a new BST node
BSTNode* createBSTNode(Node_  house) {
    BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
    newNode->house = house;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a house into the BST
BSTNode* insertBST(BSTNode* root, Node_ house) {
    if (root == NULL) {
        return createBSTNode(house);
    }

    if (house.id < root->house.id) {
        root->left = insertBST(root->left, house);
    } else if (house.id > root->house.id) {
        root->right = insertBST(root->right, house);
    }

    return root;
}

// Function to display the BST in-order
void displayBST(BSTNode* root) {
    if (root != NULL) {
        displayBST(root->left);
        printf("House ID: %d, Name: %s, Cost: Rs %d\n", root->house.id, root->house.name, root->house.cost);
        displayBST(root->right);
    }
}

// Function to find the minimum distance vertex
int minDistance(int dist[], int visited[], int numNodes) {
    int min = INF, minIndex;

    for (int v = 0; v < numNodes; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

// Function to calculate the minimum wire length and total cost
void findMinWireLength(int graph[MAX_NODES][MAX_NODES], int numNodes, Node_  houses[], int powerStation) {
    int dist[MAX_NODES];
    int visited[MAX_NODES];

    // Initialize distances and visited array
    for (int i = 0; i < numNodes; i++) {
        dist[i] = INF;
        visited[i] = 0;
    }

    // Distance from power station to itself is 0
    dist[powerStation] = 0;

    for (int count = 0; count < numNodes - 1; count++) {
        int u = minDistance(dist, visited, numNodes);
        visited[u] = 1;

        for (int v = 0; v < numNodes; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // Find the minimum wire length
    int minWireLength = dist[1]; // Assuming the first house is the reference
    for (int i = 2; i < numNodes; i++) {
        if (dist[i] < minWireLength) {
            minWireLength = dist[i];
        }
    }

    // Calculate total cost based on the minimum wire length
    int totalCost = 0;
    for (int i = 2; i < numNodes; i++) {
        if (dist[i] != INF) {
            int length = dist[i];
            int houseId = houses[i].id;
            int cost = (length - minWireLength) * 30; // Assuming 1 meter costs 30 Rs
            houses[i].cost = cost;
            printf("Minimum wire length to house %d (%s): %d meters, Cost: Rs %d\n", houseId-1, houses[i].name, length, cost);
            totalCost += cost;
        }
    }

    printf("Total cost: Rs %d\n", totalCost);
}
//************************************************************Bubble sort******************************************\\

typedef struct {
    char area[50];
    int crimeCount;
    char crimeType[50];
    char policeStation[50];
    char securityStatus[50];
} CrimeData;

// Function to compare crime data for bubble sort based on crime counts
int compareCrimeData(const void *a, const void *b) {
    return ((CrimeData *)b)->crimeCount - ((CrimeData *)a)->crimeCount;
}

// Function to perform Bubble Sort on crime data based on crime counts
void bubbleSort(CrimeData *crimeData, int dataSize) {
    for (int i = 0; i < dataSize - 1; i++) {
        for (int j = 0; j < dataSize - i - 1; j++) {
            if (compareCrimeData(&crimeData[j], &crimeData[j + 1]) > 0) {
                // Swap crimeData[j] and crimeData[j + 1]
                CrimeData temp = crimeData[j];
                crimeData[j] = crimeData[j + 1];
                crimeData[j + 1] = temp;
            }
        }
    }
}

// Function to read crime data from file
int readCrimeDataFromFile(const char *fp, CrimeData **crimeData, int *dataSize) {
     fp = fopen(fp, "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file: %s\n", fp);
        return 0; // Return 0 to indicate failure
    }

    // Count the number of lines in the file to determine the size
    int count = 0;
    char line[200]; // Assuming a maximum line size of 200 characters
    while (fgets(line, sizeof(line), fp) != NULL) {
        count++;
    }

    // Allocate memory for crimeData array
    *crimeData = (CrimeData *)malloc(count * sizeof(CrimeData));
    if (*crimeData == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        fclose(fp);
        return 0; // Return 0 to indicate failure
    }

    // Reset file pointer to the beginning
    fseek(fp, 0, SEEK_SET);

    // Read data from file into the crimeData array
    for (int i = 0; i < count; i++) {
        if (fscanf(fp, "%s %d %s %s %s", (*crimeData)[i].area, &(*crimeData)[i].crimeCount,
                   (*crimeData)[i].crimeType, (*crimeData)[i].policeStation, (*crimeData)[i].securityStatus) != 5) {
            fprintf(stderr, "Error reading data from file\n");
            fclose(fp);
            free(*crimeData);
            return 0; // Return 0 to indicate failure
        }
    }

    // Set the dataSize
    *dataSize = count;

    // Close the file
    fclose(fp);

    return 1; // Return 1 to indicate success
}

// ********************************************************* MENU ***************************************************8
// Function: menu
// Description: Displays a menu for the user with various options
// Input parameters: None
// Return Type: void
void menu()
{
    printf("\n");
    for(int i=0; i<50; i++)
    {
        printf("*");
        if(i == 25)
        {
            printf(" MENU ");
        }
    }

    printf("\nEnter\n");
    printf("1 to see the thift's\n");
    printf("2 to see the minumal spanning tree\n");
    printf("3 to get the shortest path\n");
    printf("4 to see information of nodes used in dikjtras throw dfs\n");
    printf("5 to view houses in slum\n");
    printf("6 For knowing panchayat members of slums\n");
    printf("7 Identifying and Prioritizing High-Need Slum Areas for Hospital Services\n");
    printf("8 Hygiene improvement and toilet management\n");
    printf("9 optimizing electric network : with cost effective\n");
    printf("10 Displaying the high criminal areas with details and their security status\n");
    printf("11-To display programs present in slum\n");
    printf("12. To check the presence of particular service in slum\n");
    printf("13.street light information\n");
    printf("14.minimum distance travelled by ambulance\n");
    printf("15.Most occurred Disease in a slum\n");
    printf("16.education information of a slum\n");
    printf("Enter any other number to exit\n");
    return;
}

//----------------------------------------bhagya-------------------------------------------------
struct Resident {
    char name[50];
    int age;
};

// Define a structure for a program
struct Program {
    char name[50];
    char description[100];
};

// Define a structure for a node in the queue
struct QueueNode {
    struct Resident resident;
    struct QueueNode* next;
};

// Define a structure for the queue
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
};
//------------------------
struct StreetLight {
    char name[50];
    int brightness;
    struct StreetLight *left, *right;
};

// Structure to represent a slum with a BST of street lights
struct Mslum {
    char name[50];
    struct StreetLight *root;
};
//-------------------------
struct Aslum
{
    char name[10];
    int id;
};
//---------------------
struct DiseaseData {
    char diseaseName[100];
    int diseaseCounts;  // Count of each disease
};

struct Dslum {
    char name[50];
    int population;
    struct DiseaseData d1;
    struct DiseaseData d2;
    struct DiseaseData d3;
};
//-----------------------
struct teacher {
    int noT;
    char avgDeg[10];
};

struct info {
    struct teacher t;
    int noS;
};

struct ESubArea {
    char name[50];
    int no_school;
    float avg;
    struct info p;
    float hygeine;
    float edurate;
};

struct ESlumArea {
    char name[50];
    int numSubAreas;
    struct ESubArea *ESubAreas;
    float tot;
};
struct ESlumArea read_info(FILE *fp);
void edu(struct ESlumArea *slumAreas, int num_slums);
//-----------------------------
struct job {
    char qualification[30];  // Increased size for safety
    char company[30];        // Increased size for consistency
    char post[30];
};
//------------------------------------------------------------programs-----------------------------------------------------------------
// Function to initialize an empty queue
void initializeQueue(struct Queue* queue) {
    queue->front = queue->rear = NULL;
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue a resident into the queue
void enqueue(struct Queue* queue, struct Resident resident) {
    // Create a new node
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->resident = resident;
    newNode->next = NULL;

    // If the queue is empty, set both front and rear to the new node
    if (isQueueEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        // Otherwise, add the new node to the rear of the queue
        queue->rear->next = newNode;
        queue->rear = newNode;
    }

    printf("%s has joined the program!\n", resident.name);
}

// Function to dequeue a resident from the queue
struct Resident dequeue(struct Queue* queue) {
    // Check if the queue is empty
    if (isQueueEmpty(queue)) {
        struct Resident emptyResident = {"", 0};
        return emptyResident;
    }

    // Remove the front node from the queue
    struct QueueNode* temp = queue->front;
    struct Resident dequeuedResident = temp->resident;

    queue->front = temp->next;
    free(temp);

    // If the queue becomes empty after dequeue, update the rear
    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    return dequeuedResident;
}

// Function to display the programs in the community center
void displayPrograms(struct Program programs[], int numPrograms) {
    printf("Programs Available:\n");
    for (int i = 0; i < numPrograms; i++) {
        printf("%d. %s - %s\n", i + 1, programs[i].name, programs[i].description);
    }
}
//---------------------------------------------------------service check--------------------------------------------------------------------
// Rabin-Karp algorithm for string matching
void searchResource(char pattern[], char dataset[]) {
    int patternLength = strlen(pattern);
    int datasetLength = strlen(dataset);
    int patternHash = 0;
    int datasetHash = 0;
    int h = 1;

    // Calculate the hash value for the pattern and the initial window in the dataset
    for (int i = 0; i < patternLength - 1; i++)
        h = (h * 256) % PRIME;

    for (int i = 0; i < patternLength; i++) {
        patternHash = (256 * patternHash + pattern[i]) % PRIME;
        datasetHash = (256 * datasetHash + dataset[i]) % PRIME;
    }

    // Search for the pattern in the dataset
    for (int i = 0; i <= datasetLength - patternLength; i++) {
        // Check if the hash values match
        if (patternHash == datasetHash) {
            // Check character by character to avoid hash collisions
            int j;
            for (j = 0; j < patternLength; j++) {
                if (dataset[i + j] != pattern[j])
                    break;
            }

            // If the pattern is found
            if (j == patternLength) {
                printf("Pattern found at position %d\n", i);
                // You can perform resource management actions or gather insights here
            }
        }

        // Calculate the hash value for the next window
        if (i < datasetLength - patternLength) {
            datasetHash = (256 * (datasetHash - dataset[i] * h) + dataset[i + patternLength]) % PRIME;
            if (datasetHash < 0)
                datasetHash += PRIME;
        }
    }
}
//---------------------------------------------------------street light-------------------------------------------------------------------
// Function to create a new street light node
struct StreetLight *createStreetLight(const char *name, int brightness) {
    struct StreetLight *light = (struct StreetLight *)malloc(sizeof(struct StreetLight));
    strcpy(light->name, name);
    light->brightness = brightness;
    light->left = light->right = NULL;
    return light;
}

// Function to insert a street light into the BST
struct StreetLight *insertStreetLight(struct StreetLight *root, struct StreetLight *light) {
    if (root == NULL) {
        return light;
    }

    if (light->brightness < root->brightness) {
        root->left = insertStreetLight(root->left, light);
    } else {
        root->right = insertStreetLight(root->right, light);
    }

    return root;
}

// Function to find the street light with the lowest brightness in the BST
struct StreetLight *findMinBrightness(struct StreetLight *root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to print the street light with the lowest brightness in the slum
void printMinBrightness(struct Mslum *slum) {
    if (slum->root == NULL) {
        printf("Slum: %s, No street lights available\n", slum->name);
    } else {
        struct StreetLight *minLight = findMinBrightness(slum->root);
        printf("Slum: %s, Lowest Brightness Street Light: %s (%d)\n", slum->name, minLight->name, minLight->brightness);
    }
}
//----------------------------------------------------------ambulance--------------------------------------------------------------------
void Dijkstras(int matrix[10][10], int src, int v, int distance[10], int path[10], int visited[10])
{
    visited[src] = 1;
    int u;
    int min = 9999;
    for (int count = 0; count < v - 1; count++)
    {
        for (int i = 0; i < v; i++)
        {
            if (visited[i] == 0 && distance[i] < min)
            {
                u = i;
                min = distance[i];
            }
        }
        visited[u] = 1;
        for (int i = 0; i < v; i++)
        {
            if (visited[i] == 0 && distance[i] > distance[u] + matrix[u][i])
            {
                path[i] = u;
                distance[i] = distance[u] + matrix[u][i];
            }
        }
    }
}
//-----------------------------------------------------------------Disease--------------------------------------------------------------
void identifyMostOccurringDisease(struct Dslum *slumss, int numSlums) {
    for (int i = 0; i < numSlums; i++) {
        int maxCount = 0;
        char mostOccurredDisease[100];

        if (slumss[i].d1.diseaseCounts > maxCount) {
            maxCount = slumss[i].d1.diseaseCounts;
            strcpy(mostOccurredDisease, slumss[i].d1.diseaseName);
        }

        if (slumss[i].d2.diseaseCounts > maxCount) {
            maxCount = slumss[i].d2.diseaseCounts;
            strcpy(mostOccurredDisease, slumss[i].d2.diseaseName);
        }

        if (slumss[i].d3.diseaseCounts > maxCount) {
            maxCount = slumss[i].d3.diseaseCounts;
            strcpy(mostOccurredDisease, slumss[i].d3.diseaseName);
        }

        printf("Slum %s:\n", slumss[i].name);
        printf("Most frequently occurred disease: %s (%d cases)\n", mostOccurredDisease, maxCount);
        if(strcmp (mostOccurredDisease,"typhoid")==0 || (strcmp(mostOccurredDisease,"dengue")==0)||(strcmp(mostOccurredDisease,"malaria")==0))
            printf("sol:vaccination\n");
        else if(strcmp(mostOccurredDisease,"Diabetes")==0)
            printf("sol:Lifestyle Management: A healthy diet, regular exercise, and adequate sleep are key to managing diabetes\n");
        else if (strcmp(mostOccurredDisease,"Malnutrition")==0)
            printf("sol:Dietary Changes: Ensure adequate intake of essential nutrients like proteins, carbohydrates, fats, vitamins, and minerals\n");
        else if(strcmp(mostOccurredDisease,"viral-fever")==0)
            printf("sol:Rest and Recuperation\n");
    }

}
//-----------------------------------------------------------education-------------------------------------------------------------------
struct ESlumArea read_info(FILE *fp) {
    struct ESlumArea slum;
    slum.tot=0;
    fscanf(fp, "%s %d", slum.name, &slum.numSubAreas);
    slum.ESubAreas = (struct ESubArea *)malloc(slum.numSubAreas * sizeof(struct ESubArea));

    for (int i = 0; i < slum.numSubAreas; i++) {
        fscanf(fp, "%s %d %f %d %s %d", slum.ESubAreas[i].name, &slum.ESubAreas[i].no_school,
               &slum.ESubAreas[i].avg, &slum.ESubAreas[i].p.t.noT, slum.ESubAreas[i].p.t.avgDeg, &slum.ESubAreas[i].p.noS);

        slum.ESubAreas[i].edurate = slum.ESubAreas[i].no_school + slum.ESubAreas[i].avg;

    }
    for (int i = 0; i < slum.numSubAreas; i++)
    {
        slum.tot=slum.ESubAreas[i].edurate+slum.tot;
    }

    return slum;
}

void edu(struct ESlumArea *slumAreas,int num_slums) {
    int i, j;
    struct ESlumArea temp;

    for (i = 0; i < num_slums - 1; i++) {
        for (j = i+1; j < num_slums - 1; j++) {
            if (slumAreas[i].tot < slumAreas[j].tot) {
                temp = slumAreas[i];
                slumAreas[i] = slumAreas[j];
                slumAreas[j] = temp;
            }
        }
    }

    printf("Highest education is in slum: %s\n", slumAreas[0].name);
    printf("Lowest education is in slum: %s\n", slumAreas[num_slums - 1].name);

}

int main()
{
    FILE * fp;
    Theft p;
    struct House* root = NULL;
    struct HashTable hashTable;
      // Initialize the queue
    struct Queue residentQueue;
    initializeQueue(&residentQueue);
    int ch;
    // Define programs available in the community center
    struct Program programs[] = {
        {"Educational Classes", "Learn new skills and subjects."},
        {"Health and Fitness", "Join fitness classes and health workshops."},
        {"Community Events", "Participate in various community-building activities."},
    };

    int numPrograms = sizeof(programs) / sizeof(programs[0]);
    // Residents joining the programs
    struct Resident resident1 = {"John", 25};
    struct Resident resident2 = {"Maria", 30};
    struct Resident resident3 = {"safia", 21};
    // Residents leaving the programs
    struct Resident dequeuedResident = dequeue(&residentQueue);
    //------------------------------------------------------
     // Example dataset
    char dataset[] = "Innovation in slum area involves managing resources like water, sanitation, and education.";

    // Example resource pattern
    char resourcePattern[] = "water";
    //-------------------------------------------------------------
        struct Mslum slums[5];

    // Initialize slums
    for (int i = 0; i < 5; i++) {
        sprintf(slums[i].name, "Slum-%d", i + 1);
        slums[i].root = NULL;
    }

    // Insert street lights into BST for each slum
    slums[0].root = insertStreetLight(slums[0].root, createStreetLight("StreetLight-1", 200));
    slums[0].root = insertStreetLight(slums[0].root, createStreetLight("StreetLight-2", 150));
    slums[1].root = insertStreetLight(slums[1].root, createStreetLight("StreetLight-3", 180));
    slums[1].root = insertStreetLight(slums[1].root, createStreetLight("StreetLight-4", 120));
    slums[2].root = insertStreetLight(slums[2].root, createStreetLight("StreetLight-5", 250));
    slums[2].root = insertStreetLight(slums[2].root, createStreetLight("StreetLight-6", 100));
    slums[3].root = insertStreetLight(slums[3].root, createStreetLight("StreetLight-7", 130));
    slums[3].root = insertStreetLight(slums[3].root, createStreetLight("StreetLight-8", 160));
    slums[4].root = insertStreetLight(slums[4].root, createStreetLight("StreetLight-9", 140));
    slums[4].root = insertStreetLight(slums[4].root, createStreetLight("StreetLight-10", 110));
    //--------------------------------------------
    struct Aslum s[] = {{"a", 0}, {"b", 1}, {"c", 2}, {"d", 3}, {"e", 4},{"f",5}};
    int dist[10];
    int paths[10], Visited[10];
    int mat[6][6] = {{0,3,9999,7,9999},{3,0,4,2,9999},{7,4,0,8,6},{9999,4,0,8,6},{7,2,8,0,4},{9999,9999,4,4,0}};
    struct Aslum sou;
     int v=5;
     //-------------------------------------------
      struct Dslum slumss[] = {
        {"a", 20000, {"dengue", 10}, {"malaria", 13}, {"typhoid", 23}},
        {"b", 10000, {"viral-fever", 20}, {"Diarrhea", 32}, {"Diabetes", 50}},
        {"c", 15000, {"Malaria", 9}, {"diarrhea", 15}, {"viral-fever", 19}},
        {"d", 19000, {"Tuberculosis", 7}, {"Malnutrition", 48}, {"typhoid", 17}},
        {"e", 16520, {"Typhoid", 14}, {"viral-fever", 13}, {"dengue", 18}},
    };
      int numSlums = 5;
    //-----------------------------------------------
    FILE *fP = fopen("education.txt", "r");

    while(1)
    {
        // function to display the menu
        menu();
        int ch;
        scanf("%d",&ch);

        switch(ch)
        {
        case 1:

            for (int i = 0; i < 5; i++)
            {
                p = (Theft)malloc(sizeof(struct theft));

                p->slumNumber = (i+1);
                printf("Enter the number of thefts in slum %d: ", i+1);
                scanf("%d", &(p->thefts));

                printf("Enter the date of the theft (format: DD/MM/YYYY): ");
                scanf("%s", p->date);

                printf("Enter the time of the theft (format: HH:MM AM/PM): ");
                scanf("%s", p->time);



                node[i] = p;
            }
            quick_sort(node, 0, 4);
            printf("\nSorted theft records based on the number of thefts:\n");
            for (int i = 0; i < 5; i++)
            {
                printf("Slum %d - Number of thefts: %d\n", node[i]->slumNumber, node[i]->thefts);
            }
            for (int i = 0; i < 5; i++)
            {
                free(node[i]);
            }
            break;
        case 2 :
            data = (Node*)malloc(100 * sizeof(Node));
            edges = (NODE*)malloc(300 *sizeof(NODE));

            // inserting data;
            fillKruskalsFile(fp);

            //reading data from kruskals file
            readKruskals(fp, data);
            printf("HI");

            printf("The relation between the nodes and the names in city are \n");
            displayData(100, data);

            // funtion to fill snanning txt
            fillSpanningFile(fp);

            // Reading input from file spanning.txt
            fp = fopen("spanning.txt", "r");

            int i =0;
            while(!feof(fp))
            {
                fscanf(fp, "%d %d %d",&edges[i].u, &edges[i].v, &edges[i].w);
                i++;
            }


            // closing the file
            fclose(fp);

            // sorting on basis of weight
            quickSort(edges, 0, 100);

            int arr[100];
            for(int i=0; i<100; i++)
            {
                arr[i] = i;
            }

            // calling kruskal function
            printf("The edges are\n");
            int ans = kruskals(edges, 100, arr);
            printf("\nThe total weight is %d",ans);

            free(data);
            free(edges);

            break;

        case 3:
            printf("Enter the number of vertices\n");
            scanf("%d", &v);

            // allocating memory for nodeNames structure in the form of array
            nodesNames* area = (nodesNames*) malloc (v * sizeof(nodesNames));

            // nodesNames area[50];
            int cost[MAX_VERTICES][MAX_VERTICES];
            assignCostMatrixValue(cost);
            generateRandomEdges(cost);

            // reading the weights of graph from file
            //readGraphFromFile(cost);
            writeGraphToFile(cost);
            printf("HI!!!\n");
            // loading the names of places on file with respective nodes
            int n = loadThenodeNames(area, fp);
            printf("Reading from file completed\n");

            char source[50];
            printf("Enter the source among these\n");
            printAreaNames(n,area);
            printf("Enter the source\n");
            scanf("%s", &source);
            int src = findSource(source, area, v);
            printf("finding the source completed\n");

            if(src == -1)
            {
                printf("Print valid source\n");
                return -1;
            }

            for (int i = 0; i < v; i++)
            {
                distance[i] = cost[src][i];
            }
            for (int i = 0; i < v; i++)
            {
                path[i] = src;
            }

            dijkstras(cost, v, src);
            print(v, area);
            break;

        case 4:

            // Input the number of vertices
            printf("Enter the number of vertices: ");
            scanf("%d", &n);

            // Input the adjacency matrix from a fill
            fillValue(fp, graph);

            // allocating memmory for nodes
            DFS_Names * Names = (DFS_Names*) malloc (MAX *sizeof(DFS_Names));
            fillNames(fp, Names);


            // Input the starting vertex for DFS
            printf("Enter the starting vertex for DFS: ");
            scanf("%d", &start);

            // Perform DFS and display the result
            dfs(graph, n, start, Names);
            break;

        case 5:
            // Inserting houses into the BST from a file
            fp = fopen("houses.txt", "r");

            if(fp == NULL)
            {
                printf("House not found\n");
                break;
            }
            int slumNo;
            int houseNo;
            int numOfMembers;
            char houseName[50];

            while (fscanf(fp, "%d %d %d %s", &slumNo, &houseNo, &numOfMembers, houseName) == 4)
            {
                root = insert(root, slumNo, houseNo, numOfMembers, houseName);
            }

            // while(!feof(fp))
            // {
            //     printf("hi");

            //     fscanf(fp, "%d %d %d %s\n", &slumNo, &houseNo, &numOfMembers, houseName);
            //     root = insert(root, slumNo, houseNo, numOfMembers, houseName);
            // }
            fclose(fp);

            // displaying all the houses
            printf("The total number of houses in slum are\n");
            displayHouses(root);

            // Displaying houses in Slum No 5
            printf("Houses in Slum No 5:\n");
            displayHousesInSlum(root, 5);

            // Deleting a house with house number 42 from the BST
            int houseNumberToDelete;

            printf("Enter the house which is to be deleted\n");
            scanf("%d",&houseNumberToDelete);

            printf("\nDeleting House No %d from the BST.\n", houseNumberToDelete);
            root = deleteNode(root, houseNumberToDelete);

            // displaying all the houses
            printf("The total number of houses in slum are\n");
            displayHouses(root);

            // Displaying the updated BST
            printf("\nUpdated BST:\n");
            displayHousesInSlum(root, 5);

            // Freeing the memory
            freeBST(root);
            root = NULL;
            break;
        case 6:
            fp = fopen("slum_info_data.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    for (int i = 0; i < 5; i++) {
        fscanf(fp, "%s", mumbai[i].slumName);

        for (int j = 0; j < MAX_MEMBERS; j++) {
            fscanf(fp, "%s %f %d", mumbai[i].members[j].name, &mumbai[i].members[j].education, &mumbai[i].members[j].age);
        }

        heapSort_education(mumbai[i].members, MAX_MEMBERS);
        select_commette_leader(&mumbai[i]);
    }
    displayCommetteLeader();

    fclose(fp);
    break;

        case 7:
            fp = fopen("hospital_data.txt", "r");
    if (fp == NULL) {

        printf("Error opening file");
        return 1;
    }
    int num_slums;
     struct SlumArea *slumAreas = (struct SlumArea *)malloc(num_slums * sizeof(struct SlumArea));

    fscanf(fp, "%d", &num_slums);


    for (int i = 0; i < num_slums; i++) {
        slumAreas[i] = read_information(fp);
    }

    fclose(fp);

    mergeSort(slumAreas, 0, num_slums - 1);

printf("\nSorted Slum Areas in Ascending Order of Priority Score:\n");
for (int i = 0; i < num_slums; i++) {
    printf("\nSlum Area: %s - Priority Score: %f\n", slumAreas[i].name, slumAreas[i].priority);
    printf("Sub-Areas:\n");
    for (int j = 0; j < slumAreas[i].numSubAreas; j++) {
        printf("%s - Population Density: %f\n Health Risks: %f\n Existing Facilities: %f\n Priority Score: %f\n",
               slumAreas[i].subAreas[j].name,
               slumAreas[i].subAreas[j].pop_density,
               slumAreas[i].subAreas[j].healthRisks,
               slumAreas[i].subAreas[j].existingFacilities,
               slumAreas[i].subAreas[j].priority);
               printf("---------------\n");
    }
    printf("-----*-----*-----*----\n");
}


    for (int i = 0; i < num_slums; i++) {
        free(slumAreas[i].subAreas);
    }
    free(slumAreas);
    break;
        case 8:

    memset(&hashTable, 0, sizeof(struct HashTable));

    struct Slum_Area* slums = readSlumData("hygiene_slum.txt", &hashTable);
    if (slums == NULL) {
        printf("Exiting program due to file read error.\n");
        return 1;
    }

    displayAllSlums(slums);

    improveHygieneAndToilets(slums, &hashTable);

    displayAllSlums(slums);
    printf("---***---");

    freeHashTable(&hashTable);
    freeSlumList(slums);
    break;


         case 9:
            // Read graph and house information from a file
    fp = fopen("electricity_data.txt", "r");
    if (fp == NULL) {
        perror("Error opening the file");
        return 1;
    }

    int numNodes;
    fscanf(fp, "%d", &numNodes);

    int graph[MAX_NODES][MAX_NODES];

    for (int i = 0; i < numNodes; i++) {
        for (int j = 0; j < numNodes; j++) {
            fscanf(fp, "%d", &graph[i][j]);
        }
    }

    Node_  houses[MAX_NODES];

    for (int i = 1; i < numNodes; i++) {
        fscanf(fp, "%d %s", &houses[i].id, houses[i].name);
    }

    int powerStation = 0;

    fclose(fp);

    findMinWireLength(graph, numNodes, houses, powerStation);
      break;


        case 10:
        fp= "crime_data.txt"; // Replace with your file name
    CrimeData *crimeData;
    int dataSize;

    // Read crime data from file
    if (readCrimeDataFromFile(fp, &crimeData, &dataSize)) {
        // Perform Bubble Sort on crime data based on crime counts
        bubbleSort(crimeData, dataSize);

        // Display crime data for areas with higher crime counts, including police station and security status
        printf("%-20s %-15s %-15s %-20s %-20s\n", "Area", "Crime Count", "Crime Type", "Police Station", "Security Status");
        printf("------------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < dataSize; i++) {
            if (crimeData[i].crimeCount > 50) { // Adjust threshold as needed
                printf("%-20s %-15d %-15s %-20s %-20s\n", crimeData[i].area, crimeData[i].crimeCount,
                       crimeData[i].crimeType, crimeData[i].policeStation, crimeData[i].securityStatus);
            }
        }

        free(crimeData);
    }
     break;
      case 11:   enqueue(&residentQueue, resident1);
                    enqueue(&residentQueue, resident2);
                    enqueue(&residentQueue, resident3);
                displayPrograms(programs, numPrograms);
                if (dequeuedResident.age != 0) {
                                                                                            // Display information about the resident leaving
                     printf("%s has left the program.\n", dequeuedResident.name);
                } else {
                    printf("The queue is empty.\n");
                }
                break;
       case 12: searchResource(resourcePattern, dataset);
                break;
       case 13:for (int i = 0; i < 5; i++) {
                  printMinBrightness(&slums[i]);
                     }
                     break;
        case 14:   sou.id=0;
                   for (int i = 0; i < v; i++)
                    {
                        dist[i] = mat[sou.id][i];
                    }
                    for (int i = 0; i < v; i++)
                    {
                        paths[i] = sou.id;
                        Visited[i] = 0;
                    }
                    Dijkstras(mat, sou.id, v, dist, paths, Visited);

                    printf("Shortest paths from source slum %c:\n", 'A' + sou.id);
                    for (int i = 0; i < v; i++)
                    {
                        printf("To slum %c: Distance = %d, Path: ", 'A' + i, dist[i]);

                        int temp = i;
                        while (temp != sou.id)
                        {
                            printf("%c <- ", 'A' + temp);
                            temp = paths[temp];
                        }
                        printf("%c\n", 'A' + sou.id);
                    }
                    break;
        case 15: identifyMostOccurringDisease(slumss, numSlums);
                break;
        case 16:
                if (fP == NULL) {
                    printf("Error opening file");
                    return 1;
                }


                fscanf(fP, "%d", &num_slums);
                struct ESlumArea *slumAreass = (struct ESlumArea *)malloc(num_slums * sizeof(struct ESlumArea));

                for (int i = 0; i < num_slums; i++) {
                    slumAreass[i] = read_info(fP);
                }

                fclose(fP);
                edu(slumAreass, num_slums);

                // Free allocated memory
                free(slumAreass);
                break;

        default :
            printf("Leaving the progmam\n");
            printf("Thank-you\n");
            printf(":D\n");
            exit(0);
            break;
        }
    }

    return 0;
}
