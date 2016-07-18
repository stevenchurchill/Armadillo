#ifndef ExternalField_H
#define ExternalField_H

#include "Kernel.h"

class ExternalField;

template<>
InputParameters validParams<ExternalField>();

class ExternalField : public Kernel
{
public:

  ExternalField(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  
  Real _H_x;
  Real _H_y;
  Real _H_z;
  Real _J_x;

};

#endif // ExternalField_H
