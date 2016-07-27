#ifndef CIRCULARWIREFIELDY_H
#define CIRCULARWIREFIELDY_H

#include "AuxKernel.h"

//Forward declarations
class CircularWireFieldy;

template<>
InputParameters validParams<CircularWireFieldy>();

class CircularWireFieldy : public AuxKernel
{
public:
  CircularWireFieldy(const InputParameters & parameters);

  virtual ~CircularWireFieldy() {}

protected:
  virtual Real computeValue();

private:
  const Real _a, _i, _loc_x, _loc_y, _loc_z, _mu;

};

#endif /* CircularWireFieldy_H */
