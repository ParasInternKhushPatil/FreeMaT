#ifndef __ClassType_hpp__
#define __ClassType_hpp__

#include "Object.hpp"
#include "Type.hpp"
#include "HashMap.hpp"
#include "HandleType.hpp"

namespace FM
{
  struct ThreadContext;

  /*
  // What we want is something like HandleClass - a class with properties and events
  struct ClassMethod {
    bool Abstract;
    AccessType Access;
    ClassMetaData* DefiningClass;
    bool Hidden;
    FMString Name;
    bool Sealed;
    bool Static;
    Object Value;
  };
  
  struct ClassProperty {
    FMString Name;
    bool AbortSet;
    bool Abstract;
    AccessType Access;
    bool Constant;
    Object DefaultValue;
    ClassMetaData* DefiningClass;
    AccessType GetAccess;
    bool Dependent;
    bool Transient;
    Object GetMethod;
    bool GetObservable;
    bool HasDefault;
    bool Hidden;
    AccessType SetAccess;
    Object SetMethod;
    bool SetObservable;
  };

  struct ClassEvent {
    FMString Name;
    bool Hidden;
    AccessType ListenAccess;
    AccessType NotifyAccess;
    ClassMetaData* DefiningClass;
  };

  struct ClassMetaData {
    bool Abstract; // True if this is an abstract class
    std::vector<ClassMetaData*> AllowedSubclasses;
    bool ConstructOnLoad;
    ClassPackage* myPackage;
    bool Enumeration;
    std::vector<ClassEvent*> EventList;
    std::vector<ClassEnumerationMember*> EnumerationMemberList;
    bool Hidden;
    std::vector<ClassMetaData*> InferiorClasses;
    std::vector<ClassMethod*> MethodList;
    FMString Name;
    std::vector<ClassProperty*> PropertyList;
    bool Sealed;
    std::vector<ClassMetaData*> SuperiorClasses;
  };

  */
  //  This is a lot of C++ code... Is it really necessary?

  class ClassMethodMetaData {
  public:
    bool m_static;
    Object m_definition;
    ClassMethodMetaData(ThreadContext *_ctxt) : m_static(false), m_definition(_ctxt) {}
  };

  class ClassPropertyMetaData {
  public:
    bool m_constant;   // Set to true if the property is constant
    bool m_dependent;  // Set to true if the property is dependent
    Object m_default;  // Default value
    Object m_getter;   // Getter (if it has one)
    Object m_setter;   // Setter (if it has one)
    ndx_t m_index;       // Index into the object instance's list of properties
    ClassPropertyMetaData(ThreadContext *_ctxt) : m_constant(false),
      m_dependent(false), m_default(_ctxt), m_getter(_ctxt),
      m_setter(_ctxt), m_index(0) {}
  };

  // Start with a  class.  Assume value type.
  class ClassMetaData {
  public:
    Object m_name;             // Name of the  class.
    HashMap<ClassPropertyMetaData*> m_properties; // Properties for the class 
    HashMap<ClassMethodMetaData*> m_methods; // Methods for the class 
    Object m_constructor;
    Object m_events;
    Object m_defaults;
    bool m_ishandle;
    ClassMetaData(ThreadContext *_ctxt);
  };
  
  class ClassMetaType : public AggregateType<ClassMetaData,HandleSemantics> {
  public:
    ClassMetaType(ThreadContext *ctxt) : AggregateType<ClassMetaData,HandleSemantics>(ctxt) {}
    void addProperty(Object &meta, const Object &name, bool constant, 
		     bool dependent, const Object &default_value,
		     const Object &getter, const Object &setter);
    void visitContainedObjects(const ObjectBase *, ObjectVisitor &) const {}
    void addMethod(Object &meta, const Object &name, const Object &definition, bool is_static);
    void addSuperClass(Object &meta, const Object &super);
    void addEvent(Object &meta, const Object &event);
    virtual DataCode code() const {return TypeMeta;}
    virtual const FMString& name() const {static FMString _name = "meta"; return _name;}
    //    Object empty();
    virtual FMString describe(const Object &a);
    virtual FMString brief(const Object &a);
    virtual bool equals(const Object &, const Object &)
    {
      return false;
    }
    Object construct(const Object &a);
    virtual Object deref(const Object &a); // Construct an object without parameters
    virtual Object getParens(const Object &a, const Object &b); // Construct with parameters
    virtual Object getField(const Object &meta, const Object &fieldname);
    virtual Object invokeConstructor(const Object &meta, const Object &self, const Object &args);
    Object import(const Object &foreign) {
      ClassMetaType *them = foreign.asType<ClassMetaType>();
      if (this == them) return foreign;
      Object ret = this->makeScalar();
      ClassMetaData *cmd = this->rw(ret);
      const ClassMetaData *ccmd = them->ro(foreign);
      cmd->m_name = ccmd->m_name.exportTo(_ctxt);
      for (auto i : ccmd->m_properties) {
	ClassPropertyMetaData *d = new ClassPropertyMetaData(_ctxt);
	d->m_constant = i.second->m_constant;
	d->m_dependent = i.second->m_dependent;
	d->m_default = i.second->m_default.exportTo(_ctxt);
	d->m_getter = i.second->m_getter.exportTo(_ctxt);
	d->m_setter = i.second->m_setter.exportTo(_ctxt);
	d->m_index = i.second->m_index;
	cmd->m_properties.insert(std::make_pair(i.first.exportTo(_ctxt),d));
      }
      for (auto i : ccmd->m_methods) {
	ClassMethodMetaData *d = new ClassMethodMetaData(_ctxt);
	d->m_static = i.second->m_static;
	d->m_definition = i.second->m_definition.exportTo(_ctxt);
	cmd->m_methods.insert(std::make_pair(i.first.exportTo(_ctxt),d));
      }
      cmd->m_constructor = ccmd->m_constructor.exportTo(_ctxt);
      cmd->m_events = ccmd->m_events.exportTo(_ctxt);
      cmd->m_defaults = ccmd->m_defaults.exportTo(_ctxt);
      cmd->m_ishandle = ccmd->m_ishandle;
      return ret;
    }
  };

  class ClassData {
  public:
    Object metaClass; // The meta class for this class.
    Object m_data; // The cell array of data for this class.
    ClassData(ThreadContext *ctxt) : metaClass(ctxt), m_data(ctxt) {}
  };

  class ClassType : public AggregateType<ClassData,ValueSemantics> {
    Object m_deletefunc_name;
    Object m_plusfunc_name;
    Object m_mtimes_name;
    Object m_mldivide_name;
    Object m_mrdivide_name;
    Object m_ldivide_name;
    Object m_rdivide_name;
    Object m_times_name;
    Object m_subtract_name;
    Object m_le_name;
    Object m_lt_name;
    Object m_gt_name;
    Object m_ge_name;
    Object m_ne_name;
    Object m_eq_name;
    Object m_or_name;
    Object m_and_name;
    Object m_neg_name;
    Object m_uplus_name;
    Object m_ctranspose_name;
    Object m_transpose_name;
    Object m_colon_name;
    Object m_vertcat_name;
    Object m_horzcat_name;
    Object m_subsref_name;
    Object m_subsasgn_name;
    Object m_type_name;
    Object m_subs_name;
    Object m_subsindex_name;
    Object bifunc(const Object &a, const Object &b, const Object &name);
    Object ufunc(const Object &a, const Object &name);
  public:
    ClassType(ThreadContext *ctxt);
    virtual DataCode code() const {return TypeClass;}
    virtual const FMString& name() const {static FMString _name = "class"; return _name;}
    void visitContainedObjects(const ObjectBase *p, ObjectVisitor &visitor) const 
    {
      visitor(this->ro(p)->m_data);
    }
    Object import(const Object &foreign) {
      ClassType *them = foreign.asType<ClassType>();
      if (this == them) return foreign;
      Object ret = this->makeScalar();
      ClassData *cd = this->rw(ret);
      const ClassData *ccd = them->ro(foreign);
      cd->metaClass = ccd->metaClass.exportTo(_ctxt);
      cd->m_data = ccd->m_data.exportTo(_ctxt);
      return ret;
    }
    bool isHandle(const Object &a);
    virtual FMString describe(const Object &a);
    virtual FMString brief(const Object &a);
    virtual Object getMethod(const Object &a, const Object &b);
    virtual Object getField(const Object &a, const Object &b);
    virtual Object getFieldNoGetters(const Object &a, const Object &b);
    virtual void setField(Object &a, const Object &args, const Object &b);
    virtual void setFieldNoSetters(Object &a, const Object &args, const Object &b);
    //    virtual Object getParens(const Object &a, const Object &args);
    //    virtual void setParens(Object &a, const Object &args, const Object &b);
    virtual bool hasMethod(const Object &a, const Object &name, Object &ret);
    const Object & className(const Object &a) const {return _ctxt->_meta->ro(this->ro(a)->metaClass)->m_name;}
    virtual bool equals(const Object &, const Object &)
    {
      // FIXME - allow equality tests
      return false;
    }
    Object empty() {throw Exception("Cannot create empty classes");}
    virtual void destroyObject(ObjectBase* p);
    virtual Object Add(const Object &a, const Object &b) {return bifunc(a,b,m_plusfunc_name);}
    virtual Object Multiply(const Object &a, const Object &b) {return bifunc(a,b,m_mtimes_name);}
    virtual Object LeftDivide(const Object &a, const Object &b) {return bifunc(a,b,m_mldivide_name);}
    virtual Object RightDivide(const Object &a, const Object &b) {return bifunc(a,b,m_mrdivide_name);}
    virtual Object DotLeftDivide(const Object &a, const Object &b) {return bifunc(a,b,m_ldivide_name);}
    virtual Object DotRightDivide(const Object &a, const Object &b) {return bifunc(a,b,m_rdivide_name);}
    virtual Object DotMultiply(const Object &a, const Object &b) {return bifunc(a,b,m_times_name);}
    virtual Object Subtract(const Object &a, const Object &b) {return bifunc(a,b,m_subtract_name);}
    virtual Object LessEquals(const Object &a, const Object &b) {return bifunc(a,b,m_le_name);}
    virtual Object LessThan(const Object &a, const Object &b) {return bifunc(a,b,m_lt_name);}
    virtual Object GreaterThan(const Object &a, const Object &b) {return bifunc(a,b,m_gt_name);}
    virtual Object GreaterEquals(const Object &a, const Object &b) {return bifunc(a,b,m_ge_name);}
    virtual Object NotEquals(const Object &a, const Object &b) {return bifunc(a,b,m_ne_name);}
    virtual Object Equals(const Object &a, const Object &b) {return bifunc(a,b,m_eq_name);}
    virtual Object Or(const Object &a, const Object &b) {return bifunc(a,b,m_or_name);}
    virtual Object And(const Object &a, const Object &b) {return bifunc(a,b,m_and_name);}
    virtual Object Neg(const Object &a) {return ufunc(a,m_neg_name);}
    virtual Object Plus(const Object &a) {return ufunc(a,m_uplus_name);}
    virtual Object Colon(const Object &a, const Object &b) {return bifunc(a,b,m_colon_name);}
    virtual Object NCat(const Object &p, ndx_t dimension);
    virtual Object DoubleColon(const Object &a, const Object &b, const Object &c);
    virtual Object Transpose(const Object &a) {return ufunc(a,m_transpose_name);}
    virtual Object Hermitian(const Object &a) {return ufunc(a,m_ctranspose_name);}
    bool hasSubsref(const Object &a);
    Object subsref(const Object &a, const Object &b);
    bool hasSubsasgn(const Object &a);
    void subsasgn(Object &a, const Object &args, const Object &b);
    Object makeSubstruct(const Object &b);
    virtual Object asIndex(const Object &a, ndx_t);
  };
};


#endif
