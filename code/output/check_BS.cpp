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
    const int nsample=22;
  	TString fileNames[nsample] = {	"new_TTToSemiLeptonic_TuneCP5_13TeV-powheg.root",
                            "new_TTTo2L2Nu_TuneCP5_13TeV-powheg.root",
                            "new_TTToHadronic_TuneCP5_13TeV-powheg.root",

                            /*"new_DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM.root",                           
                            "new_DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM.root",*/
                        
                            "new_ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo.root",
                            "new_ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin.root",
                            "new_ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin.root",
                            "new_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg.root",
                            "new_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg.root",                                                                               
                            
                            /*"new_WWTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX.root",
                            "new_ZZTo2Q2L_mllmin4p0_TuneCP5_13TeV-amcatnloFXFX.root",
                            "new_WZTo1L1Nu2Q_TuneCP5_13TeV-amcatnloFXFX.root",*/
                            
                            "new_WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM.root",
                            "new_WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM.root",
                            "new_WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM.root",
                            "new_WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM.root",
                            "new_WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM.root",
                            "new_WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM.root",
                        //    "new_WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM.root",

                            "new_QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
							"new_QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM.root",
                            "new_QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM.root",};
    TString processNames[nsample] = {"TTToSemiLeptonic",
                                    "TTTo2L2Nu",
                                    "TTToHadronic",

                                    /*"DYJetsToLL_M-50_HT-70to100",
                                    "DYJetsToLL_M-50_HT-100to200",
                                    "DYJetsToLL_M-50_HT-200to400",
                                    "DYJetsToLL_M-50_HT-400to600",
                                    "DYJetsToLL_M-50_HT-600to800",
                                    "DYJetsToLL_M-50_HT-800to1200",
                                    "DYJetsToLL_M-50_HT-1200to2500",                           
                                    "DYJetsToLL_M-50_HT-2500toInf",*/
                                
                                    "ST_s-channel_4f_leptonDecays",
                                    "ST_t-channel_antitop_4f_InclusiveDecays",
                                    "ST_t-channel_top_4f_InclusiveDecays",
                                    "ST_tW_antitop_5f_inclusiveDecays",
                                    "ST_tW_top_5f_inclusiveDecays",                                                                               
                                    
                                    /*"WWTo1L1Nu2Q",
                                    "ZZTo2Q2L",
                                    "WZTo1L1Nu2Q",*/
                                    
                                    "WJetsToLNu_HT-100To200",
                                    "WJetsToLNu_HT-200To400",
                                    "WJetsToLNu_HT-400To600",
                                    "WJetsToLNu_HT-600To800",
                                    "WJetsToLNu_HT-800To1200",
                                    "WJetsToLNu_HT-1200To2500",
                                    //"WJetsToLNu_HT-2500ToInf",

                                    "QCD_HT100to200",
                                    "QCD_HT200to300",
                                    "QCD_HT300to500",
                                    "QCD_HT500to700",
                                    "QCD_HT700to1000",
                                    "QCD_HT1000to1500",
                                    "QCD_HT1500to2000",
                                    "QCD_HT2000toInf",};
    TString process[6]={"ttbar","DY","single_top","VV","V+Jets","QCD",};
    double cross_sections[nsample]={366.91, 89.05, 377.96,
									//169.9, 147.4, 41.0, 5.7, 1.4, 0.63, 0.15, 0.0036,
									3.36, 136.02, 80.95, 35.6, 35.6,
									//45.68, 4.478, 11.66,
									1345.7, 359.7, 48.9, 12.1, 5.5, 1.3,// 0.032,
								    27990000, 1712000, 347700, 32100, 6831, 1207, 119.9, 25.2};
	double K_Factor[nsample]={1.0, 1.0, 1.0,
								//1.23,1.23,1.23,1.23,1.23,1.23,1.23,1.23,
								1.0,1.0,1.0,1.0,1.0,
								//1.0,1.0,1.0,
								1.21,1.21,1.21,1.21,1.21,1.21,//1.21,
								1.0, 1.0, 1.0,1.0, 1.0, 1.0,1.0, 1.0,};                           
    int edge[]={0,3,14};
    double lumi=137.1;
    TString legend[3]={"semi","3jets","4jets"};
    int color[] = {2, 1, 4, 226, 6, kOrange + 2, 3, kYellow, 93};
    Double_t mtt_edges[9]={0,370,420,500,600,700,800,950,2000};
    Double_t ytt_edges[10]={-5.0,-1.4,-0.9,-0.5,-0.15,0.15,0.5,0.9,1.4,5.0};
    const int xbin=8, ybin=9;
    TChain *tree[26], *tree1[26];
    double expected_num[2];
    double expected_4jets[2];
    double expected_3jets[2];
    double likelihood;
    TString condition;
    TH1D* bs[3];
    bs[1]=new TH1D("bs3","",121,8.9,33.1);
    bs[2]=new TH1D("bs4","",121,8.9,33.1);
    bs[0]=new TH1D("bs","",121,8.9,33.1);
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
    oFile.open("BS.csv", ios::out|ios::trunc);
    oFile.setf(ios::fixed, ios::floatfield);
    oFile<<"likelihood_cut"<<","<<"S/B(semi)"<<","<<"Sig(semi)"<<","<<"Back(semi)"<<",";
    oFile<<"S/B(3jets)"<<","<<"Sig(3jets)"<<","<<"Back(3jets)"<<",";
    oFile<<"S/B(4jets)"<<","<<"Sig(4jets)"<<","<<"Back(4jets)"<<endl;
    for(int k=0;k<14;k++){
        tree[k]=new TChain("mytree");
        tree1[k]=new TChain("rawtree");
        fileNames[k]=fileNames[k].ReplaceAll(".root","_*.root");
        tree[k]->Add(fileNames[k]);
        tree1[k]->Add(fileNames[k]);
    }
    for(int a=0;a<=120;a++){
        likelihood=9.0+1.0*a*0.2;
        condition=Form("(likelihood<%lf)",likelihood);
        for(int j=0;j<2;j++){
            expected_num[j]=0;
            expected_4jets[j]=0;
            expected_3jets[j]=0;
            for(int i=edge[j];i<edge[j+1];i++){                
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
        oFile<<setprecision(2)<<expected_3jets[0]/expected_3jets[1]<<","<<expected_3jets[0]*0.261<<","<<expected_3jets[1]*0.261<<",";
        oFile<<setprecision(2)<<expected_4jets[0]/expected_4jets[1]<<","<<expected_4jets[0]*0.261<<","<<expected_4jets[1]*0.261<<endl;
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
