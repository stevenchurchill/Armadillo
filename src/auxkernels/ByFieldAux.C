#include "ByFieldAux.h"

template<>

InputParameters validParams<ByFieldAux>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("PhiM", "potential");
  return params;
}


ByFieldAux::ByFieldAux(const InputParameters & parameters) :
  AuxKernel(parameters),
   _PhiM_grad(coupledGradient("PhiM"))
{
}

Real
ByFieldAux::computeValue()

{
    return - _PhiM_grad[_qp](1);
}
