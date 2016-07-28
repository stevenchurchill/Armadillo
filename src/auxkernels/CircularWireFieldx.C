#include "CircularWireFieldx.h"

template<>

InputParameters validParams<CircularWireFieldx>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<Real>("a", "coil radius");
  params.addRequiredParam<Real>("i", "current");
  params.addRequiredParam<Real>("loc_x", "x coord location of wire");
  params.addRequiredParam<Real>("loc_y", "y coord location of wire");
  params.addRequiredParam<Real>("loc_z", "z coord location of wire");
  params.addRequiredParam<Real>("mu", "susceptibility of medium");
  return params;
}


CircularWireFieldx::CircularWireFieldx(const InputParameters & parameters) :
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
CircularWireFieldx::computeValue()

{
    Real x = 0.0;
    Real y = 0.0;
    Real z = 0.0;
    Real r = 0.0;
    Real alpsq = 0.0;
    Real betsq = 0.0;
    Real ksq = 0.0;
    Real C = 0.0;
    Real rho = 0.0;
    Real pi = 3.14159265359;
    Real asymptotK = 0.0;
    Real asymptotE = 0.0;
    Real sum = 0.0;

    x +=  _q_point[_qp](0) - _loc_x;
    y +=  _q_point[_qp](1) - _loc_y;
    z +=  _q_point[_qp](2) - _loc_z;
  
    rho  += std::pow(std::pow(x, 2.0) + std::pow(y, 2.0), 0.5);

    r +=  std::pow(std::pow(x, 2.0)+ std::pow(y, 2.0)+ std::pow(z, 2.0), 0.5);

    alpsq +=  std::pow(_a, 2.0) + std::pow(r, 2.0) - 2 * _a * rho;
    betsq +=  std::pow(_a, 2.0) + std::pow(r, 2.0) + 2 * _a * rho;
    ksq +=  1.0 -  alpsq/betsq;
    
    C +=  _mu * _i / (pi);

    /// Note that we don't have C++17 support (comm. w/ D. Schwen), so the coksqp_ellint_1 and 2 functions don't have headers. We can use asyksqptotic expansions instead.
    asymptotK += pi/2.0 + (pi * ksq)/8.0 + (9 *pi *std::pow(ksq,2.0))/128.0 + ( 25.0*pi* std::pow(ksq,3.0))/512.0 + (1225.0 *pi* std::pow(ksq,4.0))/32768.0 + ( 3969.0 *pi *std::pow(ksq,5.0))/131072.0 + (53361.0* pi *std::pow(ksq,6.0))/2097152.0 + ( 184041.0 *pi* std::pow(ksq,7.0))/8388608.0 + (41409225.0* pi *std::pow(ksq,8.0))/2147483648.0;
    asymptotE += pi/2.0 - (pi *ksq)/8.0 - (3.0* pi* std::pow(ksq,2.0))/128.0 - (5 * pi * std::pow(ksq,3.0))/512.0 - ( 175.0 *pi* std::pow(ksq,4.0))/32768.0 - (441.0* pi* std::pow(ksq,5.0))/131072.0 - ( 4851.0 *pi *std::pow(ksq,6.0))/2097152.0 - (14157.0* pi * std::pow(ksq,7.0))/8388608 - ( 2760615 * pi * std::pow(ksq,8.0))/2147483648.0;

    sum += (C * x * z / (2.0 * alpsq * std::pow(betsq, 0.5) * std::pow(rho, 2.0)) ) * (( std::pow(_a, 2.0) + std::pow(r, 2.0) ) * asymptotK - alpsq * asymptotE  );
    return sum;
}
