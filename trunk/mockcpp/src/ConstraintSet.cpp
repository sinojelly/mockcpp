
#include <ConstraintSet.h>
#include <Constraint.h>
#include <Invocation.h>

#include <vector>

MOCKCPP_NS_START

struct ConstraintSetImpl
{
    typedef std::vector<Constraint*> Vector;

    Vector constraints;

    ~ConstraintSetImpl();
    bool matches(const Invocation& inv) const;
    unsigned int numberOfValidConstraint(void) const;
    std::string toString() const;
};

////////////////////////////////////////////////////////////
std::string
ConstraintSetImpl::toString() const
{
    unsigned int n = numberOfValidConstraint();
    std::string result("");
    for(unsigned int i = 0; i < n; i++) {
      result += constraints[i]->toString();
      if(i < n-1)
        result += ", ";
	 }

    return result;
}
////////////////////////////////////////////////////////////
unsigned int
ConstraintSetImpl::numberOfValidConstraint() const
{
    unsigned int num = constraints.size();

    for(int i = num-1; i >= 0; i--) {
      if(isAnyConstraint(constraints[i]))
        num--;
    }

    return num;
}
////////////////////////////////////////////////////////////
ConstraintSetImpl::~ConstraintSetImpl()
{
  for(int i=0; i<constraints.size(); i++)
    delete constraints[i];

  constraints.clear();
}

////////////////////////////////////////////////////////////
bool
ConstraintSetImpl::matches(const Invocation& inv) const
{
  for(int i=0; i<constraints.size(); i++) {
    if(!constraints[i]->eval(inv.getParameter(i+1)))
      return false;
  }
  return true;
}

////////////////////////////////////////////////////////////
ConstraintSet::ConstraintSet(
               Constraint* p1
             , Constraint* p2
             , Constraint* p3
             , Constraint* p4
             , Constraint* p5
             , Constraint* p6)
   : This(new ConstraintSetImpl())
{
   This->constraints.push_back(p1);
   This->constraints.push_back(p2);
   This->constraints.push_back(p3);
   This->constraints.push_back(p4);
   This->constraints.push_back(p5);
   This->constraints.push_back(p6);
}

////////////////////////////////////////////////////////////
ConstraintSet::~ConstraintSet()
{
    delete This;
}

////////////////////////////////////////////////////////////
bool ConstraintSet::matches(const Invocation& inv) const
{
    return This->matches(inv);    
}

////////////////////////////////////////////////////////////
std::string ConstraintSet::toString() const
{
   std::string result(".with(");
   result += This->toString();
   result += ")";
   return result;
}
////////////////////////////////////////////////////////////

MOCKCPP_NS_END

