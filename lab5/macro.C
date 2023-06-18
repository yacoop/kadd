void macro(void)
{
    ifstream ifile1;
    ifile1.open("Dane1.dat");

    ifstream ifile2;
    ifile2.open("Dane2.dat");

    ifstream ifile3;
    ifile3.open("Dane3.dat");

    double w = 800;
    double h = 600;

    auto c = new TCanvas("c", "c", w, h);
    c->Divide(2,2);

    double x1;
    double x2;
    double x3;

    //auto correlation4 = new TH2D("corr4", "m=4294967296 g=1664525 c=1013904223", 100, 0, 1, 100, 0, 1);


    auto histogramX12 = new TH2D("histX12", "histX12", 100, 1.5, 5, 100, 0, 3);
    auto histogramX13 = new TH2D("histX13", "histX13", 100, 1.5, 5, 100, 4, 16);
    auto histogramX23 = new TH2D("histX23", "histX23", 100, 0, 3, 100, 4, 16);
    // auto histogramY12 = new TH2D("histY12", "histY12", 100, 0, 100);

    while(ifile1 >> x1 && ifile2 >> x2 && ifile3 >> x3)
    {
        histogramX12->Fill(x1,x2);
        histogramX13->Fill(x1,x3);
        histogramX23->Fill(x2,x3);
        // y1 = 2.5 + 1.5 * x1 + 3 * x3;
        // y2 = 2 * x1 + 0.3 * x2 + x3;
        // histogramY12->Fill(y1, y2);  
    }

    ifile1.close();
    ifile2.close();
    ifile3.close();

    double X1_mean = histogramX12->GetMean(1);
    double X1_std = histogramX12->GetStdDev(1);

    double X2_mean = histogramX12->GetMean(2);
    double X2_std = histogramX12->GetStdDev(2);

    double X3_mean = histogramX13->GetMean(2);
    double X3_std = histogramX13->GetStdDev(2);

    double covX12 = histogramX12->GetCovariance();
    double covX13 = histogramX13->GetCovariance();
    double covX23 = histogramX23->GetCovariance();

    auto matrix = TMatrixD(3, 3);

    matrix(0,0) = X1_std*X1_std;

    matrix(0,1) = covX12;
    matrix(1,0) = covX12;

    matrix(1,1) = X2_std*X2_std;

    matrix(1,2) = covX23;
    matrix(2,1) = covX23;

    matrix(2,2) = X3_std*X3_std;

    matrix(2,0) = covX13;
    matrix(0,2) = covX13;

    cout << "X1 mean: " << X1_mean << endl;
    cout << "X1 std: " << X1_std << endl;

    cout << "X2 mean: " << X2_mean << endl;
    cout << "X2 std: " << X2_std << endl;

    cout << "X3 mean: " << X3_mean << endl;
    cout << "X3 std: " << X3_std << endl;

    cout << "macierz kowarianjci X1 X2 X3";
    matrix.Print();

    c->cd(1);
    histogramX12->Draw("colz");
    c->cd(2);
    histogramX13->Draw("colz");
    c->cd(3);
    histogramX23->Draw("colz");

    auto T = TMatrixD(2,3);
    T(0,0) = 1.5;
    T(1,0) = 2;
    T(0,1) = 0;
    T(1,1) = 0.3;
    T(0,2) = 3;
    T(1,2) = 1;

    auto matrixY = T*matrix*T.T();

    double Y1_mean = 2.5 + 1.5 * X1_mean + 3 * X3_mean;
    double Y2_mean = 2 * X1_mean + 0.3 * X2_mean + X3_mean;
    double Y1_std = sqrt(matrixY(0,0));
    double Y2_std = sqrt(matrixY(1,1));

    cout << "Y1 mean: " << Y1_mean << endl;
    cout << "Y1 std: " << Y1_std << endl;

    cout << "Y2 mean: " << Y2_mean << endl;
    cout << "Y2 std: " << Y2_std << endl;

    double rhoY12 = matrixY(1,0)/((Y1_std)*(Y2_std));
    cout << rhoY12; 

    matrixY.Print();

}