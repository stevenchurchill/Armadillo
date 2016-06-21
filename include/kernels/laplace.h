

#ifndef laplace_H
#define laplace_H

#include "Kernel.h"

class laplace;

template<>
InputParameters validParams<laplace>();

class laplace : public kernel
{
public:

  laplace(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  
  Real_mu;
};

#endif // laplace_H
