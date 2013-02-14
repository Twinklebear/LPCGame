#include <functional>
#include <SDL_opengl.h>
#include "handle.h"

GL::Handle::Handle() : mRefCnt(nullptr) {}
GL::Handle::Handle(GLuint obj, std::function<void(GLuint)> del) 
    : mRefCnt(nullptr), mDeleter(del)
{
    mObj = obj;
    mRefCnt = new int;
    *mRefCnt = 1;
}
GL::Handle::Handle(const Handle &h) : mRefCnt(nullptr) {
    Reference(h);
}
GL::Handle::~Handle(){
    Release();
}
void GL::Handle::Release(){
    //If no reference held, return 
    if (mRefCnt == nullptr)
        return;
    //Otherwise decrease ref count and check if we should free the variable
    (*mRefCnt)--;
    if (*mRefCnt == 0){
        mDeleter(mObj);
        delete mRefCnt;
        mRefCnt = nullptr;
    }
}
void GL::Handle::Reference(const Handle &h){
    //Release current object, if held
    Release();
    //Copy over value of h & increase ref count
    mObj = h.mObj;
    mDeleter = h.mDeleter;
    mRefCnt = h.mRefCnt;
    (*mRefCnt)++;
}
GL::Handle& GL::Handle::operator=(const Handle &h){
    Reference(h);
    return *this;
}
GL::Handle& GL::Handle::operator=(const GLuint &g){
    Release();
    mRefCnt = new int;
    *mRefCnt = 1;
    mObj = g;
    return *this;
}
GL::Handle::operator GLuint(){
    return mObj;
}
