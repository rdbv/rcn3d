#ifndef DEBUG_CAMERA_HPP
#define DEBUG_CAMERA_HPP

namespace rcn3d {

enum CameraDirection {
    FORWARD, BACKWARD, LEFT, RIGHT
};

class DebugCamera 
{
public:
    glm::vec3 m_position = glm::vec3(0.0f, 0.0f, 5.0f);
    glm::vec3 m_front = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 m_right;
    glm::vec3 m_worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float yaw = -90.0f;
    float pitch = 0.0f;
    float mvSpeed = 3.0f;
    float sens = 0.05f;

    DebugCamera() {
        updateCameraVectors();
    }

    glm::mat4 getViewMatrix() {
        return glm::lookAt(m_position, m_position + m_front, m_up);
    }

    void processMouse(float xoff, float yoff) {
        xoff *= sens, yoff *= sens;
        yaw += xoff, pitch += yoff;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        updateCameraVectors();
    }
    
    void processKeyboard(CameraDirection dir, float delta) {
        float vel = mvSpeed * delta;
        if(dir == FORWARD)  m_position += m_front * vel;
        if(dir == BACKWARD) m_position -= m_front * vel;
        if(dir == LEFT)     m_position -= m_right * vel;
        if(dir == RIGHT)    m_position += m_right * vel;
    }

    void updateCameraVectors() {
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        m_front = glm::normalize(front);
        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }
};

} // namespace rcn3d

#endif
