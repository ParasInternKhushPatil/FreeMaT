#ifndef __SingleType_hpp__
#define __SingleType_hpp__

#include "FloatType.hpp"
#include "BoolType.hpp"
#include "BinOp.hpp"
#include "Operators.hpp"
#include "MatrixPower.hpp"

namespace FM
{
  struct ThreadContext;

  class SingleType : public FloatType<float,TypeSingle> {
    template <class Op>
    inline Object binop(const Object &a, const Object &b)
    {
      if (a.isScalar() && b.isScalar() && !a.isComplex() && !b.isComplex() && b.type()->code() == TypeSingle) {
	const float * ap = static_cast<const float*>(a.d->data->ptr);
	const float * bp = static_cast<const float*>(b.d->data->ptr);
	float p;
	Op::template func<float,float,float,float>(&p,ap,bp);
	return makeScalar(p);
      }
      switch (b.type()->code())
	{
	case TypeDouble:
	  return dispatch_binop<float,float,double,double,Op>(a,b,a.type());
	case TypeSingle:
	  return dispatch_binop<float,float,float,float,Op>(a,b,a.type());
	default:
	  throw Exception(FMString("Unsupported combination of ") + this->name() + 
			  FMString(" and ") + b.type()->name());
	}
    }
    template <class Op>
    inline Object cmpop(const Object &a, const Object &b, BoolType *o)
    {
      if (a.isScalar() && b.isScalar() && !a.isComplex() && !b.isComplex() && b.type()->code() == TypeSingle) {
	const float * ap = static_cast<const float*>(a.d->data->ptr);
	const float * bp = static_cast<const float*>(b.d->data->ptr);
	bool p;
	Op::template func<bool,float,float,float>(&p,ap,bp);
	return o->makeScalar(p);
      }
      switch (b.type()->code())
	{
	case TypeDouble:
	  return dispatch_cmpop<bool,float,double,double,Op>(a,b,o);
	case TypeSingle:
	  return dispatch_cmpop<bool,float,float,float,Op>(a,b,o);
	default:
	  throw Exception(FMString("Unsupported combination of ") + this->name() + 
			  FMString(" and ") + b.type()->name());
	}
    }
  public:
    SingleType(ThreadContext *ctxt) : FloatType<float,TypeSingle>(ctxt,"single") {}
    virtual Type* typeInstance() {return this;}
    virtual Object Add(const Object &a, const Object &b) {return binop<OpAdd>(a,b);}
    virtual Object Subtract(const Object &a, const Object &b) {return binop<OpSubtract>(a,b);}
    virtual Object DotPower(const Object &a, const Object &b) {
      if (!a.isComplex() && !b.isComplex() && !this->isNonNegative(a) && !this->isIntegerValued(b)) 
	return binop<OpDotPower>(this->asComplex(a),this->asComplex(b));
      return binop<OpDotPower>(a,b);
    }
    virtual Object Power(const Object &a, const Object &b) {
      return MatrixPower(a,b,_ctxt);
    }
    virtual Object DotMultiply(const Object &a, const Object &b) {return binop<OpDotMultiply>(a,b);}
    virtual Object DotRightDivide(const Object &a, const Object &b) {return binop<OpDotRightDivide>(a,b);}
    virtual Object DotLeftDivide(const Object &a, const Object &b) {return binop<OpDotLeftDivide>(a,b);}
    virtual Object LessEquals(const Object &a, const Object &b) {return cmpop<OpLE>(a,b,_ctxt->_bool);}
    virtual Object LessThan(const Object &a, const Object &b) {return cmpop<OpLT>(a,b,_ctxt->_bool);}
    virtual Object GreaterEquals(const Object &a, const Object &b) {return cmpop<OpGE>(a,b,_ctxt->_bool);}
    virtual Object GreaterThan(const Object &a, const Object &b) {return cmpop<OpGT>(a,b,_ctxt->_bool);}
    virtual Object Equals(const Object &a, const Object &b) {return cmpop<OpEQ>(a,b,_ctxt->_bool);}
    virtual Object NotEquals(const Object &a, const Object &b) {return cmpop<OpNE>(a,b,_ctxt->_bool);}
    virtual Object Or(const Object &a, const Object &b) {return cmpop<OpOr>(a,b,_ctxt->_bool);}
    virtual Object And(const Object &a, const Object &b) {return cmpop<OpAnd>(a,b,_ctxt->_bool);}
    virtual Object Multiply(const Object &a, const Object &b);
    virtual Object LeftDivide(const Object &a, const Object &b);
    virtual Object RightDivide(const Object &a, const Object &b);
  };
}

#endif
