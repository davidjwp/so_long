#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int f;
    int g;
    int h;
    Point parent;
} Node;

Node** createMap() {
    Node** map = (Node**)malloc(MAP_HEIGHT * sizeof(Node*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        map[i] = (Node*)malloc(MAP_WIDTH * sizeof(Node));
        for (int j = 0; j < MAP_WIDTH; j++) {
            map[i][j].f = INT_MAX;
            map[i][j].g = INT_MAX;
            map[i][j].h = INT_MAX;
            map[i][j].parent.x = -1;
            map[i][j].parent.y = -1;
        }
    }
    return map;
}

void destroyMap(Node** map) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(map[i]);
    }
    free(map);
}

int heuristicCost(Point start, Point end) {
    // Manhattan distance heuristic
    return abs(start.x - end.x) + abs(start.y - end.y);
}

void printPath(Node** map, Point end) {
    printf("Path: ");
    Point current = end;
    while (current.x != -1 && current.y != -1) {
        printf("(%d, %d) ", current.x, current.y);
        Point parent = map[current.x][current.y].parent;
        current = parent;
    }
    printf("\n");
}

void aStarSearch(char** inputMap, Point start, Point end) {
    Node** map = createMap();
    map[start.x][start.y].f = 0;
    map[start.x][start.y].g = 0;
    map[start.x][start.y].h = 0;

    int openListSize = 1;
    Point* openList = (Point*)malloc(openListSize * sizeof(Point));
    openList[0] = start;

    while (openListSize > 0) {
        // Find the node with the lowest f value
        int minIndex = 0;
        for (int i = 1; i < openListSize; i++) {
            Point current = openList[i];
            if (map[current.x][current.y].f < map[openList[minIndex].x][openList[minIndex].y].f) {
                minIndex = i;
            }
        }

        Point current = openList[minIndex];
        if (current.x == end.x && current.y == end.y) {
            printPath(map, end);
            break;
        }

        // Remove the current node from the open list
        for (int i = minIndex; i < openListSize - 1; i++) {
            openList[i] = openList[i + 1];
        }
        openListSize--;

        // Explore neighboring nodes
        int dx[4] = { -1, 1, 0, 0 };
        int dy[4] = { 0, 0, -1, 1 };
        for (int i = 0; i < 4; i++) {
            int nextX = current.x + dx[i];
            int nextY = current.y + dy[i];
            if (nextX >= 0 && nextX < MAP_HEIGHT && nextY >= 0 && nextY < MAP_WIDTH && inputMap[nextX][nextY] != '#') {
                int newG = map[current.x][current.y].g + 1;
                if (newG < map[nextX][nextY].g) {
                    map[nextX][nextY].g = newG;
                    map[nextX][nextY].h = heuristicCost((Point) { nextX, nextY }, end);
                    map[nextX][nextY].f = newG + map[nextX][nextY].h;
                    map[nextX][nextY].parent = current;

                    int isInOpenList = 0;
                    for (int j = 0; j < openListSize; j++) {
                        if (openList[j].x == nextX && openList[j].y == nextY) {
                            isInOpenList = 1;
                            break;
                        }
                    }
                    if (!isInOpenList) {
                        openListSize++;
                        openList = (Point*)realloc(openList, openListSize * sizeof(Point));
                        openList[openListSize - 1].x = nextX;
                        openList[openListSize - 1].y = nextY;
                    }
                }
            }
        }
    }

    free(openList);
    destroyMap(map);
}

int main() {
    char* inputMap[MAP_HEIGHT] = {
        "##########",
        "#S.......#",
        "#........#",
        "#.######.#",
        "#........#",
        "#.######.#",
        "#........#",
        "#.......E#",
        "#........#",
        "##########"
    };

    Point start = { 1, 1 };
    Point end = { 7, 8 };

    aStarSearch(inputMap, start, end);

    return 0;
}
