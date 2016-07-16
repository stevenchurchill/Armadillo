#include "BxFieldAux.h"

template<>

InputParameters validParams<BxFieldAux>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("PhiM", "potential");
  return params;
}


BxFieldAux::BxFieldAux(const InputParameters & parameters) :
  AuxKernel(parameters),
   _PhiM_grad(coupledGradient("PhiM"))
{
}

Real
BxFieldAux::computeValue()

{
    return - _PhiM_grad[_qp](0);
}
