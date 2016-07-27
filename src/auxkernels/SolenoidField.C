#include "SolenoidFieldx.h"

template<>

InputParameters validParams<SolenoidFieldx>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<Real>("a", "coil radius");
  params.addRequiredParam<Real>("i", "current");
  params.addRequiredParam<Real>("loc_x", "x coord location of coil");
  params.addRequiredParam<Real>("loc_y", "y coord location of coil");
  params.addRequiredParam<Real>("loc_z", "z coord location of coil");

  return params;
}


SolenoidFieldx::SolenoidFieldx(const InputParameters & parameters) :
  AuxKernel(parameters),
   _a(getParam<Real>("a")),
   _i(getParam<Real>("i")),
   _loc_x(getParam<Real>("loc_x")),
   _loc_y(getParam<Real>("loc_y")),
   _loc_z(getParam<Real>("loc_z")),
   _mu(getParam<Real>("mu"))
{

}

Real
SolenoidFieldx::computeValue()

{
    Real x = 0.0;
    Real y = 0.0;
    Real z = 0.0;
    Real r = 0.0;
    Real TH = 0.0;
    Real alpsq = 0.0;
    Real betsq = 0.0;
    Real ksq = 0.0;
    Real C = 0.0;

    x +=  _qpoint(0) - _loc_x;
    y +=  _qpoint(1) - _loc_y;
    z +=  _qpoint(2) - _loc_z;

    r +=  std::pow(std::pow(x, 2.0)+ std::pow(y, 2.0)+ std::pow(z, 2.0), 0.5);
    TH +=  std::acos(z * std::pow(r,-1));

    alpsq +=  std::pow(a,2.0) + std::pow(r,2.0) - 2 * a * r * sin(TH);
    betsq +=  std::pow(a,2.0) + std::pow(r,2.0) + 2 * a * r * sin(TH);
    ksq +=  1 -  alpsq/betsq;
    
    C =  _mu * _i / (4 * 3.14159);

    return 0.0;
}
