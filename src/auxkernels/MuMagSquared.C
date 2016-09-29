#include "MuMagSquared.h"



template<>

InputParameters validParams<MuMagSquared>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Hx", "x component applied field");
  params.addRequiredCoupledVar("Hy", "y component applied field");
  params.addRequiredCoupledVar("Hz", "z component applied field");
  params.addRequiredParam<Real>("A", "fit param 1");
  params.addRequiredParam<Real>("B", "fit param 2");
  params.addRequiredParam<Real>("C", "fit param 3");
  params.addRequiredParam<Real>("D", "fit param 4");
  params.addRequiredParam<Real>("E", "fit param 5");
  params.addParam<Real>("mu00", 0.0, "magnetic susceptibility00");
  params.addParam<Real>("mu01", 0.0, "magnetic susceptibility01");
  params.addParam<Real>("mu02", 0.0, "magnetic susceptibility02");
  params.addParam<Real>("mu10", 0.0, "magnetic susceptibility10");
  params.addParam<Real>("mu11", 0.0, "magnetic susceptibility11");
  params.addParam<Real>("mu12", 0.0, "magnetic susceptibility12");
  params.addParam<Real>("mu20", 0.0, "magnetic susceptibility20");
  params.addParam<Real>("mu21", 0.0, "magnetic susceptibility21");
  params.addParam<Real>("mu22", 0.0, "magnetic susceptibility22");
  params.addRequiredParam<Real>("mu", "medium magnetic susceptibility");
  return params;
}


MuMagSquared::MuMagSquared(const InputParameters & parameters) :
  AuxKernel(parameters),
   _Hx(coupledValue("Hx")),
   _Hy(coupledValue("Hy")),
   _Hz(coupledValue("Hz")),
   _A(getParam<Real>("A")),
   _B(getParam<Real>("B")),
   _C(getParam<Real>("C")),
   _D(getParam<Real>("D")),
   _E(getParam<Real>("E")),
   _mu00(getParam<Real>("mu00")),
   _mu01(getParam<Real>("mu01")),
   _mu02(getParam<Real>("mu02")),
   _mu10(getParam<Real>("mu10")),
   _mu11(getParam<Real>("mu11")),
   _mu12(getParam<Real>("mu12")),
   _mu20(getParam<Real>("mu20")),
   _mu21(getParam<Real>("mu21")),
   _mu22(getParam<Real>("mu22")),
   _mu(getParam<Real>("mu"))
{
  std::cout<<"First, calculating the field from a coil located at loc_x, loc_y, loc_z"<<"\n";
  std::cout<<"Next, calculating the field from  "<<"\n";
  std::cout<<"Note, we are using MOOSE's API and the 'solve' is pointless!"<<"\n";
}

Real
MuMagSquared::computeValue()

{
//(_Hx[_qp] * _Hx[_qp] * _mu00 + _Hx[_qp] * _Hy[_qp] * _mu01 + _Hx[_qp] * _Hz[_qp] * _mu02 + _Hx[_qp] * _Hy[_qp] * _mu10 + _Hy[_qp] * _Hy[_qp] * _mu11 + _Hz[_qp] * _Hy[_qp] * _mu12 + _Hx[_qp] * _Hz[_qp] * _mu20 + _Hz[_qp] * _Hy[_qp] * _mu21 + _Hz[_qp] * _Hz[_qp] *_mu22);

    Real M = 0.0;
    Real x = std::pow(std::pow(_Hz[_qp] / _mu, 2.0), 0.5);
    M += _A * std::tanh(_B * ( x + _C ) + _D) + _E;
    return std::pow(M, 2)/(2*_mu);
}
