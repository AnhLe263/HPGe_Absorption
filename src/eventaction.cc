#include "eventaction.hh"
#include "analysis.hh"
#include "G4SystemOfUnits.hh"
eventaction::eventaction() : G4UserEventAction()
{

}

eventaction::~eventaction() {}

void eventaction::BeginOfEventAction(const G4Event *)
{
    fTotalStepLength = 0.;
    fTotalDepositE = 0.;
    fTotalReleasEOfelectron = 0.;
}

void eventaction::EndOfEventAction(const G4Event *)
{
   // Store information
    //if (fTotalDepositE > 0.) 
    {
        G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
        G4double CorrectedE = fTotalDepositE - fTotalReleasEOfelectron;
        analysisManager->FillNtupleDColumn(0,fTotalStepLength);
        analysisManager->FillNtupleDColumn(1,fTotalDepositE/keV);
        analysisManager->FillNtupleDColumn(2,fTotalReleasEOfelectron); 
        analysisManager->AddNtupleRow();
    }

}
