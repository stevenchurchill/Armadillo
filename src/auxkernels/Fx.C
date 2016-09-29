#include "Fx.h"

template<>

InputParameters validParams<Fx>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("mumag", "interaction energy of applied magnetic field with soft magnet");
  return params;
}


Fx::Fx(const InputParameters & parameters) :
  AuxKernel(parameters),
   _mumag_grad(coupledGradient("mumag"))

{
}

Real
Fx::computeValue()

{
    return _mumag_grad[_qp](0);
}
