#ifndef HMAG_H
#define HMAG_H

#include "AuxKernel.h"


//Forward declarations
class HMag;

template<>
InputParameters validParams<HMag>();

class HMag : public AuxKernel
{
public:
  HMag(const InputParameters & parameters);

  virtual ~HMag() {}

protected:
  virtual Real computeValue();

private:
  const unsigned int _Hx_var;
  const unsigned int _Hy_var;
  const unsigned int _Hz_var;
  const VariableValue & _Hx;
  const VariableValue & _Hy;
  const VariableValue & _Hz;

};

#endif /* HMAG_H */
