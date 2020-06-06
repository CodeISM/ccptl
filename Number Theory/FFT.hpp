/*
 * Author: Someone on codeforces.com, Ankur Dua
 * Use: Multiplying polynomials
 * Features: Highly optimized. Can be used in place of NTT too.
 * Time Complexity: O(NlogN) for multiplication.
 * Notes: 1. Public Functions are at the end along with their documentation.
 *        2. Don't play with the code unless you understand its working.
 *	  3. If you want to use it in a constrained memory environment, consider decreasing maxBase below.
 *	  4. Changing double to long double will increase accuracy if you ever encounter precision issues.	 
 * 
 * Status: Tested on multiple problems on codeforces and codechef.
 */
#include<bits/stdc++.h>
using  namespace std;

class FFT {
private:
    #define pw(x) (1LL << (x))
    typedef double dbl;
    const dbl PI = acos(-1);

    /*------------Change These variables as required--------------*/

    //1<<maxBase should be the maximum value of N ever encountered otherwise RTE will occur
    	//N is the max value of size(x)+size(y) after rounding up to nearest power of 2
	//Memory requirement is approximately 80*pow(2, maxBase-20) MB
    const int maxBase=20;


    /*------------------------------------------------------------*/



    /*------------CUSTOM STRUCT FOR FFT--------------------------*/

    struct num
    {
        dbl x, y;
        num(){}
        num(dbl xx, dbl yy): x(xx), y(yy) {}
        num(dbl alp): x(cos(alp)), y(sin(alp)) {}
        inline num operator + (num b) { return num(x + b.x, y + b.y); }
        inline num operator - (num b) { return num(x - b.x, y - b.y); }
        inline num operator * (num b) { return num(x * b.x - y * b.y, x * b.y + y * b.x); }

    };
    inline num conj(num a) { return num(a.x, -a.y); }

    /*------------CUSTOM STRUCT ENDS---------------------------*/

    /*-------------Do not change these variables--------------*/
    bool rootsPrepared=false;
    int base, N;
    int lastRevN = -1;
    num* root=NULL;
    int *rev=NULL;
    /*---------------------------------------------------------*/

    /*-------------Helper functions----------------------------*/
    void prepRoots()
    {
        if (rootsPrepared) return;
        rootsPrepared = true;
        root=new num[pw(maxBase)];
        root[1] = num(1, 0);
        for (int k = 1; k < maxBase; ++k)
        {
            num x(2 * PI / pw(k + 1));
            for (int i = pw(k - 1); i < pw(k); ++i)
            {
                root[2 * i] = root[i];
                root[2 * i + 1] = root[i] * x;
            }
        }
    }


    void prepRev()
    {
        if (lastRevN == N) return;
        lastRevN = N;
        if(rev!=NULL)
            delete[] rev;
        rev=new int[pw(base)];
        rev[0]=0;
        for(int i=0; i<N; i++)
            rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (base - 1));
    }

    void prepAB(long long *x, long long *y, int n1, int n2)
    {
        base = 1;
        N = 2;
        while (N < n1 + n2) base++, N <<= 1;
        prepRoots();
        prepRev();

        //Copy x,y into A,B
        for(int i=0;i<n1;i++)
            A[i]=x[i];

        for(int i=0;i<n2;i++)
            B[i]=y[i];

        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;
    }
    void prepAB(vector<long long> &x, vector<long long> &y)
    {
        int n1=x.size();
        int n2=y.size();
        base = 1;
        N = 2;
        while (N < n1 + n2) base++, N <<= 1;
        prepRoots();
        prepRev();

        //Copy x,y into A,B

        for(int i=0;i<n1;i++)
            A[i]=x[i];

        for(int i=0;i<n2;i++)
            B[i]=y[i];

        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;
    }
    void prepAB(vector<long long> &x, vector<long long> &y, int n1, int n2)
    {
        n1=min(n1, (int)x.size());
        n2=min(n2, (int)y.size());
        base = 1;
        N = 2;
        while (N < n1 + n2) base++, N <<= 1;
        prepRoots();
        prepRev();

        //Copy x,y into A,B

        for(int i=0;i<n1;i++)
            A[i]=x[i];

        for(int i=0;i<n2;i++)
            B[i]=y[i];

        for (int i = n1; i < N; ++i) A[i] = 0;
        for (int i = n2; i < N; ++i) B[i] = 0;
    }
    /*------------------------------------------------------------*/

    /*------------------ACTUAL FFT--------------------------------*/

    //computes the dft of a. Finally the DFT is stored in f.
    void fft(num *a, num *f)
    {
        //bit reversal permutation
        for(int i=0;i<N;i++)
            f[i] = a[rev[i]];

        //iterative FFT
        for (int k = 1; k < N; k <<= 1)
            for (int i = 0; i < N; i += 2 * k)
                for(int j=0;j<k;j++)
                {
                    num z = f[i + j + k] * root[j + k];
                    f[i + j + k] = f[i + j] - z;
                    f[i + j] = f[i + j] + z;
                }

    }

    /*-------------------------------------------------------------*/

    /*---------------------DO NOT TOUCH THESE----------------------*/
    num *a=NULL, *b=NULL, *f=NULL, *g=NULL;
    long long *A=NULL, *B=NULL, *C=NULL;

    void _multMod(int mod, bool eq)
    {

        for(int i=0;i<N;i++)
        {
            int x = A[i] % mod;
            a[i] = num(x & (pw(15) - 1), x >> 15);
        }

        for(int i=0;i<N;i++)
        {
            int x = B[i] % mod;
            b[i] = num(x & (pw(15) - 1), x >> 15);
        }

        fft(a, f);

        if (!eq) {
            fft(b, g);
        } else {
            for (int i = 0; i < N; i++) g[i] = f[i];
        }

        for(int i=0;i<N;i++)
        {
            int j = (N - i) & (N - 1);
            num a1 = (f[i] + conj(f[j])) * num(0.5, 0);
            num a2 = (f[i] - conj(f[j])) * num(0, -0.5);
            num b1 = (g[i] + conj(g[j])) * num(0.5 / N, 0);
            num b2 = (g[i] - conj(g[j])) * num(0, -0.5 / N);
            a[j] = a1 * b1 + a2 * b2 * num(0, 1);
            b[j] = a1 * b2 + a2 * b1;
        }

        fft(a, f);
        fft(b, g);

        for(int i=0;i<N;i++)
        {
            long long aa = f[i].x + 0.5;
            long long bb = g[i].x + 0.5;
            long long cc = f[i].y + 0.5;
            C[i] = (aa + bb % mod * pw(15) + cc % mod * pw(30)) % mod;
        }
    }

    void mult()
    {
        for(int i=0;i<N;i++) a[i] = num(A[i], B[i]);
        fft(a, f);
        for(int i=0;i<N;i++)
        {
            int j = (N - i)  & (N - 1);
            a[i] = (f[j] * f[j] - conj(f[i] * f[i])) * num(0, -0.25 / N);
        }
        fft(a, f);
        for(int i=0;i<N;i++) C[i] = (long long)round(f[i].x);
    }
    /*---------------------------------------------------------------------------------*/

    /*-------------------PUBLIC FUNCTIONS THAT CAN BE USED-----------------------------*/

public:

	/*------------Constructor----------------------------------*/
	FFT(){
		int N=pw(maxBase);
		a=new num[N];
		b=new num[N];
		f=new num[N];
		g=new num[N];
		A=new long long[N];
		B=new long long[N];
		C=new long long[N];
	}

    /**
     * Multiplication under modulo. Can be used in place of NTT.
     * @param x Array1
     * @param y Array2
     * @param n1 Length of Array1
     * @param n2 Length of Array2
     * @param mod modulo to be used for multiplication
     * @return Array containing result. It can be further passed as argument for multiplication.
     * You can modify it but do not delete it. The values in this array are not persisted between calls
     * to multiply functions. If you need to store the array, consider using the version
     * that returns vector.
     */
    long long* multiply(long long *x, long long *y, int n1, int n2, long long mod){
        prepAB(x,y, n1, n2);
        _multMod(mod, false);
        return C;
    }
    vector<long long> multiply(vector<long long> &x, vector<long long> &y,long long mod){
        prepAB(x,y);
        _multMod(mod, false);
        vector<long long> ret(x.size()+y.size()-1);
        for(int i=0;i<ret.size();i++)
            ret[i]=C[i];

        return ret;
    }
    vector<long long> multiply(vector<long long> &x, vector<long long> &y, int n1, int n2, long long mod){
        prepAB(x,y, n1, n2);
        _multMod(mod, false);

        vector<long long> ret(n1+n2-1);
        for(int i=0;i<ret.size();i++)
            ret[i]=C[i];

        return ret;
    }

    /**
     * Multiplication without modulo. Result can overflow. Should not be used when the
     * resultant coeffecients can exceed 9e14
     * @param x Array1
     * @param y Array2
     * @param n1 Length of Array1
     * @param n2 Length of Array2
     * @return Result of multiplicatin of Array1 and Array2
     */

    long long* multiply(long long *x, long long *y, int n1, int n2){
        prepAB(x,y,n1,n2);
        mult();
        return C;
    }

    vector<long long> multiply(vector<long long> &x, vector<long long> &y){
        prepAB(x,y);
        mult();

        vector<long long> ret(x.size()+y.size()-1);
        for(int i=0;i<ret.size();i++)
            ret[i]=C[i];

        return ret;
    }
    

    /**
     * Multiplication for getting exact result in long long without mod.
     * Uses CRT with two modulos.
     * @param x
     * @param y
     * @param n1
     * @param n2
     * @return
     */
    long long* multiplyLL(long long *x, long long *y, int n1, int n2){
        prepAB(x,y,n1,n2);
        int mod1=1.5e9;
        int mod2=mod1+1;
        _multMod(mod1, false);
        long long *D=new long long[N];

        for(int i=0;i<N;i++)
            D[i]=C[i];

        _multMod(mod2, false);

        for(int i=0;i<N;i++){
            C[i] = D[i] + (C[i] - D[i] + (long long)mod2) * (long long)mod1 % mod2 * mod1;
        }
        delete[] D;
        return C;
    }

    vector<long long> multiplyLL(vector<long long> &x, vector<long long> &y){
        prepAB(x,y);
        int mod1=1.5e9;
        int mod2=mod1+1;
        _multMod(mod1, false);
        long long *D=new long long[N];

        for(int i=0;i<N;i++)
            D[i]=C[i];

        _multMod(mod2, false);

        for(int i=0;i<N;i++){
            C[i] = D[i] + (C[i] - D[i] + (long long)mod2) * (long long)mod1 % mod2 * mod1;
        }
        delete[] D;
        vector<long long> ret(x.size()+y.size()-1);
        for(int i=0;i<ret.size();i++)
            ret[i]=C[i];
        return ret;
    }


    //Destructor
    ~FFT(){
        delete[] rev;
        delete[] A;
        delete[] B;
        delete[] C;
        delete[] root;
        delete[] a;
	delete[] b;
	delete[] f;
	delete[] g;
    }
};
