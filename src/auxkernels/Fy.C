#include "Fy.h"

template<>

InputParameters validParams<Fy>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("mumag", "interaction energy of applied magnetic field with soft magnet");
  return params;
}


Fy::Fy(const InputParameters & parameters) :
  AuxKernel(parameters),
   _mumag_grad(coupledGradient("mumag"))
{
}

Real
Fy::computeValue()

{
    return _mumag_grad[_qp](1);
}
