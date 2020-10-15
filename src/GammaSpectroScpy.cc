#include "GammaSpectroScpy.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaSpectroScpy::GammaSpectroScpy()
: G4VUserDetectorConstruction()
{ 
    isCylindral = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaSpectroScpy::~GammaSpectroScpy()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
G4VPhysicalVolume* GammaSpectroScpy::Construct()
{  
  //Cleanup old geometry 
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance(); 
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 15.*cm;
  G4double world_sizeZ  = 15.*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");
  gal_mat = nist->FindOrBuildMaterial("G4_Galactic");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  
  G4LogicalVolume* WholeDet_Logic = ModellingHPGe();
  new G4PVPlacement(0,G4ThreeVector(),WholeDet_Logic,"WholeDet",logicWorld,false,0,checkOverlaps);

  // hop mau
    if (isCylindral)
    {
        G4Tubs *Mau_Solid = new G4Tubs("Sample",0,fDmau/2.,fHmau/2.,0.*deg,360*deg);
        Mau_Logic = new G4LogicalVolume(Mau_Solid,sample_mat,"Sample");
        fSamplePosZ = -(fHSurrounding/2. + fHmau/2.) + fDistaneSD;
        new G4PVPlacement(0,G4ThreeVector(0,0,fSamplePosZ),Mau_Logic,"Sample",logicWorld,false,0,true);
    }
  //
  //always return the physical World
  //
  return physWorld;
}

G4LogicalVolume* GammaSpectroScpy::ModellingHPGe()
{
    G4double F = 94.*mm;//Cup Length
    G4double G = 3.*mm;//Space 
    G4double I = 1.*mm; //Al
    fHSurrounding = F + G+ I;
    G4double fDEndCap = 70.*mm;// endcap Diameter
    G4NistManager* nist = G4NistManager::Instance(); 
    G4Material* Al_mat = nist->FindOrBuildMaterial("G4_Al");
    G4double phiV = 360*deg;
    // Tao hinh tru chua tat ca
    G4Tubs *WholeDet_Solid = new G4Tubs("WholeDet",0.,fDEndCap/2.,fHSurrounding/2.,0.*deg,phiV);
    G4LogicalVolume* WholeDet_Logic = new G4LogicalVolume(WholeDet_Solid,gal_mat,"WholeDet");

    // Endcap
    G4Tubs *Encap_Solid = new G4Tubs("Endcap",0,fDEndCap/2.,I/2.,0.*deg,phiV);
    G4LogicalVolume* Endcap_Logic = new G4LogicalVolume(Encap_Solid,Al_mat,"Endcap");
    G4double Encap_posZ = -(fHSurrounding/2.-I + I/2.);
    new G4PVPlacement(0,G4ThreeVector(0,0,Encap_posZ),Endcap_Logic,"Endcap",WholeDet_Logic,false,0,true);
    //Surounding-Al
    
    G4Tubs *AlSurounding_Solid = new G4Tubs("AlSurounding",fDEndCap/2.-I,fDEndCap/2.,(fHSurrounding-I)/2.,0.*deg,phiV);
    G4double AlSurounding_posZ = I/2.;
    G4LogicalVolume* AlSurounding_Logic = new G4LogicalVolume(AlSurounding_Solid,Al_mat,"AlSurounding");
    new G4PVPlacement(0,G4ThreeVector(0,0,AlSurounding_posZ),AlSurounding_Logic,"AlSurounding",WholeDet_Logic,false,0,true);
    
    // Al stick to Mylar
    G4double H = 0.03*mm;
    G4double DAlMyla = 60.*mm;
    G4Tubs *AlStickMylar_Solid = new G4Tubs("AlStickMylar",0,DAlMyla/2.,H/2.,0.*deg,phiV);
    G4double AlStickMylar_posZ = -(fHSurrounding/2. - I -G - H + H/2);
    G4LogicalVolume* AlStickMylar_Logic = new G4LogicalVolume(AlStickMylar_Solid,Al_mat,"AlStickMylar");
    new G4PVPlacement(0,G4ThreeVector(0,0,AlStickMylar_posZ),AlStickMylar_Logic,"AlStickMylar",WholeDet_Logic,false,0,true);
    //Mylar 
    G4Material* Mylar_mat = nist->FindOrBuildMaterial("G4_MYLAR");
    G4Tubs *Mylar_Solid = new G4Tubs("Mylar",0,DAlMyla/2.,H/2.,0.*deg,phiV);
    G4double Mylar_posZ = -(fHSurrounding/2. - I -G - 2*H + H/2);
    G4LogicalVolume* Mylar_Logic = new G4LogicalVolume(Mylar_Solid,Mylar_mat,"Mylar");
    new G4PVPlacement(0,G4ThreeVector(0,0,Mylar_posZ),Mylar_Logic,"Mylar",WholeDet_Logic,false,0,true);

    // Inner Alsurounding
    G4double K = 0.8*mm;
    G4double HInnerAlsurounding = fHSurrounding - I -G -2*H;
    G4Tubs *InnerAlSurounding_Solid = new G4Tubs("InnerAlSurounding",DAlMyla/2.-K,DAlMyla/2.,HInnerAlsurounding/2.,0.*deg,phiV);
    G4double InnerAlSurounding_posZ = (I+G+2*H)/2;
    G4LogicalVolume* InnerAlSurounding_Logic = new G4LogicalVolume(InnerAlSurounding_Solid,Al_mat,"InnerAlSurounding");
    new G4PVPlacement(0,G4ThreeVector(0,0,InnerAlSurounding_posZ),InnerAlSurounding_Logic,"InnerAlSurounding",WholeDet_Logic,false,0,true);

    // Volume containe Ge
    G4double B = 54.7*mm;
    G4double M = 0.7*mm; // Ge/Li Deadlayer
    G4double N = 0.3*um; //Ge/B Deadlayer
    G4Material* Li_mat = nist->FindOrBuildMaterial("G4_Li");
    G4Material* B_mat = nist->FindOrBuildMaterial("G4_B");
    G4double A = 53.*mm;
    G4Tubs *WholeGePart_Solid = new G4Tubs("WholeGePart",0,A/2.,B/2.,0.*deg,phiV);
    G4double WholeGePart_posZ = -(fHSurrounding/2. - I - G - 2*H - B +B/2.);
    G4LogicalVolume* WholeGePart_Logic = new G4LogicalVolume(WholeGePart_Solid,gal_mat,"WholeGePart");
    new G4PVPlacement(0,G4ThreeVector(0,0,WholeGePart_posZ),WholeGePart_Logic,"WholeGePart",WholeDet_Logic,false,0,true);
    
    // Dead layer on top
    G4Tubs *DeadTop_Solid = new G4Tubs("DeadTop",0,A/2.,M/2.,0.*deg,phiV);
    G4double DeadTop_posZ = -(B/2.-M+M/2.);
    G4LogicalVolume* DeadTop_Logic = new G4LogicalVolume(DeadTop_Solid,Li_mat,"DeadTop");
    new G4PVPlacement(0,G4ThreeVector(0,0,DeadTop_posZ),DeadTop_Logic,"DeadTop",WholeGePart_Logic,false,0,true);
    
    // Dead layer suroungding Ge
    
    G4double HGe = B - M;
    G4Tubs *Deadsuroungding_Solid = new G4Tubs("Deadsuroungding",A/2-M,A/2.,HGe/2.,0.*deg,phiV);
    G4double Deadsuroungding_posZ = -(B/2.-M - HGe + HGe/2.);
    G4LogicalVolume* Deadsuroungding_Logic = new G4LogicalVolume(Deadsuroungding_Solid,Li_mat,"Deadsuroungding");
    new G4PVPlacement(0,G4ThreeVector(0,0,Deadsuroungding_posZ),Deadsuroungding_Logic,"Deadsuroungding",WholeGePart_Logic,false,0,true);

    // Ge
    G4Material* Ge_mat = nist->FindOrBuildMaterial("G4_Ge");
    G4Tubs *Ge_Solid = new G4Tubs("Ge",0,A/2.-M,HGe/2.,0.*deg,phiV);
    G4double Ge_posZ = -(B/2.-M - HGe + HGe/2.);
    G4LogicalVolume* Ge_Logic = new G4LogicalVolume(Ge_Solid,Ge_mat,"Ge");
    new G4PVPlacement(0,G4ThreeVector(0,0,Ge_posZ),Ge_Logic,"Ge",WholeGePart_Logic,false,0,true);

    // Loi Truc
    G4double D = 42.9*mm;
    G4double C = 9.6*mm;
    G4double Hcore = D+N;
    G4Tubs *InnerDead_Solid = new G4Tubs("InnerDead",0,C/2.+N,Hcore/2.,0.*deg,phiV);
    G4double InnerDead_posZ = (HGe/2.-Hcore+Hcore/2.);
    G4LogicalVolume* InnerDead_Logic = new G4LogicalVolume(InnerDead_Solid,B_mat,"InnerDead");
    new G4PVPlacement(0,G4ThreeVector(0,0,InnerDead_posZ),InnerDead_Logic,"InnerDead",Ge_Logic,false,0,true);
    // Chan khong Loi truc
    G4Tubs *Core_Solid = new G4Tubs("Core",0,C/2.,D/2.,0.*deg,phiV);
    G4double Core_posZ = Hcore/2. -D +D/2;
    G4LogicalVolume* Core_Logic = new G4LogicalVolume(Core_Solid,gal_mat,"Core");
    new G4PVPlacement(0,G4ThreeVector(0,0,Core_posZ),Core_Logic,"Core",InnerDead_Logic,false,0,true);
    return WholeDet_Logic;
}

void GammaSpectroScpy::SetUserCylindralSample(G4double hmau,G4double dmau,G4double distance,G4String matName)
{
    isCylindral = true;
    fHmau = hmau;
    fDmau = dmau;
    fDistaneSD = distance;
    G4NistManager* nist = G4NistManager::Instance(); 
    sample_mat = nist->FindOrBuildMaterial(matName);
    if (!sample_mat) {
        G4cout<<"Wrong matname\n";
        exit(0);
    }
}