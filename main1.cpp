#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "TGraph.h"
#include "TCanvas.h"
#include "TMath.h"

#include "TH1F.h"
#include "TF1.h"
#include "TStyle.h"


#include "eventTools.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
        return 2;
    
    std::string filePath = argv[1];
         
    std::vector<std::string> fileNames;

    fileNames.push_back( filePath+"TR_0_0.txt");
//    fileNames.push_back( filePath+"wave_0.txt");
//    fileNames.push_back( filePath+"wave_1.txt");
//    fileNames.push_back( filePath+"wave_2.txt");
//    fileNames.push_back( filePath+"wave_3.txt");
//    fileNames.push_back( filePath+"wave_4.txt");
//    fileNames.push_back( filePath+"wave_5.txt");
//    fileNames.push_back( filePath+"wave_6.txt");
    fileNames.push_back( filePath+"wave_7.txt");
    
    
//             sineWave->SetParameter(0, 2000);
//             sineWave->SetParameter(1, 1000);
//             sineWave->SetParameter(2, 200);
// 
//    fileNames.push_back( filePath+"TR_0_0.txt");
//    fileNames.push_back( filePath+"TR_0_0_1.txt");
//    fileNames.push_back( filePath+"TR_0_0_2.txt");
//    fileNames.push_back( filePath+"TR_0_0_3.txt");
//    fileNames.push_back( filePath+"TR_0_0_4.txt");
//    fileNames.push_back( filePath+"TR_0_0_5.txt");
//    fileNames.push_back( filePath+"wave_0_1.txt");
//    fileNames.push_back( filePath+"wave_0_2.txt");
//    fileNames.push_back( filePath+"wave_0_3.txt");
//    fileNames.push_back( filePath+"wave_0_4.txt");
//    fileNames.push_back( filePath+"wave_0_5.txt");

     //         sineWave->SetParameter(0, 2000);
//             sineWave->SetParameter(1, 800);
//             sineWave->SetParameter(2, 600);
// 
    
//     fileNames.push_back( filePath+"TR_0_0_6.txt");
//     fileNames.push_back( filePath+"TR_0_0_7.txt");
//     fileNames.push_back( filePath+"TR_0_0_8.txt");
//     fileNames.push_back( filePath+"TR_0_0_9.txt");
//     fileNames.push_back( filePath+"TR_0_0_10.txt");

//         fileNames.push_back( filePath+"wave_0_6.txt");
//         fileNames.push_back( filePath+"wave_0_7.txt");
//         fileNames.push_back( filePath+"wave_0_8.txt");
//         fileNames.push_back( filePath+"wave_0_9.txt");
//         fileNames.push_back( filePath+"wave_0_10.txt");
//         
    checkTWsize(fileNames);
    
    std::vector<double> timeAxis;
    for(int i = 0; i < 1024; i++)
    {
        timeAxis.push_back(double(i));
    }
    
//     for (auto& path: fileNames)
//         plotSignals(path);

    gStyle->SetOptFit(1);
    
//    std::ofstream results;
//    results.open("results.txt", std::ofstream::app);
//    results <<  "FilePath \t Mean Amp \t Mean Period \t Chi2/NDF" << std::endl;
    
    for (auto& path: fileNames)
    {
        TString outName = path;
        outName.ReplaceAll(".txt","");
        std::ifstream file;
        file.open( path.c_str() );
        std::cout <<"Starting with: " <<  path <<  std::endl;
    
        std::vector< std::vector < double > > signals;
        int allEvents = checkEventSize( file );
        int counter = 0;
        
        
        
//        results <<  outName <<  "\t";
        
        for(int event = 0; event < 50; event++)
        {
            std::vector<double> points;
            for(int i = 0; i < 1024; i++)
            {
                double Y = 0;
                file >> Y;
                points.push_back(Y);
            }
            counter++;
            if (counter %  1000 == 0)
                std::cout <<  "Read "  << counter <<  " signals\n";
            if (points.size() != 1024 )
                return 5;
            
            signals.push_back(points);
        }
//        TH1F* hAmplitude = new TH1F("amp", "amp", 3000, 0, 3000);
//        TH1F* hPeriod = new TH1F("period", "period", 1000, 0, 1000);
//        TH1F* hChi2dNDF = new TH1F("chi2dNDF", "chi2dNDF", 100, 0, 100);
        counter = 0;
        //std::cout<<signals.size();
        for(auto& sig: signals)
        {
//            std::cout<<counter;
            TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",800, 800);
        
            TGraph* signalPlot = new TGraph(sig.size(), &timeAxis[0], &sig[0]);
            
            signalPlot->Draw("AC*");
//            TF1* sineWave = new TF1("sineWave","[0]+[1]*sin(2*3.14*x/[2]+[3])",0,1024);
//            std::cout<< *max_element(sig.begin(),sig.end())<<std::endl;

//            double intercept = ((*max_element(sig.begin(),sig.end())) + (*min_element(sig.begin(),sig.end())))/2;
//            double ampli = ((*max_element(sig.begin(),sig.end())) - (*min_element(sig.begin(),sig.end())))/2;
//            long int dist;
//            for (auto i =max_element(sig.begin(),sig.end()); i!=sig.end(); i++ )
//            {
//                //std::cout<<*i<<"\t"<<*(i+1)<<std::endl;
//                if(*i < *(i+10))
//                 {
//                     dist = distance((max_element(sig.begin(),sig.end())),(i+5));
//                     break;

//                 }

//            }
           // std::cout<<dist<<"\t";//<<*max_element(sig.begin(),sig.end())<<"\t"<<*(max_element(sig.begin(),sig.end())+2)<<"\t";
//            long int dist = distance((max_element(sig.begin(),sig.end())),(min_element(sig.begin(),sig.end())));

//            sineWave->SetParameter(0, intercept);
//            sineWave->SetParameter(1, ampli);
//            sineWave->SetParameter(2, 2*dist);
            //std::cout<<dist<<std::endl;


//            sineWave->SetParameter(0, 2000);
//            sineWave->SetParameter(1, 800);
//            sineWave->SetParameter(2, 200);



//            signalPlot->Fit("sineWave", "QM");
            
            
            counter++;
            if (counter < 50)
            {
//                std::cout<<"A="<<ampli<<"\t lamda="<<2*dist<<std::endl;
                TString name = outName;
                name += "_";
                name += counter;
                signalPlot->Draw("AP*");
                c1->SaveAs( name+".root");
                c1->SaveAs( name+".png");
            }


//            hChi2dNDF->Fill( sineWave->GetChisquare() / sineWave->GetNDF() );
//            double amplitude = sineWave->GetParameter(1);
//            hAmplitude->Fill(amplitude);
//            hPeriod->Fill( sineWave->GetParameter(2) );
            
//            if (counter % 1000 ==  0)
//                std::cout << "Fitted " <<  counter <<  " signals "<<  std::endl;
            
            delete c1;
            delete signalPlot;
//            delete sineWave;
//            if (counter==50) break;
        }
        
        TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",800, 800);

//        hAmplitude->Draw();
//        results <<  hAmplitude->GetMean() << "\t";
//        c1->SaveAs(outName+"amps.png");
//        c1->SaveAs(outName+"amps.root");
//        delete hAmplitude;
                
//        hPeriod->Draw();
//        results <<  hPeriod->GetMean() << "\t";
//        c1->SaveAs(outName+"period.root");
//        c1->SaveAs(outName+"period.png");
//        delete hPeriod;
        
//        hChi2dNDF->Draw();
//        results <<  hChi2dNDF->GetMean() << std::endl;
//        c1->SaveAs(outName+"chi2.root");
//        c1->SaveAs(outName+"chi2.png");
//        delete hChi2dNDF;
        
        delete c1;
        file.close();
    }
//    results.close();
    return 0;
}

