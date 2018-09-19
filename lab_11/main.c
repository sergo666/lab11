
#include <stdio.h>
#include <math.h>

const float EPS = 0.001;

float function(float x, float y) {
    float f;
    f = (x * x) - (2 * y);
    return f;
}


void second_block(float h, float x, float y[], int i, float k[]) {
    float xb, yb;
    xb = x;
    yb = y[i];

    k[0] = function(xb, yb);
    printf("\n k[0]: %f\n", k[0]);

    xb = x + (h/2);
    yb = y[i] + (h * (k[0]/2));
    k[1] = function(xb, yb);
    printf("\n k[1]: %f\n", k[1]);

    yb = y[i] + (h * (k[1]/2));
    k[2] = function(xb, yb);
    printf("\n k[2]: %f\n", k[2]);

    xb = x + h;
    yb = y[i] + (h * k[2]);
    k[3] = function(xb, yb);
    printf("\n k[3]: %f\n", k[3]);

    y[i+1] = y[i] + ((h/6) * (k[0] + (k[1] * 2) + (k[2] * 2) + k[3]));
    printf("\n y[%d] = %f\n", i+1, y[i+1]);

}

int main() {
    int i, n;
    float k[4];
    FILE *f;

    float h;
    float a, b, y0;

   // first_block(&a, &b, &n, &y0);
    
        printf("\n Function was load successfully. \n");
    printf("\n [a;b]: ");
    scanf("%f %f", &a, &b);
    printf("\n n:  ");
    scanf("%d", &n);
    printf("\n y(0): ");
    scanf("%f", &y0);
    printf("\n");
    float *x, *y, *x2, *y2;
    //float x[n+1], y[n+1];
    //float x2[n*2+1], y2[n*2+1];
    x = (float*)malloc(sizeof(float) * (n+1));
    y = (float*)malloc(sizeof(float) * (n+1));
    x2 = (float*)malloc(sizeof(float) * (n*2+1));
    y2 = (float*)malloc(sizeof(float) * (n*2+1));
    h = (b - a) / n;
    x[0] = a;
    y[0] = y0;
    x2[0] = a;
    y2[0] = y0;
    for(i = 0; i < n; i++) {
	     x[i+1] = x[i] + h;
    }
    h /= 2;
    for(i = 0; i < n*2; i++) {
      x2[i+1] = x2[i] + h;
    }
    h *= 2;
    int flag_quit = 1;
    while(flag_quit){
      for(i = 0; i < n; i++) {
	       printf("\n\n [%d]:\n\n x[%d] = %f ; y[%d] = %f\n\n", i, i, x[i], i,  y[i]);
	        second_block(h, x[i], y, i, k);
        }
        for(i = 0; i < n*2; i++) {
	         printf("\n\n [%d]:\n\n x2[%d] = %f ; y2[%d] = %f\n\n", i, i, x2[i], i,  y2[i]);
	         second_block(h/2, x2[i], y2, i, k);
        }
        for(i = 0; i < n; i++) {
            if (fabs (y[i] - y2[i*2]) > EPS){
              h /= 2;
              n *= 2;
              realloc(x, sizeof(float) * (n+1));
              realloc(y, sizeof(float) * (n+1));
              realloc(x2, sizeof(float) * (n*2+1));
              realloc(y2, sizeof(float) * (n*2+1));
              for(i = 0; i < n; i++)
          	     x[i+1] = x[i] + h;
              h /= 2;
              for(i = 0; i < n*2; i++)
                x2[i+1] = x2[i] + h;
              break;
            }
            flag_quit = 0;
        }
    }

    f = fopen("arrays.txt", "w");

    for(i = 0; i <= n; i++) {
	fprintf(f, "%f %f\n", x[i], y[i]);
    }

    fclose(f);

    printf("\n ");
    return 0;

}
/*gnu
gnuplot> set ylabel "y"
gnuplot> set output "1.png"
gnuplot> plot "arrays.txt" with lines
*/
