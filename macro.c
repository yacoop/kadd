void macro()
{
    unsigned long g = 157;      //23    //157   //16807     //1664525
    unsigned long m = 32363;    //97    //32363 //147483647 //4294967296

    unsigned long c = 0;   //0     //0     //0         //1013904223 

    unsigned long x[1000000];

    x[0] = time(NULL)%(m-1);

    for(int i = 0; i < 1000000; i++)
    {
        x[i+1] = (g * x[i] + c)%m;
    }

    ofstream ofile("losowe2.dat");
    for(int i = 0; i < 100000; i++)
    {
        ofile << (double) x[i] / (m-1) << endl;
    }
    ofile.close();
}