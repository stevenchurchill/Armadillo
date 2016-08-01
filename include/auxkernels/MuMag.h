#ifndef MUMAG_H
#define MUMAG_H

#include "AuxKernel.h"


//Forward declarations
class MuMag;

template<>
InputParameters validParams<MuMag>();

class MuMag : public AuxKernel
{
public:
  MuMag(const InputParameters & parameters);

  virtual ~MuMag() {}

protected:
  virtual Real computeValue();

private:
  const VariableValue & _Hx;
  const VariableValue & _Hy;
  const VariableValue & _Hz;
  const Real _A, _B, _C, _D, _E, _mu00, _mu01, _mu02, _mu10, _mu11, _mu12, _mu20, _mu21, _mu22, _mu;
};

#endif /* MUMAG_H */
