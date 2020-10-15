
#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class PhysicsListMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PhysicsList: public G4VModularPhysicsList
{
  public:
    PhysicsList();
   ~PhysicsList();

    virtual void ConstructParticle();
        
    void AddPhysicsList(const G4String& name);
    virtual void ConstructProcess();
    void AddDecay();
  private:       
    G4String                      fEmName;
    G4VPhysicsConstructor*        fEmPhysicsList;    
    PhysicsListMessenger*  fMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

