

#include "LaplaceMat.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<LaplaceMat>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("mu", "mu (variable)");
  return params;
}

LaplaceMat::LaplaceMat(const InputParameters & parameters) :
  Kernel(parameters),
   _mu(getParam<Real>("mu"))
{}

Real LaplaceMat::computeQpResidual()
{

  return (_grad_test[_i]*_grad_test[_i][_qp])*(_mu[_i][_j]*_grad_u[_qp]);
}

Real LaplaceMat::computeQpJacobian()
{

  return (_grad_test[_i]*_grad_test[_j][_qp])*(_mu[_i][_j]*_grad_phi[_j][_qp]);
}


