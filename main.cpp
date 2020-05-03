#include <iostream>
#include <vector>
using namespace std;
int len=2;
vector <vector<float>> h={{1,0},{0,1}};
float alpha=1;
vector<float> d={-1,1};
vector<float> x={0,0},b={0,0},a={-1,1};
vector <vector<float>> d_d={{0,0},{0,0}};

float fonction(vector<float> x)
{
   
  return (x[0]-x[1]+2*x[0]*x[0]+2*x[1]*x[0]+x[1]*x[1]);
        
        
    
    
}
vector<float> gradientf(vector<float> x) //graduient
{vector<float> f(2,0);
    for(int i=0;i<len;i++)
        { if (i==0)
            f[i]=(1+4*(x[0])+2*(x[1]));
           else
               f[i]=(-1+2*x[0]+2*x[1]);}
    return f;
}

float produit_tv(vector<float>x,vector<float> y) //produit scalaire de 2 vecteurs

{   float s =0;
    for(int i=0;i<len;i++)
        s=s+((x[i])*(y[i]));
    return s ;
    
}

vector<double> s(vector<double> a,vector<double>b)
{       vector<double> s;
            for(int i=0;i<len;i++)
                s.push_back(b[i]-a[i]);
    return s ;
                
        }
vector<float> y(vector<float>a ,vector<float>b )
    {
        vector<float>y;
        vector<float> gradienta=gradientf(a),gradientb=gradientf(b);
        for(int i=0;i<len;i++)
            y.push_back(gradienta[i]-gradientb[i]);
        return y;
        
    }

vector <vector<float>> produitv(vector<float> x,vector<float> y)              //produit  de 2 vecteurs
{vector <vector<float>> p={{0,0},{0,0}};;
    for(int i=0;i<len;i++)
        {for(int j=0;j<len;j++)
            p[i][j]=((x[i])*(y[j]));
    }
    return p ;
    
    
}

vector<float> produitmv(vector <vector<float>> h,vector<float> y)
{vector <float> p;
   // double r=0;
    for(int i=0;i<len;i++)
    {p.push_back(0);
        for(int j=0;j<len;j++)
            p[i]=p[i]+h[i][j]*y[j];}
          
    return p;
    
}


vector <vector<float>> A()
{vector <vector<float>> d_dt={{0,0},{0,0}};
    d_dt=produitv(d, d);
   // vector <vector<float>> p(2,0);
    float  dt_y=0;
   dt_y =produit_tv(d, y(a, b));
    std::cout <<"lll"<<":"<<1/dt_y <<endl;
    for(int i=0;i<len;i++)
    {for (int j=0;j<len;j++)
        d_dt[i][j]=d_dt[i][j]*alpha/dt_y;}
        
    
    return d_dt;
        
    }

vector<float> somme(vector<float> a,vector<float>b)
{  vector<float> s(len,0);
    for(int i=0;i<len;i++)
        s[i]=a[i]+b[i];
    return s;
}

vector<float> alphaxvect(int a , vector<float> m)
{
    for(int i=0;i<len;i++)
        m[i]=m[i]*a;
    return m;
    
}
vector <vector<float>> B()
{   vector <vector<float>> r={{0,0},{0,0}};
    r= produitv(produitmv(h, y(a,b)), produitmv(h, y(a,b)));
    float s=produit_tv(y(a,b), produitmv(h, y(a,b)));
     std::cout <<"SSS:"<<s<<endl;
    for (int i =0;i<len;i++)
    {for (int j =0;j<len;j++)
        r[i][j]=r[i][j]*alpha/(-s);
        
        }
    return r;
    
}


vector <vector<float>> d_f_p()
{ vector <vector<float>> g={{0,0},{0,0}};
    vector <vector<float>> matriceA={{0,0},{0,0}};
    vector <vector<float>> matriceb={{0,0},{0,0}};
    matriceA=A();
    matriceb=B();
    for (int i=0;i<len;i++)
    {for (int j=0;j<len;j++)
        h[i][j]=matriceA[i][j]+matriceb[i][j]+h[i][j];}
    return h;
        
    
    
    
    
    
    }
float wolfe_rule()
{float alphac=7,inf=0,sup=1000;
    bool trouve=false;
    while(!trouve){
if (fonction(somme(x, alphaxvect(alphac, d)))>(fonction(x)+0.1*alphac *produit_tv(gradientf(x), d)))
    {
        sup=alphac;
        alphac=0.5*(inf+sup);
        
    }
else{
    if (produit_tv(gradientf(somme(x, alphaxvect(alphac, d))), d)<0.9*produit_tv(gradientf(x), d))
        {inf =alphac;
            alphac=0.5*(inf+sup);}
    else
        trouve = true;}
}

    return alphac;
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
           
       vector <vector<float>> matriceB={{0,0},{0,0}};
         matriceB=d_f_p();
       for(int i=0;i<len;i++)
       {for (int j=0;j<len;j++)
           std::cout <<"b:"<<i<<j<<":"<<matriceB[i][j] <<endl;}
    
    float v=wolfe_rule();
    std:: cout<<"v"<<v<<endl;
    
    return 0;
}

