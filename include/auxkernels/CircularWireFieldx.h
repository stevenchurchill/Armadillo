#ifndef CIRCULARWIREFIELDX_H
#define CIRCULARWIREFIELDX_H

#include "AuxKernel.h"

//Forward declarations
class CircularWireFieldx;

template<>
InputParameters validParams<CircularWireFieldx>();

class CircularWireFieldx : public AuxKernel
{
public:
  CircularWireFieldx(const InputParameters & parameters);

  virtual ~CircularWireFieldx() {}

protected:
  virtual Real computeValue();

private:
  const Real _a, _i, _loc_x, _loc_y, _loc_z, _mu;

};

#endif /* CircularWireFieldx_H */
