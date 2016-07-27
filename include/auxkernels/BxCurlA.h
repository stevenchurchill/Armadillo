#ifndef BXCURLA_H
#define BXCURLA_H

#include "AuxKernel.h"


//Forward declarations
class BxCurlA;

template<>
InputParameters validParams<BxCurlA>();

class BxCurlA : public AuxKernel
{
public:
  BxCurlA(const InputParameters & parameters);

  virtual ~BxCurlA() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _Ax_grad;
  const VariableGradient & _Ay_grad;
  const VariableGradient & _Az_grad;

};

#endif /* BXCURLA_H */
