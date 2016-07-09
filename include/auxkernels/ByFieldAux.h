#ifndef BYFIELDAUX_H
#define BYFIELDAUX_H

#include "AuxKernel.h"


//Forward declarations
class ByFieldAux;

template<>
InputParameters validParams<ByFieldAux>();

class ByFieldAux : public AuxKernel
{
public:
  ByFieldAux(const InputParameters & parameters);

  virtual ~ByFieldAux() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _grad_PhiM;

};

#endif /* BYFIELDAUX_H */
