#include "GammaSource.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaSource::GammaSource(GammaSpectroScpy* det)
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0), fDet(det), isTranmissionMethod(true), isRandomDirection(false)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="gamma");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(30.*keV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

GammaSource::~GammaSource()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void GammaSource::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of ecah event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.
  G4double x =0.*mm;
  G4double y =0.*mm;
  G4double z =0.*mm;
  G4bool isSample = fDet->GetIsCylindral();
  if (isSample) {
      G4double Dmau = fDet->GetDmau();
      G4double Hmau = fDet->GetHmau();
      G4double samplePosZ = fDet->GetSamplePosZ();
      if (!isTranmissionMethod) {
        G4double zmin = samplePosZ - Hmau/2.;
        G4double zmax = samplePosZ + Hmau/2.;
        z = zmin + G4UniformRand()*(zmax-zmin);
        G4double a=2.*CLHEP::pi*G4UniformRand(); //angle
        G4double rc=Dmau/2;//radius
        G4double r=(rc*std::sqrt(G4UniformRand()));
        G4double Xo=0.*mm, Yo=0.*mm;//origin
        x=r*std::cos(a)+Xo;
        y=r*std::sin(a)+Yo;
      } else {
        z = samplePosZ - Hmau/2.;
      }
      
  }

  G4bool isSample2 = fDet->GetIsMarinelli();
  if (isSample2) {
    G4double Dmau = fDet->GetDmau();
    G4double Hmau = fDet->GetHmau();
    G4double Hmau2 = fDet->GetHmau2();
    G4double t3 = fDet->Gett3();
    G4double W = fDet->GetW();
    G4double samplePosZ = fDet->GetSamplePosZ();
    G4double V1 =  fDet->GetV1Mirinelli();
    G4double V2 = fDet->GetV2Mirinelli();
    G4double xs1 = V1/(V1+V2);
    G4double xs2 = V2/(V1+V2);
    //G4cout<<"Xa suat "<<V1<<"\t"<<V2<<G4endl;
    G4double rr= G4UniformRand();
    if (rr<=xs1) {
      //G4double samplePosZ2 = samplePosZ - Hmau2/2.-Hmau/2.;
      G4double zmin = samplePosZ - Hmau;
      G4double zmax = samplePosZ;
      if (!isTranmissionMethod){
        z = zmin + G4UniformRand()*(zmax-zmin);
        G4double a=2.*CLHEP::pi*G4UniformRand(); //angle
        G4double rc=Dmau/2;//radius
        G4double r=(rc*std::sqrt(G4UniformRand()));
        G4double Xo=0.*mm, Yo=0.*mm;//origin
        x=r*std::cos(a)+Xo;
        y=r*std::sin(a)+Yo;
      } 
    } 
    if (xs1< rr && rr <=(xs1+xs2)) {
      G4double zmin = samplePosZ;
      G4double zmax = samplePosZ + Hmau2 - t3;
      if (!isTranmissionMethod){
        z = zmin + G4UniformRand()*(zmax-zmin); 
        G4double a=2.*CLHEP::pi*G4UniformRand(); //angle
        G4double rc=Dmau/2;//radius
        G4double Xo=0.*mm, Yo=0.*mm;//origin
        G4double rmin = rc-W;
        
          G4double r=((rc-rmin)*std::sqrt(G4UniformRand())) + rmin;
          x=r*std::cos(a)+Xo;
          y=r*std::sin(a)+Yo;
        
      } 
    }
    if (isTranmissionMethod) z = samplePosZ - Hmau;
  }

  //Uniform direction:
  G4double alphaMin =  0*deg;      //alpha in [0,pi]
  G4double alphaMax = 180*deg;
  G4double fCosAlphaMin = std::cos(alphaMin);
  G4double fCosAlphaMax = std::cos(alphaMax);
  
  G4double fPsiMin = 0*deg;       //psi in [0, 2*pi]
  G4double fPsiMax = 360*deg;
  G4double cosAlpha = fCosAlphaMin-G4UniformRand()*(fCosAlphaMin-fCosAlphaMax);
  G4double sinAlpha = std::sqrt(1. - cosAlpha*cosAlpha);
  G4double psi = fPsiMin + G4UniformRand()*(fPsiMax - fPsiMin);

  G4double ux = sinAlpha*std::cos(psi),
           uy = sinAlpha*std::sin(psi),
           uz = cosAlpha;
  if (isRandomDirection) fParticleGun->SetParticleMomentumDirection(G4ThreeVector(ux,uy,uz));
  fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z));

  fParticleGun->GeneratePrimaryVertex(anEvent);
}
