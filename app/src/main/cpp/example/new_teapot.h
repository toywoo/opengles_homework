#ifndef OPENGLES_NEW_TEAPOT_H
#define OPENGLES_NEW_TEAPOT_H

#include "utility/scene.h"
#include "render/light.h"

class NewTeapot : public Scene {
protected:
    virtual void start();
    virtual void update(const float deltaTime);
private:
    RenderTarget renderTarget;
    Shader shadow1VertexShader{ Shader::Type::VERTEX, AssetManager::readShader("new_teapot_first_vs") };
    Shader shadow1FragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("new_teapot_first_fs") };
    Shader shadow2VertexShader{ Shader::Type::VERTEX, AssetManager::readShader("new_teapot_second_vs") };
    Shader shadow2FragmentShader{ Shader::Type::FRAGMENT, AssetManager::readShader("new_teapot_second_fs") };
    Program shadow1Program{ { shadow1VertexShader, shadow1FragmentShader } };
    Program shadow2Program{ { shadow2VertexShader, shadow2FragmentShader } };
    Texture shadowMap{ Texture::Type::ShadowMap };
    Texture dirtColor{ Texture::Type::ColorMap, AssetManager::readTexture("dirt") };
    Texture grassColor{ Texture::Type::ColorMap, AssetManager::readTexture("grass") };
    Material grass{ { grassColor } };
    Material dirt{ { dirtColor } };
    Object floor{ AssetManager::readObject("floor"), grass };
    Object teapot{ AssetManager::readObject("teapot"),  dirt};
    Camera camera;
    Light light{ Light::Type::POINT };
};

#endif // OPENGLES_NEW_TEAPOT_H
