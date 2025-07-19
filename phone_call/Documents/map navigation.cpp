/*#include <stdio.h>
 #include <stdlib.h>
 #include <limits.h>
 #include <string.h>
 #define NUM_LOCATIONS 6
 // Enum to represent locations in Jaipur
 enum Location {
 JAIPUR_JUNCTION,
 HAWA_MAHAL,
 CITY_PALACE,
 ALBERT_HALL,
 JANTAR_MANTAR,
 AMER_FORT
 };
 Operation:
 // Structure for an edge in the graph (road connection)
 typedef struct {
 int destination;  // Index of the destination location
 int distance;   // Distance between locations in kilometers
 } Edge;
 // Structure for the map (graph)
 typedef struct {
 int numVertices;    
// Number of locations (vertices) in the graph
 Edge adjacencyList[NUM_LOCATIONS][NUM_LOCATIONS];  // Adjacency list for the graph
 } Map;
 // Helper function to get location name based on index
const char* getLocationName(int index) {
 switch (index) {
 case JAIPUR_JUNCTION: return "Jaipur Junction";
 case HAWA_MAHAL: return "Hawa Mahal";
 case CITY_PALACE: return "City Palace";
 case ALBERT_HALL: return "Albert Hall Museum";
 case JANTAR_MANTAR: return "Jantar Mantar";
 case AMER_FORT: return "Amer Fort";
 default: return "Unknown";
 }
 }
 // Initialize the map with road connections (distances) between locations
 void initializeMap(Map* map) {
 map->numVertices = NUM_LOCATIONS;
 // Initialize all edges with destination -1 (invalid) and distance INT_MAX (infinity)
 for (int i = 0; i < NUM_LOCATIONS; i++) {
 for (int j = 0; j < NUM_LOCATIONS; j++) {
 map->adjacencyList[i][j].destination = -1;
 map->adjacencyList[i][j].distance = INT_MAX;
 }
 }
 // Define road connections (distances) between specific locations
 map->adjacencyList[JAIPUR_JUNCTION][HAWA_MAHAL].destination = HAWA_MAHAL;
 map->adjacencyList[JAIPUR_JUNCTION][HAWA_MAHAL].distance = 3;
 map->adjacencyList[JAIPUR_JUNCTION][CITY_PALACE].destination = CITY_PALACE;
 map->adjacencyList[JAIPUR_JUNCTION][CITY_PALACE].distance = 2;
 map->adjacencyList[HAWA_MAHAL][CITY_PALACE].destination = CITY_PALACE;
  map->adjacencyList[HAWA_MAHAL][CITY_PALACE].distance = 1;
  map->adjacencyList[HAWA_MAHAL][ALBERT_HALL].destination = ALBERT_HALL;
  map->adjacencyList[HAWA_MAHAL][ALBERT_HALL].distance = 2;
  map->adjacencyList[CITY_PALACE][ALBERT_HALL].destination = ALBERT_HALL;
  map->adjacencyList[CITY_PALACE][ALBERT_HALL].distance = 2.5;
  map->adjacencyList[CITY_PALACE][JANTAR_MANTAR].destination = JANTAR_MANTAR;
  map->adjacencyList[CITY_PALACE][JANTAR_MANTAR].distance = 1.5;
  map->adjacencyList[ALBERT_HALL][JANTAR_MANTAR].destination = JANTAR_MANTAR;
  map->adjacencyList[ALBERT_HALL][JANTAR_MANTAR].distance = 1;
  map->adjacencyList[ALBERT_HALL][AMER_FORT].destination = AMER_FORT;
  map->adjacencyList[ALBERT_HALL][AMER_FORT].distance = 10;
  map->adjacencyList[JANTAR_MANTAR][AMER_FORT].destination = AMER_FORT;
  map->adjacencyList[JANTAR_MANTAR][AMER_FORT].distance = 8;
 }
 // Display the map with textual representation of locations and connections
 void displayMap() {
  printf("\n");
  printf("            Amer Fort\n");
  printf("              |\n");
  printf("         8 km    |\n");
  printf("    +-----------------+ \n");
  printf("    |         |\n");
  printf("    |         | 10 km\n");
  printf("    |  Jantar Mantar +-----------+ Albert Hall Museum\n");
  printf("    |         | 1 km    |      |\n");
  printf("    +-----------------+-----------+      |\n");
  printf("              | 2.5 km        |\n");
  printf("              +----------------------+\n");
  printf("              | 1.5 km        |\n");
  printf("         2 km    +----------------------+\n");
  printf("    +-----------------+  |   1 km       |\n");
  printf("    |         |  |           |\n");
  printf("    | Jaipur Junction +--+           |\n");
  printf("    |         |             |\n");
  printf("    +-----------------+             |\n");
  printf("         3 km               |\n");
  printf("     +-----------------+            |\n");
  printf("     |         |            |\n");
  printf("     |         | 2 km          |\n");
  printf("     |  Hawa Mahal   +-----------------------+\n");
  printf("     |         | 2 km\n");
  printf("     +-----------------+\n");
  printf("        City Palace\n");
  printf("\n");
 }
 // Display menu of locations with corresponding indices
 void displayLocationsMenu() {
  printf("Select a location:\n");
  printf("0. Jaipur Junction\n");
  printf("1. Hawa Mahal\n");
  printf("2. City Palace\n");
  printf("3. Albert Hall Museum\n");
  printf("4. Jantar Mantar\n");
  printf("5. Amer Fort\n");
 }
 // Get user's choice of location from the menu
int getLocationChoice() {
 int choice;
 displayLocationsMenu();
 printf("Enter the index of the location: ");
 scanf("%d", &choice);
 return choice;
 }
 // Perform Dijkstra's algorithm to find the shortest path from a source location to all other
 locations
 void dijkstra(Map* map, int source, int destination) {
 int dist[NUM_LOCATIONS];
 int visited[NUM_LOCATIONS] = {0};
 // Initialize distances to all locations as infinity
 for (int i = 0; i < NUM_LOCATIONS; i++) {
 dist[i] = INT_MAX;
 }
 // Distance to source location is 0
 dist[source] = 0;
 // Main loop
 for (int count = 0; count < NUM_LOCATIONS - 1; count++) {
 // Find the location with the minimum distance value
 int minDist = INT_MAX;
 int minLocation = -1;
 for (int v = 0; v < NUM_LOCATIONS; v++) {
 if (!visited[v] && dist[v] < minDist) {
 minDist = dist[v];
 minLocation = v;
      }
    }
 // Mark the selected location as visited
    visited[minLocation] = 1;
 // Update distances of adjacent locations
 for (int i = 0; i < NUM_LOCATIONS; i++) {
 if (!visited[i] && map->adjacencyList[minLocation][i].destination != -1 &&
        dist[minLocation] != INT_MAX &&
        dist[minLocation] + map->adjacencyList[minLocation][i].distance < dist[i]) {
        dist[i] = dist[minLocation] + map->adjacencyList[minLocation][i].distance;
      }
    }
  }
 // Print the shortest distance from the source location to the destination location
  printf("\nShortest distance from %s to %s: %d kilometers\n", getLocationName(source),
 getLocationName(destination), dist[destination]);
 }
 int main() {
 // Create and initialize the map of Jaipur
  Map jaipurMap;
  initializeMap(&jaipurMap);
 // Display the map with textual representation
  displayMap();
 // Get user input for source and destination locations
 int source, destination;
printf("\nSelect the source location:\n");
 source = getLocationChoice();
 printf("\nSelect the destination location:\n");
 destination = getLocationChoice();
 // Perform Dijkstra's algorithm from the specified source location to the destination location
 dijkstra(&jaipurMap, source, destination);
 return 0;
 }
*/
/*#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#define NUM_LOCATIONS 6

// Enum to represent locations in Jaipur
enum Location {
    JAIPUR_JUNCTION,
    HAWA_MAHAL,
    CITY_PALACE,
    ALBERT_HALL,
    JANTAR_MANTAR,
    AMER_FORT
};

// Structure for an edge in the graph (road connection)
typedef struct {
    int destination;  // Index of the destination location
    int distance;     // Distance between locations in kilometers
} Edge;

// Structure for the map (graph)
typedef struct {
    int numVertices;  // Number of locations (vertices) in the graph
    Edge adjacencyList[NUM_LOCATIONS][NUM_LOCATIONS];  // Adjacency list for the graph
} Map;

// Helper function to get location name based on index
const char* getLocationName(int index) {
    switch (index) {
        case JAIPUR_JUNCTION: return "Jaipur Junction";
        case HAWA_MAHAL: return "Hawa Mahal";
        case CITY_PALACE: return "City Palace";
        case ALBERT_HALL: return "Albert Hall Museum";
        case JANTAR_MANTAR: return "Jantar Mantar";
        case AMER_FORT: return "Amer Fort";
        default: return "Unknown";
    }
}

// Initialize the map with road connections (distances) between locations
void initializeMap(Map* map) {
    map->numVertices = NUM_LOCATIONS;
    // Initialize all edges with destination -1 (invalid) and distance INT_MAX (infinity)
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        for (int j = 0; j < NUM_LOCATIONS; j++) {
            map->adjacencyList[i][j].destination = -1;
            map->adjacencyList[i][j].distance = INT_MAX;
        }
    }
    // Define road connections (distances) between specific locations
    // ... (rest of the initialization remains the same)
}

// Function to display the map based on the Map data structure
void displayMap(const Map* map) {
    // This function should be implemented to display the map based on the actual data
    // For now, we'll keep the static display as a placeholder
    // ... (rest of the displayMap function remains the same)
}

// Function to display menu of locations with corresponding indices
void displayLocationsMenu() {
    // ... (rest of the displayLocationsMenu function remains the same)
}

// Function to get user's choice of location from the menu
int getLocationChoice() {
    int choice;
    do {
        displayLocationsMenu();
        printf("Enter the index of the location (0-5): ");
        scanf("%d", &choice);
    } while (choice < 0 || choice >= NUM_LOCATIONS);  // Validate input
    return choice;
}

// Function to perform Dijkstra's algorithm to find the shortest path
void dijkstra(const Map* map, int source, int destination) {
    // ... (rest of the dijkstra function remains the same)
    // Add functionality to print the actual path, not just the distance
}

int main() {
    // ... (rest of the main function remains the same)
    // Add error handling for invalid location choices
    return 0;
}*/

/*#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NUM_LOCATIONS 6

// Enum to represent locations in Jaipur
enum Location {
    JAIPUR_JUNCTION,
    HAWA_MAHAL,
    CITY_PALACE,
    ALBERT_HALL,
    JANTAR_MANTAR,
    AMER_FORT
};

// Structure for an edge in the graph (road connection)
typedef struct {
    int destination;  // Index of the destination location
    int distance;     // Distance between locations in kilometers
} Edge;

// Structure for the map (graph)
typedef struct {
    int numVertices;  // Number of locations (vertices) in the graph
    Edge adjacencyList[NUM_LOCATIONS][NUM_LOCATIONS];  // Adjacency list for the graph
} Map;

// Helper function to get location name based on index
const char* getLocationName(int index) {
    switch (index) {
        case JAIPUR_JUNCTION: return "Jaipur Junction";
        case HAWA_MAHAL: return "Hawa Mahal";
        case CITY_PALACE: return "City Palace";
        case ALBERT_HALL: return "Albert Hall Museum";
        case JANTAR_MANTAR: return "Jantar Mantar";
        case AMER_FORT: return "Amer Fort";
        default: return "Unknown";
    }
}

// Initialize the map with road connections (distances) between locations
void initializeMap(Map* map) {
    // ... (initialization code remains the same)
}

// Function to display the map based on the Map data structure
void displayMap(const Map* map) {
    // ... (displayMap function remains the same)
}

// Function to display menu of locations with corresponding indices
void displayLocationsMenu() {
    // ... (displayLocationsMenu function remains the same)
}

// Function to get user's choice of location from the menu
int getLocationChoice() {
    // ... (getLocationChoice function remains the same)
}

// Function to perform Dijkstra's algorithm to find the shortest path
void dijkstra(const Map* map, int source, int destination) {
    // ... (dijkstra function remains the same)
}

int main() {
    Map jaipurMap;
    initializeMap(&jaipurMap);
    displayMap(&jaipurMap);

    printf("\nSelect the source location:\n");
    int source = getLocationChoice();
    printf("\nSelect the destination location:\n");
    int destination = getLocationChoice();

    dijkstra(&jaipurMap, source, destination);

    return 0;
}
*/


// this is workable // 
/*#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NUM_LOCATIONS 10

typedef struct {
    char name[20];
    int distance[NUM_LOCATIONS];
} Location;

Location locations[NUM_LOCATIONS] = {
    {"Amer Fort", {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}},
    {"City Palace", {10, 0, 15, 25, 35, 45, 55, 65, 75, 85}},
    {"Hawa Mahal", {20, 15, 0, 10, 20, 30, 40, 50, 60, 70}},
    {"Jantar Mantar", {30, 25, 10, 0, 15, 25, 35, 45, 55, 65}},
    {"Nahargarh Fort", {40, 35, 20, 15, 0, 10, 20, 30, 40, 50}},
    {"Albert Hall Museum", {50, 45, 30, 25, 10, 0, 15, 25, 35, 45}},
    {"Birla Mandir", {60, 55, 40, 35, 20, 15, 0, 10, 20, 30}},
    {"Jal Mahal", {70, 65, 50, 45, 30, 25, 10, 0, 15, 25}},
    {"Sisodia Rani Garden", {80, 75, 60, 55, 40, 35, 20, 15, 0, 10}},
    {"Jaipur Zoo", {90, 85, 70, 65, 50, 45, 30, 25, 10, 0}}
};

void printMenu() {
    printf("Jaipur Map Navigation System\n");
    printf("-------------------------------\n");
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        printf("%d. %s\n", i + 1, locations[i].name);
    }
    printf("-------------------------------\n");
    printf("Enter your choice (1-10): ");
}

void navigate(Location* locations, int source, int destination) {
    int distances[NUM_LOCATIONS];
    int visited[NUM_LOCATIONS];
    int previous[NUM_LOCATIONS];

    // Initialize distances and visited arrays
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = -1;
    }

    distances[source] = 0;

    int current = source;
    while (current != -1) {
        visited[current] = 1;

        for (int i = 0; i < NUM_LOCATIONS; i++) {
            if (!visited[i] && locations[current].distance[i] != 0 && distances[current] + locations[current].distance[i] < distances[i]) {
                distances[i] = distances[current] + locations[current].distance[i];
                previous[i] = current;
            }
        }

        int minDistance = INT_MAX;
        current = -1;
        for (int i = 0; i < NUM_LOCATIONS; i++) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                current = i;
            }
        }
    }

    // Print the shortest path
    if (distances[destination] != INT_MAX) {
        printf("Shortest path from %s to %s: ", locations[source].name, locations[destination].name);
        int path[NUM_LOCATIONS];
        int index = 0;
        for (int i = destination; i != -1; i = previous[i]) {
            path[index++] = i;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("%s ", locations[path[i]].name);
        }
        printf("\nDistance: %d km\n", distances[destination]);
    } else {
        printf("No path from %s to %s\n", locations[source].name, locations[destination].name);
    }
}

int main() {
    int source, destination;

    printMenu();
    printf("Enter source location (1-10): ");
    scanf("%d", &source);
    source--; // adjust for 0-based indexing

    printMenu();
    printf("Enter destination location (1-10): ");
    scanf("%d", &destination);
    destination--; // adjust for 0-based indexing

    navigate(locations, source, destination); // <--- Add closing parenthesis here
    return 0; // Add a return statement to indicate successful execution
}*/
/*#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NUM_LOCATIONS 10

typedef struct {
    char name[20];
    int distance[NUM_LOCATIONS];
} Location;

Location locations[NUM_LOCATIONS] = {
    {"Amer Fort", {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}},
    {"City Palace", {10, 0, 15, 25, 35, 45, 55, 65, 75, 85}},
    {"Hawa Mahal", {20, 15, 0, 10, 20, 30, 40, 50, 60, 70}},
    {"Jantar Mantar", {30, 25, 10, 0, 15, 25, 35, 45, 55, 65}},
    {"Nahargarh Fort", {40, 35, 20, 15, 0, 10, 20, 30, 40, 50}},
    {"Albert Hall Museum", {50, 45, 30, 25, 10, 0, 15, 25, 35, 45}},
    {"Birla Mandir", {60, 55, 40, 35, 20, 15, 0, 10, 20, 30}},
    {"Jal Mahal", {70, 65, 50, 45, 30, 25, 10, 0, 15, 25}},
    {"Sisodia Rani Garden", {80, 75, 60, 55, 40, 35, 20, 15, 0, 10}},
    {"Jaipur Zoo", {90, 85, 70, 65, 50, 45, 30, 25, 10, 0}}
};

void printMenu() {
    printf("Jaipur Map Navigation System\n");
    printf("-------------------------------\n");
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        printf("%d. %s\n", i + 1, locations[i].name);
    }
    printf("-------------------------------\n");
    printf("Enter your choice (1-10): ");
}

void printGraph() {
    printf("Graph:\n");
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        for (int j = 0; j < NUM_LOCATIONS; j++) {
            printf("%3d ", locations[i].distance[j]);
        }
        printf("\n");
    }
}

void navigate(Location* locations, int source, int destination) {
    int distances[NUM_LOCATIONS];
    int visited[NUM_LOCATIONS];
    int previous[NUM_LOCATIONS];

    // Initialize distances and visited arrays
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = -1;
    }

    distances[source] = 0;

    int current = source;
    while (current != -1) {
        visited[current] = 1;

        for (int i = 0; i < NUM_LOCATIONS; i++) {
            if (!visited[i] && locations[current].distance[i] != 0 && distances[current] + locations[current].distance[i] < distances[i]) {
                distances[i] = distances[current] + locations[current].distance[i];
                previous[i] = current;
            }
        }

        int minDistance = INT_MAX;
        current = -1;
        for (int i = 0; i < NUM_LOCATIONS; i++) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                current = i;
            }
        }
    }

    // Print the shortest path
    if (distances[destination] != INT_MAX) {
        printf("Shortest path from %s to %s: ", locations[source].name, locations[destination].name);
        int path[NUM_LOCATIONS];
        int index = 0;
        for (int i = destination; i != -1; i = previous[i]) {
            path[index++] = i;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("%s ", locations[path[i]].name);
        }
        printf("\nDistance: %d km\n", distances[destination]);
    } else {
        printf("No path from %s to %s\n", locations[source].name, locations[destination].name);
    }
}

int main() {
    int source, destination;

    printMenu(); // Call printMenu function
    printf("Enter source location (1-10): ");
    scanf("%d", &source);
    source--; // adjust for 0-based indexing

    printMenu(); // Call printMenu function again
    printf("Enter destination location (1-10): ");
    scanf("%d", &destination);
    destination--; // adjust for 0-based indexing

    navigate(locations, source, destination);
    return 0; // Add a return statement to indicate successful execution
}*/
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NUM_LOCATIONS 10

typedef struct {
    char name[20];
    int distance[NUM_LOCATIONS];
} Location;

Location locations[NUM_LOCATIONS] = {
    {"Amer Fort", {0, 10, 20, 30, 40, 50, 60, 70, 80, 90}},
    {"City Palace", {10, 0, 15, 25, 35, 45, 55, 65, 75, 85}},
    {"Hawa Mahal", {20, 15, 0, 10, 20, 30, 40, 50, 60, 70}},
    {"Jantar Mantar", {30, 25, 10, 0, 15, 25, 35, 45, 55, 65}},
    {"Nahargarh Fort", {40, 35, 20, 15, 0, 10, 20, 30, 40, 50}},
    {"Albert Hall Museum", {50, 45, 30, 25, 10, 0, 15, 25, 35, 45}},
    {"Birla Mandir", {60, 55, 40, 35, 20, 15, 0, 10, 20, 30}},
    {"Jal Mahal", {70, 65, 50, 45, 30, 25, 10, 0, 15, 25}},
    {"Sisodia Rani Garden", {80, 75, 60, 55, 40, 35, 20, 15, 0, 10}},
    {"Jaipur Zoo", {90, 85, 70, 65, 50, 45, 30, 25, 10, 0}}
};

void printMenu() {
    printf("Jaipur Map Navigation System\n");
    printf("-------------------------------\n");
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        printf("%d. %s\n", i + 1, locations[i].name);
    }
    printf("-------------------------------\n");
    printf("Enter your choice (1-10): ");
}

void printGraph() {
    printf("Graph:\n");
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        for (int j = 0; j < NUM_LOCATIONS; j++) {
            printf("%3d ", locations[i].distance[j]);
        }
        printf("\n");
    }
}

void navigate(Location* locations, int source, int destination) {
    int distances[NUM_LOCATIONS];
    int visited[NUM_LOCATIONS];
    int previous[NUM_LOCATIONS];

    // Initialize distances and visited arrays
    for (int i = 0; i < NUM_LOCATIONS; i++) {
        distances[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = -1;
    }

    distances[source] = 0;

    int current = source;
    while (current != -1) {
        visited[current] = 1;

        for (int i = 0; i < NUM_LOCATIONS; i++) {
            if (!visited[i] && locations[current].distance[i] != 0 && distances[current] + locations[current].distance[i] < distances[i]) {
                distances[i] = distances[current] + locations[current].distance[i];
                previous[i] = current;
            }
        }

        int minDistance = INT_MAX;
        current = -1;
        for (int i = 0; i < NUM_LOCATIONS; i++) {
            if (!visited[i] && distances[i] < minDistance) {
                minDistance = distances[i];
                current = i;
            }
        }
    }

    // Print the shortest path
    if (distances[destination] != INT_MAX) {
        printf("Shortest path from %s to %s: ", locations[source].name, locations[destination].name);
        int path[NUM_LOCATIONS];
        int index = 0;
        for (int i = destination; i != -1; i = previous[i]) {
            path[index++] = i;
        }
        for (int i = index - 1; i >= 0; i--) {
            printf("%s ", locations[path[i]].name);
        }
        printf("\nDistance: %d km\n", distances[destination]);
    } else {
        printf("No path from %s to %s\n", locations[source].name, locations[destination].name);
    }
}

int main() {
    int source, destination;

    printMenu();
    printf("Enter source location (1-10): ");
    scanf("%d", &source);
    source--; // adjust for 0-based indexing

    printMenu();
    printf("Enter destination location (1-10): ");
    scanf("%d", &destination);
    destination--; // adjust for 0-based indexing

    printGraph(); // Call printGraph function to print the graph
    navigate(locations, source, destination);
    return 0; // Add a return statement to indicate successful execution
}
