
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

#include "TGraph.h"
#include "TCanvas.h"

int checkEventSize( std::ifstream& file);
int checkTWsize( std::vector<std::string>& fileNames );
int plotSignals( std::string& path, int toPlot = 20 );
