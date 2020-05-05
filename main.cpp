//
//  main.cpp
//  quasi newton
//
//  Created by MacBook Pro on 5/1/20.
//  Copyright © 2020 MacBook Pro. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
int len=2,k=0;
vector <vector<float>> h={{1,0},{0,1}};
float alpha;
vector<float> d;
vector<float> x={0,0};

float fonction(vector<float> x)
{
   
  return (x[0]-x[1]+2*x[0]*x[0]+2*x[1]*x[0]+x[1]*x[1]);
        
        
    
    
}
vector<float> gradientf(vector<float> a) //graduient
{vector<float> f(len,0);
    for(int i=0;i<len;i++)
        { if (i==0)
            f[i]=(1+4*(a[0])+2*(a[1]));
           else
               f[i]=(-1+2*a[0]+2*a[1]);}
    return f;
}

float produit_tv(vector<float>a,vector<float> y) //produit scalaire de 2 vecteurs

{   float s =0;
    for(int i=0;i<len;i++)
        s=s+((a[i])*(y[i]));
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
            y.push_back(gradientb[i]-gradienta[i]);
        return y;
        
    }

vector <vector<float>> produitv(vector<float> a,vector<float> y)              //produit  de 2 vecteurs
{vector <vector<float>> p={{0,0},{0,0}};;
    for(int i=0;i<len;i++)
        {for(int j=0;j<len;j++)
            p[i][j]=((a[i])*(y[j]));
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
vector<float> alphaxvect(int a , vector<float> m)
{
    for(int i=0;i<len;i++)
        m[i]=m[i]*a;
    return m;
    
}
vector<float> somme(vector<float> a,vector<float>b)
{  vector<float> s={0,0};
    for(int i=0;i<len;i++)
        s[i]=a[i]+b[i];
    return s;
}

vector <vector<float>> A()
{vector <vector<float>> d_dt={{0,0},{0,0}};
    d_dt=produitv(d, d);
   // vector <vector<float>> p(2,0);
    float  dt_y=0;
   dt_y =produit_tv(d, y(x, somme(x, alphaxvect(alpha, d))));
    for(int i=0;i<len;i++)
      //  std::cout <<"lll"<<":"<< <<endl;
    std::cout <<"lll"<<":"<<dt_y <<endl;
    for(int i=0;i<len;i++)
    {for (int j=0;j<len;j++)
        d_dt[i][j]=d_dt[i][j]*alpha/dt_y;}
        
    
    return d_dt;
        
    }




vector <vector<float>> B()
{   vector <vector<float>> r={{0,0},{0,0}};
    r= produitv(produitmv(h, y(x, somme(x, alphaxvect(alpha, d)))), produitmv(h, y(x, somme(x, alphaxvect(alpha, d)))));
    float s=produit_tv(y(x, somme(x, alphaxvect(alpha, d))), produitmv(h, y(x, somme(x, alphaxvect(alpha, d)))));
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
    int iteration = 0;
    bool trouve=false;
    while(!trouve&(iteration<=1000)){
if (fonction(somme(x, alphaxvect(alphac, d)))>(fonction(x)+0.1*alphac *produit_tv(gradientf(x), d)))
    {
        sup=alphac;
        alphac=0.5*(inf+sup);
         iteration++;
        
    }
else{
    if (produit_tv(gradientf(somme(x, alphaxvect(alphac, d))), d)<0.9*produit_tv(gradientf(x), d))
        {inf =alphac;
            alphac=0.5*(inf+sup);}
    else
        trouve = true;
    iteration++;
}
}

    return alphac;
    
}
float norme(vector<float> vecteur) // calcul norme d'un vecteur
{   float n=0;
    for(int i =0;i<len;i++)
        n=(vecteur[i]*(vecteur[i]))+n;
    return sqrt(n);
}
vector <float> quasi_newton()
{
    k=0;
    vector <float> x={0,0},g =gradientf(x);
        std::cout <<"foncde"<<":"<<fonction(x) <<endl;
    while (norme(gradientf(x))>0.1)
        {
            d=alphaxvect(-1, produitmv(h, g))  ;
             for (int i=0;i<len;i++)
                         std::cout <<"d"<<i<<":"<<d[i] <<endl;
            alpha = wolfe_rule();
            std::cout <<"pas"<<k<<":"<<alpha <<endl;
            x=somme(x,alphaxvect(alpha, d));
             for (int i=0;i<len;i++)
             std::cout <<"xxx"<<k<<i<<":"<<x[i] <<endl;
            g=gradientf(x);
            for (int i=0;i<len;i++)
            std::cout <<"gggg"<<i<<":"<<g[i] <<endl;
            float w=fonction(x);
              std::cout <<"fonc"<<k<<":"<<w <<endl;
            h=d_f_p();
            k=k+1;
        }
    
    return x;
    
    
    
    
    
}


int main(int argc, const char * argv[]) {
    // insert code here...
           
    vector <float> j={0,0};
    j=quasi_newton();
    for (int i=0;i<len;i++)
        std::cout <<"jjj"<<":"<<j[i] <<endl;
    

    return 0;
}

