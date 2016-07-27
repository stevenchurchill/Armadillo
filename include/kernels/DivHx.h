#ifndef DIVHX
#define DIVHX

#include "Kernel.h"

class DivHx;

template<>
InputParameters validParams<DivHx>();

class DivHx : public Kernel
{
public:

  DivHx(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  const unsigned int _Hx_var;
  const unsigned int _Hy_var;
  const unsigned int _Hz_var;
  const VariableValue & _Hx;
  const VariableValue & _Hy;
  const VariableValue & _Hz;
  const VariableGradient & _Hx_grad;
  const VariableGradient & _Hy_grad;
  const VariableGradient & _Hz_grad;

};

#endif // DivHx_H
