#include "DivHy.h"

template<>
InputParameters validParams<DivHy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("Hx", "Magnetic Field_x");
  params.addRequiredCoupledVar("Hy", "Magnetic Field_y");
  params.addRequiredCoupledVar("Hz", "Magnetic Field_z");

  return params;
}

DivHy::DivHy(const InputParameters & parameters) :
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

Real DivHy::computeQpResidual()
{
  return _test[_i][_qp]*( _Hx_grad[_qp](0) + _Hy_grad[_qp](1) + _Hz_grad[_qp](2));
}

Real DivHy::computeQpJacobian()
{
  return _test[_i][_qp]*( _grad_phi[_j][_qp](1));
}

Real
DivHy::computeQpOffDiagJacobian(unsigned int jvar)
{
    Real a = 0.0;
    if (jvar == _Hx_var)
    {
       a += _test[_i][_qp] * _grad_phi[_j][_qp](0);
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


