#include "ExternalFieldz.h"

template<>
InputParameters validParams<ExternalFieldz>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("Hx", "Magnetic Field_x");
  params.addRequiredCoupledVar("Hy", "Magnetic Field_y");
  params.addRequiredCoupledVar("Hz", "Magnetic Field_z");
  params.addRequiredParam<Real>("Jx", "Current Density_x");
  params.addRequiredParam<Real>("Jy", "Current Density_y");
  params.addRequiredParam<Real>("Jz", "Current Density_z");


  return params;
}

ExternalFieldz::ExternalFieldz(const InputParameters & parameters) :
  Kernel(parameters),
   _Hx_var(coupled("Hx")),
   _Hy_var(coupled("Hy")),
   _Hz_var(coupled("Hz")),
   _Hx(coupledValue("Hx")),
   _Hy(coupledValue("Hy")),
   _Hz(coupledValue("Hz")),
   _Hx_grad(coupledGradient("Hx")),
   _Hy_grad(coupledGradient("Hy")),
   _Hz_grad(coupledGradient("Hz")),
   _Jx(getParam<Real>("Jx")),
   _Jy(getParam<Real>("Jy")),
   _Jz(getParam<Real>("Jz"))
{
}

Real ExternalFieldz::computeQpResidual()
{

  return _test[_i][_qp]*(_Hy_grad[_qp](0)-_Hx_grad[_qp](1) - _Jz);
}

Real ExternalFieldz::computeQpJacobian()
{

  return 0.0;
}

