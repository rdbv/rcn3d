#ifndef DEBUG_CAMERA_HPP
#define DEBUG_CAMERA_HPP

#include "Math.hpp"

namespace rcn3d {

enum CameraDirection {
    FORWARD, BACKWARD, LEFT, RIGHT
};

class DebugCamera 
{
public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 10.0f);
    glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 right;
    glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;
    float mvSpeed = 4.0f;
    float sens = 0.05f;

    DebugCamera() {
        update_camera_vectors();
    }

    glm::mat4 get_view_matrix() {
        return glm::lookAt(position, position + front, up);
    }

    void process_mouse(float xoff, float yoff) {
        xoff *= sens, yoff *= sens;
        yaw += xoff, pitch += yoff;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        update_camera_vectors();
    }
    
    void process_keyboard(CameraDirection dir, float delta) {
        float vel = mvSpeed * delta;
        if(dir == FORWARD)  position += front * vel;
        if(dir == BACKWARD) position -= front * vel;
        if(dir == LEFT)     position -= right * vel;
        if(dir == RIGHT)    position += right * vel;
    }

    void update_camera_vectors() {
        glm::vec3 frnt;
        frnt.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        frnt.y = sin(glm::radians(pitch));
        frnt.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        front = glm::normalize(frnt);
        right = glm::normalize(glm::cross(front, worldUp));
        up = glm::normalize(glm::cross(right, front));
    }
};

} // namespace rcn3d

#endif

