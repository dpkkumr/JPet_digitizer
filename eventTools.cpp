#include "eventTools.h"

int checkEventSize( std::ifstream& file)
{
       int lineCounter = 0;
    std::string line;
    while( std::getline(file, line) )
        lineCounter++;
    
    const int eventSize = 1024;
    if( lineCounter%1024!= 0 )
        return -1;
    
    file.clear();
    file.seekg (0, std::ios::beg);
    
    return lineCounter / eventSize;
    
}

int checkTWsize( std::vector<std::string>& fileNames )
{
    int events = 0;
    
    for(auto& path : fileNames )
    {
        std::ifstream file;
        file.open( path.c_str() );
        
        if( !file.good() )
            return 1;
        
        events = checkEventSize( file );         
        file.close();
        
        if(events == -1)
        {
            std::cout << "Wrong amount of events in file: " << path << std::endl;
            return 3;
        }
    }
    std::cout << "Files are fine\n";
    
    
    
    return events;
}

int plotSignals( std::string& path, int toPlot )
{
    std::ifstream file;
    file.open( path.c_str() );
    
    
    std::vector<double> timeAxis;
    
    for(int i = 0; i < 1024; i++)
    {
        timeAxis.push_back(double(i));
    }
    
    int allEvents = checkEventSize( file );

    std::vector< std::vector < double > > signals;
    for(int event = 0; event < allEvents; event++)
    {
        if( event == toPlot )
            break;
        std::vector<double> points;
        for(int i = 0; i < 1024; i++)
        {
            double Y = 0;
            file >> Y;
            points.push_back(Y);
        }
    
        if (points.size() != 1024 )
            return 5;
        
        signals.push_back(points);
    }
    int counter = 0;
    for(auto& sig: signals)
    {
        TCanvas *c1 = new TCanvas("c1","A Simple Graph Example",200,10,500,300);
        
        TGraph* signalPlot = new TGraph(sig.size(), &timeAxis[0], &sig[0]);
        
        signalPlot->Draw("AC*");
        
        TString outPlotName = path;
        outPlotName.ReplaceAll(".txt","");
        outPlotName+="_";
        outPlotName+=counter;
        counter++;
        c1->SaveAs(outPlotName+".png");
        delete c1;
    }
    file.close();
    file.clear();
    file.seekg (0, std::ios::beg);
    
    return 0;
}    
