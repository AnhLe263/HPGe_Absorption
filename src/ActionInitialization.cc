#include "ActionInitialization.hh"
#include "GammaSource.hh"
#include "RunAction.hh"
#include "eventaction.hh"
#include "steppingaction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization(GammaSpectroScpy* det)
 : G4VUserActionInitialization(), fDet(det)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  SetUserAction(new GammaSource(fDet));

  RunAction* runAction = new RunAction;
  SetUserAction(runAction);
  
  eventaction* eventAction = new eventaction();
  SetUserAction(eventAction);
  
  SetUserAction(new steppingaction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......