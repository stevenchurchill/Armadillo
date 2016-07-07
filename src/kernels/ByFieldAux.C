#include "ByFieldAux.h"

template<>

InputParameters validParams<ByFieldAux>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("ByVec", "y component of vector");
  return params;
}


ByFieldAux::ByFieldAux(const InputParameters & parameters) :
  AuxKernel(parameters),
   _grad_PhiM(coupledGradient("ByVec"))
{
}

Real
ByFieldAux::computeValue()

{
    return - _grad_PhiM[_qp](1);
}
