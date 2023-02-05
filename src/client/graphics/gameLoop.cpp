/*
** EPITECH PROJECT, 2022
** R-Type
** File description:
** window.cpp
*/

#include "../../../includes/networking/UDP/UDPClient.hpp"

int gameLoop(char* ip, char* port)
{
    RType::Network::UDPClient client;
    boost::array<char, 1> pEvent;
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "RType");

    Vector2 player = { (float)screenWidth/2, (float)screenHeight/4 };

    SetTargetFPS(60);

    client.SetServerInfo(ip, port);
    std::thread t([&client] { client.Run(); });

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_RIGHT))  {
            player.x += 2.0f;
            pEvent = { RType::Actions::RIGHT };
            client.Send(pEvent);
        }
        if (IsKeyDown(KEY_LEFT)) {
            player.x -= 2.0f;
            pEvent = { RType::Actions::LEFT };
            client.Send(pEvent);
        }
        if (IsKeyDown(KEY_UP)) {
            player.y -= 2.0f;
            pEvent = { RType::Actions::UP };
            client.Send(pEvent);
        }
        if (IsKeyDown(KEY_DOWN)) {
            player.y += 2.0f;
            pEvent = { RType::Actions::DOWN };
            client.Send(pEvent);
        }

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawCircleV(player, 50, MAROON);

        EndDrawing();
    }

    CloseWindow();

    client.io_context.stop();
    t.join();

    return 0;
}