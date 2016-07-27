/************************************************************************/
/* FarField BC:                                                         */
/*     This BC is intended to implement |B0| -> 0   at a boundary.      */
/************************************************************************/

#ifndef OPENCIRCUITBC_H
#define OPENCIRCUITBC_H

#include "IntegratedBC.h"

//Forward Declarations
class FarFieldBC;

template<>
InputParameters validParams<FarFieldBC>();

class FarFieldBC : public IntegratedBC
{
public:

  FarFieldBC(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

private:
  const VariableGradient & _Ax_grad;
  const VariableGradient & _Ay_grad;
  const VariableGradient & _Az_grad;
};

#endif /* FARFIELDBC_H */
