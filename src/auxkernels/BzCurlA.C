#include "BzCurlA.h"

template<>

InputParameters validParams<BzCurlA>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Ax", "x component vector potential");
  params.addRequiredCoupledVar("Ay", "y component vector potential");
  params.addRequiredCoupledVar("Az", "z component vector potential");
  return params;
}


BzCurlA::BzCurlA(const InputParameters & parameters) :
  AuxKernel(parameters),
   _Ax_grad(coupledGradient("Ax")),
   _Ay_grad(coupledGradient("Ay")),
   _Az_grad(coupledGradient("Az"))
{
}

Real
BzCurlA::computeValue()

{
    return _Ay_grad[_qp](0) - _Ax_grad[_qp](1);
}
