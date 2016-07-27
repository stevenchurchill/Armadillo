#include "PoissonAx.h"

template<>
InputParameters validParams<PoissonAx>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("Q", "the vector potential field split");
  params.addRequiredParam<Real>("Jx", "Current Density_x");

  return params;
}

PoissonAx::PoissonAx(const InputParameters & parameters) :
  Kernel(parameters),
   _Q_var(coupled("Q")),
   _Q(coupledValue("Q")),
   _Q_grad(coupledGradient("Q")),
   _Jx(getParam<Real>("Jx"))
{
}

Real PoissonAx::computeQpResidual()
{
  return _test[_i][_qp]*( _Q_grad[_qp](0) - _Jx);
}

Real PoissonAx::computeQpJacobian()
{
  return _test[_i][_qp] * _grad_phi[_j][_qp](0);
}


