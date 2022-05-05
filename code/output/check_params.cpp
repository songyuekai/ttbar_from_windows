void setzero(double* a, int k){
    for(int i=0;i<k;i++){
        a[i]=0;
    }
}
void sumall(double *a, TH2D **h1, int k){
    for(int i=0;i<k;i++){
        a[i]=a[i]+h1[i]->GetSumOfWeights();
    }
}
void check_params(){
    const int nsample=21;
  	TString fileNames[nsample]={"new_TT_TuneCH3_13TeV-powheg-herwig7.root",
        
                            "new_W1JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                            "new_W2JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                            "new_W3JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",
                            "new_W4JetsToLNu_TuneCP5_13TeV-madgraphMLM.root",

                            "new_ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin.root",
                            "new_ST_t-channel_top_4f_InclusiveDecays_TuneCP5_13TeV-powheg-madspin.root",
                            "../../output2/new_ST_tW_antitop_5f_inclusiveDecays_TuneCP5_13TeV-powheg.root",
                            "../../output2/new_ST_tW_top_5f_inclusiveDecays_TuneCP5_13TeV-powheg.root",
                            "new_ST_s-channel_4f_leptonDecays_TuneCP5_13TeV-amcatnlo.root",

                            "new_DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                            "new_DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM.root",                           
                            "new_DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM.root",
                                
                            "new_WW_TuneCP5_13TeV.root",
                            "new_WZ_TuneCP5_13TeV.root",
                            "new_ZZ_TuneCP5_13TeV.root",                                                                                          
                   
    };
    TString process[6]={"ttbar","WJets","STop","DYJets","VV","QCD",};
    Float_t cross_sections[nsample]={832,
                                    11917.5, 3850.4, 1124, 579.3,
                                    81, 136, 35.6, 35.6, 3.4,
                                    169.9, 147.4, 41.0, 5.7, 1.4, 0.63, 0.15, 0.0036,
                                    118.5, 47.1, 16.5,
                                    //27990000, 1712000, 347700, 32100, 6831, 1207, 119.9, 25.2,
                                    };
    Float_t K_Factor[nsample]={ 1.0,
                                1.0, 1.0, 1.0, 1.0, 
                                1.0, 1.0, 1.0, 1.0, 1.0,
                                1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23, 1.23,
                                1.0, 1.0, 1.0,
                                //1.0, 1.0, 1.0,1.0, 1.0, 1.0,1.0, 1.0,
                            };
    TString EW_weight[6]={"weight_ci0000","weight_ci0100","weight_ci0010","weight_ci0001"};                           
    int edge[]={0,1,5,10,18,21};
    double lumi=137.1;
    Double_t mtt_edges[9]={0,370,420,500,600,700,800,950,2000};
    Double_t ytt_edges[10]={-5.0,-1.4,-0.9,-0.5,-0.15,0.15,0.5,0.9,1.4,5.0};
    const int xbin=8, ybin=9;
    TString treesname[]={"jesUp","jesDown","jerUp","jerDown","unclusUp","unclusDown"};
    TString pdfname[]={"pdfUp","pdfDown"};
    TString pdffiles[]={"pdfweight_4jets.root","pdfweight_3jets.root"};
    TFile* pdffile[2];
    TChain *tree, *tree1;
    TChain *trees[6];
    double expected_num;
    double expected_4jets;
    double expected_3jets;
    TString condition="(likelihood<19.0)";
    ofstream oFile;
    oFile.open("params.csv", ios::out|ios::trunc);
    oFile.setf(ios::fixed, ios::floatfield);
    oFile << "process" << "," << "expected_number" << "," << ">=4jets" <<","<<"3jets"<<",";
    oFile << "jesup(%)"<<","<<"jesdown(%)"<<","<<"jerup(%)"<<","<<"jerdown(%)"<<","<<"unclusup(%)"<<","<<"unclusdown(%)"<<",";
    TH2D* ncut4;
    TH2D* ncut3;
    TH2D* yield[6], *yield1[4], *yield2[4];
    double weightup[4], weightdown[4];
    double param[6];
    TH1D* nmc;
    TH1D* pdf[4];
    vector<TString> sysNames;
    double global_weight;
    for(int num=0;num<2;num++)
        pdffile[num]=new TFile(pdffiles[num]);
    for(int j=0;j<4;j++){
        expected_num=0;
        expected_4jets=0;
        expected_3jets=0;
        setzero(param,6);
        setzero(weightup,4);
        setzero(weightdown,4);
        for(int i=edge[j];i<edge[j+1];i++){
            tree=new TChain("mytree");
            tree1=new TChain("rawtree");
            fileNames[i]=fileNames[i].ReplaceAll(".root","_*.root");
            tree->Add(fileNames[i]);
            tree1->Add(fileNames[i]);
            if(i==0){
                TH1D* hname=new TH1D("hname","hname",20,0,20);
                tree->Draw("weight_name>>hname");
                for(int k=0;k<hname->GetNbinsX();k++){
                    TString sysname=hname->GetXaxis()->GetBinLabel(k+1);
                    sysNames.push_back(sysname);
                    oFile << sysname+"Up(%)"<<","<<sysname+"Down(%)"<<",";
                }
                oFile << "pdfup(%)"<<","<<"pdfdown(%)"<<",";
                oFile << "pdfup_4jets(%)"<<","<<"pdfdown_4jets(%)"<<","<<"pdfup_3jets(%)"<<","<<"pdfdown_3jets(%)"<<",";
                oFile<<endl;
            }
            for(int k=0;k<6;k++){
                trees[k]=new TChain(treesname[k]);
                trees[k]->Add(fileNames[i]);
                yield[k]=new TH2D(treesname[k],"",xbin,mtt_edges, ybin, ytt_edges);
                yield[k]->Sumw2();
            }
            for(int k=0;k<sysNames.size();k++){
                yield1[k]=new TH2D(sysNames[k]+"Up","",xbin,mtt_edges, ybin, ytt_edges);
                yield2[k]=new TH2D(sysNames[k]+"Down","",xbin,mtt_edges, ybin, ytt_edges);
                yield1[k]->Sumw2();
                yield2[k]->Sumw2();
            }
            ncut4=new TH2D("ncut4","",xbin,mtt_edges, ybin, ytt_edges);
            ncut3=new TH2D("ncut3","",xbin,mtt_edges, ybin, ytt_edges);
            nmc=new TH1D("nmc","",50,0,100);
            ncut4->Sumw2();
            ncut3->Sumw2();
            nmc->Sumw2();
            tree1->Draw("nJet>>nmc","Generator_weight");
            global_weight=cross_sections[i]*lumi*K_Factor[i]*1000/nmc->GetSumOfWeights();
            tree->Draw("rapidity_tt:mass_tt>>ncut4",Form("(jet_num>=4)*Generator_weight*%lf*",global_weight)+condition);
            tree->Draw("rapidity_tt:mass_tt>>ncut3",Form("(jet_num==3)*Generator_weight*%lf*",global_weight)+condition);
            for(int k=0;k<6;k++){
                trees[k]->Draw("rapidity_tt:mass_tt>>"+treesname[k],Form("Generator_weight*%lf*",global_weight)+condition);
            }
            for(int k=0;k<sysNames.size();k++){
                tree->Draw("rapidity_tt:mass_tt>>"+sysNames[k]+"Up",Form("Generator_weight*%lf*weight_up*(weight_name==\"%s\")*",global_weight,sysNames[k].Data())+condition);
                tree->Draw("rapidity_tt:mass_tt>>"+sysNames[k]+"Down",Form("Generator_weight*%lf*weight_down*(weight_name==\"%s\")*",global_weight,sysNames[k].Data())+condition);
            }
            expected_num+=ncut4->GetSumOfWeights()+ncut3->GetSumOfWeights();
            expected_4jets+=ncut4->GetSumOfWeights();
            expected_3jets+=ncut3->GetSumOfWeights();
            sumall(weightup,yield1,4);
            sumall(weightdown,yield2,4);
            sumall(param,yield,6);
            delete ncut3;
            delete ncut4;
            delete nmc;
            delete tree;
            delete tree1;
            for(int k=0;k<6;k++){
                delete trees[k];
                delete yield[k];
            }
            for(int k=0;k<sysNames.size();k++){
                delete yield1[k];
                delete yield2[k];
            }
        }
        oFile<<process[j]<<",";
        oFile<<setprecision(2)<<expected_num<<","<<expected_4jets<<","<<expected_3jets<<",";
        for(int k=0;k<6;k++)
            oFile<<setprecision(2)<<(param[k]/expected_num*100-100)<<",";
        for(int k=0;k<sysNames.size();k++)
            oFile<<setprecision(2)<<(weightup[k]/expected_num*100-100)<<","<<(weightdown[k]/expected_num*100-100)<<",";
        if(j>0){
            pdf[0]=(TH1D*)pdffile[0]->GetObjectChecked(process[j]+"_pdfUp","TH1D");
            pdf[1]=(TH1D*)pdffile[0]->GetObjectChecked(process[j]+"_pdfDown","TH1D");
            pdf[2]=(TH1D*)pdffile[1]->GetObjectChecked(process[j]+"_pdfUp","TH1D");
            pdf[3]=(TH1D*)pdffile[1]->GetObjectChecked(process[j]+"_pdfDown","TH1D");
            oFile<<setprecision(2)<<((pdf[0]->GetSumOfWeights()+pdf[2]->GetSumOfWeights())/expected_num*100-100)<<",";
            oFile<<setprecision(2)<<((pdf[1]->GetSumOfWeights()+pdf[3]->GetSumOfWeights())/expected_num*100-100)<<",";
            oFile<<setprecision(2)<<(pdf[0]->GetSumOfWeights()/expected_4jets*100-100)<<",";
            oFile<<setprecision(2)<<(pdf[1]->GetSumOfWeights()/expected_4jets*100-100)<<",";
            oFile<<setprecision(2)<<(pdf[2]->GetSumOfWeights()/expected_3jets*100-100)<<",";
            oFile<<setprecision(2)<<(pdf[3]->GetSumOfWeights()/expected_3jets*100-100)<<",";
            oFile<<endl;
            for(int k=0;k<4;k++)
                delete pdf[k];
        }   
        else{
            oFile<<endl;
            for(int nweight=0;nweight<4;nweight++){
                expected_num=0;
                expected_4jets=0;
                expected_3jets=0;
                setzero(param,6);
                setzero(weightup,4);
                setzero(weightdown,4);
                for(int i=edge[0];i<edge[1];i++){
                    tree=new TChain("mytree");
                    tree1=new TChain("rawtree");
                    tree->Add(fileNames[i]);
                    tree1->Add(fileNames[i]);
                    for(int k=0;k<6;k++){
                        trees[k]=new TChain(treesname[k]);
                        trees[k]->Add(fileNames[i]);
                        yield[k]=new TH2D(treesname[k],"",xbin,mtt_edges, ybin, ytt_edges);
                        yield[k]->Sumw2();
                    }
                    for(int k=0;k<sysNames.size();k++){
                        yield1[k]=new TH2D(sysNames[k]+"Up","",xbin,mtt_edges, ybin, ytt_edges);
                        yield2[k]=new TH2D(sysNames[k]+"Down","",xbin,mtt_edges, ybin, ytt_edges);
                        yield1[k]->Sumw2();
                        yield2[k]->Sumw2();
                    }
                    ncut4=new TH2D("ncut4","",xbin,mtt_edges, ybin, ytt_edges);
                    ncut3=new TH2D("ncut3","",xbin,mtt_edges, ybin, ytt_edges);
                    nmc=new TH1D("nmc","",50,0,100);
                    ncut4->Sumw2();
                    ncut3->Sumw2();
                    nmc->Sumw2();
                    tree1->Draw("nJet>>nmc","Generator_weight");
                    global_weight=cross_sections[i]*lumi*K_Factor[i]*1000/nmc->GetSumOfWeights();
                    tree->Draw("rapidity_tt:mass_tt>>ncut4",Form("(jet_num>=4)*Generator_weight*%s*%lf*",EW_weight[nweight].Data(),global_weight)+condition);
                    tree->Draw("rapidity_tt:mass_tt>>ncut3",Form("(jet_num==3)*Generator_weight*%s*%lf*",EW_weight[nweight].Data(),global_weight)+condition);
                    for(int k=0;k<6;k++){
                        trees[k]->Draw("rapidity_tt:mass_tt>>"+treesname[k],Form("Generator_weight*%s*%lf*",EW_weight[nweight].Data(),global_weight)+condition);
                    }
                    for(int k=0;k<sysNames.size();k++){
                        tree->Draw("rapidity_tt:mass_tt>>"+sysNames[k]+"Up",Form("Generator_weight*%s*%lf*weight_up*(weight_name==\"%s\")*",EW_weight[nweight].Data(),global_weight,sysNames[k].Data())+condition);
                        tree->Draw("rapidity_tt:mass_tt>>"+sysNames[k]+"Down",Form("Generator_weight*%s*%lf*weight_down*(weight_name==\"%s\")*",EW_weight[nweight].Data(),global_weight,sysNames[k].Data())+condition);
                    }
                    expected_num+=ncut4->GetSumOfWeights()+ncut3->GetSumOfWeights();
                    expected_4jets+=ncut4->GetSumOfWeights();
                    expected_3jets+=ncut3->GetSumOfWeights();
                    sumall(weightup,yield1,4);
                    sumall(weightdown,yield2,4);
                    sumall(param,yield,6);
                    delete ncut3;
                    delete ncut4;
                    delete nmc;
                    delete tree;
                    delete tree1;
                    for(int k=0;k<6;k++){
                        delete trees[k];
                        delete yield[k];
                    }
                    for(int k=0;k<sysNames.size();k++){
                        delete yield1[k];
                        delete yield2[k];
                    }
                }
                oFile<<process[j]+EW_weight[nweight]<<",";
                oFile<<setprecision(2)<<expected_num<<","<<expected_4jets<<","<<expected_3jets<<",";
                for(int k=0;k<6;k++)
                    oFile<<setprecision(2)<<(param[k]/expected_num*100-100)<<",";
                for(int k=0;k<sysNames.size();k++)
                    oFile<<setprecision(2)<<(weightup[k]/expected_num*100-100)<<","<<(weightdown[k]/expected_num*100-100)<<",";
                pdf[0]=(TH1D*)pdffile[0]->GetObjectChecked(process[0]+"_"+EW_weight[nweight]+"_pdfUp","TH1D");
                pdf[1]=(TH1D*)pdffile[0]->GetObjectChecked(process[0]+"_"+EW_weight[nweight]+"_pdfDown","TH1D");
                pdf[2]=(TH1D*)pdffile[1]->GetObjectChecked(process[0]+"_"+EW_weight[nweight]+"_pdfUp","TH1D");
                pdf[3]=(TH1D*)pdffile[1]->GetObjectChecked(process[0]+"_"+EW_weight[nweight]+"_pdfDown","TH1D");
                oFile<<setprecision(2)<<((pdf[0]->GetSumOfWeights()+pdf[2]->GetSumOfWeights())/expected_num*100-100)<<",";
                oFile<<setprecision(2)<<((pdf[1]->GetSumOfWeights()+pdf[3]->GetSumOfWeights())/expected_num*100-100)<<",";
                oFile<<setprecision(2)<<(pdf[0]->GetSumOfWeights()/expected_4jets*100-100)<<",";
                oFile<<setprecision(2)<<(pdf[1]->GetSumOfWeights()/expected_4jets*100-100)<<",";
                oFile<<setprecision(2)<<(pdf[2]->GetSumOfWeights()/expected_3jets*100-100)<<",";
                oFile<<setprecision(2)<<(pdf[3]->GetSumOfWeights()/expected_3jets*100-100)<<",";
                oFile<<endl;
                for(int k=0;k<4;k++)
                    delete pdf[k];
            }
        }        
    }
    oFile.close();
}

