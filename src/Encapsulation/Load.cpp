/*
** EPITECH PROJECT, 2022
** load.cpp
** File description:
** load
*/

#include "Load.hpp"

namespace rtype {
    Texture2D Load::loadTextureFromImage(const Image &image) {
        return LoadTextureFromImage(image);
    }

    Image Load::loadImage(const char *fileName) {
        return LoadImage(fileName);
    }

    Shader Load::loadShader(const char *vsFileName, const char *fsFileName) {
        return LoadShader(vsFileName, fsFileName);
    }

    RenderTexture2D Load::loadRenderTexture(int width, int height) {
        return LoadRenderTexture(width, height);
    }

    Font Load::loadFontEx(const char *fileName, int fontSize, int *fontChars, int glyphCount) {
        return LoadFontEx(fileName, fontSize, fontChars, glyphCount);
    }

    Model Load::loadModel(const char *fileName) {
        return LoadModel(fileName);
    }

    Texture2D Load::loadTexture(const char *fileName) {
        return LoadTexture(fileName);
    }

    void Load::unloadTexture(Texture2D texture) {
        return UnloadTexture(texture);
    }

    Model Load::loadModelFromMesh(Mesh mesh) {
        return LoadModelFromMesh(mesh);
    }

    void Load::setMaterialTexture(Material *material, int mapType, Texture2D texture) {
        return SetMaterialTexture(material, mapType, texture);
    }

    void Load::updateCamera(Camera *camera) {
        return UpdateCamera(camera);
    }

    void Load::setCameraMode(Camera camera, int mode) {
        return SetCameraMode(camera, mode);
    }

    bool Load::checkCollisionPointRec(Vector2 point, Rectangle rec) {
        return CheckCollisionPointRec(point, rec);
    }
}
