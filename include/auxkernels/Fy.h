#ifndef FY_H
#define FY_H

#include "AuxKernel.h"


//Forward declarations
class Fy;

template<>
InputParameters validParams<Fy>();

class Fy : public AuxKernel
{
public:
  Fy(const InputParameters & parameters);

  virtual ~Fy() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _mumag_grad;
};

#endif /* FY_H */
