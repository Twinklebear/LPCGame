#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <queue>
#include <memory>
#include <stdexcept>
#include <thread>

//TODO: Why do i have this, it's never used
///An object pool
/**
*  An object pool where users can request objects,
*  run them, and return them too the pool
*/
template<typename T>
class ObjectPool{
public:
	/**
	*  Initialize an object pool with chunkSize objects
	*  @throw invalid_argument if chunksize is 0
	*  @throw bad_alloc if allocation fails
	*/
	ObjectPool(size_t chunkSize = kDefaultChunkSize)
		throw(std::invalid_argument, std::bad_alloc);
	/**
	*  Reserve an object for use
	*  Note: Users must NOT free the object
	*  @return The object's shared pointer
	*/
	std::shared_ptr<T> AcquireObject();
	/**
	*  Return an object to the pool
	*  Note: Users must NOT use the object after returning
	*  @param obj The object to return to the pool
	*/
	void ReturnObject(std::shared_ptr<T> obj);

protected:
	///Allocate mChunkSize objects for the pool to use
	void AllocateChunk();

protected:
	///The list of objects not currently in use
	std::queue<std::shared_ptr<T>> mFreeList;
	size_t mChunkSize;
	static const size_t kDefaultChunkSize = 10;

private:
	///Prevent assignment and pass-by-value
	ObjectPool(const ObjectPool<T> &src);
	ObjectPool<T>& operator=(const ObjectPool<T> &rhs);
};
template<typename T> const size_t ObjectPool<T>::kDefaultChunkSize;

template<typename T> ObjectPool<T>::ObjectPool(size_t chunkSize)
		throw(std::invalid_argument, std::bad_alloc)
{
	if (chunkSize <= 0)
		throw std::invalid_argument("Chunk size cannot be <= 0");
	mChunkSize = chunkSize;
	//allocate an initial chunk of objects
	AllocateChunk();
}
template<typename T> std::shared_ptr<T> ObjectPool<T>::AcquireObject(){
	//if free list is empty, create more
	if (mFreeList.empty())
		AllocateChunk();
	auto obj = mFreeList.front();
	mFreeList.pop();
	return obj;
}
template<typename T> void ObjectPool<T>::ReturnObject(std::shared_ptr<T> obj){
	mFreeList.push(obj);
}
template<typename T> void ObjectPool<T>::AllocateChunk(){
	for (size_t i = 0; i < mChunkSize; ++i)
		mFreeList.push(std::make_shared<T>());
}

//Trying an idea
typedef ObjectPool<std::thread> ThreadPool;

#endif