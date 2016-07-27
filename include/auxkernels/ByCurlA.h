#ifndef BYCURLA_H
#define BYCURLA_H

#include "AuxKernel.h"


//Forward declarations
class ByCurlA;

template<>
InputParameters validParams<ByCurlA>();

class ByCurlA : public AuxKernel
{
public:
  ByCurlA(const InputParameters & parameters);

  virtual ~ByCurlA() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _Ax_grad;
  const VariableGradient & _Ay_grad;
  const VariableGradient & _Az_grad;

};

#endif /* BYCURLA_H */
