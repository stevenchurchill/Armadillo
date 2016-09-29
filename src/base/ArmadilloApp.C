#include "ArmadilloApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "Laplace.h"
#include "LaplaceMat.h"
#include "BxFieldAux.h"
#include "ByFieldAux.h"
#include "BzFieldAux.h"
#include "BMag.h"
#include "ExternalFieldx.h"
#include "ExternalFieldy.h"
#include "ExternalFieldz.h"
#include "HMag.h"

#include "MuMag.h"
#include "MuMagSquared.h"

#include "FarFieldBC.h"

#include "PoissonAx.h"
#include "PoissonAy.h"
#include "PoissonAz.h"

#include "CircularWireFieldx.h"
#include "CircularWireFieldy.h"
#include "CircularWireFieldz.h"

#include "SolenoidFieldx.h"
#include "SolenoidFieldy.h"
#include "SolenoidFieldz.h"

#include "DivASplit.h"

#include "DivHx.h"
#include "DivHy.h"
#include "DivHz.h"

#include "BxCurlA.h"
#include "ByCurlA.h"
#include "BzCurlA.h"

#include "Fx.h"
#include "Fy.h"
#include "Fz.h"


#include "fMag.h"


//Specific Modules
#include "TensorMechanicsApp.h"

template<>
InputParameters validParams<ArmadilloApp>()
{
  InputParameters params = validParams<MooseApp>();

  params.set<bool>("use_legacy_uo_initialization") = false;
  params.set<bool>("use_legacy_uo_aux_computation") = false;
  params.set<bool>("use_legacy_output_syntax") = false;

  return params;
}

ArmadilloApp::ArmadilloApp(InputParameters parameters) :
    MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  //ModulesApp::registerObjects(_factory);
  ArmadilloApp::registerObjects(_factory);

  TensorMechanicsApp::registerObjects(_factory);
  TensorMechanicsApp::associateSyntax(_syntax, _action_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  //ModulesApp::associateSyntax(_syntax, _action_factory);
  ArmadilloApp::associateSyntax(_syntax, _action_factory);
}

ArmadilloApp::~ArmadilloApp()
{
}

// External entry point for dynamic application loading
extern "C" void ArmadilloApp__registerApps() { ArmadilloApp::registerApps(); }
void
ArmadilloApp::registerApps()
{
  registerApp(ArmadilloApp);
}

// External entry point for dynamic object registration
extern "C" void ArmadilloApp__registerObjects(Factory & factory) { ArmadilloApp::registerObjects(factory); }
void
ArmadilloApp::registerObjects(Factory & factory)
{
  //Boundary Conditions
  registerBoundaryCondition(FarFieldBC); //deprecated

  //Kernels
  registerKernel(Laplace); 
  registerKernel(LaplaceMat);
  registerKernel(ExternalFieldx);  //likely deprecated
  registerKernel(ExternalFieldy);
  registerKernel(ExternalFieldz);

  registerKernel(PoissonAx);  //approach is degenerate for choice of field split Q
  registerKernel(PoissonAy);
  registerKernel(PoissonAz);

  registerKernel(DivASplit); // see above. deprecated

  registerKernel(DivHx);
  registerKernel(DivHy);
  registerKernel(DivHz);

  //Aux Kernels
  registerAuxKernel(BxFieldAux);
  registerAuxKernel(ByFieldAux);
  registerAuxKernel(BzFieldAux);

  registerAuxKernel(BxCurlA);
  registerAuxKernel(ByCurlA);
  registerAuxKernel(BzCurlA);

  registerAuxKernel(CircularWireFieldx);
  registerAuxKernel(CircularWireFieldy);
  registerAuxKernel(CircularWireFieldz);

  registerAuxKernel(SolenoidFieldx);
  registerAuxKernel(SolenoidFieldy);
  registerAuxKernel(SolenoidFieldz);

  registerAuxKernel(BMag);
  registerAuxKernel(MuMag);
  registerAuxKernel(MuMagSquared);

  registerAuxKernel(Fz);
  registerAuxKernel(Fy);
  registerAuxKernel(Fx);

  registerAuxKernel(fMag);

  registerAuxKernel(HMag);
}

// External entry point for dynamic syntax association
extern "C" void ArmadilloApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { ArmadilloApp::associateSyntax(syntax, action_factory); }
void
ArmadilloApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
