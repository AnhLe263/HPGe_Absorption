#include "RunAction.hh"


#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "analysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
 : G4UserRunAction()
{  
 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{ 
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "G4Run.hh"
void RunAction::BeginOfRunAction(const G4Run* run)
{ 
    G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
    analysisManager->SetNtupleMerging(true);
    // Open Output
    auto runID = run->GetRunID();
    G4String fileName = "Result_run" + std::to_string(runID)+".root";
    analysisManager->OpenFile(fileName);
    analysisManager->CreateNtuple("GammaSpec","procducts inform");
    analysisManager->CreateNtupleDColumn("PathLength");//Pathlength in sample
    analysisManager->CreateNtupleDColumn("Edeposit");//Edep in Ge
    analysisManager->CreateNtupleDColumn("CorrectedEdeposit");//Corrected Edeposit in Ge
    analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
    G4AnalysisManager* analysisManager=G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......