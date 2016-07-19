#ifndef EXTERNALFIELDZ
#define EXTERNALFIELDZ

#include "Kernel.h"

class ExternalFieldz;

template<>
InputParameters validParams<ExternalFieldz>();

class ExternalFieldz : public Kernel
{
public:

  ExternalFieldz(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

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
  const Real _Jx;
  const Real _Jy;
  const Real _Jz;

};

#endif // ExternalFieldz_H
