

#include "laplace.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<laplace>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("mu", "mu (variable)");
  return params;
}

laplace::laplace(const InputParameters & parameters) :
  Kernel(parameters),
   _mu(getParam<Real>("mu"))
{}

Real laplace::computeQpResidual()
{
  // mu * _grad_u[_qp] is actually doing a dot product
  return _grad_test[_i][_qp]*(_mu*_grad_u[_qp]);
}

Real laplace::computeQpJacobian()
{
  // the partial derivative of _grad_u is just _grad_phi[_j]
  return _grad_test[_i][_qp]*(_mu*_grad_phi[_j][_qp]);
}
