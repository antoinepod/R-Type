/*
** EPITECH PROJECT, 2022
** objects.hpp
** File description:
** objects
*/

#pragma once

#include "raylib.h"

struct MyVector2 : Vector2 {
    constexpr MyVector2() : Vector2{0, 0} {}
    constexpr MyVector2(float x, float y) : Vector2{x, y} {}
};

struct MyVector3 : Vector3 {
    constexpr MyVector3() : Vector3{0, 0, 0} {}
    constexpr MyVector3(float x, float y, float z) : Vector3{x, y, z} {}
};

struct MyCamera2D : Camera2D {
    constexpr MyCamera2D() : Camera2D{{0, 0}, {0, 0}, 0, 0} {}
    constexpr MyCamera2D(MyVector2 offset, MyVector2 target, float rotation, float zoom) : Camera2D{offset, target, rotation, zoom} {}
};

struct MyCamera : Camera {
    constexpr MyCamera() : Camera{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, 0, 0} {}
    constexpr MyCamera(MyVector3 position, MyVector3 target, MyVector3 up, float fovy, int projection) : Camera{position, target, up, fovy, projection} {}
};

struct MyShader : Shader {
    constexpr MyShader() : Shader{0, nullptr} {}
    constexpr MyShader(unsigned int id, int *locs) : Shader{id, locs} {}
};

struct MyImage : Image {
    constexpr MyImage() : Image{nullptr, 0, 0, 0, 0} {}
    constexpr MyImage(void *data, int width, int height, int mipmaps, int format) : Image{data, width, height, mipmaps, format} {}
};

struct MySound : Sound {
    constexpr MySound() : Sound{{nullptr, 0, 0, 0},  0} {}
    constexpr MySound(AudioStream stream, unsigned int frameCount) : Sound{stream, frameCount} {}
};

struct MyRectangle : Rectangle {
    constexpr MyRectangle() : Rectangle{0, 0, 0, 0} {}
    constexpr MyRectangle(float x, float y, float width, float height) : Rectangle{x, y, width, height} {}
};

struct MyTexture : Texture {
    constexpr MyTexture() : Texture{0, 0, 0, 0, 0} {}
    constexpr MyTexture(unsigned int id, int width, int height, int mipmaps, int format) : Texture {id, width, height, mipmaps, format} {}
};

struct MyRay : Ray {
    constexpr MyRay() : Ray{{0, 0, 0}, {0, 0, 0}} {}
    constexpr MyRay(MyVector3 position, MyVector3 direction) : Ray {position, direction} {}
};

