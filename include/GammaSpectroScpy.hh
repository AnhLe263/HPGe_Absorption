#ifndef GammaSpectroScpy_h
#define BGammaSpectroScpy_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
/// Detector construction class to define materials and geometry.

class GammaSpectroScpy : public G4VUserDetectorConstruction
{
  public:
    GammaSpectroScpy();
    virtual ~GammaSpectroScpy();

    virtual G4VPhysicalVolume* Construct();
    G4LogicalVolume* ModellingHPGe();
    void SetUserCylindralSample(G4double hmau=10,G4double dmau=70,G4double distance=0,G4String matName = "G4_Galactic");
    G4bool GetIsCylindral() {return isCylindral;}
    G4double GetDistance() {return fDistaneSD;}
    G4double GetHmau() {return fHmau;}
    G4double GetDmau() {return fDmau;}
    G4double GetSamplePosZ() {return fSamplePosZ;}
    
  protected:
    G4double fHSurrounding; 
    G4Material* gal_mat;
    G4Material* sample_mat;
    G4bool isCylindral;
    G4double fHmau;
    G4double fDmau;
    G4double fDistaneSD;
    G4double fSamplePosZ;
    G4LogicalVolume* Mau_Logic;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif