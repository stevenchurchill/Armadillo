#include "BxFieldAux.h"

template<>

InputParameters validParams<BxFieldAux>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("BxVec", "x component of vector");
  return params;
}


BxFieldAux::BxFieldAux(const InputParameters & parameters) :
  AuxKernel(parameters),
   _grad_PhiM(coupledGradient("BxVec"))
{
}

Real
BxFieldAux::computeValue()

{
    return - _grad_PhiM[_qp](0);
}
