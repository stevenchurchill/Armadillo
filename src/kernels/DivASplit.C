#include "DivASplit.h"

template<>
InputParameters validParams<DivASplit>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("Ax", "x component vector potential");
  params.addRequiredCoupledVar("Ay", "y component vector potential");
  params.addRequiredCoupledVar("Az", "z component vector potential");
  params.addRequiredCoupledVar("Q", "the vector potential field split");

  return params;
}

DivASplit::DivASplit(const InputParameters & parameters) :
  Kernel(parameters),
   _Ax_var(coupled("Ax")),
   _Ay_var(coupled("Ay")),
   _Az_var(coupled("Az")),
   _Ax(coupledValue("Ax")),
   _Ay(coupledValue("Ay")),
   _Az(coupledValue("Az")),
   _Ax_grad(coupledGradient("Ax")),
   _Ay_grad(coupledGradient("Ay")),
   _Az_grad(coupledGradient("Az")),
   _Q(coupledValue("Q"))
{
}

Real DivASplit::computeQpResidual()
{
  return _test[_i][_qp]*( _Ax_grad[_qp](0) + _Ay_grad[_qp](1) + _Az_grad[_qp](2)  -   _Q[_qp]);
}

Real DivASplit::computeQpJacobian()
{
  return - _test[_i][_qp] * _phi[_j][_qp];
}

Real
DivASplit::computeQpOffDiagJacobian(unsigned int jvar)
{
    Real a = 0.0;
    if (jvar == _Ax_var)
    {
       a += _test[_i][_qp] * _grad_phi[_j][_qp](0);
       return a;
    }
    else if (jvar == _Ay_var)
    {
       a += _test[_i][_qp] * _grad_phi[_j][_qp](1);
       return a;
    }
    else if (jvar == _Az_var)
    {
       a += _test[_i][_qp] * _grad_phi[_j][_qp](2);
       return a;
    }
    else
       return 0.0;
}


