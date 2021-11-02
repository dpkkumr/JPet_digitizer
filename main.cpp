#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "TGraph.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TMath.h"

#include "TH1F.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLegend.h"


#include "eventTools.h"

double aver( std::vector <double> &v );
double deviation ( std::vector <double> &v );
int main(int argc, char *argv[])
{
    if(argc != 2)
        return 2;
    
    const float xfactor = 0.2; // depands upon the frequecy of the data
    const float yfactor = 0.5; // depands upon digitizer
    int base = 20;


    std::string filePath = argv[1];

    std::vector<std::string> N;

    N.push_back("TR_0_0.txt");
//    N.push_back("wave_0.txt");
//    N.push_back("wave_1.txt");
//    N.push_back("wave_2.txt");
//    N.push_back("wave_3.txt");
//    N.push_back("wave_4.txt");
//    N.push_back("wave_5.txt");
//    N.push_back("wave_6.txt");
//    N.push_back("wave_7.txt");


    std::vector<std::string> fileNames;
    for (auto name : N)
    {
        fileNames.push_back( filePath + name);
    }

     checkTWsize(fileNames);

    std::vector<double> timeAxis;
        for(int i = 0; i < 1024; i++)
        {
            timeAxis.push_back(xfactor*double(i));
        }
    int file_number = 0;
//    TH1D * min;
//    TH1D * base_mean;
//    TH1D * sda_base;


//    auto C2 = new TCanvas("C2","Minimum of baseline",800,800);
//    auto C3 = new TCanvas("C3","All Base-Mean",800,800);
//    auto C5 = new TCanvas("C5","All Base-SD",800,800);

//    auto legend = new TLegend(0.1,0.7,0.48,0.9);



    for(auto path : fileNames)
    {
        std::ifstream file;
        file.open(path.c_str());
        int number_signal = checkEventSize(file);
        //    std::cout<<number_signal<<"KK";

        double mini = 0.0;
        double avg_base = 0.0;
        double sd_base = 0.0;
        auto C = new TCanvas("C","C",800,800);
        auto C1 = new TCanvas("C","C",1600,1600);
        C1->Divide(2,2);

        TString hist_min_title = "Min Values of Baseline " + N[file_number];
        auto min_hist = new TH1D("min hist",hist_min_title,200,1040,1140);
        TString hist_base_title = "Mean Values of Signal Baseline "+N[file_number];
        auto mean_hist_base = new TH1D("mean base hist",hist_base_title,500,1050,1120);


        TString hist_base_sd_title = "S.D. of Signal Baseline "+N[file_number];
        auto hist_base_sd = new TH1D("sd base hist",hist_base_sd_title,500,-1,10);

        auto test = new TH1D("you know","i dont know",520,0,520);

        for(int event = 0; event < number_signal; event++)
        {
            base = 80;
            std::vector <double> sig;
            std::vector <double> sig_avg;
            for(int j = 0; j < 1024; j++)
            {
                double y;
                file>>y;
                sig.push_back(y*yfactor);
            }


            //sub-vector for baseline calulation


            std::vector <double> sub(sig.begin(),sig.begin() + base + 1);


            double baseline  = aver(sub);
            sd_base = deviation(sub);

            while(TMath::Abs(sig[base] - baseline) < (2*sd_base))
            {
                sub.push_back(sig[base]);
                baseline = aver(sub);
                sd_base = deviation(sub);
                base++;

                if (base == (sig.size()/2)) break;

            }

            test->Fill(base);


            if (baseline < 1114)
            {
                auto G = new TGraph(sig.size(),&timeAxis[0],&sig[0]);

                C->cd();

                TString plot = path;
                plot.ReplaceAll(".txt","");
                plot += "_";
                plot += event;
                G->Draw();
                C->SaveAs(plot+".png");
            }



            avg_base = baseline;
            min_hist->Fill(*min_element(sub.begin(),sub.end()));
            mean_hist_base->Fill(avg_base);
            hist_base_sd->Fill(sd_base);
        }

        TString plot = path;
        plot.ReplaceAll(".txt","");
            C1->cd(3);
            min_hist->Draw();

            C1->cd(1);
            mean_hist_base->Draw();

            C1->cd(2);
            hist_base_sd->Draw();

            C1->cd(4);
            test->Draw();

            C1->SaveAs(plot+"_Base.png");
            C1->SaveAs(plot+"_Base.root");



//         min = (TH1D*)min_hist->Clone();
//         base_mean= (TH1D*) mean_hist_base->Clone();;
//         sda_base = (TH1D*)hist_base_sd->Clone();

        TString l1= "Mean of "+ N[file_number];
//         legend->AddEntry(mean,l1,"f");


//         C2->cd();
//         C2->Update();
//         min->SetTitle("Minimum");
//         min->SetLineColor(file_number+1);
//         min->SetLineWidth(2);


//         min->Draw("SAME");
////       legend->Draw("SAME");
//         C2->SaveAs("Min.png");
//         C2->SaveAs("Min.root");

//         C2->Update();

//         C3->cd();
//         C3->Update();
//         base_mean->SetTitle("Basline Mean");
//         base_mean->SetLineColor(file_number+1);
//         base_mean->SetLineWidth(2);
//         base_mean->Draw("SAME");
////         legend->Draw("SAME");
//         C3->SaveAs("Base Mean.png");
//         C3->Update();


//         C5->cd();
//         C5->Update();
//         sda_base->SetTitle("Standard Deviation of Baseline");
//         sda_base->SetLineColor(file_number+1);
//         sda_base->SetLineWidth(2);
//         sda_base->Draw("SAME");
////         legend->Draw("SAME");
//         C5->SaveAs("Base_SD.png");
//         C5->Update();



            delete C1;
//         delete min_hist;
         delete mean_hist_base;
         delete hist_base_sd;


            file.close();
            std::cout<<N[file_number]<<" done \n";
            file_number++;

    }




//    delete C2,C3,C4,C5;
    return 0;
}


//auto legend = new TLegend(0.1,0.7,0.48,0.9);
//legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
//legend->AddEntry(h1,"Histogram filled with random numbers","f");
//legend->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
//legend->AddEntry("gr","Graph with error bars","lep");
//legend->Draw();

//function to calcaulate hte mean of a given vector
double aver ( std::vector <double>& v )
{
        double return_value = 0.0;
        int n = v.size();

        for ( int i=0; i < n; i++)
        {
            return_value += v[i];
        }

        return ( return_value / n);
}

//function to calcaulate the Standard Devitation of a given vector

double deviation ( std::vector <double> &v )
{
        double sum = 0.0;
        double temp = 0.0;
        double sigma = 0.0;
        double mean = aver(v);

        for ( auto j : v)
        {
            temp = pow((j - mean),2);
            sum += temp;
        }

        return sigma = sqrt(sum/(v.size() -1));  // N-1 is used
}





    /////////////////////////////////////////////////////////////////////////


//        std::cout<<deviation(sig)<<"\n";


//        auto line  = new TLine(0,baseline,1024*0.2,baseline);
//        line->SetLineColor(3);
//        auto l  = new TLine(0,signal_mean,1024*0.2,signal_mean);
//        l->SetLineColor(2);

//        auto l1  = new TLine(0,signal_mean + deviation(sig),1024*0.2,signal_mean + deviation(sig));
//        auto l2  = new TLine(0,signal_mean - deviation(sig),1024*0.2,signal_mean - deviation(sig));
//        l1->SetLineColor(5);
//        l2->SetLineColor(5);

//        if (deviation(sig)>5)
//        {
////            coincidence.push_back(i);
//            std::cout<<deviation(sig)<<"\n";
//            auto C = new TCanvas("C","C",800,800);
//            auto G = new TGraph(sig.size(),&timeAxis[0],&sig[0]);
//            auto F = new TGraph(sig_avg.size(),&timeAxis[0],&sig_avg[0]);
//            F->SetLineColor(2);

//            // Max-Min >40
//            if (*max_element(sig_avg.begin(),sig_avg.end()) - *min_element(sig_avg.begin(),sig_avg.end()) > 40)
//            {
//                F->SetLineColor(3);
//                if (baseline > signal_mean && baseline < (signal_mean + deviation(sig) ) )
//                {
//                F->SetLineColor(4);
//                }

//            }

//            F->SetLineWidth(2);

//            TString plot = refile;
//            plot.ReplaceAll(".txt","");
//            plot += "_";
//            plot += i;
//            G->Draw("AC");
//            F->Draw("SAME");
//            line->Draw("SAME");
//            l->Draw("SAME");

//            l1->Draw("SAME");
//            l2->Draw("SAME");
//            C->SaveAs(plot+".png");

//            delete C;

//        }







//    std::vector<std::string> fileNames;

//    fileNames.push_back( filePath+"wave_7.txt");
//    fileNames.push_back( filePath+"TR_0_0.txt");
////    fileNames.push_back( filePath+"wave_0.txt");
//////    fileNames.push_back( filePath+"wave_1.txt");
//////    fileNames.push_back( filePath+"wave_2.txt");
//////    fileNames.push_back( filePath+"wave_3.txt");
//////    fileNames.push_back( filePath+"wave_4.txt");
//////    fileNames.push_back( filePath+"wave_5.txt");
//////    fileNames.push_back( filePath+"wave_6.txt");
    
    
    
//    checkTWsize(fileNames);
    
//    std::vector<double> timeAxis;
//    for(int i = 0; i < 1024; i++)
//    {
//        timeAxis.push_back(0.2*double(i));
//    }
    
//     for (auto& path: fileNames)
//         plotSignals(path);

//    gStyle->SetOptFit(1);
    
//    std::ofstream results;
//    results.open("results.txt", std::ofstream::app);
//    results <<  "FilePath \t Mean Amp \t Mean Period \t Chi2/NDF" << std::endl;
    
//    for (auto& path: fileNames)
//    {
//        TString outName = path;
//        outName.ReplaceAll(".txt","");
//        std::ifstream file;
//        file.open( path.c_str() );
//        std::cout <<"Starting with: " <<  path <<  std::endl;
    
//        std::vector< std::vector < double > > signals;
//        int allEvents = checkEventSize( file );
//        int counter = 0;
        
        
        
////        results <<  outName <<  "\t";
        
//        for(int event = 0; event < 50; event++)
//        {
//            std::vector<double> points;
//            for(int i = 0; i < 1024; i++)
//            {
//                double Y = 0;
//                file >> Y;
//                points.push_back(Y);
//            }
//            counter++;
//            if (counter %  1000 == 0)
//                std::cout <<  "Read "  << counter <<  " signals\n";
//            if (points.size() != 1024 )
//                return 5;
            
//            signals.push_back(points);
//        }
//        counter = 0;
//        for(auto& sig: signals)
//        {
//            TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",800, 800);
        
//            TGraph* signalPlot = new TGraph(sig.size(), &timeAxis[0], &sig[0]);
            
//            signalPlot->Draw("AC*");


            
            
//            counter++;
//            if (counter < 100)
//            {
//                TString name = outName;
//                name += "_";
//                name += counter;
//                signalPlot->Draw("AP*");
////                c1->SaveAs( name+".root");
//                c1->SaveAs( name+".png");
//            }


            
//            delete c1;
//            delete signalPlot;
//        }
        
//        file.close();
//    }
