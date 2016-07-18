#ifndef EXTERNALFIELDZ
#define EXTERNALFIELDZ

#include "Kernel.h"

class ExternalFieldz;

template<>
InputParameters validParams<ExternalFieldz>();

class ExternalFieldz : public Kernel
{
public:

  ExternalFieldz(const InputParameters & parameters);

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

#endif // ExternalFieldz_H
