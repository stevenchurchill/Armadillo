#ifndef EXTERNALFIELDX
#define EXTERNALFIELDX

#include "Kernel.h"

class ExternalFieldx;

template<>
InputParameters validParams<ExternalFieldx>();

class ExternalFieldx : public Kernel
{
public:

  ExternalFieldx(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const VariableValue & _H_x;
  const VariableValue & _H_y;
  const VariableValue & _H_z;
  const VariableGradient & _H_x;
  const VariableGradient & _H_y;
  const VariableGradient & _H_z;
  const Real _J_x;
  const Real _J_y;
  const Real _J_z;

};

#endif // ExternalFieldx_H
