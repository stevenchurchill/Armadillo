#include "PoissonAy.h"

template<>
InputParameters validParams<PoissonAy>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("Q", "the vector potential field split");
  params.addRequiredParam<Real>("Jy", "Current Density_y");

  return params;
}

PoissonAy::PoissonAy(const InputParameters & parameters) :
  Kernel(parameters),
   _Q_var(coupled("Q")),
   _Q(coupledValue("Q")),
   _Q_grad(coupledGradient("Q")),
   _Jy(getParam<Real>("Jy"))
{
}

Real PoissonAy::computeQpResidual()
{
  return _test[_i][_qp]*( _Q_grad[_qp](1) - _Jy);
}

Real PoissonAy::computeQpJacobian()
{
  return _test[_i][_qp] * _grad_phi[_j][_qp](1);
}

