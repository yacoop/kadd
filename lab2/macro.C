
double func (double *val, double *par)
{
    double x = val[0];
    double y = val[1];

    if((x >= 0 && x <=1) && (y >= 0 && y <=1))
    {
        double a = par[0];
        double b = par[1];
        double c = par[2];

        double f = c*(x-a*pow(x,2))*pow(y,b);

        return f;
    }
    else return 0;
}    

void macro (void)
{
    auto width = 620;
    auto height = 480;

    double X_MAX = 1;
    double X_MIN = 0;
    double Y_MAX = 1;
    double Y_MIN = 0;

    auto c1 = new TCanvas("c1", "c1", width, height);
    c1->Divide(2,2);

    auto prob_func = new TF2("gestosc", "func", X_MIN, X_MAX, Y_MIN, Y_MAX, V_NUM);

    prob_func->SetParameter(0, 1.);
    prob_func->SetParameter(1, 2.);
    prob_func->SetParameter(2, 1.);

    double norm_par = 1./prob_func->Integral(X_MIN, X_MAX, Y_MIN, Y_MAX);

    prob_func->SetParameter(2, norm_par);
    
    prob_func->SetTitle("gestosc");
    prob_func->GetXaxis()->SetTitle("x");
    prob_func->GetYaxis()->SetTitle("y");
    prob_func->GetZaxis()->SetTitle("f(x,y)");


    auto dist = new TH2D("dist", "dystrybuanta", 100, 0, 1, 100, 0, 1);

    for(int i = 1; i<=100; i++)
    {
        for(int j = 1; j<=100; j++)
        {
            dist->SetBinContent(i, j, prob_func->Integral(0, 0.01*i, 0, 0.01*j));
        }
    }
    dist->GetXaxis()->SetTitle("x");
    dist->GetYaxis()->SetTitle("y");
    dist->GetZaxis()->SetTitle("d(x,y)");

    auto g = new TH1D("brzegx", "rozklad brzegowy x", 100, 0, 1);

    for(int i = 1; i<=100; i++)
    {
            g->SetBinContent(i, prob_func->Integral(0.01*(i-1), 0.01*i, 0, 1));
    }
    g->GetXaxis()->SetTitle("x");
    g->GetYaxis()->SetTitle("g(x)");

    auto h = new TH1D("brzegy", "rozklad brzegowy y", 100, 0, 1);

    for(int i = 1; i<=100; i++)
    {
            h->SetBinContent(i, prob_func->Integral(0, 1, 0.01*(i-1), 0.01*i));
    }
    h->GetXaxis()->SetTitle("y");
    h->GetYaxis()->SetTitle("h(y)");

    c1->cd(1);
    prob_func->Draw("surf2");

    c1->cd(2);
    dist->Draw("surf2");

    c1->cd(3);
    g->Draw();

    c1->cd(4);
    h->Draw();
}

