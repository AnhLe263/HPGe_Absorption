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
    void SetUserMarinelliSample(G4double hmau=10,G4String matName = "G4_Galactic");
    G4bool GetIsCylindral() {return isCylindral;}
    G4bool GetIsMarinelli() {return isMarinelli;}
    G4double GetDistance() {return fDistaneSD;}
    G4double GetHmau() {return fHmau;}
    G4double GetHmau2() {return fHmau2;}
    G4double GetDmau() {return fDmau;}
    G4double GetDmau2() {return fDmau2;}
    G4double GetSamplePosZ() {return fSamplePosZ;}
    void ModellingMirinelli450();
    G4double GetV1Mirinelli() {return fV1Mirinelli;}
    G4double GetV2Mirinelli() {return fV2Mirinelli;}
    G4double Gett3(){return t3;}
    G4double GetW(){return W;}
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
    G4bool isMarinelli;
    G4LogicalVolume* logicWorld;
    G4double fV1Mirinelli;
    G4double fV2Mirinelli;
    G4double fHmau2;
    G4double fDmau2;
    G4double t3,W;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif