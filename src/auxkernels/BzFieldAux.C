#include "BzFieldAux.h"

template<>

InputParameters validParams<BzFieldAux>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("PhiM", "potential");
  return params;
}


BzFieldAux::BzFieldAux(const InputParameters & parameters) :
  AuxKernel(parameters),
   _PhiM_grad(coupledGradient("PhiM"))
{
}

Real
BzFieldAux::computeValue()

{
    return - _PhiM_grad[_qp](2);
}
