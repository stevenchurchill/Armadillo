#ifndef BZCURLA_H
#define BZCURLA_H

#include "AuxKernel.h"


//Forward declarations
class BzCurlA;

template<>
InputParameters validParams<BzCurlA>();

class BzCurlA : public AuxKernel
{
public:
  BzCurlA(const InputParameters & parameters);

  virtual ~BzCurlA() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _Ax_grad;
  const VariableGradient & _Ay_grad;
  const VariableGradient & _Az_grad;

};

#endif /* BZCURLA_H */
