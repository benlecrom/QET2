#define QET_cxx
#include "QET.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <TMath.h>
#include <TTreeFormula.h>
#include <TFile.h>
#include <TGraph.h>
#include <vector>
using namespace std;

void QET::Loop()
{
 TFile file1("QET.root","UPDATE");

 Double_t bin[7][3]={0.};
 Double_t t_bin[7][3]={0.};
 Int_t TrueEvents = 0;
 
   Double_t th_min[7]={30.,50.,70.,90.,110.,130.,150.};
   Double_t th_max[7]={50.,70.,90.,110.,130.,150.,170.};

   //only 5 channels used
   Double_t cryst2phi[9]={-1.,0.,-1.,270.,-1.,90.,-1,180.,-1.};
   
   vector <Double_t> thDiffA;
   vector <Double_t> thetaA;
   vector <Double_t> thDiffB;
   vector <Double_t> thetaB;
   
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   cout<<"nb entries "<<nentries<<endl;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      Double_t totEnergy = 0;
      Double_t tHA[9]={0.};
      Double_t tHB[9]={0.};
      Double_t StHA = 0.;
      Double_t StHB = 0.;

      Double_t cryst[18] = {crystal0,crystal1,crystal2,
                            crystal3,crystal4,crystal5,
			    crystal6,crystal7,crystal8,
			    crystal9,crystal10,crystal11,
                            crystal12,crystal13,crystal14,
			    crystal15,crystal16,crystal17};

    
      for (Int_t i=0; i<9; i++){
	if ((i!=4)&&(cryst[i]>0)){
	  tHA[i] = TMath::ACos(2-(511./cryst[i]))*TMath::RadToDeg();}
	if (i == 4){
	  tHA[i]= TMath::ACos(2-(511./(511.-cryst[i])))*TMath::RadToDeg();}
      }

      for (Int_t i=0; i<9; i++){
	if ((i!=4)&&(cryst[i+9]>0)){
	  tHB[i] = TMath::ACos(2-(511./cryst[i+9]))*TMath::RadToDeg();}
	if (i == 4){
	  tHB[i]= TMath::ACos(2-(511./(511.-cryst[i+9])))*TMath::RadToDeg();}
      }
      
      StHA = TMath::ACos(cosA)*TMath::RadToDeg();
      StHB = TMath::ACos(cosB)*TMath::RadToDeg();
      

      Int_t th_bin = -1;
      Int_t t_th_bin = -1;
      Double_t phiA = -1;
      Double_t phiB = -1;
      Double_t t_phiA = -1;
      Double_t t_phiB = -1;
      
      for (Int_t j=1; j<7; j++){
	if ((tHA[4]>th_min[j])&&(tHA[4]<th_max[j])&&(tHB[4]>th_min[j])&&(tHB[4]<th_max[j])){
	  th_bin = j;}
	if ((StHA>th_min[j])&&(StHA<th_max[j])&&(StHB>th_min[j])&&(StHB<th_max[j])){
	  t_th_bin = j;}
      }    
      
      for (Int_t i=0; i<9; i++){
	if ((th_bin>-1)&&(i!=4)&&(tHA[i]>th_min[th_bin])&&(tHA[i]<th_max[th_bin])) {
	  phiA = cryst2phi[i];}
      }
      for (Int_t k=0; k<9; k++){
	if ((th_bin>-1)&&(k!=4)&&(tHB[k]>th_min[th_bin])&&(tHB[k]<th_max[th_bin])) {
	  phiB = cryst2phi[k];}
      }

      for (Int_t i=0; i<9; i++){
      	if ((t_th_bin>-1)&&(i!=4)&&(tHA[i]>th_min[t_th_bin])&&(tHA[i]<th_max[t_th_bin])) {
      	  t_phiA = cryst2phi[i];}
      }
       for (Int_t k=0; k<9; k++){
      	if ((t_th_bin>-1)&&(k!=4)&&(tHB[k]>th_min[t_th_bin])&&(tHB[k]<th_max[t_th_bin])) {
      	  t_phiB = cryst2phi[k];}
      }
      
       if ((phiA>-1)&&(phiB>-1)&&(TrueEvent == 1)){
	thDiffA.push_back(StHA-tHA[4]);
	thetaA.push_back(tHA[4]);
	thDiffB.push_back(StHB-tHB[4]);
	thetaB.push_back(tHB[4]);
	Double_t phiDiff = TMath::Abs(phiA-phiB);
	if (phiDiff == 0.) bin[th_bin][0] += 1.;
	if (phiDiff == 90.) bin[th_bin][1] += 1.;
	if (phiDiff == 180.) bin[th_bin][2] += 1.;
	if (phiDiff == 270.) bin[th_bin][1] += 1.;
	TrueEvents += TrueEvent;}

      if((t_phiA>-1)&&(t_phiB>-1)){
	Double_t tphiDiff = TMath::Abs(t_phiA-t_phiB);
	if (tphiDiff == 0.) t_bin[t_th_bin][0] += 1.;
	if (tphiDiff == 90.) t_bin[t_th_bin][1] += 1.;
	if (tphiDiff == 180.)t_bin[t_th_bin][2] += 1.;
	if (tphiDiff == 270.)t_bin[t_th_bin][1] += 1.;}
      
   }
   cout<<"Nb of true QET events: "<<TrueEvents<<endl;
   cout<< bin[0][0]<<" "<< bin[0][1] << " " << bin[0][2]<<endl;
   cout<< bin[1][0]<<" "<< bin[1][1] << " " << bin[1][2]<<endl;
   cout<< bin[2][0]<<" "<< bin[2][1] << " " << bin[2][2]<<endl;
   cout<< bin[3][0]<<" "<< bin[3][1] << " " << bin[3][2]<<endl;
   cout<< bin[4][0]<<" "<< bin[4][1] << " " << bin[4][2]<<endl;
   cout<< bin[5][0]<<" "<< bin[5][1] << " " << bin[5][2]<<endl;
   cout<< bin[6][0]<<" "<< bin[6][1] << " " << bin[6][2]<<endl;
   cout<<endl;
   cout<< t_bin[0][0]<<" "<< t_bin[0][1] << " " << t_bin[0][2]<<endl;
   cout<< t_bin[1][0]<<" "<< t_bin[1][1] << " " << t_bin[1][2]<<endl;
   cout<< t_bin[2][0]<<" "<< t_bin[2][1] << " " << t_bin[2][2]<<endl;
   cout<< t_bin[3][0]<<" "<< t_bin[3][1] << " " << t_bin[3][2]<<endl;
   cout<< t_bin[4][0]<<" "<< t_bin[4][1] << " " << t_bin[4][2]<<endl;
   cout<< t_bin[5][0]<<" "<< t_bin[5][1] << " " << t_bin[5][2]<<endl;
   cout<< t_bin[6][0]<<" "<< t_bin[6][1] << " " << t_bin[6][2]<<endl;
   Double_t x_rho[7]={40.,60.,80.,100.,120.,140.,160.};
   Double_t y_rho[7]={0.};
   Double_t y_t_rho[7]={0.};
   Double_t yerr_rho[7]={0.};
   Double_t t_yerr_rho[7]={0.};
   Double_t xerr_rho[7]={0.};
   Double_t x_phi[4]={0.,90.,180.,270.};
   Double_t y_phi[4]={0.};


   for (Int_t i = 0.; i<7; i++){
     y_phi[0] += bin[i][0];
     y_phi[1] += bin[i][1]/2.;
     y_phi[2] += bin[i][2];
     y_phi[3] += bin[i][1]/2;
     if (bin[i][0]!=0){
       y_rho[i] = bin[i][1]/(2*bin[i][0]);
       yerr_rho[i] = y_rho[i]*TMath::Sqrt((1/bin[i][1])+(1/bin[i][0]));
       //y_rho[i] = bin[i][2]/bin[i][0];
     }
   }

   for (Int_t i = 0.; i<7; i++){
     if (t_bin[i][0]!=0){
       y_t_rho[i] = t_bin[i][1]/(2*t_bin[i][0]);
       t_yerr_rho[i] = y_t_rho[i]*TMath::Sqrt((1/t_bin[i][1])+(1/t_bin[i][0]));
     }
   }

   const Int_t size = thDiffA.size();
   cout<<size<<endl;
   Double_t thADarr[size] = {0.};
   Double_t thAarr[size]= {0.};
   Double_t thBDarr[size] = {0.};
   Double_t thBarr[size]= {0.};

   for (Int_t i=0; i<size ; i++){
     thADarr[i] = thDiffA[i];
     thAarr[i] = thetaA[i];
     thBDarr[i] = thDiffB[i];
     thBarr[i] = thetaB[i];
   }

   
   TGraphErrors* rho90 = new TGraphErrors(7,x_rho,y_rho,xerr_rho,yerr_rho);
   TCanvas *c1 = new TCanvas("c1", "rho90", 10, 30, 700, 500);
   rho90->GetXaxis()->SetTitle("theta/degrees");
   rho90->GetYaxis()->SetTitle("rho 90");
   rho90->Draw("A*");
   
   TGraph* phi = new TGraph(7,x_phi,y_phi);
   TCanvas *c2 = new TCanvas("c2", "phiDiff", 10, 30, 700, 500);
   phi->GetXaxis()->SetTitle("phi/degrees");
   phi->GetYaxis()->SetTitle("nb events");
   phi->Draw("A*");
   
   TGraph* thA = new TGraph(size, thAarr, thADarr);
   TCanvas *c3 = new TCanvas("c3", "thDiffA", 10, 30, 700, 500);
   thA->SetMarkerColor(4);
   thA->SetMarkerStyle(21);
   thA->GetXaxis()->SetTitle("lab theta/deg");
   thA->GetYaxis()->SetTitle("sim theta - lab theta/deg");
   thA->Draw("A*");
   TGraph* thB = new TGraph(size, thBarr, thBDarr);
   thB->SetMarkerStyle(21);
   thB->SetMarkerColor(2);
   thB->Draw("*");

   TGraphErrors* trho90 = new TGraphErrors(7,x_rho,y_t_rho,xerr_rho,t_yerr_rho);
   TCanvas *c4 = new TCanvas("c4", "true rho90", 10, 30, 700, 500);
   trho90->GetXaxis()->SetTitle("theta/degrees");
   trho90->GetYaxis()->SetTitle("'true events' rho 90");
   trho90->Draw("A*");

   file1.Write();
   file1.Close();

}
