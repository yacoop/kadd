double f(double *val, double *par) {
    double x = val[0];

    if (x >= 0)
        return TMath::Exp(-x/2) / 2;
    else
        return 0;
}

double F(double *val, double *par) {
    double x = val[0];

    if (x >= 0)
        return -2 * TMath::Log(1 - x);
    else
        return 0;
}

void macro2(void)
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
    c->Divide(3,2);

    double value;
    auto func = new TF1("func", f, 0, 8);
    auto Func = new TF1("Func", F, 0, 8);

	auto hist1 = new TH1D("hist1", "m=97, g=23", 100, 0, 8);
    while (ifile1 >> value)
        hist1->Fill(Func->Eval(value));
    hist1->Scale(1 / hist1->Integral(0, 100) / hist1->GetBinWidth(1));

	auto hist2 = new TH1D("hist2", "m=32363, g=157", 100, 0, 8);
    while (ifile2 >> value)
        hist2->Fill(Func->Eval(value));
    hist2->Scale(1 / hist2->Integral(0, 100) / hist2->GetBinWidth(1));

	auto hist3 = new TH1D("hist3", "m=147483647 g=16807", 100, 0, 8);
    while (ifile3 >> value)
        hist3->Fill(Func->Eval(value));
    hist3->Scale(1 / hist3->Integral(0, 100) / hist3->GetBinWidth(1));

	auto hist4 = new TH1D("hist4", "m=4294967296 g=1664525 c=1013904223", 100, 0, 8);

    while (ifile4 >> value)
        hist4->Fill(Func->Eval(value));
    hist4->Scale(1 / hist4->Integral(0, 100) / hist4->GetBinWidth(1));

	auto hist5 = new TH1D("hist5", "standarowy generator", 100, 0, 8);
    for (long i = 0; i < 1000000; ++i) 
        hist5->Fill(func->GetRandom());
    hist5->Scale(1 / hist5->Integral(0, 100) / hist5->GetBinWidth(1));

    ifile1.close();
    ifile2.close();
    ifile3.close();
    ifile4.close();

    c->cd(1);
    hist1->Draw();
    func->Draw("same");

    c->cd(2);
    hist2->Draw();
    func->Draw("same");

    c->cd(3);
    hist3->Draw();
    func->Draw("same");

    c->cd(4);
    hist4->Draw();
    func->Draw("same");

    c->cd(5);
    hist5->Draw();
    func->Draw("same");

}