double  losujVonNeumann(TF1 *g, double min, double max)
{
    double y = gRandom->Uniform(min, max);
    return g->Eval(y);
}

double wydajnoscVonNeumann(TF1 *g, double min, double max, int n)
{
    double y1, y2;
    int acc = 0;
    int rej = 0;
    for(int i = 0; i < n; i++)
    {
        y1 = gRandom->Uniform(g->GetMinimum(min,max),g->GetMaximum(min, max));
        y2 = losujVonNeumann(g,min,max);
        if(y2 >= y1) acc++;
        else rej++;
    }

    return (double) acc/(acc+rej);
}

double calkaVonNeumann(TF1 *g, double min, double max, int n)
{
    return wydajnoscVonNeumann(g, min, max, n)*(max-min)*(g->GetMaximum(min, max)-g->GetMinimum(min,max));
}

double calkaVonNeumannZPomoc(TF1 *g, TF1 *s, double min, double max, int n, double &wydajnosc)
{
    double y1, y2;
    int acc = 0;
    int rej = 0;
    for(int i = 0; i < n; i++)
    {
        y1 = gRandom->Uniform(g->GetMinimum(min,max),s->GetMaximum(min, max));
        y2 = losujVonNeumann(g,min,max);
        if(y2 >= y1) acc++;
        else rej++;
    }

    wydajnosc = (double) acc/(acc+rej);

    return wydajnoscVonNeumann(g, min, max, n)*(max-min)*(g->GetMaximum(min, max)-g->GetMinimum(min,max));
}


void macro2(void)
{
    double width = 1200;
    double height = 400;

    auto g = new TF1("func", "exp(-5*x)");
    auto s = new TF1("func", "x-1/2*x*x");
    
    double min = 0;
    double max = 1;

    int n = 100000;

    double wydajnosc = 0;

    cout << wydajnoscVonNeumann(g, min, max, n) << "\n";
    cout << calkaVonNeumann(g,min,max,n) << "\n";


    cout << -1./5*exp(-5*max) + 1./5*exp(-5*min) << "\n\n";

    cout << calkaVonNeumannZPomoc(g, s, min, max, n, wydajnosc) << "\n";
    cout << wydajnosc;

}