#ifndef EXTERNALFIELDY
#define EXTERNALFIELDY

#include "Kernel.h"

class ExternalFieldy;

template<>
InputParameters validParams<ExternalFieldy>();

class ExternalFieldy : public Kernel
{
public:

  ExternalFieldy(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  const VariableValue& _H_x;
  const VariableValue& _H_y;
  const VariableValue& _H_z;
  const Real _J_x;
  const Real _J_y;
  const Real _J_z;

};

#endif // ExternalFieldy_H
