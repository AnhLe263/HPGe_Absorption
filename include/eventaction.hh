#ifndef EVENTACTION_HH
#define EVENTACTION_HH
#include "G4UserEventAction.hh"
#include "globals.hh"
class eventaction: public G4UserEventAction
{
public:
    eventaction();
    virtual ~eventaction();
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);
    void AddStepLength(G4double l) {fTotalStepLength += l;}
    void AddDepositE(G4double e) {fTotalDepositE += e;}
    void AddTotalReleasEOfelectron(G4double e) {fTotalReleasEOfelectron += e;}
    
private:
    G4double fTotalStepLength;
    G4double fTotalDepositE;
    G4double fTotalReleasEOfelectron;
};
#endif // EVENTACTION_HH
