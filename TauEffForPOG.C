#include <iostream>
#include <map>
#include <vector>
#include "TString.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include <chrono>
#include <cmath>
#include "Math/Vector4D.h"

using namespace std;

void analyze(TString srcfile, int sample) {
  TString extra="";
  if(sample!=0) extra="root://xrootd-cms.infn.it/"; 
  TString filename = extra + srcfile;
  cout<<"Opening "<<filename<<endl;
  TFile *f = TFile::Open(filename);
  TFile *output= new TFile("testoutput.root","RECREATE");
  TTree* tree = (TTree*)f->Get("Events");

  TH1F *thvseselected = new TH1F("thvseselected","thvseselected",1000,0,1);
  TH1F *thvsmuselected = new TH1F("thvsmuselected","thvsmuselected",1000,0,1);
  TH1F *thvsjetselected = new TH1F("thvsjetselected","thvsjetselected",1000,0,1);

  TH1F *thvsetotal = new TH1F("thvsetotal","thvsetotal",1000,0,1);
  TH1F *thvsmutotal = new TH1F("thvsmutotal","thvsmutotal",1000,0,1);
  TH1F *thvsjettotal = new TH1F("thvsjettotal","thvsjettotal",1000,0,1);

  TH1F *thvseselectedBG = new TH1F("thvseselectedBG","thvseselected",1000,0,1);
  TH1F *thvsmuselectedBG = new TH1F("thvsmuselectedBG","thvsmuselected",1000,0,1);
  TH1F *thvsjetselectedBG = new TH1F("thvsjetselectedBG","thvsjetselected",1000,0,1);

  TH1F *thvsetotalBG = new TH1F("thvsetotalBG","thvsetotal",1000,0,1);
  TH1F *thvsmutotalBG = new TH1F("thvsmutotalBG","thvsmutotal",1000,0,1);
  TH1F *thvsjettotalBG = new TH1F("thvsjettotalBG","thvsjettotal",1000,0,1);
  
  tree->SetBranchStatus("*", 0);

  tree->SetBranchStatus("Tau_pt", 1);
  Float_t tau_pt_[128];
  tree->SetBranchAddress("Tau_pt",&tau_pt_);

  tree->SetBranchStatus("Tau_eta", 1);
  Float_t tau_eta_[128];
  tree->SetBranchAddress("Tau_eta",&tau_eta_);

  tree->SetBranchStatus("Tau_mass", 1);
  Float_t tau_mass_[128];
  tree->SetBranchAddress("Tau_mass",&tau_mass_);

  tree->SetBranchStatus("Tau_phi", 1);
  Float_t tau_phi_[128];
  tree->SetBranchAddress("Tau_phi",&tau_phi_);

  tree->SetBranchStatus("Tau_decayMode", 1);
  UChar_t tau_decay_[128];
  tree->SetBranchAddress("Tau_decayMode",&tau_decay_);

  tree->SetBranchStatus("Tau_rawPNetVSe", 1);
  Float_t tau_pnetvse_[128];
  tree->SetBranchAddress("Tau_rawPNetVSe",&tau_pnetvse_);

  tree->SetBranchStatus("Tau_rawPNetVSmu", 1);
  Float_t tau_pnetvsmu_[128];
  tree->SetBranchAddress("Tau_rawPNetVSmu",&tau_pnetvsmu_);

  tree->SetBranchStatus("Tau_rawPNetVSjet", 1);
  Float_t tau_pnetvsjet_[128];
  tree->SetBranchAddress("Tau_rawPNetVSjet",&tau_pnetvsjet_);

  tree->SetBranchStatus("Tau_dxy", 1);
  Float_t tau_dxy_[128];
  tree->SetBranchAddress("Tau_dxy",&tau_dxy_);

  tree->SetBranchStatus("Tau_dz", 1);
  Float_t tau_dz_[128];
  tree->SetBranchAddress("Tau_dz",&tau_dz_);

  tree->SetBranchStatus("Tau_genPartFlav", 1);
  UChar_t tau_source_[128];
  tree->SetBranchAddress("Tau_genPartFlav",&tau_source_);

  tree->SetBranchStatus("nTau", 1);
  UInt_t ntaus_;
  TBranch* b_ntaus = tree->GetBranch("nTau");
  b_ntaus->SetAddress(&ntaus_);
  
  auto startTime = std::chrono::high_resolution_clock::now();

  Long64_t numEntries = tree->GetEntries();
  cout<<"# of entries: "<<numEntries<<endl;
  for (Long64_t i = 0; i < numEntries; ++i) {

    tree->GetEntry(i);

    if(i%100000==0) cout<<"Analyzing event n: "<<i<<endl;

    for(int i=0; i<ntaus_; i++){
      if(tau_pt_[i] > 20 && abs(tau_eta_[i]) < 2.3 && abs(tau_dz_[i])<0.2 && static_cast<int>(tau_decay_[i])!=5 && static_cast<int>(tau_decay_[i])!=6){  //Baseline tau selection

        //Signal efficiencies

	if(static_cast<int>(tau_source_[i])==5){
	  
	  for(int x=1;x<1001;x++){
            thvsetotal->Fill(0.001*x);
	    thvsmutotal->Fill(0.001*x);
	    thvsjettotal->Fill(0.001*x);
	  }
          for(int x=1;x<1001;x++){
	    if(tau_pnetvse_[i]>=0.001*x) thvseselected->Fill(0.001*x);
	    else break;
	  }
	  for(int x=1;x<1001;x++){
            if(tau_pnetvsmu_[i]>=0.001*x) thvsmuselected->Fill(0.001*x);
            else break;
	  }
	  for(int x=1;x<1001;x++){
            if(tau_pnetvsjet_[i]>=0.001*x) thvsjetselected->Fill(0.001*x);
            else break;
	  }  
	}

        //Jet BG efficiencies

        else if(static_cast<int>(tau_source_[i])==0){
          for(int x=1;x<1001;x++){
            thvsjettotalBG->Fill(0.001*x);
          }
          for(int x=1;x<1001;x++){
            if(tau_pnetvsjet_[i]>=0.001*x) thvsjetselectedBG->Fill(0.001*x);
            else break;
          }          
	}

        //e BG efficiencies

	else if(static_cast<int>(tau_source_[i])==1){
          for(int x=1;x<1001;x++) {
            thvsetotalBG->Fill(0.001*x);
	  } 
          for(int x=1;x<1001;x++){
            if(tau_pnetvse_[i]>=0.001*x) thvseselectedBG->Fill(0.001*x);
            else break;
          }         
	}

        //mu BG efficiencies

        else if(static_cast<int>(tau_source_[i])==2){
	  for(int x=1;x<1001;x++) {
            thvsmutotalBG->Fill(0.001*x);
          }
	  for(int x=1;x<1001;x++){
	    if(tau_pnetvsmu_[i]>=0.001*x) thvsmuselectedBG->Fill(0.001*x);
            else break;
          }
	}

      }
    }
    
  }

  auto endTime = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
  std::cout << "Computation time: " << duration << " milliseconds" << std::endl;

  f->Close();  

  output->Write("thvseselected");
  output->Write("thvsetotal");
  output->Write("thvsmuselected");
  output->Write("thvsmutotal");
  output->Write("thvsjetselected");
  output->Write("thvsjettotal");
  output->Write("thvseselectedBG");
  output->Write("thvsetotalBG");
  output->Write("thvsmuselectedBG");
  output->Write("thvsmutotalBG");
  output->Write("thvsjetselectedBG");
  output->Write("thvsjettotalBG");

}

int main(int argc, char* argv[]) {

  TString filename=argv[1];
  int sample= std::atoi(argv[2]);
  TString srcfile;

  if(sample==0)
    srcfile="/eos/user/g/gmarozzo/crabOutput/GluGluHToTauTau_M125/Output.root";
  if(sample==1)
    srcfile="/store/mc/Run3Summer22NanoAODv12/GluGluHto2Tau_M-125_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/" + filename;
  if(sample==2)
    srcfile="/store/mc/Run3Summer22EENanoAODv12/GluGluHto2Tau_M-125_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_postEE_v6-v2/" + filename;
  if(sample==3)
    srcfile="/store/mc/Run3Summer22NanoAODv12/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_v5-v2/" + filename;
  if(sample==4)
    srcfile="/store/mc/Run3Summer22EENanoAODv12/TTtoLNu2Q_TuneCP5_13p6TeV_powheg-pythia8/NANOAODSIM/130X_mcRun3_2022_realistic_postEE_v6-v2/" + filename;

  analyze(srcfile,sample);

  return 1;
}
