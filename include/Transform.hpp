#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include "header_only/Math.hpp"

#define GLEW_STATIC
#include <GL/glew.h>

#include <vector>

namespace rcn3d {

class Transform
{
    public:
        Transform();

        /*get transform in local space*/
        glm::mat4 getLocalTransformMatrix();
        /*get transform in global space (scene)*/
        glm::mat4 getGlobalTransformMatrix();

        void setParent(Transform* t);

        void translate(GLfloat dx, GLfloat dy, GLfloat dz=0.f);
        void setPosition(GLfloat x, GLfloat y, GLfloat z=0.f);
        void setScale(GLfloat dx, GLfloat dy, GLfloat dz=1.0f);

        /* -###- move by d -###- */
        void rotateX(GLfloat dx){rotX+=dx;needUpdate=true;}
        void rotateY(GLfloat dy){rotY+=dy;needUpdate=true;}
        void rotateZ(GLfloat dz){rotZ+=dz;needUpdate=true;}
        void moveX(GLfloat dx){posX+=dx;needUpdate=true;}
        void moveY(GLfloat dy){posY+=dy;needUpdate=true;}
        void moveZ(GLfloat dz){posZ+=dz;needUpdate=true;}
        void scaleUpX(GLfloat dx){scaleX += dx; needUpdate=true;}
        void scaleUpY(GLfloat dy){scaleY += dy; needUpdate=true;}
        void scaleUpZ(GLfloat dz){scaleZ += dz; needUpdate=true;}
        /* -###- getters -###- */
        GLfloat getX(){return posX;}
        GLfloat getY(){return posY;}
        GLfloat getZ(){return posZ;}
        GLfloat getScaleX(){return scaleX;}
        GLfloat getScaleY(){return scaleY;}
        GLfloat getScaleZ(){return scaleZ;}
        GLfloat getRotX(){return rotX;}
        GLfloat getRotY(){return rotY;}
        GLfloat getRotZ(){return rotZ;}
        /* -###- setters -###- */
        void setX(GLfloat x){posX=x;needUpdate=true;}
        void setY(GLfloat y){posY=y;needUpdate=true;}
        void setZ(GLfloat z){posZ=z;needUpdate=true;}
        void setScaleX(GLfloat x){scaleX=x;needUpdate=true;}
        void setScaleY(GLfloat y){scaleY=y;needUpdate=true;}
        void setScaleZ(GLfloat z){scaleZ=z;needUpdate=true;}
        void setRotX(GLfloat x){rotX=x;needUpdate=true;}
        void setRotY(GLfloat y){rotY=y;needUpdate=true;}
        void setRotZ(GLfloat z){rotZ=z;needUpdate=true;}

    private:
        glm::mat4 mxTransform;
        bool needUpdate=false;
        GLfloat posX, posY, posZ;
        GLfloat scaleX, scaleY, scaleZ;
        GLfloat rotX, rotY, rotZ;
        Transform* parent;
        std::vector<Transform* > vecChildren;
};

}
#endif // TRANSFORM_HPP
