#include "ExternalFieldx.h"

template<>
InputParameters validParams<ExternalFieldx>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("H_x", "Magnetic Field_x");
  params.addRequiredCoupledVar("H_y", "Magnetic Field_y");
  params.addRequiredCoupledVar("H_z", "Magnetic Field_z");
  params.addRequiredParam<Real>("J_x", "Current Density_x");
  params.addRequiredParam<Real>("J_y", "Current Density_y");
  params.addRequiredParam<Real>("J_z", "Current Density_z");


  return params;
}

ExternalFieldx::ExternalFieldx(const InputParameters & parameters) :
  Kernel(parameters),
   _H_x(coupledValue("H_x")),
   _H_y(coupledValue("H_y")),
   _H_z(coupledValue("H_z")),
   _H_x_grad(coupledGradient("H_x")),
   _H_y_grad(coupledGradient("H_y")),
   _H_z_grad(coupledGradient("H_z")),
   _J_x(getParam<Real>("J_x")),
   _J_y(getParam<Real>("J_y")),
   _J_z(getParam<Real>("J_z"))
{
}

Real ExternalFieldx::computeQpResidual()
{

  return _test[_i][_qp]*((_grad_H_z[_qp](1)-_grad_H_y[_qp](2)-J_x);
}

Real ExternalFieldx::computeQpJacobian()
{

  return _test[_i][_qp]*((_grad_H_z[_qp](1)-_grad_H_y[_qp](2)-J_x);
}



