#include "ExternalField.h"

template<>
InputParameters validParams<ExternalField>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("H_x", "Magnetic Field_x");
  params.addRequiredParam<Real>("H_y", "Magnetic Field_y");
  params.addRequiredParam<Real>("H_z", "Magnetic Field_z");
  params.addRequiredParam<Real>("J_x", "Current Density_x");

  return params;
}

ExternalField::ExternalField(const InputParameters & parameters) :
  Kernel(parameters),
   _H_x(getParam<Real>("H_x")),
   _H_y(getParam<Real>("H_y")),
   _H_z(getParam<Real>("H_z")),
   _J_x(getParam<Real>("J_x"))
{
}

Real ExternalField::computeQpResidual()
{

  return _grad_test[_i][_qp](0)*(_H_z*_grad_u[_qp](1)-_H_y*_grad_u[_qp](2))+_grad_test[_i][_qp](1)*(_H_x*_grad_u[_qp](2)-_H_z*_grad_u[_qp](0))+_grad_test[_i][_qp](2)*(_H_y*_grad_u[_qp](0)-_H_x*_grad_u[_qp](1))-_J_x;
}

Real ExternalField::computeQpJacobian()
{

  return _grad_test[_i][_qp](0)*(_H_z*_grad_phi[_j][_qp](1)-_H_y*_grad_phi[_j][_qp](2))+_grad_test[_i][_qp](1)*(_H_x*_grad_phi[_j][_qp](2)-_H_z*_grad_phi[_j][_qp](0))+_grad_test[_i][_qp](2)*(_H_y*_grad_phi[_j][_qp](0)-_H_x*_grad_phi[_j][_qp](1))-_J_x;
}



