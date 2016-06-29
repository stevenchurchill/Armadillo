

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
  
  Real _mu00;
  Real _mu01;
  Real _mu02;
  Real _mu10;
  Real _mu11;
  Real _mu12;
  Real _mu20;
  Real _mu21;
  Real _mu22;
};

#endif // LaplaceMat_H
