/*
** EPITECH PROJECT, 2022
** load.hpp
** File description:
** load
*/

#include "raylib.h"
#include "Objects.hpp"
#include <iostream>

namespace rtype {
    class Load {
    public:
        // Load texture from image data
        static Texture2D loadTextureFromImage(const Image &image);

        // Load image from file into CPU memory (RAM)
        static Image loadImage(const char *fileName);

        // Load shader from files and bind default locations
        static Shader loadShader(const char *vsFileName, const char *fsFileName);

        // Load texture for rendering (framebuffer)
        static RenderTexture2D loadRenderTexture(int width, int height);

        // Load font from file with extended parameters
        static Font loadFontEx(const char *fileName, int fontSize, int *fontChars, int glyphCount);

        // Load model from files (meshes and materials)
        static Model loadModel(const char *fileName);

        // Load texture from file into GPU memory (VRAM)
        static Texture2D loadTexture(const char *fileName);

        // Unload texture from GPU memory (VRAM)
        static void unloadTexture(Texture2D texture);

        // Load model from generated mesh (default material)
        static Model loadModelFromMesh(Mesh mesh);

        // Set texture for a material map type (MATERIAL_MAP_DIFFUSE, MATERIAL_MAP_SPECULAR...)
        static void setMaterialTexture(Material *material, int mapType, Texture2D texture);

        // Update camera position for selected mode
        static void updateCamera(Camera *camera);

        // Set camera mode (multiple camera modes available)
        static void setCameraMode(Camera camera, int mode);

        // Check if point is inside rectangle
        static bool checkCollisionPointRec(Vector2 point, Rectangle rec);
    };
}