#ifndef FMAG_H
#define FMAG_H

#include "AuxKernel.h"


//Forward declarations
class fMag;

template<>
InputParameters validParams<fMag>();

class fMag : public AuxKernel
{
public:
  fMag(const InputParameters & parameters);

  virtual ~fMag() {}

protected:
  virtual Real computeValue();

private:
  const VariableGradient & _mumag_grad;


};

#endif /* FMAG_H */
