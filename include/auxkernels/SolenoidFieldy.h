#ifndef SOLENOIDFIELDY_H
#define SOLENOIDFIELDY_H

#include "AuxKernel.h"

//Forward declarations
class SolenoidFieldy;

template<>
InputParameters validParams<SolenoidFieldy>();

class SolenoidFieldy : public AuxKernel
{
public:
  SolenoidFieldy(const InputParameters & parameters);

  virtual ~SolenoidFieldy() {}

protected:
  virtual Real computeValue();

private:
  const Real _N, _a, _i, _loc_x, _loc_y, _loc_z, _mu, _translation_direction, _solenoid_height;

};

#endif /* SolenoidFieldy_H */
