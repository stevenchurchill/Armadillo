

#include "Laplace.h"

/**
 * This function defines the valid parameters for
 * this Kernel and their default values
 */
template<>
InputParameters validParams<Laplace>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredParam<Real>("mu", "magnetic susceptibility");
  return params;
}

Laplace::Laplace(const InputParameters & parameters) :
  Kernel(parameters),
   _mu(getParam<Real>("mu"))
{}

Real Laplace::computeQpResidual()
{
  return _grad_test[_i][_qp] * (_mu * _grad_u[_qp]);
}

Real Laplace::computeQpJacobian()
{
  // the partial derivative of _grad_u is just _grad_phi[_j]
  return _grad_test[_i][_qp] * (_mu * _grad_phi[_j][_qp]);
}
