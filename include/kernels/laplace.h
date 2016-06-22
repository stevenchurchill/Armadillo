

#ifndef laplace_H
#define laplace_H

#include "Kernel.h"

class laplace;

template<>
InputParameters validParams<laplace>();

class laplace : public Kernel
{
public:

  laplace(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  
  Real _mu;
};

#endif // laplace_H
