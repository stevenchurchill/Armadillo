#include "fMag.h"

template<>

InputParameters validParams<fMag>()

{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("mumag", "interaction energy of applied magnetic field with soft magnet");
  return params;
}


fMag::fMag(const InputParameters & parameters) :
  AuxKernel(parameters),
   _mumag_grad(coupledGradient("mumag"))
{
}

Real
fMag::computeValue()

{
    return std:std::pow(_mumag_grad[_qp](2), 2.0),0.5);
}
