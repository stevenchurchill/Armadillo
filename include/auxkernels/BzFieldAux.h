#ifndef BZFIELDAUX_H
#define BZFIELDAUX_H

#include "AuxKernel.h"


//Forward declarations
class BzFieldAux;

template<>
InputParameters validParams<BzFieldAux>();

class BzFieldAux : public AuxKernel
{
public:
  BzFieldAux(const InputParameters & parameters);

  virtual ~BzFieldAux() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _PhiM_grad;

};

#endif /* BZFIELDAUX_H */
