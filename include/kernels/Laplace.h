

#ifndef LAPLACE_H
#define LAPLACE_H

#include "Kernel.h"

class Laplace;

template<>
InputParameters validParams<Laplace>();

class Laplace : public Kernel
{
public:

  Laplace(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  
  Real _mu;
};

#endif // LAPLACE_H
