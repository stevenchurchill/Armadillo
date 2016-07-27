#ifndef POISSONAX_H
#define POISSONAX_H

#include "Kernel.h"

class PoissonAx;

template<>
InputParameters validParams<PoissonAx>();

class PoissonAx : public Kernel
{
public:

  PoissonAx(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const unsigned int _Q_var;
  const VariableValue & _Q;
  const VariableGradient & _Q_grad;
  const Real _Jx;

};

#endif // PoissonAx_H
