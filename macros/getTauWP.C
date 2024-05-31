#include "TH2F.h"
#include "TFile.h"
#include "TLatex.h"

void getTauWP(TString particle){

  TFile *file;
  file= new TFile("../results/TauEff2.root"); //TauEff2.root HtoTauTau(_EE).root
			
  TH1F *th2muon1 = (TH1F*) file->Get("thvs"+particle+"selected");
  TH1F *th2muon2 = (TH1F*) file->Get("thvs"+particle+"total");

  th2muon1->Sumw2();
  th2muon2->Sumw2();
  
  th2muon1->Divide(th2muon2);
  gStyle->SetOptStat(0);
  
  for(int i=1;i<th2muon1->GetNbinsX()+1;i++){
    cout<<"Discriminator: "<<0.001*(i-1)<<" Efficiency: "<<th2muon1->GetBinContent(i)<<" +- "<<th2muon1->GetBinError(i)<<endl;
  }
}
