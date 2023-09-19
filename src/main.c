#include "calc3.h"

/*

https://web.ma.utexas.edu/users/m408m/Display13-4-2.shtml

What direction are we going? This is given by a tangent vector T which gives the direction of the velocity vector.

Which direction are we curving? Are we turning left, right, up, down, or a combination? This is given by a vector called the principal normal N

How fast are we turning? By fast we mean a derivative with respect to distance, not with respect to time. How much will our direction change in the next inch, or foot, or mile? This is described by the curvature
κ, and by the radius of curvature R=1/κ
The bigger the curvature, the tighter the turn and the smaller the radius of curvature.

What plane are we currently moving in? The binormal vector B=T×N
is perpendicular to both T and N, so it gives the plane in which the curve lies.

*/

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    const Vector3 BODY_ORIGIN = (Vector3){0.0f, 1.0f, 0.0f};

    Camera3D camera = createCamera();
    Body body = createBody(BODY_ORIGIN);

    InitWindow(screenWidth, screenHeight, "Calc 3 Example - Ben Schreiber");

    DisableCursor();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {

        UpdateCamera(&camera, CAMERA_FIRST_PERSON);
        updateBodyPosition(&body);
        bodyCalculus(&body);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        drawScene();
        drawBody(body.position);
        drawGraphs(&body);

        EndMode3D();

        // drawInfoBoxes(&body);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}