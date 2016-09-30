#include "MuMag.h"


//This auxkernel calculates the residual magnetic field at a point based on the magnitude of the applied field
//The fit is done in Mathematica for the CoFe  (vacoflux17 material).
//This file should be generalized for any of the materials they have.

template<>

InputParameters validParams<MuMag>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Bx", "x component applied magnetic flux field");
  params.addRequiredCoupledVar("By", "y component applied magnetic flux field");
  params.addRequiredCoupledVar("Bz", "z component applied magnetic flux field");
  params.addRequiredParam<Real>("A", "fit param 1");
  params.addRequiredParam<Real>("B", "fit param 2");
  params.addRequiredParam<Real>("C", "fit param 3");
  params.addRequiredParam<Real>("D", "fit param 4");
  params.addRequiredParam<Real>("E", "fit param 5");
  params.addRequiredParam<Real>("mu", "medium magnetic susceptibility");
  return params;
}


MuMag::MuMag(const InputParameters & parameters) :
  AuxKernel(parameters),
   _Bx(coupledValue("Bx")),
   _By(coupledValue("By")),
   _Bz(coupledValue("Bz")),
   _A(getParam<Real>("A")),
   _B(getParam<Real>("B")),
   _C(getParam<Real>("C")),
   _D(getParam<Real>("D")),
   _E(getParam<Real>("E")),
   _mu(getParam<Real>("mu"))
{
  std::cout<<"First, calculating the field from a coil located at loc_x, loc_y, loc_z"<<"\n";
  std::cout<<"Next, calculating the field from  "<<"\n";
  std::cout<<"Note, we are using MOOSE's API and the 'solve' is pointless!"<<"\n";
}

Real
MuMag::computeValue()

{
//(_Hx[_qp] * _Hx[_qp] * _mu00 + _Hx[_qp] * _Hy[_qp] * _mu01 + _Hx[_qp] * _Hz[_qp] * _mu02 + _Hx[_qp] * _Hy[_qp] * _mu10 + _Hy[_qp] * _Hy[_qp] * _mu11 + _Hz[_qp] * _Hy[_qp] * _mu12 + _Hx[_qp] * _Hz[_qp] * _mu20 + _Hz[_qp] * _Hy[_qp] * _mu21 + _Hz[_qp] * _Hz[_qp] *_mu22);

    Real m = 0.0;
    Real h = _Bz[_qp] / _mu;
    m += _A * std::tanh(_B * ( h + _C ) + _D) + _E;
    return (_Bz[_qp] ) * m - (1.0 / _mu) * m * m;
}
