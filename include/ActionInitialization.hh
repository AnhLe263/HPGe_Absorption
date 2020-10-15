#ifndef ActionInitialization_h
#define ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

/// Action initialization class.
class GammaSpectroScpy;
class ActionInitialization : public G4VUserActionInitialization
{
  public:
    ActionInitialization(GammaSpectroScpy* det);
    virtual ~ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
    private:
    GammaSpectroScpy * fDet;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif