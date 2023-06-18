void macro1(void)
{
    ifstream ifile1;
    ifile1.open("losowe1.dat");

    ifstream ifile2;
    ifile2.open("losowe2.dat");

    ifstream ifile3;
    ifile3.open("losowe3.dat");

    ifstream ifile4;
    ifile4.open("losowe4.dat");

    double w = 800;
    double h = 600;

    auto c = new TCanvas("c", "c", w, h);
    c->Divide(4,2);

    double value;
    double next_value;

    auto histogram1 = new TH1D("hist1", "m=97 g=23", 100, 0, 1);
    auto correlation1 = new TH2D("corr1", "m=97 g=23", 100, 0, 1, 100, 0, 1);
    while(ifile1 >> value && ifile1 >> next_value)
    {
        histogram1->Fill(value);
        correlation1->Fill(value, next_value);
    }

    auto histogram2 = new TH1D("hist2", "m=32363 g=157", 100, 0, 1);
    auto correlation2 = new TH2D("corr2", "m=32363 g=157", 100, 0, 1, 100, 0, 1);
    
    while(ifile2 >> value && ifile2 >> next_value)
    {
        histogram2->Fill(value);
        correlation2->Fill(value, next_value);
    }

    auto histogram3 = new TH1D("hist3", "m=147483647 g=16807", 100, 0, 1);
    auto correlation3 = new TH2D("corr3", "m=147483647 g=16807", 100, 0, 1, 100, 0, 1);
    while(ifile3 >> value && ifile3 >> next_value)
    {
        histogram3->Fill(value);
        correlation3->Fill(value, next_value);
    }

    auto histogram4 = new TH1D("hist4", "m=4294967296 g=1664525 c=1013904223", 100, 0, 1);
    auto correlation4 = new TH2D("corr4", "m=4294967296 g=1664525 c=1013904223", 100, 0, 1, 100, 0, 1);
    while(ifile4 >> value && ifile4 >> next_value)
    {
        histogram4->Fill(value);
        correlation4->Fill(value, next_value);
    }

    ifile1.close();
    ifile2.close();
    ifile3.close();
    ifile4.close();

    c->cd(1);
    histogram1->Draw();
    c->cd(2);
    histogram2->Draw();
    c->cd(3);
    histogram3->Draw();
    c->cd(4);
    histogram4->Draw();
    c->cd(5);
    correlation1->Draw("colz2");
    c->cd(6);
    correlation2->Draw("colz2");
    c->cd(7);
    correlation3->Draw("colz2");
    c->cd(8);
    correlation4->Draw("colz2");

}