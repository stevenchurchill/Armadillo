#include "SolenoidFieldx.h"

template<>

InputParameters validParams<SolenoidFieldx>()

{

  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<Real>("N", "number of turns");
  params.addRequiredParam<Real>("a", "coil radius");
  params.addRequiredParam<Real>("i", "current");
  params.addRequiredParam<Real>("loc_x", "x coord location of coil");
  params.addRequiredParam<Real>("loc_y", "y coord location of coil");
  params.addRequiredParam<Real>("loc_z", "z coord location of coil");
  params.addRequiredParam<Real>("mu", "susceptibility of medium");
  params.addRequiredParam<Real>("translation_param", "translation_param");
  params.addRequiredParam<Real>("solenoidal_height", "solenoidal_height");

  return params;
}


SolenoidFieldx::SolenoidFieldx(const InputParameters & parameters) :
  AuxKernel(parameters),
   _N(getParam<Real>("N")),
   _a(getParam<Real>("a")),
   _i(getParam<Real>("i")),
   _loc_x(getParam<Real>("loc_x")),
   _loc_y(getParam<Real>("loc_y")),
   _loc_z(getParam<Real>("loc_z")),
   _mu(getParam<Real>("mu")),
   _translation_param(getParam<Real>("translation_param")),
   _solenoidal_height(getParam<Real>("solenoidal_height"))
{
}

Real
SolenoidFieldx::computeValue()

{
    Real sum = 0.0;
    Real x = 0.0;
    Real y = 0.0;
    Real z = 0.0;
    Real r = 0.0;
    Real alpsq = 0.0;
    Real betsq = 0.0;
    Real ksq = 0.0;
    Real C = 0.0;
    Real rho = 0.0;
    Real pi = 3.14159;
    Real asymptotK = 0.0;
    Real asymptotE = 0.0;

    x +=  _q_point[_qp](0) - _loc_x;
    y +=  _q_point[_qp](1) - _loc_y;
    z +=  _q_point[_qp](2) - _loc_z;
  
    rho  += std::pow(x, 2.0) + std::pow(y,2.0);

    r +=  std::pow(std::pow(x, 2.0)+ std::pow(y, 2.0)+ std::pow(z, 2.0), 0.5);

    alpsq +=  std::pow(_a,2.0) + std::pow(r,2.0) - 2 * _a * r * rho;
    betsq +=  std::pow(_a,2.0) + std::pow(r,2.0) + 2 * _a * r * rho;
    ksq +=  1.0 -  alpsq/betsq;
    
    C +=  _mu * _i / (4.0 * pi);

    /// Note that we don't have C++17 support (comm. w/ D. Schwen), so the comp_ellint_1 and 2 functions don't have headers. We can use asymptotic expansions instead.
    asymptotK += pi / 2.0 +  (pi / 8.0) * (ksq / (1.0 -  ksq) ) - (pi / 16.0) * ( std::pow(ksq, 2.0) / (1.0 - ksq) );
    asymptotE += (pi / 2.0 ) * ( 1.0 - (1.0 /4.0) * std::pow(ksq, 4.0) - (9.0 / 64.0) * std::pow(ksq, 8.0) );

    return (C * x * z / (2.0 * alpsq * betsq * std::pow(rho, 2.0)) ) * (( std::pow(_a, 2.0) + std::pow(r, 2.0) ) * asymptotE - alpsq * asymptotK  );

    return sum;
}
