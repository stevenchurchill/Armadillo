#include "BMag.h"

template<>

InputParameters validParams<BMag>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addCoupledVar("PhiM", "potential");
  return params;
}


BMag::BMag(const InputParameters & parameters) :
  AuxKernel(parameters),
   _PhiM_grad(coupledGradient("potential"))
{
}

Real
BMag::computeValue()

{
    return std::pow(_PhiM_grad[_qp](0) * _PhiM_grad[_qp](0)+_PhiM_grad[_qp](1) * _PhiM_grad[_qp](1) + _PhiM_grad[_qp](2) * _PhiM_grad[_qp](2),0.5);
}
