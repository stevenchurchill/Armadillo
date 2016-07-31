#include "Fz.h"

template<>

InputParameters validParams<Fz>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("mumag", "interaction energy of applied magnetic field with soft magnet");
  return params;
}


Fz::Fz(const InputParameters & parameters) :
  AuxKernel(parameters),
   _mumag_grad(coupledGradient("mumag"))
{
}

Real
Fz::computeValue()

{
    return _mumag_grad[_qp](2);
}
