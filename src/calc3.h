#include "../lib/raylib.h"
#include "../lib/rcamera.h"
#include "../lib/raymath.h"
#include "../lib/rlgl.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;
} Body;

Body createBody(Vector3 origin)
{
    Body body = {0};
    body.position = origin;
    body.velocity = (Vector3){0.0f, 0.0f, 0.0f};
    body.acceleration = (Vector3){0.0f, 0.0f, 0.0f};

    return body;
}

void copyBody(Body *body, Body *copy)
{
    copy->position = body->position;
    copy->velocity = body->velocity;
    copy->acceleration = body->acceleration;
}

Camera3D createCamera(void)
{
    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 2.0f, 4.0f};
    camera.target = (Vector3){0.0f, 2.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    return camera;
}

void updateBodyPosition(Body *body)
{
    float frame = GetTime();

    body->position.x = 2.0f * sin(frame);
    body->position.z = 2.0f * cos(frame);
}

void bodyCalculus(Body *body) {
    static Body *lastBody = NULL;
    if (lastBody == NULL) {
        lastBody = malloc(sizeof(Body));
        copyBody(body, lastBody);
        printf("copy");
    }

    // Calculate velocity
    body->velocity = Vector3Subtract(body->position, lastBody->position);

    // Calculate acceleration
    body->acceleration = Vector3Subtract(body->velocity, lastBody->velocity);

    copyBody(body, lastBody);
}

void drawScene(void)
{
    // floor
    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){32.0f, 32.0f}, LIGHTGRAY);

    // ceiling
    DrawCube((Vector3){0.0f, 12.0f, 0.0f}, 32.0f, 1.0f, 32.0f, LIGHTGRAY);
}

void drawBody(Vector3 body)
{
    DrawCube(body, 1.0f, 2.0f, 1.0f, GRAY);
    DrawCubeWires(body, 1.0f, 2.0f, 1.0f, DARKGRAY);

    // X
    DrawCube((Vector3){body.x + 1.0f, body.y, body.z}, 2.0f, 0.1f, 0.1f, RED);
    DrawCubeWires((Vector3){body.x + 1.0f, body.y, body.z}, 2.0f, 0.1f, 0.1f, MAROON);

    // Y
    DrawCube((Vector3){body.x, body.y + 2.0f, body.z}, 0.1f, 2.0f, 0.1f, GREEN);
    DrawCubeWires((Vector3){body.x, body.y + 2.0f, body.z}, 0.1f, 2.0f, 0.1f, LIME);

    // Z
    DrawCube((Vector3){body.x, body.y, body.z + 1.0f}, 0.1f, 0.1f, 2.0f, BLUE);
    DrawCubeWires((Vector3){body.x, body.y, body.z + 1.0f}, 0.1f, 0.1f, 2.0f, DARKBLUE);
}

#define GRAPH_SIZE 0xFFF

typedef struct {
    Vector3 values[GRAPH_SIZE];
    unsigned int index;
} Graph;

void addGraphValue(Graph *graph, Vector3 value) {
    graph->values[graph->index] = value;
    graph->index++;
    if (graph->index >= GRAPH_SIZE) {
        graph->index = 0;
    }
}

void drawGraphs(Body *body) {

    static Graph positionGraph = {0};
    static Graph velocityGraph = {0};
    static Graph accelerationGraph = {0};

    const double frame = GetTime();

    // draw the graphs in an arbitrary location
    const Vector3 graphOrigin = (Vector3){-10.0f, 0.0f, 0.0f};

    addGraphValue(&positionGraph, body->position);
    addGraphValue(&velocityGraph, body->velocity);
    addGraphValue(&accelerationGraph, body->acceleration);

    // draw the graphs from graph origin
    for (int i = 0; i < GRAPH_SIZE; i++) {
        // position
        DrawCube(
            Vector3Add(graphOrigin, positionGraph.values[i]),
            0.1f, 0.1f, 0.1f, RED
        );

        // velocity
        DrawCube(
            Vector3Add(graphOrigin, velocityGraph.values[i]),
            0.1f, 0.1f, 0.1f, GREEN
        );

        // acceleration
        DrawCube(
            Vector3Add(graphOrigin, accelerationGraph.values[i]),
            0.1f, 0.1f, 0.1f, BLUE
        );
    }
}
