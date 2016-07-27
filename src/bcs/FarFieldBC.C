/************************************************************************/
/* FarField BC:                                                         */
/*     This BC is intended to implement |B0| -> 0   at a boundary.      */
/************************************************************************/

#include "FarFieldBC.h"

template<>
InputParameters validParams<FarFieldBC>()
{
  InputParameters params = validParams<IntegratedBC>();
  params.addRequiredCoupledVar("Ax", "x component vector potential");
  params.addRequiredCoupledVar("Ay", "y component vector potential");
  params.addRequiredCoupledVar("Az", "z component vector potential");
  return params;
}

FarFieldBC::FarFieldBC(const InputParameters & parameters) :
  IntegratedBC(parameters),
   _Ax_grad(coupledGradient("Ax")),
   _Ay_grad(coupledGradient("Ay")),
   _Az_grad(coupledGradient("Az"))
{
}

Real
FarFieldBC::computeQpResidual()
{
  return std::pow(_Ay_grad[_qp](0) - _Ax_grad[_qp](1), 2.0) + std::pow(_Ax_grad[_qp](2) - _Az_grad[_qp](0), 2.0) + std::pow((_Ay_grad[_qp](0) - _Ax_grad[_qp](1)), 2.0);
}
