#include "PhysicsTools/Utilities/macros/setTDRStyle.C"

#include "TCanvas.h"
#include "TH1.h"
#include "TFile.h"
#include "TLegend.h"
#include "TROOT.h"

#include <map>
#include <string>
#include <vector>

#include <iostream>

int main()
{
  // include comparisons between HW and data TPs
  //  bool includeHW = false;
  //  int rebinFactor = 1;

  setTDRStyle();
  gROOT->ForceStyle();

  // default, then new conditions
  std::vector<std::string> filenames = {"rates_new_cond_QCD.root", "rates_new_cond_LLP_mh125_pl1000.root",  "rates_new_cond_LLP_mh250_pl1000.root", "rates_new_cond_LLP_mh350_pl1000.root", "rates_new_cond_LLP_mh1000_pl1000.root"};
  std::vector<std::string> multTypes = {"ADC50_3ns_4JetMultHB", "ADC50_3ns_4JetMultHE", "ADC50_3ns_4JetMultHBHE"};

  std::map<std::string, TH1F*> multHists_QCD;
  std::map<std::string, TH1F*> multHists_LLPmh125;
  std::map<std::string, TH1F*> multHists_LLPmh250;
  std::map<std::string, TH1F*> multHists_LLPmh350;
  std::map<std::string, TH1F*> multHists_LLPmh1000;

  std::vector<TFile*> files;
  for(auto file : filenames) {
    files.push_back(TFile::Open(file.c_str()));
  }

  for(auto multType : multTypes) {
    std::string histName(multType);
    histName += "_emu";

    multHists_QCD[multType] = dynamic_cast<TH1F*>(files.at(0)->Get(histName.c_str()));
    multHists_LLPmh125[multType] = dynamic_cast<TH1F*>(files.at(1)->Get(histName.c_str()));
    multHists_LLPmh250[multType] = dynamic_cast<TH1F*>(files.at(2)->Get(histName.c_str()));
    multHists_LLPmh350[multType] = dynamic_cast<TH1F*>(files.at(3)->Get(histName.c_str()));
    multHists_LLPmh1000[multType] = dynamic_cast<TH1F*>(files.at(4)->Get(histName.c_str()));
  }

  for(auto pair : multHists_QCD) pair.second->SetLineWidth(2);
  for(auto pair : multHists_LLPmh125) pair.second->SetLineWidth(2);
  for(auto pair : multHists_LLPmh250) pair.second->SetLineWidth(2);
  for(auto pair : multHists_LLPmh350) pair.second->SetLineWidth(2);
  for(auto pair : multHists_LLPmh1000) pair.second->SetLineWidth(2);

  std::vector<TCanvas*> canvases;
  std::vector<TPad*> pad1;
  std::vector<TPad*> pad2;

  for(auto hist : multTypes) {
    canvases.push_back(new TCanvas);
    canvases.back()->SetWindowSize(canvases.back()->GetWw(), 1.3*canvases.back()->GetWh());
    pad1.push_back(new TPad("pad1", "pad1", 0, 0, 1, 1));
    pad1.back()->SetGrid();
    pad1.back()->Draw();
    pad1.back()->cd();

    multHists_QCD[hist]->SetLineColor(kBlack); 
    TString name(multHists_QCD[hist]->GetName());
    int yMax = 0;
    yMax = multHists_QCD[hist]->GetMaximum();
    multHists_QCD[hist]->GetYaxis()->SetRangeUser(0,1.2*yMax);
    multHists_QCD[hist]->SetFillStyle(3005);
    multHists_QCD[hist]->Scale(1./multHists_QCD[hist]->Integral());
    multHists_QCD[hist]->Draw("hist pfc");
    TLegend *leg = new TLegend(0.4, 0.6, 0.95, 0.9);
    multHists_LLPmh125[hist]->SetLineColor(kBlue);
    multHists_LLPmh125[hist]->Scale(1./multHists_LLPmh125[hist]->Integral());
    multHists_LLPmh125[hist]->Draw("hist same");
    multHists_LLPmh250[hist]->SetLineColor(kGreen+1);
    multHists_LLPmh250[hist]->Scale(1./multHists_LLPmh250[hist]->Integral());
    multHists_LLPmh250[hist]->Draw("hist same");
    multHists_LLPmh350[hist]->SetLineColor(kRed);
    multHists_LLPmh350[hist]->Scale(1./multHists_LLPmh350[hist]->Integral());
    multHists_LLPmh350[hist]->Draw("hist same");
    multHists_LLPmh1000[hist]->SetLineColor(kMagenta);
    multHists_LLPmh1000[hist]->Scale(1./multHists_LLPmh1000[hist]->Integral());
    multHists_LLPmh1000[hist]->Draw("hist same");
    leg->AddEntry(multHists_QCD[hist],"QCD", "F");
    leg->AddEntry(multHists_LLPmh125[hist], "LLP, mH=125GeV, mX=50GeV", "L");
    leg->AddEntry(multHists_LLPmh250[hist], "LLP, mH=250GeV, mX=120GeV", "L");
    leg->AddEntry(multHists_LLPmh350[hist], "LLP, mH=350GeV, mX=160GeV", "L");
    leg->AddEntry(multHists_LLPmh1000[hist], "LLP, mH=1000GeV, mX=450GeV", "L");
    multHists_QCD[hist]->GetYaxis()->CenterTitle(true);
    multHists_QCD[hist]->SetTitle("Number of cells >=" + name(0,5) + " and " + name(6,3)+", from TPs within DR<0.5 of " + name (10,1) + " L1 Jets"); // general name "mult at 3 GeV and 1 ns, TP matched w/jet"
    multHists_QCD[hist]->GetXaxis()->SetLabelSize(0.03);
    multHists_QCD[hist]->GetYaxis()->SetLabelSize(0.03);
    multHists_QCD[hist]->GetXaxis()->SetTitleSize(0.04);
    multHists_QCD[hist]->GetYaxis()->SetTitleSize(0.04);
    multHists_QCD[hist]->GetXaxis()->SetTitleOffset(1.2);
    multHists_QCD[hist]->GetYaxis()->SetTitleOffset(1.5);
    leg->SetBorderSize(0);
    leg->Draw();
    canvases.back()->Print(Form("plots/%sOverlay.pdf", hist.substr(0).c_str()));
  }
   
  return 0;
}