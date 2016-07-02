#include <string>

#include "Math.hpp"
#include "../Transform.hpp"
#include "../Renderer.hpp"
#include "../Engine.hpp"

namespace rcn3d {

class Renderer;

class GameObject: public Transform {
public:
    virtual void draw(Renderer* r, glm::mat4 proj, glm::mat4 view) {

    }

    void drawGizmos() {}; //TODO


    std::string getName() {
        return name;
    }
    void setName(std::string s) {
        name = s;
    }

private:
    std::string name;
};

}
