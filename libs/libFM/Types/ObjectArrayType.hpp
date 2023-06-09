#ifndef __ObjectArrayType__
#define __ObjectArrayType__

#include "ArrayType.hpp"

// Manages N-dimensional arrays of Objects - handles
// construction, reference release, and destructors
// correctly.

namespace FM
{
  struct ThreadContext;
  
  class ObjectArrayType : public ArrayType<Object> {
    virtual void* allocateArray(ndx_t size) const ;
    virtual void releaseData(Object* dst, ndx_t size) const;
    virtual void freeData(Object* ptr, ndx_t size) const;
    virtual Object zeroElement() const;
  public: 
    ObjectArrayType(ThreadContext* ctxt, const FMString &name) : ArrayType<Object>(ctxt,name) {}
    virtual void visitContainedObjects(const ObjectBase *p, ObjectVisitor &visitor) const;
    virtual ~ObjectArrayType() {}
    ndx_t indexOf(const Object &a, const Object &b) {
      ndx_t a_size = a.count();
      const Object *ap = this->ro(a);
      for (ndx_t i=0;i<a_size;i++)
	if (ap[i] == b) return i;
      return -1;
    }
  };
}

#endif
