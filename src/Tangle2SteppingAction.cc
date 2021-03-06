// *******************************************************************
// * License and Disclaimer                                          *
// *                                                                 *
// * This software is copyright of Geant4 Associates International   *
// * Ltd (hereafter 'G4AI'). It is provided under the terms and      *
// * conditions described in the file 'LICENSE' included in the      *
// * software system.                                                *
// * Neither the authors of this software system nor G4AI make any   *
// * representation or warranty, express or implied, regarding this  *
// * software system or assume any liability for its use.            *
// * Please see the file 'LICENSE' for full disclaimer and the       *
// * limitation of liability.                                        *
// *******************************************************************
// $Id$
// John Allison  22nd May 2017

#include "Tangle2SteppingAction.hh"

#include "Tangle2RunAction.hh"
#include "Tangle2Data.hh"

#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4MTRunManager.hh"
#include "G4EventManager.hh"
#include "G4TrackingManager.hh"
#include "G4SteppingManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4Gamma.hh"
#include "G4Threading.hh"

Tangle2SteppingAction::Tangle2SteppingAction
(Tangle2RunAction* runAction)
{}

void Tangle2SteppingAction::BeginOfEventAction()
{
}

void Tangle2SteppingAction::EndOfEventAction()
{
}

void Tangle2SteppingAction::UserSteppingAction(const G4Step* step)
{
   G4StepPoint* preStepPoint = step->GetPreStepPoint();
  G4StepPoint* postStepPoint = step->GetPostStepPoint();

  G4double eDep = step->GetTotalEnergyDeposit();

  G4VPhysicalVolume* prePV = preStepPoint->GetPhysicalVolume();
  G4VPhysicalVolume* postPV = postStepPoint->GetPhysicalVolume();

  //G4ThreeVector prePos = preStepPoint->GetPosition();
  //G4ThreeVector postPos = postStepPoint->GetPosition();

  G4ThreeVector preMomentumDir = preStepPoint->GetMomentumDirection();
  G4ThreeVector postMomentumDir = postStepPoint->GetMomentumDirection();

  //G4Track* track = step->GetTrack();
  //G4ParticleDefinition* particleDefinition = track->GetDefinition();
  //const G4VProcess* creatorProcess = track->GetCreatorProcess();

  const G4VProcess* processDefinedStep = postStepPoint->GetProcessDefinedStep();
  
  if  (postPV){
    if ((eDep > 0)&&(postPV->GetName() != "disc")){
    Tangle2::eDepCryst[postPV->GetCopyNo()] += eDep;}
  }

  if (postPV){
  if ((prePV->GetName() == "World") && (postPV->GetCopyNo() == 4)){
    Tangle2::TrueEvent = 1.;}
  }

  if (processDefinedStep->GetProcessName() == "compt"){
    if ((preMomentumDir[0] > 0)&&(Tangle2::nbComptA == 0)){
      Tangle2::cosA = preMomentumDir.dot(postMomentumDir);
      Tangle2::nbComptA += 1.;}
    if ((preMomentumDir[0] < 0)&&(Tangle2::nbComptB == 0)){
      Tangle2::cosB = preMomentumDir.dot(postMomentumDir);
      Tangle2::nbComptB += 1.;}
  }


  
  return;
}
