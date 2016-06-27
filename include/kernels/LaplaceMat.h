

#ifndef LaplaceMat_H
#define LaplaceMat_H

#include "Kernel.h"

class LaplaceMat;

template<>
InputParameters validParams<LaplaceMat>();

class LaplaceMat : public Kernel
{
public:

  LaplaceMat(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  
  Real _mu;
};

#endif // LaplaceMat_H
