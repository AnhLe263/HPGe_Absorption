#include "steppingaction.hh"
#include "analysis.hh"

#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4HadronicProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4VProcess.hh"
#include "G4Isotope.hh"
steppingaction::steppingaction(eventaction* evt)
    :G4UserSteppingAction(), fEvent(evt)
{}

steppingaction::~steppingaction()
{}

void steppingaction::UserSteppingAction(const G4Step *step)
{
    //if (step->GetTotalEnergyDeposit() == 0.) return;
    
    //Get pointer to pre-point
    G4StepPoint* prePoint=dynamic_cast<G4StepPoint*>(step->GetPreStepPoint());
    if (!prePoint){
        G4cout<<"No pre-Point\n";
        exit(0);
    }

    //Get pointer to post-point
    G4StepPoint* postPoint=dynamic_cast<G4StepPoint*>(step->GetPostStepPoint());
    if (!postPoint){
        G4cout<<"No post-Point\n";
        exit(0);
    }

    //Get current Volume
    G4VPhysicalVolume* stepVol=dynamic_cast<G4VPhysicalVolume*>(prePoint->GetTouchableHandle()->GetVolume());
    if (!stepVol){
        G4cout<<"No Volume\n";
        exit(0);
    }
    //GetTrack:
    G4Track *atrack = step->GetTrack();
    auto partname = atrack->GetParticleDefinition()->GetParticleName();
    //det ID, convenient to store for post-analysis
    G4int iDet=-1;
    if (stepVol->GetName()=="Sample" || stepVol->GetName()=="Sample1" || stepVol->GetName()=="Sample2") iDet=1;
    if (stepVol->GetName()=="Ge") iDet=2;
    if (stepVol->GetName()=="Core") {
        //G4cout<<"Core\n"<<G4endl;
    }
    //G4cout<<stepVol->GetName()<<G4endl;
    if (partname== "gamma" && iDet == 1) {
        auto stl = step->GetStepLength();
        fEvent->AddStepLength(stl);
    }


    if (iDet == 2) {
        auto E = step->GetTotalEnergyDeposit();
        fEvent->AddDepositE(E);
    }

    if (partname == "e-" && iDet == 2 && postPoint->GetStepStatus() == fGeomBoundary) {
        G4double E = postPoint->GetKineticEnergy();
        fEvent->AddTotalReleasEOfelectron(E);
    }

}
