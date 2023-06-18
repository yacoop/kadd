void ReadData(string name, double* tabt, double* taby, double* tabs)
 {
    ifstream ifile;
    ifile.open(name);
    int i = 0;
    double t,y;
    while(ifile >> t && ifile >> y)
    {
        tabt[i] = t;
        taby[i] = y;
        tabs[i] = sqrt(y);
        i++;
    }
    ifile.close();
}

double dopasuj(int st, int n, double* tabt, double* taby, double* tabs, double *wsp, double *bwsp)
{
    auto A = new TMatrixD(n,st);
    auto H = new TMatrixD(n,n);
    auto G = new TMatrixD(n,n);
    auto c = new TMatrixD(n,1);


    for (int i = 0; i < n; i++)
    {
        (*H)(i,i) = 1./tabs[i];
        (*c)(i,0) = taby[i];

        for(int j = 0; j < st; j++)
        {
            (*A)(i,j) = pow(tabt[i], j);
        }
    }

    auto Ap = new TMatrixD(*H, TMatrixD::kMult, *A);
    auto cp = new TMatrixD(*H, TMatrixD::kMult, *c);
    auto ApT = new TMatrixD(TMatrixD::kTransposed, *Ap);

    auto ApTInv = new TMatrixD(*ApT, TMatrixD::kMult, *Ap);
    ApTInv->Invert();
    auto prawie = new TMatrixD(*ApTInv, TMatrixD::kMult, *ApT);

    auto x = new TMatrixD(*prawie, TMatrixD::kMult, *cp);

    auto nzfalka = new TMatrixD(*A, TMatrixD::kMult, *x);

    double M = 0;
    for(int i = 0; i < n; i++)
    {
        M+=pow((taby[i]-(*nzfalka)(i,0))/tabs[i] ,2);
    }

       
    for(int i = 0; i < st; i++)
    {
        wsp[i] = (*x)(i,0);
        bwsp[i] = sqrt((*ApTInv)(i,i));
    }




    return M;
}
int macro(void)
{
    int n = 15;
    int st = 5;

    double* tabt = new double[n];
    double* taby = new double[n];
    double* tabs = new double[n];

    double* wsp = new double[st];
    double* bwsp = new double[st];

    double M;

    ReadData("dane.dat", tabt, taby, tabs);


    cout << M << endl;
    for(int i = 0; i < st-1; i++)
    {
        cout << wsp[i] << " (" << bwsp[i] << ")" << endl;
    }

    auto c = new TCanvas("c", "c", 800, 600);
    auto tabfunc = new TF1*[st];
    auto graph = new TGraphErrors(15, tabt,taby, NULL, tabs);
    graph->Draw("ap*");
    for(int i = 0; i<st; i++)
    {
        //cos jest nie tak z indeksami
        tabfunc[i] = new TF1(Form("%i", i-1),Form("pol%i", i-1), 0, 16);
        M = dopasuj(i, n, tabt, taby, tabs, wsp, bwsp);
        tabfunc[i]->SetParameters(wsp);
        tabfunc[i]->Draw("Same l");
        tabfunc[i]->SetLineColor(i);
    }

    //trzeba jeszcze sprawdzic z tym testem z poprzednich zajec
 

    return 0;
}
