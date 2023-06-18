void macro (void)
{
    auto w = 620;
    auto h = 480;

    double a = 10; //z calki

    double MAX = 100;
    double MIN = 0;

    auto c1 = new TCanvas("c1", "c1", w, h);

    c1->Divide(2,1);

    auto fun1 = new TF1("gestosc","1/[0]*exp(-x/10)", MIN, MAX);
    fun1->SetParameter(0, a);
    fun1->SetTitle("gestosc");
    fun1->GetXaxis()->SetTitle("x");
    fun1->GetYaxis()->SetTitle("f(x)");

    auto fun2 = new TF1("dystrybuanta", "-10/[0]*(exp(-x/10)-1)", MIN, MAX);
    fun2->SetParameter(0,a);
    fun2->SetTitle("dystrybuanta");
    fun2->GetXaxis()->SetTitle("x");
    fun2->GetYaxis()->SetTitle("f(x)");
    fun2->SetLineColor(kBlue);

    int n = 100;
    double bin_w = (MAX-MIN)/double(n);

    double tabx[n];
    double taby[n];

    tabx[0] = bin_w/2;
    taby[0] = fun1->Eval(tabx[0]);

    for(int i = 1; i < n; i++)
    {
        taby[i] = taby[i-1]+fun1->Eval(tabx[i])*bin_w;
        tabx[i] = tabx[i-1]+bin_w;
    }

    c1->cd(1);
    fun1->Draw();

    c1->cd(2);
    fun2->Draw();

    // double p_dist = taby[50]-taby[25];
    double p_dens = fun1->Integral(25,50);
    // cout << "prawdopodobienstwo 25<=X<=50 z dystrybuanty: " << p_dist << endl;
    cout << "prawdopodbienstwo 25<=X=<50 z gestosci: "<< p_dens << endl;

    double EX = fun1->Mean(MIN, MAX);

    cout << "EX: "<< EX << endl;

    double var = fun1->Variance(MIN, MAX);

    cout << "wariancje: "<< var << endl;

    double lower_q = fun2->GetX(0.25);

    cout << "dolny kwatnyl: "<< lower_q << endl;
    
    double med = fun2->GetX(0.5);

    cout << "mediana: "<< med << endl;
    
    double decyl07 = fun2->GetX(0.7);

    cout << "decyl 0.7: "<< decyl07 << endl;

    double decyl09 = fun2->GetX(0.9);

    cout << "decyl 0.9: "<< decyl09 << endl;

    double mode = fun1->GetX(fun1->GetMaximum());

    cout << "moda: " << mode << endl;
    
}