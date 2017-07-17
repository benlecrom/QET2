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

#include "Tangle2EventAction.hh"

#include "Tangle2Data.hh"
#include "Tangle2RunAction.hh"
#include "Tangle2VSteppingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

#include "G4Event.hh"

Tangle2EventAction::Tangle2EventAction
(Tangle2VSteppingAction* onePhotonSteppingAction)
: fpTangle2VSteppingAction(onePhotonSteppingAction)
{}

Tangle2EventAction::~Tangle2EventAction()
{
delete G4AnalysisManager::Instance();
}

void Tangle2EventAction::BeginOfEventAction(const G4Event*)
{
  fpTangle2VSteppingAction->BeginOfEventAction();
  for (G4int i = 0; i<18; i++){
    Tangle2::eDepCryst[i] = 0.;}
  Tangle2::TrueEvent = 0;
  Tangle2::nbComptA = 0;
  Tangle2::nbComptB = 0;
  Tangle2::cosA = -1.;
  Tangle2::cosB = -1.;

}

void Tangle2EventAction::EndOfEventAction(const G4Event*)
{   
  fpTangle2VSteppingAction->EndOfEventAction();
  
  // Always use a lock when writing a file in MT mode
  G4AutoLock lock(&Tangle2::outFileMutex);
  

  //Check if the event is a 'true lab event'
  //using AND trigger between central crystals

  G4double eDepEvent = 0.;
  G4double eThres = 150*keV; //in MeV

  //Tot energy
  for (G4int i = 0; i< 18 ; i++){
    eDepEvent += Tangle2::eDepCryst[i];
   }

  //Output only 'true lab events' to the root file
  //
  if ((Tangle2::eDepCryst[4] > eThres) && (Tangle2::eDepCryst[13] > eThres)){
      G4AnalysisManager* man = G4AnalysisManager::Instance();
      for (G4int i = 0 ; i < 18 ; i++){
	man->FillNtupleDColumn(i, Tangle2::eDepCryst[i]/keV);}
      man->FillNtupleIColumn(18, Tangle2::TrueEvent);
      man->FillNtupleDColumn(19, Tangle2::cosA);
      man->FillNtupleDColumn(20, Tangle2::cosB);
      
      man->AddNtupleRow();
  }

  //Record the number of events with 511 keV deposited in the central crystals
  if (eDepEvent > eThres){
    Tangle2::nEventsPh += 1;
  }
  
}
