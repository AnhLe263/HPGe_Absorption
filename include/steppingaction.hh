#ifndef STEPPINGACTION_H
#define STEPPINGACTION_H
#include "G4UserSteppingAction.hh"
#include "eventaction.hh"
class steppingaction:public G4UserSteppingAction
{
public:
    steppingaction(eventaction *evt);
    virtual ~steppingaction();
    virtual void UserSteppingAction(const G4Step*);
private:
    eventaction* fEvent;
};
#endif // STEPPINGACTION_H
