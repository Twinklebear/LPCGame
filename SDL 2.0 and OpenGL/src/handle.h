#ifndef GL_HANDLE_H
#define GL_HANDLE_H

#include <functional>
#include <SDL_opengl.h>

/**
* A simple reference counting handler for automatically freeing
* OpenGL objects. It's basically a simple shared_ptr that will 
* implicitly behave like a GLuint
* could i just inherit from shared pointer? or use a shared pointer to
* a GLuint internally?
*/
namespace GL {
    class Handle {
    public:
        //Mark mRefCnt as nullptr to note that nothing is held
        Handle();
        //Construct the handler, giving it an object to handle and a destruction function
        Handle(GLuint obj, std::function<void(GLuint)> del);
        //Need to increase ref count if copying a handle
        Handle(const Handle &h);
        //Free the object using the deleter function if no more references
        ~Handle();
        //Need to increment # of references when copying a handle
        Handle& operator=(const Handle &h);
        //Behave like the stored object (GLuint) implicitly
        operator GLuint();

    private:
        //Release the object, delete if no other references
        void Release();
        //Set this handle to reference another handle
        void Reference(const Handle &h);

    private:
        int *mRefCnt;
        GLuint *mObj;
        std::function<void(GLuint)> mDeleter;
    };
}

#endif