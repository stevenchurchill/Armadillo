#include "ByCurlA.h"

template<>

InputParameters validParams<ByCurlA>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Ax", "x component vector potential");
  params.addRequiredCoupledVar("Ay", "y component vector potential");
  params.addRequiredCoupledVar("Az", "z component vector potential");
  return params;
}


ByCurlA::ByCurlA(const InputParameters & parameters) :
  AuxKernel(parameters),
   _Ax_grad(coupledGradient("Ax")),
   _Ay_grad(coupledGradient("Ay")),
   _Az_grad(coupledGradient("Az"))
{
}

Real
ByCurlA::computeValue()

{
    return _Ax_grad[_qp](2) - _Az_grad[_qp](0);
}
