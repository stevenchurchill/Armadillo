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
  const VariableValue & _Bx;
  const VariableValue & _By;
  const VariableValue & _Bz;
  const Real _A, _B, _C, _D, _E, _mu;
};

#endif /* MUMAG_H */
