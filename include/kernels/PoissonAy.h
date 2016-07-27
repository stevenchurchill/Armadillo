#ifndef POISSONAY_H
#define POISSONAY_H

#include "Kernel.h"

class PoissonAy;

template<>
InputParameters validParams<PoissonAy>();

class PoissonAy : public Kernel
{
public:

  PoissonAy(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const unsigned int _Q_var;
  const VariableValue & _Q;
  const VariableGradient & _Q_grad;
  const Real _Jy;

};

#endif // PoissonAy_H
