void Format_TH1D(TH1D* h2, int color, TString xtitle, TString ytitle, double ylow, double yup){
    h2->SetLineColor(color);
    h2->SetLineWidth(2);
    h2->SetStats(kFALSE);
    h2->GetXaxis()->SetTitle(xtitle);
    h2->GetYaxis()->SetTitle(ytitle);
    h2->SetTitle("");
    h2->GetXaxis()->CenterTitle();
    h2->GetYaxis()->CenterTitle();
    h2->GetXaxis()->SetTitleSize(0.06);
    h2->GetYaxis()->SetTitleSize(0.06);
    h2->GetXaxis()->SetTitleOffset(0.9);
    h2->GetYaxis()->SetTitleOffset(1.3);
    h2->GetXaxis()->SetLabelSize(0.05);
    h2->GetYaxis()->SetLabelSize(0.05);
        //h1->GetYaxis()->SetRangeUser(0., max*1.4);
    h2->GetYaxis()->SetRangeUser(ylow, yup);
}
void Format_Leg(TLegend* leg){
    leg->SetFillColor(0);
    leg->SetLineColor(0);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.052);
}
void Format_Canvas(TCanvas* c){
        c->SetFillColor(0);
        c->SetBorderMode(0);
        c->SetBorderSize(2);
        c->SetTickx(1);
        c->SetTicky(1);
        c->SetLeftMargin(0.12);
        c->SetRightMargin(0.16);
        c->SetTopMargin(0.07);
        c->SetBottomMargin(0.13);
        c->SetFrameFillStyle(0);
        c->SetFrameBorderMode(0);
        c->SetFrameFillStyle(0);
        c->SetFrameBorderMode(0);
}
void check_BS(){
    const int nsample=10;
	TString fileNames[nsample]={"new_TT_TuneCH3_13TeV-powheg-herwig7.root",
                                "new_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                                "new_W2JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                                "new_W3JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                                "new_W4JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                                "new_ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin.root",
                                "new_ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin.root",
                                "new_ST_tW_antitop_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg.root",
                                "new_ST_tW_top_5f_NoFullyHadronicDecays_TuneCP5_13TeV-powheg.root",
                                "new_ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo.root",
                                };
    double cross_sections[nsample]={832, 11917.5, 3850.4, 1124, 579.3, 81, 136, 19.3, 19.3, 3.4};
	double K_Factor[nsample]={1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,};                           
    int edge[]={0,1,10};
    double lumi=137.1;
    TString legend[3]={"semi","3jets","4jets"};
    int color[] = {2, 1, 4, 226, 6, kOrange + 2, 3, kYellow, 93};
    Double_t mtt_edges[9]={0,370,420,500,600,700,800,950,2000};
    Double_t ytt_edges[10]={-5.0,-1.4,-0.9,-0.5,-0.15,0.15,0.5,0.9,1.4,5.0};
    const int xbin=8, ybin=9;
    TChain *tree[10], *tree1[10];
    double expected_num[2];
    double expected_4jets[2];
    double expected_3jets[2];
    double events[2];
    double likelihood;
    TString condition;
    TH1D* bs[3];
    bs[1]=new TH1D("bs3","",81,16.9,33.1);
    bs[2]=new TH1D("bs4","",81,16.9,33.1);
    bs[0]=new TH1D("bs","",81,16.9,33.1);
    TH2D* ncut4;
    TH2D* ncut3;
    TH1D* nmc;
    double global_weight;
    TCanvas *canvas;
    canvas=new TCanvas("canvas","canvas",10,30,600,600);
    Format_Canvas(canvas);
    auto leg = new TLegend(.55, .65, .75, .95);
    Format_Leg(leg);
    TLegendEntry *leg_entry[3];
    ofstream oFile;
    oFile.open("BS_inc_csv.csv", ios::out|ios::trunc);
    oFile.setf(ios::fixed, ios::floatfield);
    oFile<<"likelihood_cut"<<","<<"S/B(semi)"<<","<<"Sig(semi)"<<","<<"Back(semi)"<<","<<"Sig_eff(semi)(%)"<<","<<"Back_eff(semi)(%)"<<",";
    oFile<<"S/B(3jets)"<<","<<"Sig(3jets)"<<","<<"Back(3jets)"<<","<<"Sig_eff(3jets)(%)"<<","<<"Back_eff(3jets)(%)"<<",";
    oFile<<"S/B(4jets)"<<","<<"Sig(4jets)"<<","<<"Back(4jets)"<<","<<"Sig_eff(4jets)(%)"<<","<<"Back_eff(4jets)(%)"<<endl;
    for(int k=0;k<10;k++){
        tree[k]=new TChain("mytree");
        tree1[k]=new TChain("rawtree");
        fileNames[k]=fileNames[k].ReplaceAll(".root","_*.root");
        cout<<fileNames[k]<<endl;
        tree[k]->Add(fileNames[k]);
        tree1[k]->Add(fileNames[k]);
    }
    for(int a=0;a<=80;a++){
        likelihood=17+1.0*a*0.2;
        condition=Form("((likelihood<%lf)&&(MtW<140))",likelihood);
        for(int j=0;j<2;j++){
            expected_num[j]=0;
            expected_4jets[j]=0;
            expected_3jets[j]=0;
            events[j]=0;
            for(int i=edge[j];i<edge[j+1];i++){             
                //cout<<i<<endl;
                ncut4=new TH2D("ncut4","",xbin,mtt_edges, ybin, ytt_edges);
                ncut3=new TH2D("ncut3","",xbin,mtt_edges, ybin, ytt_edges);
                nmc=new TH1D("nmc","",50,0,100);
                ncut4->Sumw2();
                ncut3->Sumw2();
                nmc->Sumw2();
                tree1[i]->Draw("nJet>>nmc","Generator_weight");
                global_weight=cross_sections[i]*lumi*K_Factor[i]*1000/nmc->GetSumOfWeights();
                if(j==0){
                    tree[i]->Draw("rapidity_tt:mass_tt>>ncut4",Form("(jet_num>=4)*Generator_weight*%lf*",global_weight)+condition);
                    tree[i]->Draw("rapidity_tt:mass_tt>>ncut3",Form("(jet_num==3)*Generator_weight*%lf*",global_weight)+condition);
                }
                else{
                    tree[i]->Draw("rapidity_tt:mass_tt>>ncut4",Form("(jet_num>=4)*Generator_weight*%lf*",global_weight)+condition);
                    tree[i]->Draw("rapidity_tt:mass_tt>>ncut3",Form("(jet_num==3)*Generator_weight*%lf*",global_weight)+condition);
                }
                events[j]+=cross_sections[i]*lumi*K_Factor[i]*1000;
                expected_num[j]+=ncut4->GetSumOfWeights()+ncut3->GetSumOfWeights();
                expected_4jets[j]+=ncut4->GetSumOfWeights();
                expected_3jets[j]+=ncut3->GetSumOfWeights();
                delete ncut3;
                delete ncut4;
                delete nmc;
            }
        }
        int bin=bs[0]->FindBin(likelihood);
        bs[0]->SetBinContent(bin,expected_num[0]/expected_num[1]);
        bs[1]->SetBinContent(bin,expected_3jets[0]/expected_3jets[1]);
        bs[2]->SetBinContent(bin,expected_4jets[0]/expected_4jets[1]);
        oFile<<"<="<<setprecision(2)<<likelihood<<","<<expected_num[0]/expected_num[1]<<","<<expected_num[0]*0.261<<","<<expected_num[1]*0.261<<",";
        oFile<<setprecision(2)<<expected_num[0]/events[0]*100<<","<<expected_num[1]/events[1]*100<<",";
        oFile<<setprecision(2)<<expected_3jets[0]/expected_3jets[1]<<","<<expected_3jets[0]*0.261<<","<<expected_3jets[1]*0.261<<",";
        oFile<<setprecision(2)<<expected_3jets[0]/events[0]*100<<","<<expected_3jets[1]/events[1]*100<<",";
        oFile<<setprecision(2)<<expected_4jets[0]/expected_4jets[1]<<","<<expected_4jets[0]*0.261<<","<<expected_4jets[1]*0.261<<",";
        oFile<<setprecision(2)<<expected_4jets[0]/events[0]*100<<","<<expected_4jets[1]/events[1]*100<<endl;
    }
    for(int k=0;k<3;k++){
        Format_TH1D(bs[k],color[k],"likelihood","S/B",0,40);
        leg_entry[k]=leg->AddEntry(bs[k], legend[k]);
        leg_entry[k]->SetTextColor(color[k]);
    }
    canvas->cd();
    bs[0]->Draw("colz");
    bs[1]->Draw("colzSame");
    bs[2]->Draw("colzSame");
    leg->Draw("same");
    canvas->Modified();
    canvas->Update();
    canvas->Print("BS.png"); 
    oFile.close(); 
}
