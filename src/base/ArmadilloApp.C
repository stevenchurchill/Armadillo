#include "ArmadilloApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "Laplace.h"
#include "LaplaceMat.h"
#include "BxFieldAux.h"
#include "ByFieldAux.h"
#include "BzFieldAux.h"

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
  registerKernel(Laplace); 
  registerKernel(LaplaceMat);
  registerAuxKernel(BxFieldAux);
  registerAuxKernel(ByFieldAux);
  registerAuxKernel(BzFieldAux);
}

// External entry point for dynamic syntax association
extern "C" void ArmadilloApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory) { ArmadilloApp::associateSyntax(syntax, action_factory); }
void
ArmadilloApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
