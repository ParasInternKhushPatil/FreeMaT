#ifndef __Type_hpp__
#define __Type_hpp__

#include "FMLib.hpp"
#include "Exception.hpp"

namespace FM {

  
  typedef unsigned ref_t;
  typedef int64_t ndx_t;

  class ObjectBase;
  struct ThreadContext;

  enum DataCode {
    TypeInvalid = 0,
    TypeCellArray = 1,
    TypeStruct = 2,
    TypeString = 3,
    TypeBool = 4,
    TypeInt8 = 5,
    TypeUInt8 = 6,
    TypeInt16 = 7,
    TypeUInt16 = 8,
    TypeInt32 = 9,
    TypeUInt32 = 10,
    TypeInt64 = 11,
    TypeUInt64 = 12,
    TypeSingle = 13,
    TypeDouble = 14,
    TypeIndex = 15,
    TypeListArray = 16,
    TypeMeta = 17,
    TypeClass = 18,
    TypeCode = 19,
    TypeModule = 20,
    TypeCaptured = 21,
    TypeFunction = 22,
    TypeBoundFunction = 23,
    TypeFunctionHandle = 24,
    TypeAnonymous = 25,
    TypeBreakpoint = 26,
    TypeSparseLogical = 27,
    TypeSparseDouble = 28,
    TypeSparseComplex = 29
  };

  class Object;
  class ObjectVector;
  class Tuple;
  struct Data;

  class ObjectVisitor {
  public:
    virtual void operator()(const Object &p) = 0;
  };

  class Type {
  protected:
    ThreadContext *_ctxt;
  public:
    Type(ThreadContext *ctxt) : _ctxt(ctxt) {}
    virtual ~Type() {}
    ThreadContext *context() const {return _ctxt;}
    virtual DataCode code() const = 0;
    virtual const FMString& name() const = 0;
    virtual void destroyObject(ObjectBase* p) = 0;
    virtual Data* duplicateData(const ObjectBase * p, ndx_t &reserve) const = 0;
    virtual void visitContainedObjects(const ObjectBase *p, ObjectVisitor &visitor) const = 0;
    virtual Object empty() = 0;
    virtual Object import(const Object &foreign) = 0;
    virtual Object Add(const Object &a, const Object &b);
    virtual Object Multiply(const Object &a, const Object &b);
    virtual Object Power(const Object &a, const Object &b);
    virtual Object LeftDivide(const Object &a, const Object &b);
    virtual Object RightDivide(const Object &a, const Object &b);
    virtual Object DotLeftDivide(const Object &a, const Object &b);
    virtual Object DotRightDivide(const Object &a, const Object &b);
    virtual Object DotMultiply(const Object &a, const Object &b);
    virtual Object DotPower(const Object &a, const Object &b);
    virtual Object Subtract(const Object &a, const Object &b);
    virtual Object LessEquals(const Object &a, const Object &b);
    virtual Object LessThan(const Object &a, const Object &b);
    virtual Object GreaterThan(const Object &a, const Object &b);
    virtual Object GreaterEquals(const Object &a, const Object &b);
    virtual Object NotEquals(const Object &a, const Object &b);
    virtual Object Equals(const Object &a, const Object &b);
    virtual Object Or(const Object &a, const Object &b);
    virtual Object And(const Object &a, const Object &b);
    virtual Object Neg(const Object &a);
    virtual Object Not(const Object &a);
    virtual Object Plus(const Object &a);
    virtual Object Colon(const Object &a, const Object &b);
    virtual Object NCat(const Object &p, ndx_t dimension);
    virtual Object DoubleColon(const Object &a, const Object &b, const Object &c);
    virtual Object Transpose(const Object &a);
    virtual Object Hermitian(const Object &a);
    virtual bool equals(const Object &a, const Object &b) = 0;
    virtual FMString describe(const Object &a) = 0;
    virtual FMString brief(const Object &a) = 0;
    virtual Object asIndex(const Object &a, ndx_t max);
    virtual Object asIndexNoBoundsCheck(const Object &a);
    virtual Object asLogical(const Object &a);
    virtual Object getParens(const Object &a, const Object &b);
    virtual Object getBraces(const Object &a, const Object &b);
    virtual Object getField(const Object &a, const Object &b);
    virtual Object getFieldNoGetters(const Object &a, const Object &b);
    virtual Object sliceColumn(const Object &a, ndx_t column);
    virtual Object convert(const Object &a);
    virtual double doubleValue(const Object &a);
    virtual void setParens(Object &a, const Object &args, const Object &b);
    virtual void setBraces(Object &a, const Object &args, const Object &b);
    virtual void setField(Object &a, const Object &args, const Object &b);
    virtual void setFieldNoSetters(Object &a, const Object &args, const Object &b);
    virtual Object get(const Object &a, const Object &b, bool invokeGetters);
    virtual void set(Object &a, const Object &args, const Object &b, bool invokeSetters);
    virtual void resize(Object &a, const Tuple &newsize);
    virtual void print(const Object &a);
    virtual Object deref(const Object &a);
    virtual Object call(const Object &a, const Object &args, ndx_t nargout);
  };
}

#endif
