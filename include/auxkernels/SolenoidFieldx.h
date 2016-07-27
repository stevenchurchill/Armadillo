#ifndef SOLENOIDFIELDX_H
#define SOLENOIDFIELDX_H

#include "AuxKernel.h"

//Forward declarations
class SolenoidFieldx;

template<>
InputParameters validParams<SolenoidFieldx>();

class SolenoidFieldx : public AuxKernel
{
public:
  SolenoidFieldx(const InputParameters & parameters);

  virtual ~SolenoidFieldx() {}

protected:
  virtual Real computeValue();

private:
  const Real _N, _a, _i, _loc_x, _loc_y, _loc_z, _mu, _translation_param, _solenoidal_height;

};

#endif /* SolenoidFieldx_H */
