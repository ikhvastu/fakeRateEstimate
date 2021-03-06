#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <iomanip>
#include "fstream"
#include "sstream" 

#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TLorentzVector.h"
#include "TChain.h"
#include "TClonesArray.h"
#include "TLegend.h"
#include "THStack.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TApplication.h"
#include "TFrame.h"

#include "TLatex.h"
//#include "TASImage.h"

//#include "mt2_bisect.h"

TString lumi_13TeV = "2.11 fb^{-1}";

using namespace std;

int _multiWP[3] = {2,1,0};//Medium - ele, Loose - mu

const int numSUSY1 = 1; //2 - T1tttt1200, 1 - T1tttt1500 
const int numSUSY2 = 1;
     
const int signalSUSY = 2;//2 - T1tttt1200, 3 - T1tttt1500 
   
const int SRNumberAll = 72;

namespace{
  const int bands = 999;
  int rainbow[bands];
  int patriotic[bands];
}

bool comp (const pair<double, int> i, const pair<double, int> j) { return (i.first>j.first); }

//void CMS_lumi( TPad* pad, int iPeriod, int iPosX ); 

double uncCalc(double a, double b, double c);

void showHist(TVirtualPad *, TH1D *, TH1D *, THStack *, string, string, string, double, TLegend*);

TH2D TranslateHisto(const TH2 &input);

void GetPatrioticPalette();
void GetRainbowPalette();

void readTreeQCD()
{
    
    
    const int nLeptonsMax = 10;
    int fontToUse = 42;
    gStyle->SetPaintTextFormat("4.3f");
    gStyle->SetOptFit(0);
    gStyle->SetCanvasColor(kWhite);
    gStyle->SetPadColor(kWhite);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(1);
    gStyle->SetNdivisions(505,"XY");
    
    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kTRUE);
    gStyle->SetTickLength(0.03, "XYZ");
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);
    
    gStyle->SetLabelFont(fontToUse,"XYZ");
    gStyle->SetLabelSize(0.05,"XYZ");
    gStyle->SetLabelOffset(0.001,"X");
    
    gStyle->SetTitleFont(fontToUse,"");
    gStyle->SetTitleFont(fontToUse,"XYZ");
    gStyle->SetTitleFontSize(0.06);
    gStyle->SetTitleSize(0.06,"XY");
    //gStyle->SetTitleXOffset(1.0);
    gStyle->SetTitleXOffset(0.9);
    gStyle->SetTitleYOffset(1.2);
    
    gStyle->SetErrorX(0.);
    
    gStyle->SetPadTopMargin(0.10);
    gStyle->SetPadBottomMargin(0.12);
    gStyle->SetPadRightMargin(0.035);
    gStyle->SetPadLeftMargin(0.15);
    
    gStyle->SetStatFont(fontToUse);
    gStyle->SetStatColor(10);
    gStyle->SetStatFontSize(0.08);
    gStyle->SetTitleFont(fontToUse);
    gStyle->SetTitleFontSize(0.08);
    
    gStyle->SetMarkerSize(1.);
    gStyle->SetMarkerStyle(20);
    gStyle->SetMarkerColor(gStyle->GetHistLineColor());
    
    gStyle->SetPalette(1,0);
    
    gStyle->SetFuncColor(kRed);

  /*
    TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(600); //Height of canvas
  tdrStyle->SetCanvasDefW(600); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);
  
// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  // tdrStyle->SetErrorMarker(20);
  //tdrStyle->SetErrorX(0.);
  
  tdrStyle->SetMarkerStyle(20);
  
//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("3.2g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.05);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:

  tdrStyle->SetOptTitle(0);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.02, "X");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.04, "X");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(505, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
  // tdrStyle->SetPalette(Int_t ncolors = 0, Int_t* colors = 0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->SetHatchesLineWidth(5);
  tdrStyle->SetHatchesSpacing(0.05);

  tdrStyle->cd();
*/
    // List of branches
    TBranch        *b__eventNb;   //!
    TBranch        *b__runNb;   //!
    TBranch        *b__lumiBlock;   //!
    TBranch        *b__weight;   //!
    TBranch        *b__genqpt;   //!
    TBranch        *b__nLeptons;   //!
    TBranch        *b__lPt;   //!
    TBranch        *b__lEta;   //!
    TBranch        *b__lPhi;   //!
    TBranch        *b__lE;   //!
    TBranch        *b__lPtmc;   //!
    TBranch        *b__lEtamc;   //!
    TBranch        *b__lPhimc;   //!
    TBranch        *b__lEmc;   //!
    TBranch        *b__nuPtmc;   //!
    TBranch        *b__nuEtamc;   //!
    TBranch        *b__nuPhimc;   //!
    TBranch        *b__nuEmc;   //!
    TBranch        *b__mtmc;   //!
    TBranch        *b__nEle;   //!
    TBranch        *b__nMu;   //!
    TBranch        *b__nTau;   //!
    TBranch        *b__flavors;   //!
    TBranch        *b__charges;   //!
    TBranch        *b__indeces;   //!
    TBranch        *b__isolation;   //!
    TBranch        *b__miniisolation;   //!
    TBranch        *b__multiisolation;   //!
    TBranch        *b__ptrel;   //!
    TBranch        *b__ptratio;   //!
    TBranch        *b__origin;   //!
    TBranch        *b__originReduced;   //!
    TBranch        *b__PVchi2;   //!
    TBranch        *b__PVerr;   //!
    TBranch        *b__ipPV;   //!
    TBranch        *b__ipPVerr;   //!
    TBranch        *b__ipZPV;   //!
    TBranch        *b__ipZPVerr;   //!
    TBranch        *b__ipPVmc;   //!
    TBranch        *b__3dIP;   //!
    TBranch        *b__3dIPerr;   //!
    TBranch        *b__3dIPsig;   //!
    TBranch        *b__mt;   //!
    TBranch        *b__mt2;   //!
    TBranch        *b__mt2ll;   //!
    TBranch        *b__mt2blbl;   //!
    TBranch        *b__isloose;   //!
    TBranch        *b__istight;   //!
    TBranch        *b__istightID;   //!
    TBranch        *b__closeJetPtAll;   //!
    TBranch        *b__closeJetAngAll;   //!
    TBranch        *b__ptRelAll;   //!
    TBranch        *b__closeJetPtAllMC;   //!
    TBranch        *b__closeJetPtAllstatus;   //!
    TBranch        *b__partonIdMatched;   //!
    TBranch        *b__sameParton;   //!
    TBranch        *b__n_PV;   //!
    TBranch        *b__met;   //!
    TBranch        *b__met_phi;   //!
    TBranch        *b_HT;   //!
    TBranch        *b_HT40;   //!
    TBranch        *b__genmet;   //!
    TBranch        *b__genmet_phi;   //!
    TBranch        *b__mompt;   //!
    TBranch        *b__momphi;   //!
    TBranch        *b__mometa;   //!
    TBranch        *b__mompdg;   //!
    TBranch        *b__n_bJets;   //!
    TBranch        *b__n_Jets;   //!
    TBranch        *b__bTagged;   //!
    TBranch        *b__jetE;
    TBranch        *b__jetEta;   //!
    TBranch        *b__jetPhi;   //!
    TBranch        *b__jetPt;   //!
    TBranch        *b__csv;   //!
    TBranch        *b__jetDeltaR;   //!
    TBranch        *b__jetDeltaRloose;   //!

    TBranch        *b__trigDiMuIso;
    TBranch        *b__trigMu8Ele23Iso;
    TBranch        *b__trigMu23Ele12Iso;
    TBranch        *b__trigEle23Ele12Iso;

    TBranch        *b__chargeConst;

    
 
    
    // Declaration of leaf types
    ULong64_t       _eventNb;
    ULong64_t       _runNb;
    ULong64_t       _lumiBlock;
    Double_t        _weight;
    Double_t        _genqpt;
    Int_t           _nLeptons;
    Double_t        _lPt[10];
    Double_t        _lEta[10];
    Double_t        _lPhi[10];
    Double_t        _lE[10];
    Double_t        _lPtmc[10];
    Double_t        _lEtamc[10];
    Double_t        _lPhimc[10];
    Double_t        _lEmc[10];
    Double_t        _nuPtmc[10];
    Double_t        _nuEtamc[10];
    Double_t        _nuPhimc[10];
    Double_t        _nuEmc[10];
    Double_t        _mtmc[10];
    Int_t           _nEle;
    Int_t           _nMu;
    Int_t           _nTau;
    Int_t           _flavors[10];
    Double_t        _charges[10];
    Int_t           _indeces[10];
    Double_t        _isolation[10];
    Double_t        _miniisolation[10][2];
    Bool_t          _multiisolation[10][5];
    Double_t        _ptrel[10];
    Double_t        _ptratio[10];
    Int_t           _origin[10];
    Int_t           _originReduced[10];
    Double_t        _PVchi2;
    Double_t        _PVerr[3];
    Double_t        _ipPV[10];
    Double_t        _ipPVerr[10];
    Double_t        _ipZPV[10];
    Double_t        _ipZPVerr[10];
    Double_t        _ipPVmc[10];
    Double_t        _3dIP[10];
    Double_t        _3dIPerr[10];
    Double_t        _3dIPsig[10];
    Double_t        _mt[10];
    Double_t        _mt2[10][10];
    Double_t        _mt2ll;
    Double_t        _mt2blbl;
    Bool_t          _isloose[10];
    Bool_t          _istight[10];
    Bool_t          _istightID[10];
    Double_t        _closeJetPtAll[10];
    Double_t        _closeJetAngAll[10];
    Double_t        _ptRelAll[10];
    Double_t        _closeJetPtAllMC[10];
    Double_t        _closeJetPtAllstatus[10];
    Int_t           _partonIdMatched[10];
    Bool_t          _sameParton[10];
    Int_t           _n_PV;
    Double_t        _met;
    Double_t        _met_phi;
    Double_t        HT;
    Double_t        HT40;
    Double_t        _genmet;
    Double_t        _genmet_phi;
    Double_t        _mompt[10];
    Double_t        _momphi[10];
    Double_t        _mometa[10];
    Int_t           _mompdg[10];
    Int_t           _n_bJets;
    Int_t           _n_Jets;
    Bool_t          _bTagged[20];
    Double_t        _jetE[20];
    Double_t        _jetEta[20];
    Double_t        _jetPhi[20];
    Double_t        _jetPt[20];
    Double_t        _csv[20];
    Double_t        _jetDeltaR[20][10];
    Double_t        _jetDeltaRloose[20];

    bool _trigEmulator[nLeptonsMax];
    bool _isotrigEmulator[nLeptonsMax];

    bool _fromHardProcessFinalState[nLeptonsMax];
    bool _isPromptFinalState[nLeptonsMax];

    Double_t _mvaValue[nLeptonsMax];

    Bool_t          _trigDiMuIso;
    Bool_t          _trigMu8Ele23Iso;
    Bool_t          _trigMu23Ele12Iso;
    Bool_t          _trigEle23Ele12Iso;

    Bool_t          _chargeConst[nLeptonsMax];

    
    TH1D* _hCounter = new TH1D("hCounter", "Events counter", 5,0,5);
    
    const int nSamples = 22;
    TString fileList[nSamples] = {
        //mu-enriched QCD
        "QCDmu.root","QCDmu5a.root","QCDmu5b.root","QCDmu5c.root","QCDmu5d.root","QCDmu5e.root","QCDmu5f.root","QCDmu5g.root",
        //bc->e enriched qcd
        "qcdb1.root","qcdb2.root","qcdb3.root","qcdb4.root","qcdb5.root","qcdb6.root",
        //em-enriched qcd
        "qcdE1.root","qcdE2.root","qcdE3.root","qcdE4.root","qcdE5.root","qcdE6.root","qcdE7.root","qcdE8a.root"};
    
    
    double xSections[nSamples] = {
        720648000*0.00042,1273190000*0.003,558528000*0.0053,139803000*0.01182,19222500*0.02276,2758420*0.03844,469797*0.05362,117989*0.07335,
        1272980000*0.0002,557627000*0.00059,159068000*0.00255, 3221000*0.01183, 105771*0.02492, 21094.1*0.03375,
        1273000000*0.0018, 557600000*0.0096, 136000000*0.073, 19800000*0.146, 2800000*0.125, 477000*0.132, 114000*0.165, 9000*0.15
    };
    

    Color_t colsStack[nSamples] = {
      kGray, kGray, kGray, kGray, kGray, kGray, kGray, kGray, 
      kGray, kGray, kGray, kGray, kGray, kGray, 
      kGray, kGray, kGray, kGray, kGray, kGray, kGray, kGray, 
    };
    double weights[nSamples];
    
    
    TFile *hfile[nSamples];
    TTree* inputTreeFake[nSamples];
    
    TString names[nSamples] = {
      "QCDmu", "QCDmu", "QCDmu", "QCDmu", "QCDmu", "QCDmu", "QCDmu", "QCDmu",
      "qcdb",  "qcdb",  "qcdb",  "qcdb",  "qcdb",  "qcdb", 
      "qcde",  "qcde",  "qcde",  "qcde",  "qcde",  "qcde",
    };
    

    TH1D* h_leadpt[nSamples];
    TH1D* h_2ndleadpt[nSamples];
    TH1D* h_trailpt[nSamples];
    TH1D* h_sumpt[nSamples];
    TH1D* h_mll[nSamples];
    TH1D* h_njets[nSamples];
    TH1D* h_SR[nSamples];
    TH1D* h_SIP3D[nSamples];

    TH1D* h_trilep[nSamples];
    TH1D* h_secLepIso[4];
    
    TH2D* h_pt_eta_2D[2][2];

    const int ptnbin = 6;
    double ptbins[ptnbin] = {10., 15., 25., 35., 50., 70.};

    const int etanbin = 4;
    double etabins[etanbin] = {0., 1., 2., 2.5};

    for(int i = 0; i < 2; i++){
      TString name;
      for(int j = 0; j < 2; j++){
        
        name = Form("h_pt_eta_2D_%d_%d",i,j);
        h_pt_eta_2D[i][j] = new TH2D(name, "h_pt_eta_2D;p_{T}; #eta", ptnbin-1, ptbins, etanbin-1, etabins);
        //h_pt_eta_2D[i][j]->SetLineColor(colsStack[i]);
        //h_pt_eta_2D[i][j]->SetFillColor(colsStack[i]);
        h_pt_eta_2D[i][j]->SetFillStyle(1001);
        //h_pt_eta_2D[i][j]->SetMarkerColor(colsStack[i]);
        h_pt_eta_2D[i][j]->Sumw2();
      }

      
    }

    const int isobins_comp = 8;
    double iso_comp[isobins_comp] = {0., 0.1, 0.15, 0.2, 0.25, 0.3, 0.35, 0.4};

    for(int i = 0; i < 4; i++){
      TString name;
      name = Form("second_lep_isolation_%d",i);
      h_secLepIso[i] = new TH1D(name, "Second lepton Isolation ;isolation; events", isobins_comp-1, iso_comp);
      h_secLepIso[i]->SetLineColor(kBlack);
      h_secLepIso[i]->SetFillColor(kBlack);
      h_secLepIso[i]->SetFillStyle(1001);
      h_secLepIso[i]->SetMarkerColor(kBlack);
      //h_leadpt[sample]->SetMarkerStyle(20+sample*5);
      h_secLepIso[i]->Sumw2();
    }
    
    for (int sample=0; sample!=nSamples; ++sample)  {
        weights[sample] = 0;

        TString name;

        name = Form("h_each_trilepton_%d",sample);
        h_trilep[sample] = new TH1D(name, "Tri-lepton events"+names[sample]+";trilep; events / 1", 5, -0.5, 4.5);
        h_trilep[sample]->SetLineColor(colsStack[sample]);
        h_trilep[sample]->SetFillColor(colsStack[sample]);
        h_trilep[sample]->SetFillStyle(1001);
        h_trilep[sample]->SetMarkerColor(colsStack[sample]);
        h_trilep[sample]->Sumw2();

        h_trilep[sample]->GetXaxis()->SetBinLabel(1, "Total");
        h_trilep[sample]->GetXaxis()->SetBinLabel(2, "#mu#mu#mu");
        h_trilep[sample]->GetXaxis()->SetBinLabel(3, "#mu#mue");
        h_trilep[sample]->GetXaxis()->SetBinLabel(4, "#muee");
        h_trilep[sample]->GetXaxis()->SetBinLabel(5, "eee");

        h_trilep[sample]->GetXaxis()->SetTitleSize(0.15);
        h_trilep[sample]->GetXaxis()->SetLabelSize(0.25);
        h_trilep[sample]->GetXaxis()->SetLabelOffset(0.02);

        name = Form("SIP3D_%d",sample);
        h_SIP3D[sample] = new TH1D(name, "SIP_{3D}"+names[sample]+";SIP_{3D}; events", 25, 0, 10);
        h_SIP3D[sample]->SetLineColor(colsStack[sample]);
        h_SIP3D[sample]->SetFillColor(colsStack[sample]);
        h_SIP3D[sample]->SetFillStyle(1001);
        h_SIP3D[sample]->SetMarkerColor(colsStack[sample]);
        //h_leadpt[sample]->SetMarkerStyle(20+sample*5);
        h_SIP3D[sample]->Sumw2();

        name = Form("lead_leptons_%d",sample);
        h_leadpt[sample] = new TH1D(name, "Leading lepton p_{T} "+names[sample]+";Leading lepton p_{T} [GeV]; events / 10 GeV", 20, 0, 200);
        h_leadpt[sample]->SetLineColor(colsStack[sample]);
        h_leadpt[sample]->SetFillColor(colsStack[sample]);
        h_leadpt[sample]->SetFillStyle(1001);
        h_leadpt[sample]->SetMarkerColor(colsStack[sample]);
        //h_leadpt[sample]->SetMarkerStyle(20+sample*5);
        h_leadpt[sample]->Sumw2();
        
        name = Form("2ndlead_leptons_%d",sample);
        h_2ndleadpt[sample] = new TH1D(name, "2nd Leading lepton p_{T} "+names[sample]+";2nd Leading lepton p_{T} [GeV]; events / 10 GeV", 10, 0, 100);
        h_2ndleadpt[sample]->SetLineColor(colsStack[sample]);
        h_2ndleadpt[sample]->SetFillColor(colsStack[sample]);
        h_2ndleadpt[sample]->SetFillStyle(1001);
        h_2ndleadpt[sample]->SetMarkerColor(colsStack[sample]);
        //h_leadpt[sample]->SetMarkerStyle(20+sample*5);
        h_2ndleadpt[sample]->Sumw2();
        
        name = Form("trail_leptons_%d",sample);
        h_trailpt[sample] = new TH1D(name, "Trailing lepton p_{T} "+names[sample]+";Trailing lepton p_{T} [GeV]; events / 10 GeV", 10, 0, 100);
        h_trailpt[sample]->SetLineColor(colsStack[sample]);
        h_trailpt[sample]->SetFillColor(colsStack[sample]);
        h_trailpt[sample]->SetFillStyle(1001);
        h_trailpt[sample]->SetMarkerColor(colsStack[sample]);
        //h_trailpt[sample]->SetMarkerStyle(20+sample*5);
        h_trailpt[sample]->Sumw2();
        
        name = Form("sumpt_leptons_%d",sample);
        h_sumpt[sample] = new TH1D(name, "Sum lepton p_{T} "+names[sample]+";Sum lepton p_{T} [GeV]; events / 10 GeV", 40, 0, 400);
        h_sumpt[sample]->SetLineColor(colsStack[sample]);
        h_sumpt[sample]->SetFillColor(colsStack[sample]);
        h_sumpt[sample]->SetFillStyle(1001);
        h_sumpt[sample]->SetMarkerColor(colsStack[sample]);
        //h_trailpt[sample]->SetMarkerStyle(20+sample*5);
        h_sumpt[sample]->Sumw2();
        
        name = Form("mll_%d",sample);
        h_mll[sample] = new TH1D(name, "Invariant mass of 2 lepton "+names[sample]+";Invariant mass of 2 lepton [GeV]; events / 10 GeV", 20, 70, 110);
        h_mll[sample]->SetLineColor(colsStack[sample]);
        h_mll[sample]->SetFillColor(colsStack[sample]);
        h_mll[sample]->SetFillStyle(1001);
        h_mll[sample]->SetMarkerColor(colsStack[sample]);
        h_mll[sample]->Sumw2();
        
        
        name = Form("h_njets_%d",sample);
        h_njets[sample] = new TH1D(name, "N_{jets} "+names[sample]+";N_{jets}; events / 1", 10, 0, 10);
        h_njets[sample]->SetLineColor(colsStack[sample]);
        h_njets[sample]->SetFillColor(colsStack[sample]);
        h_njets[sample]->SetFillStyle(1001);
        h_njets[sample]->SetMarkerColor(colsStack[sample]);
        //h_njets[sample]->SetMarkerStyle(20+sample*5);
        h_njets[sample]->Sumw2();
        
        name = Form("h_SR_%d",sample);
        h_SR[sample] = new TH1D(name, "N_{jets} "+names[sample]+";SR; events / 1", 400, 0, 400);
        h_SR[sample]->SetLineColor(colsStack[sample]);
        h_SR[sample]->SetFillColor(colsStack[sample]);
        h_SR[sample]->SetFillStyle(1001);
        h_SR[sample]->SetMarkerColor(colsStack[sample]);
        h_SR[sample]->Sumw2();
    }
    
    THStack* st_leadpt = new THStack("st_leadpt","Leading lepton p_{T}");
    THStack* st_2ndleadpt = new THStack("st_2ndleadpt","2nd Leading lepton p_{T}");
    THStack* st_trailpt = new THStack("st_trailpt","Trailing lepton p_{T}");
    THStack* st_sumpt = new THStack("st_sumpt","Sum lepton p_{T}");
    THStack* st_mll = new THStack("st_mll","Invariant mass of 2 leptons");
    THStack* st_njets = new THStack("st_njets","N_{jets}");
    THStack* st_SR = new THStack("st_SR","SR");
    THStack* st_trilep = new THStack("st_trilep","Di-lepton events");
    THStack* st_SIP3D = new THStack("st_SIP3D","SIP_{3D}");
    
    
    for (int i=nSamples-2; i!=-1; --i) {
        st_leadpt->Add(h_leadpt[i]);
        st_2ndleadpt->Add(h_2ndleadpt[i]);
        st_trailpt->Add(h_trailpt[i]);
        st_sumpt->Add(h_sumpt[i]);
        st_mll->Add(h_mll[i]);
        st_njets->Add(h_njets[i]);
        st_SR->Add(h_SR[i]);
        st_trilep->Add(h_trilep[i]);
        st_SIP3D->Add(h_SIP3D[i]);
    }
    
    const int nVars  = 17;
    TH1D* distribs[nVars][nSamples];
    THStack* distribsST[nVars];
    TString varN[nVars] = {"p_{T}^{leading} [GeV]","p_{T}^{trailing} [GeV]",
        "|#eta|^{max}","M_{ll}(OSSF)","M_{T} [GeV]","R_{0.3}","R_{mini}",
        "E_{T}^{miss}","H_{T}","N_{jets}","N_{jets40}","N_{b jets}","M_{T2}","M_{T2}^{true}","#DeltaM(OSSF,Z)", "M_{T2ll}", "M_{T2blbl}"};
    double varMin[nVars] = {0,0,
        0,70,0,0,0,
        30,0,0,0,0,0,0,0, 0, 0};
    
    double varMax[nVars] = {200,100,
        2.4,120,200,10,10,
        100,200,4,10,2,200,200,100, 200, 400
    };
    
    int nBins[nVars] = {40,20,
        12,10,20,50,50,
        7,5,4,10,2,40,40,20, 20, 40
    };
    
    for (int i=0; i!=nVars;++i) {
        TString name = Form("varST_%d",i);
        distribsST[i] = new THStack(name,varN[i]);
        for (int j=nSamples-1; j!=-1; --j) {
            name = Form("var_%d_%d",i,j);
            distribs[i][j] = new TH1D(name,name+";"+varN[i],nBins[i],varMin[i],varMax[i]);
            distribs[i][j]->SetLineColor(colsStack[j]);
            if (j < nSamples-1)
                distribs[i][j]->SetFillColor(colsStack[j]);
            distribs[i][j]->SetMarkerColor(colsStack[j]);
            distribs[i][j]->SetMarkerStyle(20);
            distribs[i][j]->SetMarkerSize(0.5);
            distribs[i][j]->SetLineWidth(1);
            distribs[i][j]->Sumw2();
            if (j < nSamples-1)
                distribsST[i]->Add(distribs[i][j]);
        }
        
    }

    
    double _multiConst[3][3];
    
    //loose
    _multiConst[0][0] = 0.22;
    _multiConst[0][1] = 0.63;
    _multiConst[0][2] = 6;
    
    //medium
    _multiConst[1][0] = 0.14;
    _multiConst[1][1] = 0.68;
    _multiConst[1][2] = 6.7;
    
    //tight
    _multiConst[2][0] = 0.10;
    _multiConst[2][1] = 0.70;
    _multiConst[2][2] = 7;
    
    int nLoc = 0;
    int nLocLoose = 0;
    int nLocTight = 0;
    int nLocEle = 0;
    int nLocMu = 0;
    int nJLoc = 0;
    int nBLoc = 0;
    double HTLoc = 0;
    int leptInd[10];
    int leptIndTight[3];
    int leptIndLoose;
    
    TLorentzVector l0p4, l1p4;
    
    int dilep_event_bkg[2] = {0};
    int trilep_event_bkg[2] = {0};
    int both_event_bkg[2] = {0};
    int total_event_bkg[2] = {0};

    int dilep_event_sig[2][6] = {0};
    int trilep_event_sig[2][6]= {0};
    int both_event_sig[2][6] = {0};
    int total_event_sig[2][6] = {0};

    ofstream outFileEventNumber;
    outFileEventNumber.open("tableEventNb.txt");
    outFileEventNumber.precision(3);

    //0 - vloose, 1 - vloose FOIDEmu, 2 - vlooseFOIDISOEMU, 3 - tight
    double valuesMVA[3][6];
    valuesMVA[0][0] = -0.16;
    valuesMVA[1][0] = -0.65;
    valuesMVA[2][0] = -0.74;

    valuesMVA[0][1] = -0.70;
    valuesMVA[1][1] = -0.83; 
    valuesMVA[2][1] = -0.92; 

    valuesMVA[0][2] = -0.155;
    valuesMVA[1][2] = -0.56;
    valuesMVA[2][2] = -0.76; 

    valuesMVA[0][3] = 0.87;
    valuesMVA[1][3] = 0.60;
    valuesMVA[2][3] = 0.17;

    valuesMVA[0][4] = 0.913286;
    valuesMVA[1][4] = 0.805013;
    valuesMVA[2][4] = 0.358969;

    valuesMVA[0][5] = 0.22;
    valuesMVA[1][5] = -0.32;
    valuesMVA[2][5] = -0.63;



    // My WP
    double stiso[2] = {0.0354, 0.0646};

    // Deniz WP
    //double stiso[2] = {0.0893, 0.121};

    double nEventsNumber[nSamples] = {0.};

    int tight_tight[nSamples] = {0};
    int tight_loose[nSamples] = {0};
 
    for (int sam = 0; sam != nSamples; ++sam) {
        hfile[sam] = new TFile("/Users/ikhvastu/Desktop/CERN/MCsamples/QCDsamples/"+fileList[sam],"read");
        
        hfile[sam]->cd("FakeElectrons");
        inputTreeFake[sam] = static_cast<TTree*>(hfile[sam]->Get("FakeElectrons/fakeTree"));
        
        inputTreeFake[sam]->SetBranchAddress("_eventNb", &_eventNb, &b__eventNb);
        inputTreeFake[sam]->SetBranchAddress("_runNb", &_runNb, &b__runNb);
        inputTreeFake[sam]->SetBranchAddress("_lumiBlock", &_lumiBlock, &b__lumiBlock);
        inputTreeFake[sam]->SetBranchAddress("_weight", &_weight, &b__weight);
        
        inputTreeFake[sam]->SetBranchAddress("_nLeptons", &_nLeptons, &b__nLeptons);
        inputTreeFake[sam]->SetBranchAddress("_lPt", _lPt, &b__lPt);
        inputTreeFake[sam]->SetBranchAddress("_lEta", _lEta, &b__lEta);
        inputTreeFake[sam]->SetBranchAddress("_lPhi", _lPhi, &b__lPhi);
        inputTreeFake[sam]->SetBranchAddress("_lE", _lE, &b__lE);
        inputTreeFake[sam]->SetBranchAddress("_lPtmc", _lPtmc, &b__lPtmc);
        inputTreeFake[sam]->SetBranchAddress("_lEtamc", _lEtamc, &b__lEtamc);
        inputTreeFake[sam]->SetBranchAddress("_lPhimc", _lPhimc, &b__lPhimc);
        inputTreeFake[sam]->SetBranchAddress("_lEmc", _lEmc, &b__lEmc);
        inputTreeFake[sam]->SetBranchAddress("_nuPtmc", _nuPtmc, &b__nuPtmc);
        inputTreeFake[sam]->SetBranchAddress("_nuEtamc", _nuEtamc, &b__nuEtamc);
        inputTreeFake[sam]->SetBranchAddress("_nuPhimc", _nuPhimc, &b__nuPhimc);
        inputTreeFake[sam]->SetBranchAddress("_nuEmc", _nuEmc, &b__nuEmc);
        //inputTreeFake[sam]->SetBranchAddress("_mtmc", _mtmc, &b__mtmc);
        //inputTreeFake[sam]->SetBranchAddress("_nEle", &_nEle, &b__nEle);
        //inputTreeFake[sam]->SetBranchAddress("_nMu", &_nMu, &b__nMu);
        //inputTreeFake[sam]->SetBranchAddress("_nTau", &_nTau, &b__nTau);
        inputTreeFake[sam]->SetBranchAddress("_flavors", _flavors, &b__flavors);
        inputTreeFake[sam]->SetBranchAddress("_charges", _charges, &b__charges);
        //inputTreeFake[sam]->SetBranchAddress("_indeces", _indeces, &b__indeces);
        inputTreeFake[sam]->SetBranchAddress("_isolation", _isolation, &b__isolation);
        inputTreeFake[sam]->SetBranchAddress("_miniisolation", _miniisolation, &b__miniisolation);
        inputTreeFake[sam]->SetBranchAddress("_multiisolation", _multiisolation, &b__multiisolation);
        inputTreeFake[sam]->SetBranchAddress("_ptrel", _ptrel, &b__ptrel);
        inputTreeFake[sam]->SetBranchAddress("_ptratio", _ptratio, &b__ptratio);
        //inputTreeFake[sam]->SetBranchAddress("_origin", _origin, &b__origin);
        inputTreeFake[sam]->SetBranchAddress("_originReduced", _originReduced, &b__originReduced);
        inputTreeFake[sam]->SetBranchAddress("_PVchi2", &_PVchi2, &b__PVchi2);
        inputTreeFake[sam]->SetBranchAddress("_PVerr", _PVerr, &b__PVerr);
        inputTreeFake[sam]->SetBranchAddress("_ipPV", _ipPV, &b__ipPV);
        inputTreeFake[sam]->SetBranchAddress("_ipPVerr", _ipPVerr, &b__ipPVerr);
        inputTreeFake[sam]->SetBranchAddress("_ipZPV", _ipZPV, &b__ipZPV);
        inputTreeFake[sam]->SetBranchAddress("_ipZPVerr", _ipZPVerr, &b__ipZPVerr);
        inputTreeFake[sam]->SetBranchAddress("_ipPVmc", _ipPVmc, &b__ipPVmc);
        inputTreeFake[sam]->SetBranchAddress("_3dIP", _3dIP, &b__3dIP);
        inputTreeFake[sam]->SetBranchAddress("_3dIPerr", _3dIPerr, &b__3dIPerr);
        inputTreeFake[sam]->SetBranchAddress("_3dIPsig", _3dIPsig, &b__3dIPsig);
        inputTreeFake[sam]->SetBranchAddress("_mt", _mt, &b__mt);
        //inputTreeFake[sam]->SetBranchAddress("_mt2", _mt2, &b__mt2);
        //inputTreeFake[sam]->SetBranchAddress("_mt2ll", &_mt2ll, &b__mt2ll);
        //inputTreeFake[sam]->SetBranchAddress("_mt2blbl", &_mt2blbl, &b__mt2blbl);
        //inputTreeFake[sam]->SetBranchAddress("_isloose", _isloose, &b__isloose);
        inputTreeFake[sam]->SetBranchAddress("_istight", _istight, &b__istight);
        //inputTreeFake[sam]->SetBranchAddress("_istightID", _istightID, &b__istightID);
        inputTreeFake[sam]->SetBranchAddress("_closeJetPtAll", _closeJetPtAll, &b__closeJetPtAll);
        //inputTreeFake[sam]->SetBranchAddress("_closeJetAngAll", _closeJetAngAll, &b__closeJetAngAll);
        //inputTreeFake[sam]->SetBranchAddress("_ptRelAll", _ptRelAll, &b__ptRelAll);
        //inputTreeFake[sam]->SetBranchAddress("_closeJetPtAllMC", _closeJetPtAllMC, &b__closeJetPtAllMC);
        //inputTreeFake[sam]->SetBranchAddress("_closeJetPtAllstatus", _closeJetPtAllstatus, &b__closeJetPtAllstatus);
        //inputTreeFake[sam]->SetBranchAddress("_partonIdMatched", _partonIdMatched, &b__partonIdMatched);
        //inputTreeFake[sam]->SetBranchAddress("_sameParton", _sameParton, &b__sameParton);
        inputTreeFake[sam]->SetBranchAddress("_n_PV", &_n_PV, &b__n_PV);
        inputTreeFake[sam]->SetBranchAddress("_met", &_met, &b__met);
        inputTreeFake[sam]->SetBranchAddress("_met_phi", &_met_phi, &b__met_phi);
        //inputTreeFake[sam]->SetBranchAddress("HT", &HT, &b_HT);
        //inputTreeFake[sam]->SetBranchAddress("HT40", &HT40, &b_HT40);
        inputTreeFake[sam]->SetBranchAddress("_genmet", &_genmet, &b__genmet);
        inputTreeFake[sam]->SetBranchAddress("_genmet_phi", &_genmet_phi, &b__genmet_phi);
        //inputTreeFake[sam]->SetBranchAddress("_mompt", _mompt, &b__mompt);
        //inputTreeFake[sam]->SetBranchAddress("_momphi", _momphi, &b__momphi);
        //inputTreeFake[sam]->SetBranchAddress("_mometa", _mometa, &b__mometa);
        //inputTreeFake[sam]->SetBranchAddress("_mompdg", _mompdg, &b__mompdg);
        inputTreeFake[sam]->SetBranchAddress("_n_bJets", &_n_bJets, &b__n_bJets);
        inputTreeFake[sam]->SetBranchAddress("_n_Jets", &_n_Jets, &b__n_Jets);
        //inputTreeFake[sam]->SetBranchAddress("_bTagged", _bTagged, &b__bTagged);
        inputTreeFake[sam]->SetBranchAddress("_jetE", _jetE, &b__jetE);
        inputTreeFake[sam]->SetBranchAddress("_jetEta", _jetEta, &b__jetEta);
        inputTreeFake[sam]->SetBranchAddress("_jetPhi", _jetPhi, &b__jetPhi);
        inputTreeFake[sam]->SetBranchAddress("_jetPt", _jetPt, &b__jetPt);
        inputTreeFake[sam]->SetBranchAddress("_csv", _csv, &b__csv);
        inputTreeFake[sam]->SetBranchAddress("_jetDeltaR", _jetDeltaR, &b__jetDeltaR);

        inputTreeFake[sam]->SetBranchAddress("_mvaValue", &_mvaValue);
        //inputTreeFake[sam]->SetBranchAddress("_jetDeltaRloose", _jetDeltaRloose, &b__jetDeltaRloose);
        
        if(sam != 27){
            inputTreeFake[sam]->SetBranchAddress("_genqpt", &_genqpt, &b__genqpt);
        }

        inputTreeFake[sam]->SetBranchAddress("_chargeConst", _chargeConst, &b__chargeConst);
        
        inputTreeFake[sam]->SetBranchAddress("_trigDiMuIso", &_trigDiMuIso , &b__trigDiMuIso ); // Di-muon isolation trigger
        inputTreeFake[sam]->SetBranchAddress("_trigMu8Ele23Iso", &_trigMu8Ele23Iso , &b__trigMu8Ele23Iso ); // Di-muon isolation trigger
        inputTreeFake[sam]->SetBranchAddress("_trigMu23Ele12Iso", &_trigMu23Ele12Iso , &b__trigMu23Ele12Iso ); // Di-muon isolation trigger
        inputTreeFake[sam]->SetBranchAddress("_trigEle23Ele12Iso", &_trigEle23Ele12Iso , &b__trigEle23Ele12Iso ); // Di-muon isolation trigger

        inputTreeFake[sam]->SetBranchAddress("_isPromptFinalState", &_isPromptFinalState);
        inputTreeFake[sam]->SetBranchAddress("_fromHardProcessFinalState", &_fromHardProcessFinalState);
        
        int leptonProv[4] = {0};

        _hCounter->Read("hCounter");
        Double_t scale = xSections[sam]*3000/(_hCounter->GetBinContent(1));
        //Double_t scale = 1.;

        Long64_t nEntries = inputTreeFake[sam]->GetEntries();
        std::cout<<"Entries in "<<fileList[sam]<<" "<<nEntries<<std::endl;
        std::cout<<xSections[sam]<<" "<<_hCounter->GetBinContent(1)<<" "<<scale<<std::endl;
        
        for (Long64_t it=0; it!=nEntries; ++it) {

            inputTreeFake[sam]->GetEntry(it);

            if (it%100000 == 0)
                cout<<'.'<<flush;

            //if( it == 100000) break;

            if (_nLeptons < 1) continue;

            nLoc = 0;

            nLocLoose = 0;
            nLocTight = 0;
            nLocEle = 0;
            nLocMu = 0;

            for (int i=0; i!=_nLeptons; ++i) {
                if (_flavors[i] > 1) continue;
                if(_lPt[i] < 10) continue;

                //if(!_istight[i]) continue;  

                if(_miniisolation[i][0] > 0.4) continue;
                if(_3dIPsig[i] > 4) continue;

                leptInd[nLoc] = i;
                nLoc++;
                   
                  
            }

            if(nLoc != 1) continue;
            if(_n_Jets < 1) continue;


            // Jet selection

            nJLoc = 0;

            bool dR1p0 = false;

            for (int i=0; i!=_n_Jets; ++i) {
               
                bool clean = true;
                

                TLorentzVector jet;
                jet.SetPtEtaPhiE(_jetPt[i], _jetEta[i], _jetPhi[i], _jetE[i]);

                for (int j=0; j!=nLoc; ++j) {
                   
                    TLorentzVector lep;
                    lep.SetPtEtaPhiE(_lPt[leptInd[j]], _lEta[leptInd[j]], _lPhi[leptInd[j]], _lE[leptInd[j]]);

                    if(jet.DeltaR(lep) > 1. && TMath::Abs(_jetEta[i]) < 2.4)
                      dR1p0 = true;
                    /*
                    if(jet.DeltaR(lep) < 0.4){
                        clean = false;
                        break;
                    } else clean = true;
                    */
                }
                
                if (clean && _jetPt[i] > 30 && TMath::Abs(_jetEta[i]) < 2.4) {
                    nJLoc++;
                    HTLoc+=_jetPt[i];
                    if(_csv[i] > 0.89){
                        nBLoc++;
                    }
                }
            }

            if(!dR1p0) continue;
            if(_met > 20) continue;
            if(_mt[leptInd[0]] > 20) continue;

            int leptIndLoose = leptInd[0];
            double leptPtCorr;

            if(_flavors[leptIndLoose] == 0 && _ptrel[leptIndLoose] > 7.2){
              leptPtCorr = _lPt[leptIndLoose] * (1 + TMath::Max(0., _miniisolation[leptIndLoose][0] - 0.16));
            }
            else{
              leptPtCorr = TMath::Max(_lPt[leptIndLoose], _closeJetPtAll[leptIndLoose] * 0.76);
            }
            
            if(_flavors[leptIndLoose] == 1 && _ptrel[leptIndLoose] > 6.0){
              leptPtCorr = _lPt[leptIndLoose] * (1 + TMath::Max(0., _miniisolation[leptIndLoose][0] - 0.20));
            }
            else{
              leptPtCorr = TMath::Max(_lPt[leptIndLoose], _closeJetPtAll[leptIndLoose] * 0.69);
            }


            // FR 2D map calculation
            //-------------------------------------

            if(_flavors[leptIndLoose] == 0){

              bool passedMVA = false;
              if (TMath::Abs(_lEta[leptIndLoose]) < 0.8 ) {
                passedMVA = _mvaValue[leptIndLoose] > valuesMVA[0][3];
              } else if (TMath::Abs(_lEta[leptIndLoose]) < 1.479 ) {
                passedMVA = _mvaValue[leptIndLoose] > valuesMVA[1][3];
              } else {
                passedMVA = _mvaValue[leptIndLoose] > valuesMVA[2][3];
              }

              //if(passedMVA && _isolation[leptIndLoose] < stiso[TMath::Abs(_lEta[leptIndLoose]) > 1.479]){
              if((_miniisolation[leptIndLoose][0] < 0.16) && ((_ptratio[leptIndLoose] > 0.76) || (_ptrel[leptIndLoose] > 7.2))) { 
                h_pt_eta_2D[0][1]->Fill(leptPtCorr, TMath::Abs(_lEta[leptIndLoose]), scale * _weight);
              }

              else{
                h_pt_eta_2D[0][0]->Fill(leptPtCorr, TMath::Abs(_lEta[leptIndLoose]), scale * _weight);
                
              }

            }

            if(_flavors[leptIndLoose] == 1){
              
                if ((_miniisolation[leptIndLoose][0] < 0.20) && ((_ptratio[leptIndLoose] > 0.69) || (_ptrel[leptIndLoose] > 6.0))){
                //if(_isolation[leptIndLoose] < 0.1){
                  h_pt_eta_2D[1][1]->Fill(leptPtCorr, TMath::Abs(_lEta[leptIndLoose]), scale * _weight);
                  tight_tight[sam]+=1;
                }

                else{
                  h_pt_eta_2D[1][0]->Fill(leptPtCorr, TMath::Abs(_lEta[leptIndLoose]), scale * _weight);
                  tight_loose[sam]+=1;
                }
               
              
            }   
            

            //std::cout << nLoc << " " << nJLoc << std::endl;
                        
        }
        
        cout<<endl;
        
        
    }
    cout<<endl;
    
    h_pt_eta_2D[0][1]->Divide(h_pt_eta_2D[0][0]);
    h_pt_eta_2D[1][1]->Divide(h_pt_eta_2D[1][0]);

    TFile *file_ele = TFile::Open("fakerate_QCD.root","RECREATE");
    TCanvas *c1 = new TCanvas("c1","c1");
     
    h_pt_eta_2D[0][1]->SetName("fakerate_ele");
    h_pt_eta_2D[0][1]->SetTitle("Fake Rate electrons");
    h_pt_eta_2D[0][1]->Draw("colz");
    h_pt_eta_2D[0][1]->Draw("textesame");
    h_pt_eta_2D[0][1]->Write();
    file_ele->Close();

    TFile *file_mu = TFile::Open("fakerate_QCD.root","RECREATE");
    TCanvas *c2 = new TCanvas("c2","c2");

    //TH2D h_mu = TranslateHisto(*h_pt_eta_2D[1][1]);
    h_pt_eta_2D[1][1]->SetName("fakerate_mu");
    h_pt_eta_2D[1][1]->SetTitle("Fake Rate muons");
    h_pt_eta_2D[1][1]->Draw("colz");
    h_pt_eta_2D[1][1]->Draw("textesame");
    h_pt_eta_2D[1][1]->Write();
    file_mu->Close();

    /*
    TCanvas *c3 = new TCanvas("c3","c3");
    //c3->Divide(2,1);
    //c3->cd(1);
    h_secLepIso[0]->SetTitle("Iso distribution");
    h_secLepIso[0]->DrawNormalized();
    //c3->cd(2);
    //h_secLepIso[1]->SetTitle("Miniiso distribution muons");
    h_secLepIso[1]->SetLineColor(kRed);
    h_secLepIso[1]->SetMarkerColor(kRed);
    h_secLepIso[1]->DrawNormalized("same");

    TCanvas *c4 = new TCanvas("c4","c4");
    //c3->Divide(2,1);
    //c3->cd(1);
    h_secLepIso[0]->SetTitle("Iso distribution");
    h_secLepIso[0]->Draw();
    //c3->cd(2);
    //h_secLepIso[1]->SetTitle("Miniiso distribution muons");
    h_secLepIso[1]->SetLineColor(kRed);
    h_secLepIso[1]->SetMarkerColor(kRed);
    h_secLepIso[1]->Draw("same");
    */
    /*
    h_secLepIso[2]->SetLineColor(kGreen);
    h_secLepIso[2]->SetMarkerColor(kGreen);
    h_secLepIso[2]->Draw("same");
    h_secLepIso[3]->SetLineColor(kBlue);
    h_secLepIso[3]->SetMarkerColor(kBlue);
    h_secLepIso[3]->Draw("same");
    */
    /*
    TLegend *leg = new TLegend(0.5, 0.5, 0.8, 0.8);
    leg->AddEntry(h_secLepIso[0], "electrons", "l");
    leg->AddEntry(h_secLepIso[1], "muons", "l");
    //leg->AddEntry(h_secLepIso[2], "after ptrel cut", "l");
    //leg->AddEntry(h_secLepIso[3], "after ptratio and ptrel cut", "l");

    leg->Draw("same");
    
    */
    /*
    TCanvas *c4 = new TCanvas("c4","c4");
    TH1D* histStack = (TH1D*)st_SIP3D->GetStack()->Last();
    histStack->SetTitle("t#bar{t} semi-leptonic");
    histStack->SetMinimum(0);
    histStack->SetMaximum(50000);
    histStack->Draw("hist");
    TLine *line = new TLine(4, 0, 4, 50000);
    line->SetLineColor(kRed);
    line->Draw("same");
    //st_SIP3D->Draw("hist");
    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kRed);  

    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(0.06);    
    latex.DrawLatex(0.8, 0.6,"Control Region");

    TLatex latex1;
    latex1.SetNDC();
    latex1.SetTextAngle(0);
    latex1.SetTextColor(kRed);  

    latex1.SetTextFont(42);
    latex1.SetTextAlign(31); 
    latex1.SetTextSize(0.06);    
    latex1.DrawLatex(0.2, 0.6,"Application Region");
    */

    std::cout<<"Done"<<std::endl;
    return ;
    
}


void showHist(TVirtualPad* c1, TH1D *hist, TH1D *hist2, THStack *stack, string title, string titleX, string titleY, double num, TLegend *leg){   

    TPad *pad1 = new TPad("pad1","pad1",0,0.3,1,1);
    pad1->SetTopMargin(0.1);
    pad1->SetBottomMargin(0);
    pad1->Draw();
    pad1->cd();
    
    double xmin = hist->GetXaxis()->GetXmin();
    double xmax = hist->GetXaxis()->GetXmax();
    //pad1->DrawFrame(xmin, -0.1, xmax, 1.1);
    
    hist->SetTitle(title.c_str());
    //hist->GetXaxis()->SetTitle(titleX.c_str());
    hist->GetYaxis()->SetTitle(titleY.c_str());
    hist->SetMaximum(hist->GetMaximum() * num);
    hist->SetLineWidth(1);
    hist->SetFillColor(0);
    hist->SetLineColor(1);
    hist->SetLineStyle(1);
    hist->SetMarkerSize(0.5);
    //hist->GetXaxis()->SetLabelSize(0.15);
    //hist->GetXaxis()->SetTitleSize(0.08);
    hist->GetYaxis()->SetLabelSize(0.08);
    hist->GetYaxis()->SetTitleSize(0.08);
    hist->GetYaxis()->SetTitleOffset(1.);
    hist->SetMarkerStyle(1);
    hist->Draw("e");
    stack->Draw("histsame");
    hist->Draw("esame");
    pad1->cd();
    pad1->Update();
    pad1->RedrawAxis();
    pad1->GetFrame()->Draw();
    leg->Draw("same");

    TLatex latex;
    latex.SetNDC();
    latex.SetTextAngle(0);
    latex.SetTextColor(kBlack);  

    latex.SetTextFont(42);
    latex.SetTextAlign(31); 
    latex.SetTextSize(0.07);    
    latex.DrawLatex(0.98, 0.93,lumi_13TeV + "(13 TeV)");

    TLatex cmsText;
    cmsText.SetNDC();
    cmsText.SetTextAngle(0);
    cmsText.SetTextColor(kBlack);  

    cmsText.SetTextFont(61);
    cmsText.SetTextAlign(31); 
    cmsText.SetTextSize(0.08);  
    cmsText.DrawLatex(0.25, 0.93,"CMS");


    TLatex extraText;
    extraText.SetNDC();
    extraText.SetTextAngle(0);
    extraText.SetTextColor(kBlack);  

    extraText.SetTextFont(52);
    extraText.SetTextAlign(31); 
    extraText.SetTextSize(0.07);  
    extraText.DrawLatex(0.5, 0.93,"Preliminary");

    

    c1->cd();

    TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.3);
    
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.4);
    pad2->Draw();
    pad2->cd();
    TH1D * histcopy = (TH1D*)hist->Clone("histcopy");
    //TH1D * histo_stack = (TH1D*)stack->GetHistogram();
    //histcopy->Sumw2();
    TLine *line = new TLine(xmin, 1, xmax, 1);
    line->SetLineStyle(2);
    histcopy->SetStats(0);

    histcopy->SetTitle("");
    histcopy->GetXaxis()->SetTitle(titleX.c_str());
    histcopy->GetYaxis()->SetTitle("data/pred");

    //histcopy->GetXaxis()->SetLabelSize(0.15);
    histcopy->GetYaxis()->SetLabelSize(0.12);
    //histcopy->GetXaxis()->SetTitleSize(0.15);
    histcopy->GetYaxis()->SetTitleSize(0.15);

    histcopy->GetYaxis()->SetTitleOffset(0.4);

    histcopy->SetMaximum(1.5);
    histcopy->SetMinimum(0.5);
    //
    histcopy->SetMarkerStyle(1);

    TList *histos = stack->GetHists();
    TIter next(histos);
    TH1D *histo_stack = (TH1D*)stack->GetHistogram();;
    while ((hist =(TH1D*)next())) {
      //cout << "Adding " << hist->GetName() << endl;
      histo_stack->Add(hist);
    }

    histcopy->Divide(histo_stack);

    histcopy->Draw("e");
    line->Draw("same");
    /*
    hist2->SetLineWidth(2.);
    hist2->SetFillColor(0);
    hist2->SetLineColor(1);
    hist2->SetLineStyle(3);
    hist2->Draw("hist same");
    hist2->Draw("axis same");
    */

}

int main(int argc, char *argv[]){

    TApplication *rootapp = new TApplication("example", &argc, argv);

    readTreeQCD();

    rootapp->Run();

    return 0;
}

double uncCalc(double a, double b, double c){

    return TMath::Sqrt(TMath::Power((TMath::Sqrt(a) + TMath::Sqrt(b))/c,2) + TMath::Power((a - b)/c/c*TMath::Sqrt(c),2));

}

TH2D TranslateHisto(const TH2 &input){
  int nx = input.GetNbinsX();
  int ny = input.GetNbinsY();
  TH2D output(input.GetName(), input.GetTitle(), nx, 0.5, nx+0.5, ny, 0.5, ny+0.5);
  output.Sumw2();
  output.SetStats(false);
  output.SetMarkerSize(2);
  output.SetLabelSize(0.05,"XYZ");
  output.SetTitleSize(0.05,"XYZ");
  
  //std::cout << input.GetName() << " ";

  for(int ix = 0; ix <= nx+1; ++ix){
    //double minActiv = 999.;
    //double maxActiv = -999.;
    for(int iy = 0; iy <= ny+1; ++iy){
      /*
      if(input.GetBinContent(ix, iy) > maxActiv)
        maxActiv = input.GetBinContent(ix, iy);
      if(input.GetBinContent(ix, iy) < minActiv)
        minActiv = input.GetBinContent(ix, iy);
        */
      output.SetBinContent(ix, iy, input.GetBinContent(ix, iy));
      output.SetBinError(ix, iy, input.GetBinError(ix, iy));
    }
    //std::cout << (maxActiv - minActiv) / 2 << " ";
  }

  std::cout << std::endl;
  
  for(int ix = 1; ix <= nx; ++ix){
    const TAxis *iaxis = input.GetXaxis();
    TAxis *oaxis = output.GetXaxis();
    if(iaxis == NULL || oaxis == NULL) continue;
    oaxis->SetTitle(iaxis->GetTitle());
    ostringstream oss;
    oss << iaxis->GetBinLowEdge(ix) << "-" << iaxis->GetBinUpEdge(ix) << flush;
    oaxis->SetBinLabel(ix, oss.str().c_str());
  }

  for(int iy = 1; iy <= ny; ++iy){
    const TAxis *iaxis = input.GetYaxis();
    TAxis *oaxis = output.GetYaxis();
    if(iaxis == NULL || oaxis == NULL) continue;
    oaxis->SetTitle(iaxis->GetTitle());
    ostringstream oss;
    oss << iaxis->GetBinLowEdge(iy) << "-" << iaxis->GetBinUpEdge(iy) << flush;
    oaxis->SetBinLabel(iy, oss.str().c_str());
  }

  return output;
}

void GetPatrioticPalette(){
  const unsigned num = 3;   
  double red[num] = {0., 1., 1.};
  double green[num] = {0., 1., 0.};
  double blue[num] = {1., 1., 0.};
  double stops[num] = {0., 0.5, 1.};
  int fi = TColor::CreateGradientColorTable(num,stops,red,green,blue,bands);
  for(int i = 0; i < bands; ++i){
    patriotic[i] = fi + i;
  }
}

void GetRainbowPalette(){
  const unsigned num = 6;
  double red[num] =   {1.,0.,0.,0.,1.,1.};
  double green[num] = {0.,0.,1.,1.,1.,0.};
  double blue[num] =  {1.,1.,1.,0.,0.,0.};
  double stops[num] = {0.,0.2,0.4,0.6,0.8,1.};
  int fi = TColor::CreateGradientColorTable(num,stops,red,green,blue,bands);
  for(int i = 0; i < bands; ++i){
    rainbow[i] = fi+i;
  }
}
