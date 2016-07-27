#ifndef DIVASPLIT_H
#define DIVASPLIT_H

#include "Kernel.h"

class DivASplit;

template<>
InputParameters validParams<DivASplit>();

class DivASplit : public Kernel
{
public:

  DivASplit(const InputParameters & parameters);

protected:

  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

private:
  const unsigned int _Ax_var;
  const unsigned int _Ay_var;
  const unsigned int _Az_var;
  const VariableValue & _Ax;
  const VariableValue & _Ay;
  const VariableValue & _Az;
  const VariableGradient & _Ax_grad;
  const VariableGradient & _Ay_grad;
  const VariableGradient & _Az_grad;
  const VariableValue & _Q;

};

#endif // DivASplit_H
