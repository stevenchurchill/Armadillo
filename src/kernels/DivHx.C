#include "DivHx.h"

template<>
InputParameters validParams<DivHx>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("Hx", "Magnetic Field_x");
  params.addRequiredCoupledVar("Hy", "Magnetic Field_y");
  params.addRequiredCoupledVar("Hz", "Magnetic Field_z");

  return params;
}

DivHx::DivHx(const InputParameters & parameters) :
  Kernel(parameters),
   _Hx_var(coupled("Hx")),
   _Hy_var(coupled("Hy")),
   _Hz_var(coupled("Hz")),
   _Hx(coupledValue("Hx")),
   _Hy(coupledValue("Hy")),
   _Hz(coupledValue("Hz")),
   _Hx_grad(coupledGradient("Hx")),
   _Hy_grad(coupledGradient("Hy")),
   _Hz_grad(coupledGradient("Hz"))
{
}

Real DivHx::computeQpResidual()
{
  return _test[_i][_qp]*( _Hx_grad[_qp](0) + _Hy_grad[_qp](1) + _Hz_grad[_qp](2));
}

Real DivHx::computeQpJacobian()
{
  return _test[_i][_qp]*( _grad_phi[_j][_qp](0));
}

Real
DivHx::computeQpOffDiagJacobian(unsigned int jvar)
{
    Real a = 0.0;
    if (jvar == _Hy_var)
    {
       a += _test[_i][_qp] * _grad_phi[_j][_qp](1);
       return a;
    }
    else if (jvar == _Hz_var)
    {
       a += _test[_i][_qp] * _grad_phi[_j][_qp](2);
       return a;
    }
    else
       return 0.0;
}


