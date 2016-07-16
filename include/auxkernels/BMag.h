#ifndef BMAG_H
#define BMAG_H

#include "AuxKernel.h"


//Forward declarations
class BMag;

template<>
InputParameters validParams<BMag>();

class BMag : public AuxKernel
{
public:
  BMag(const InputParameters & parameters);

  virtual ~BMag() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _PhiM_grad;

};

#endif /* BMAG_H */
