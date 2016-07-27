#include "BxCurlA.h"

template<>

InputParameters validParams<BxCurlA>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Ax", "x component vector potential");
  params.addRequiredCoupledVar("Ay", "y component vector potential");
  params.addRequiredCoupledVar("Az", "z component vector potential");
  return params;
}


BxCurlA::BxCurlA(const InputParameters & parameters) :
  AuxKernel(parameters),
   _Ax_grad(coupledGradient("Ax")),
   _Ay_grad(coupledGradient("Ay")),
   _Az_grad(coupledGradient("Az"))
{
}

Real
BxCurlA::computeValue()

{
    return _Az_grad[_qp](1) - _Ay_grad[_qp](2);
}
