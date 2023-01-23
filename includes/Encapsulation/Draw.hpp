/*
** EPITECH PROJECT, 2022
** draw.hpp
** File description:
** draw
*/

#pragma once

#include "raylib.h"
#include <functional>
#include <iostream>
#include "Objects.hpp"
#include "Color.hpp"

namespace rtype {
    class Draw {
    public:
        Draw() = delete;
        virtual ~Draw() = delete;
        // Set background color (framebuffer clear color)
        static void clearBackground(const MyColor &color);

        // Setup canvas (framebuffer) to start drawing
        static void beginDrawing(void);

        // End canvas drawing and swap buffers (double buffering)
        static void endDrawing(void);

        // Begin 2D mode with custom camera (2D)
        static void beginMode2D(const MyCamera2D &camera);

        // Ends 2D mode with custom camera
        static void endMode2D(void);

        // Begin 3D mode with custom camera (3D)
        static void beginMode3D(const MyCamera &camera);

        // Ends 3D mode and returns to default 2D orthographic mode
        static void endMode3D(void);

        // Begin drawing to render texture
        static void beginTextureMode(const RenderTexture2D &target);

        // Ends drawing to render texture
        static void endTextureMode(void);

        // Begin custom shader drawing
        static void beginShaderMode(const Shader &shader);

        // End custom shader drawing (use default shader)
        static void endShaderMode(void);

        // Draw functions
        // Draw a line in 3D world space
        static void drawLine3D(const MyVector3 &startPos, const MyVector3 &endPos, const MyColor &color);

        // Draw a point in 3D space, actually a small line
        static void drawPoint3D(const MyVector3 &position, const MyColor &color);

        // Draw a circle in 3D world space
        static void drawCircle3D(const MyVector3 &center, const float &radius, const MyVector3 &rotationAxis, const float &rotationAngle, const MyColor &color);

        // Draw a color-filled triangle (vertex in counter-clockwise order!)
        static void drawTriangle3D(const MyVector3 &v1, const MyVector3 &v2, const MyVector3 &v3, const MyColor &color);

        // Draw cube
        static void drawCube(const MyVector3 &position, const float &width, const float &height, const float &length, const MyColor &color);

        // Draw cube (Vector version)
        static void drawCubeV(const MyVector3 &position, const MyVector3 &size, const MyColor &color);

        // Draw cube wires
        static void drawCubeWires(const MyVector3 &position, const float &width, const float &height, const float &length, const MyColor &color);

        // Draw cube wires (Vector version)
        static void drawCubeWiresV(const MyVector3 &position, const MyVector3 &size, const MyColor &color);

        // Draw cube textured
        static void drawCubeTexture(const Texture2D &texture, const MyVector3 &position, const float &width, const float &height, const float &length, const MyColor &color);

        // Draw cube with a region of a texture
        static void drawCubeTextureRec(const MyTexture &texture, const MyRectangle &source, const MyVector3 &position, const float &width, const float &height, const float &length, const MyColor &color);

        // Draw sphere
        static void drawSphere(const MyVector3 &centerPos, const float &radius, const MyColor &color);

        // Draw sphere with extended parameters
        static void drawSphereEx(const MyVector3 &centerPos, const float &radius, const int &rings, const int &slices, const MyColor &color);

        // Draw sphere wires
        static void drawSphereWires(const MyVector3 &centerPos, const float &radius, const int &rings, const int &slices, const MyColor &color);

        // Draw a cylinder/cone
        static void drawCylinder(const MyVector3 &position, const float &radiusTop, const float &radiusBottom, const float &height, const int &slices, const MyColor &color);

        // Draw a cylinder with base at startPos and top at endPos
        static void drawCylinderEx(const MyVector3 &startPos, const MyVector3 &endPos, const float &startRadius, const float &endRadius, const int &sides, const MyColor &color);

        // Draw a cylinder/cone wires
        static void drawCylinderWires(const MyVector3 &position, const float &radiusTop, const float &radiusBottom, const float &height, int slices, const MyColor &color);

        // Draw a cylinder wires with base at startPos and top at endPos
        static void drawCylinderWiresEx(const MyVector3 &startPos, const MyVector3 &endPos, const float &startRadius, const float &endRadius, const int &sides, const MyColor &color);

        // Draw a plane XZ
        static void drawPlane(const MyVector3 &centerPos, const MyVector2 &size, const MyColor &color);

        // Draw a ray line
        static void drawRay(const MyRay &ray, const MyColor &color);

        // Draw a grid (centered at (0, 0, 0))
        static void drawGrid(const int &slices, const float &spacing);

        // Draw a part of a texture defined by a rectangle
        static void drawTextureRec(Texture2D texture, MyRectangle source, MyVector2 position, MyColor tint);

        // Draw text using font and additional parameters
        static void drawTextEx(Font font, const char *text, MyVector2 position, float fontSize, float spacing, MyColor tint);

        // Draw a Texture2D
        static void drawTexture(Texture2D texture, int posX, int posY, MyColor tint);

        // Draw a model (with texture if set)
        static void drawModel(Model model, MyVector3 position, float scale, MyColor tint);



        //additional function: draw
        static void draw(const std::function<void()> &function);

        //additional function: mode2D
        static void mode2D(const MyCamera2D &camera, const std::function<void()> &function);

        //additional function: mode3D
        static void mode3D(const MyCamera &camera, const std::function<void()> &function);

        //additional function: textureMode
        static void textureMode(const RenderTexture2D &texture, const std::function<void()> &function);

        //additional function: shaderMode
        static void shaderMode(const MyShader &shader, const std::function<void()> &function);
    };
}
