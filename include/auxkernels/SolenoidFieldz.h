#ifndef SOLENOIDFIELDZ_H
#define SOLENOIDFIELDZ_H

#include "AuxKernel.h"

//Forward declarations
class SolenoidFieldz;

template<>
InputParameters validParams<SolenoidFieldz>();

class SolenoidFieldz : public AuxKernel
{
public:
  SolenoidFieldz(const InputParameters & parameters);

  virtual ~SolenoidFieldz() {}

protected:
  virtual Real computeValue();

private:
  const Real _N, _a, _i, _loc_x, _loc_y, _loc_z, _mu, _translation_param, _solenoidal_height;

};

#endif /* SolenoidFieldz_H */
