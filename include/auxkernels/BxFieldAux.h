#ifndef BXFIELDAUX_H
#define BXFIELDAUX_H

#include "AuxKernel.h"


//Forward declarations
class BxFieldAux;

template<>
InputParameters validParams<BxFieldAux>();

class BxFieldAux : public AuxKernel
{
public:
  BxFieldAux(const InputParameters & parameters);

  virtual ~BxFieldAux() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _PhiM_grad;

};

#endif /* BXFIELDAUX_H */
