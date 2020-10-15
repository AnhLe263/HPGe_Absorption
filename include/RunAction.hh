#ifndef B3aRunAction_h
#define B3aRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

/// Run action class

class RunAction : public G4UserRunAction
{
  public:
    RunAction();
    virtual ~RunAction();
    
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

private:
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif