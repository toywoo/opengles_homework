#include "example/new_teapot.h"

void NewTeapot::start() {
    // use program
    renderTarget.setDepthTarget(shadowMap);

    // set camera aspect and position
    camera.setAspect((float) Screen::getWidth() / Screen::getHeight())
            .setEye(glm::vec3(30.0f));

    // set light position
    light.setPosition(glm::vec3(30.0f));

    // lower floor
    floor.setWorldMatrix(glm::translate(glm::vec3(0.0f, -10.0f, 0.0f)));
}

void NewTeapot::update(const float deltaTime) {
    // clear screen
//    camera.setEye(glm::rotate(deltaTime * glm::radians(30.0f), camera.getUp())
                //  * glm::vec4(camera.getEye(), 1.0));

    // move light to move shadow
    light.setPosition(glm::rotate(deltaTime * glm::radians(20.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::vec4(light.getPosition(), 1.0f));

    // first pass - create shadow map
    {
        // use render target
        renderTarget.use();

        // set viewport and color mask
        setViewportToTexture();
        setColorMaskOff();

        // clear screen depth
        clearScreenDepth();

        // create shadow map
        shadow1Program.use();
        shadowMap.update(shadow1Program);
        light.update(shadow1Program);
        floor.draw(shadow1Program);
        teapot.draw(shadow1Program);
    }

    // second pass - draw objects
    {
        // use default render target
        renderTarget.useDefault();

        // set viewport and color mask
        setViewportToScreen();
        setColorMaskOn();

        // clear screen
        clearScreenAll();

        // draw objects with shadow mapping
        shadow2Program.use();
        shadowMap.update(shadow2Program);
        camera.update(shadow2Program);
        light.update(shadow2Program);
        floor.draw(shadow2Program);
        teapot.draw(shadow2Program);
    }
}
