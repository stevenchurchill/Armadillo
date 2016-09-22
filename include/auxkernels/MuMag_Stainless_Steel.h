#ifndef MUMAG_STAINLESS_STEEL_H
#define MUMAG_STAINLESS_STEEL_H

#include "AuxKernel.h"


//Forward declarations
class MuMag_Stainless_Steel;

template<>
InputParameters validParams<MuMag_Stainless_Steel>();

class MuMag_Stainless_Steel : public AuxKernel
{
public:
  MuMag_Stainless_Steel(const InputParameters & parameters);

  virtual ~MuMag_Stainless_Steel() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _Hx;
  const VariableValue & _Hy;
  const VariableValue & _Hz;
  const Real _A, _B, _C, _D, _E, _mu00, _mu01, _mu02, _mu10, _mu11, _mu12, _mu20, _mu21, _mu22, _mu;
};

#endif /* MUMAG_STAINLESS_STEEL_H */
