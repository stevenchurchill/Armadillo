#include "BzFieldAux.h"

template<>

InputParameters validParams<BzFieldAux>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("BzVec", "z component of vector");
  return params;
}


BzFieldAux::BzFieldAux(const InputParameters & parameters) :
  AuxKernel(parameters),
   _grad_PhiM(coupledGradient("BzVec"))
{
}

Real
BzFieldAux::computeValue()

{
    return - _grad_PhiM[_qp](2);
}
