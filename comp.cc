{
    gStyle->SetPaintTextFormat("4.2f");

    /*
    TFile *file1_mu = TFile::Open("fakerate_mu_withCorr_sip3dmore4.root");
    //TFile *file1_mu = TFile::Open("fakerate_mu_noCorr_sip3dmore4.root");
    h1 = (TH2F*) file1_mu->Get("fakerate_mu");

    TFile *file2_mu = TFile::Open("fakerate_mu_withCorr_sip3dless4.root");
    //TFile *file2_mu = TFile::Open("fakerate_mu_noCorr_sip3dless4.root");
    h2 = (TH2F*) file2_mu->Get("fakerate_mu");

    TCanvas *c1 = new TCanvas("c1", "c1", 1300, 400);
    h1->Divide(h2);
    h1->SetTitle("Fake rate comparison - muons");
    h1->SetMarkerSize(2.);
    h1->Draw("texte");

    TFile *file1_el = TFile::Open("fakerate_ele_withCorr_sip3dmore4.root");
    //TFile *file1_el = TFile::Open("fakerate_ele_noCorr_sip3dmore4.root");
    h3 = (TH2F*) file1_el->Get("fakerate_ele");

    TFile *file2_el = TFile::Open("fakerate_ele_withCorr_sip3dless4.root");
    //TFile *file2_el = TFile::Open("fakerate_ele_noCorr_sip3dless4.root");
    h4 = (TH2F*) file2_el->Get("fakerate_ele");

    TCanvas *c2 = new TCanvas("c2", "c2", 1300, 400);
    h3->Divide(h4);
    h3->SetTitle("Fake rate comparison - electrons");
    h3->SetMarkerSize(2.);
    h3->Draw("texte");
    
*/
    TString names[4] = {"Loose mu", "Tight mu", "Loose ele", "Tight ele"};

    TFile *file1 = TFile::Open("lpt_sip3dless4.root");
    TH1F *h_less[4];
    h_less[0] = (TH1F*) file1->Get("loose_mu");
    h_less[1] = (TH1F*) file1->Get("tight_mu");
    h_less[2] = (TH1F*) file1->Get("loose_ele");
    h_less[3] = (TH1F*) file1->Get("tight_ele");

    TFile *file2 = TFile::Open("lpt_sip3dmore4.root");
    TH1F *h_more[4];
    h_more[0] = (TH1F*) file2->Get("loose_mu");
    h_more[1] = (TH1F*) file2->Get("tight_mu");
    h_more[2] = (TH1F*) file2->Get("loose_ele");
    h_more[3] = (TH1F*) file2->Get("tight_ele");

    TLegend *leg = new TLegend(0.5,0.5,0.8,0.8);
    leg->AddEntry(h_less[0], "SIP3D < 4", "l");
    leg->AddEntry(h_more[0], "SIP3D > 4", "l");

    TCanvas *c1 = new TCanvas("c1", "c1", 1300, 800);
    c1->Divide(2,2);

    for(int i = 0; i < 4; i++){
        c1->cd(i+1);
        h_less[i]->SetTitle(names[i]);
        h_less[i]->DrawNormalized();    
        h_more[i]->SetMarkerColor(kRed);
        h_more[i]->SetLineColor(kRed);
        h_more[i]->DrawNormalized("same");    
        leg->Draw("same");
    }
    /*
    TString names[4] = {"Loose mu", "Tight mu", "Loose ele", "Tight ele"};

    TFile *file1 = TFile::Open("closestjetpt_sip3dless4.root");
    TH1F *h_less[4];
    h_less[0] = (TH1F*) file1->Get("loose_mu");
    h_less[1] = (TH1F*) file1->Get("tight_mu");
    h_less[2] = (TH1F*) file1->Get("loose_ele");
    h_less[3] = (TH1F*) file1->Get("tight_ele");

    TFile *file2 = TFile::Open("closestjetpt_sip3dmore4.root");
    TH1F *h_more[4];
    h_more[0] = (TH1F*) file2->Get("loose_mu");
    h_more[1] = (TH1F*) file2->Get("tight_mu");
    h_more[2] = (TH1F*) file2->Get("loose_ele");
    h_more[3] = (TH1F*) file2->Get("tight_ele");

    TLegend *leg = new TLegend(0.5,0.5,0.8,0.8);
    leg->AddEntry(h_less[0], "SIP3D < 4", "l");
    leg->AddEntry(h_more[0], "SIP3D > 4", "l");

    TCanvas *c1 = new TCanvas("c1", "c1", 1300, 800);
    c1->Divide(2,2);

    for(int i = 0; i < 4; i++){
        c1->cd(i+1);
        h_less[i]->SetTitle(names[i]);
        h_less[i]->DrawNormalized();    
        h_more[i]->SetMarkerColor(kRed);
        h_more[i]->SetLineColor(kRed);
        h_more[i]->DrawNormalized("same");    
        leg->Draw("same");
    }
    */
}
