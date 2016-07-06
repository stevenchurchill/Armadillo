

#include "LaplaceMat2.h"


template<>
InputParameters validParams<LaplaceMat2>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("mu00", "sphere magnetic susceptibility00");
  params.addRequiredParam<Real>("mu01", "sphere magnetic susceptibility01");
  params.addRequiredParam<Real>("mu02", "sphere magnetic susceptibility02");
  params.addRequiredParam<Real>("mu10", "sphere magnetic susceptibility10");
  params.addRequiredParam<Real>("mu11", "sphere magnetic susceptibility11");
  params.addRequiredParam<Real>("mu12", "sphere magnetic susceptibility12");
  params.addRequiredParam<Real>("mu20", "sphere magnetic susceptibility20");
  params.addRequiredParam<Real>("mu21", "sphere magnetic susceptibility21");
  params.addRequiredParam<Real>("mu22", "sphere magnetic susceptibility22");

  return params;
}

LaplaceMat2::LaplaceMat2(const InputParameters & parameters) :
  Kernel(parameters),
   _mu00(getParam<Real>("mu00")),
   _mu01(getParam<Real>("mu01")),
   _mu02(getParam<Real>("mu02")),
   _mu10(getParam<Real>("mu10")),
   _mu11(getParam<Real>("mu11")),
   _mu12(getParam<Real>("mu12")),
   _mu20(getParam<Real>("mu20")),
   _mu21(getParam<Real>("mu21")),
   _mu22(getParam<Real>("mu22"))
{
}

Real LaplaceMat2::computeQpResidual()
{

  return _grad_test[_i][_qp](0)*_mu00*_grad_u[_qp](0)+_grad_test[_i][_qp](1)*_mu10*_grad_u[_qp](0)+_grad_test[_i][_qp](2)*_mu20*_grad_u[_qp](0)+_grad_test[_i][_qp](0)*_mu01*_grad_u[_qp](1)+_grad_test[_i][_qp](1)*_mu11*_grad_u[_qp](1)+_grad_test[_i][_qp](2)*_mu21*_grad_u[_qp](1)+_grad_test[_i][_qp](0)*_mu02*_grad_u[_qp](2)+_grad_test[_i][_qp](1)*_mu12*_grad_u[_qp](2)+_grad_test[_i][_qp](2)*_mu22*_grad_u[_qp](2);
}

Real LaplaceMat2::computeQpJacobian()
{

  return _grad_test[_i][_qp](0)*_mu00*_grad_phi[_j][_qp](0)+_grad_test[_i][_qp](1)*_mu10*_grad_phi[_j][_qp](0)+_grad_test[_i][_qp](2)*_mu20*_grad_phi[_j][_qp](0)+_grad_test[_i][_qp](0)*_mu01*_grad_phi[_j][_qp](1)+_grad_test[_i][_qp](1)*_mu11*_grad_phi[_j][_qp](1)+_grad_test[_i][_qp](2)*_mu21*_grad_phi[_j][_qp](1)+_grad_test[_i][_qp](0)*_mu02*_grad_phi[_j][_qp](2)+_grad_test[_i][_qp](1)*_mu12*_grad_phi[_j][_qp](2)+_grad_test[_i][_qp](2)*_mu22*_grad_phi[_j][_qp](2);
}



