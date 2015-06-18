#include<cstdio>
#include<cmath>
#include<algorithm>
#include "MyUtility.h"

using namespace std;

/* expt(a,n)=a^n for integer n */

#ifdef POW_NOT_TRUSTWORTHY
/* if roundoff errors in pow cause problems, use this: */

double expt(a, n)
double a;
register int n;
{
    double x;

    x = 1.;
    if (n>0) for (; n>0; n--) x *= a;
    else for (; n<0; n++) x /= a;
    return x;
}

#else
#   define expt(a, n) pow(a, (double)(n))
#endif

//#define NTICK 10			/* desired number of tick marks */

/*
 * nicenum: find a "nice" number approximately equal to x.
 * Round the number if round=1, take ceiling if round is true
 */

double nicenum(double x, bool round)
{
        int expv;
        double f;
        double nf;

        expv = floor(log10(x));
        f = x/expt(10., expv);
        if(round){
                if(f < 1.5) nf = 1.;
                else if (f < 3.) nf = 2.;
                else if (f < 7.) nf = 5.;
                else nf = 10.;
        }else{
                if(f <= 1.) nf = 1.;
                else if(f <= 2.) nf = 2.;
                else if(f <= 5.) nf = 5.;
                else nf = 10.;
        }
        return nf*expt(10., expv);
}

void loose_label(int ntick, double minv, double maxv, double ans[3])
{
        double d;						/* tick mark spacing */
        double graphmin, graphmax;		/* graph range min and max */
        double range, x;

        /* we expect min != max */
        range = nicenum(maxv-minv, 0);
        d = nicenum(range/(ntick-1), 1);
        graphmin = floor(minv/d)*d;
        graphmax = ceil(maxv/d)*d;

        ans[0] = graphmin;
        ans[1] = graphmax;
        ans[2] = d;
}
