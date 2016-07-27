#include "PoissonAz.h"

template<>
InputParameters validParams<PoissonAz>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("Q", "the vector potential field split");
  params.addRequiredParam<Real>("Jz", "Current Density_z");

  return params;
}

PoissonAz::PoissonAz(const InputParameters & parameters) :
  Kernel(parameters),
   _Q_var(coupled("Q")),
   _Q(coupledValue("Q")),
   _Q_grad(coupledGradient("Q")),
   _Jz(getParam<Real>("Jz"))
{
}

Real PoissonAz::computeQpResidual()
{
  return _test[_i][_qp]*( _Q_grad[_qp](2) - _Jz);
}

Real PoissonAz::computeQpJacobian()
{
  return _test[_i][_qp] * _grad_phi[_j][_qp](2);
}

