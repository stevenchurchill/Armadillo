#ifndef CIRCULARWIREFIELDZ_H
#define CIRCULARWIREFIELDZ_H

#include "AuxKernel.h"

//Forward declarations
class CircularWireFieldz;

template<>
InputParameters validParams<CircularWireFieldz>();

class CircularWireFieldz : public AuxKernel
{
public:
  CircularWireFieldz(const InputParameters & parameters);

  virtual ~CircularWireFieldz() {}

protected:
  virtual Real computeValue();

private:
  const Real _a, _i, _loc_x, _loc_y, _loc_z, _mu;

};

#endif /* CircularWireFieldz_H */
