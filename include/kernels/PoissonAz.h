#ifndef POISSONAZ_H
#define POISSONAZ_H

#include "Kernel.h"

class PoissonAz;

template<>
InputParameters validParams<PoissonAz>();

class PoissonAz : public Kernel
{
public:

  PoissonAz(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const unsigned int _Q_var;
  const VariableValue & _Q;
  const VariableGradient & _Q_grad;
  const Real _Jz;

};

#endif // PoissonAz_H
