#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct xn {
  int n;
  double *x;
  double *sum;
  double *err;
};

unsigned long long factorial(int n) {
  if (n == 0)
    return 1;
  unsigned long long result = 1;
  for (int i = 1; i <= n; i++) {
    result *= i;
  }
  return result;
}

double math_sin_factorial(double x, int n) {
  return (pow(-1, n) * pow(x, 2 * n + 1)) / factorial(2 * n + 1);
}

double math_cos_factorial(double x, int n) {
  return (pow(-1, n) * pow(x, 2 * n)) / factorial(2 * n);
}

double math_exp_factorial(double x, int n) { return pow(x, n) / factorial(n); }

double math_ln_factorial(double x, int n) {
  return pow(-1, n) * pow(x, n + 1) / (n + 1);
}
//
double math_sin_recurrence(double x, int n) {
  if (n == 0)
    return x;
  return math_sin_recurrence(x, n - 1) * (-1) * (x * x) /
         ((2 * n) * (2 * n + 1));
}

double math_cos_recurrence(double x, int n) {
  if (n == 0)
    return 1;
  return math_cos_recurrence(x, n - 1) * (-1) * (x * x) /
         ((2 * n - 1) * (2 * n));
}

double math_exp_recurrence(double x, int n) {
  if (n == 0)
    return 1;
  return math_exp_recurrence(x, n - 1) * x / n;
}

double math_ln_recurrence(double x, int n) {
  if (n == 0)
    return x;
  return math_ln_recurrence(x, n - 1) * (-x * (n)) / (n + 1);
}

void init(struct xn *data, int n) {
  data->n = n;
  data->x = (double *)malloc(n * sizeof(double));
  data->sum = (double *)malloc(n * sizeof(double));
  data->err = (double *)malloc(n * sizeof(double));
}

void init_station(struct xn *data, double (*func)(double, int), double x) {
  if (func == math_sin_factorial) {
    data->sum[0] = func(x, 0);
    data->err[0] = fabs(sin(x) - data->sum[0]);
  }
  if (func == math_cos_factorial) {
    data->sum[0] = func(x, 0);
    data->err[0] = fabs(cos(x) - data->sum[0]);
  }
  if (func == math_exp_factorial) {
    data->sum[0] = func(x, 0);
    data->err[0] = fabs(exp(x) - data->sum[0]);
  }
  if (func == math_ln_factorial) {
    data->sum[0] = func(x, 0);
    data->err[0] = fabs(log(x + 1) - data->sum[0]);
  }
  if (func == math_sin_recurrence) {
    data->sum[0] = math_sin_recurrence(x, 0);
    data->err[0] = fabs(sin(x) - data->sum[0]);
  }
  if (func == math_cos_recurrence) {
    data->sum[0] = math_cos_recurrence(x, 0);
    data->err[0] = fabs(cos(x) - data->sum[0]);
  }
  if (func == math_exp_recurrence) {
    data->sum[0] = math_exp_recurrence(x, 0);
    data->err[0] = fabs(exp(x) - data->sum[0]);
  }
  if (func == math_ln_recurrence) {
    data->sum[0] = math_ln_recurrence(x, 0);
    data->err[0] = fabs(log(x + 1) - data->sum[0]);
  }
}

void fill(struct xn *data, double (*func)(double, int), double x) {
  for (int n = 1; n < data->n; n++) {
    if (func == math_sin_factorial) {
      data->sum[n] = data->sum[n - 1] + func(x, n);
      data->err[n] = fabs(sin(x) - data->sum[n]);
    }
    if (func == math_cos_factorial) {
      data->sum[n] = data->sum[n - 1] + func(x, n);
      data->err[n] = fabs(cos(x) - data->sum[n]);
    }
    if (func == math_exp_factorial) {
      data->sum[n] = data->sum[n - 1] + func(x, n);
      data->err[n] = fabs(exp(x) - data->sum[n]);
    }
    if (func == math_ln_factorial) {
      data->sum[n] = data->sum[n - 1] + func(x, n);
      data->err[n] = fabs(log(x + 1) - data->sum[n]);
    }
    if (func == math_sin_recurrence) {
      data->sum[n] = data->sum[n - 1] + func(x, n);
      data->err[n] = fabs(sin(x) - data->sum[n]);
    }
    if (func == math_cos_recurrence) {
      data->sum[n] = data->sum[n - 1] + func(x, n);
      data->err[n] = fabs(cos(x) - data->sum[n]);
    }
    if (func == math_exp_recurrence) {
      data->sum[n] = data->sum[n - 1] + func(x, n);
      data->err[n] = fabs(exp(x) - data->sum[n]);
    }
    if (func == math_ln_recurrence) {
      data->sum[n] = data->sum[n - 1] + func(x, n);
      data->err[n] = fabs(log(x + 1) - data->sum[n]);
    }
  }
}

void free_memory(struct xn *data) {
  free(data->x);
  free(data->sum);
  free(data->err);
}

int main() {
  struct xn data_sin_factorial;
  int n = 10;
  double x = M_PI / 6;

  init(&data_sin_factorial, n);
  init_station(&data_sin_factorial, math_sin_factorial, x);
  fill(&data_sin_factorial, math_sin_factorial, x);

  printf("sin_factorial\nn\tSum\t\t\tError\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%.15f\t%.15f\n", i, data_sin_factorial.sum[i],
           data_sin_factorial.err[i]);
  }

  free_memory(&data_sin_factorial);

  struct xn data_cos_factorial;

  init(&data_cos_factorial, n);
  init_station(&data_cos_factorial, math_cos_factorial, x);
  fill(&data_cos_factorial, math_cos_factorial, x);

  printf("cos_factorial\nn\tSum\t\t\tError\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%.15f\t%.15f\n", i, data_cos_factorial.sum[i],
           data_cos_factorial.err[i]);
  }

  free_memory(&data_cos_factorial);

  struct xn data_exp_factorial;

  init(&data_exp_factorial, n);
  init_station(&data_exp_factorial, math_exp_factorial, x);
  fill(&data_exp_factorial, math_exp_factorial, x);

  printf("exp_factorial\nn\tSum\t\t\tError\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%.15f\t%.15f\n", i, data_exp_factorial.sum[i],
           data_exp_factorial.err[i]);
  }

  free_memory(&data_exp_factorial);

  struct xn data_ln_factorial;

  init(&data_ln_factorial, n);
  init_station(&data_ln_factorial, math_ln_factorial, x);
  fill(&data_ln_factorial, math_ln_factorial, x);

  printf("ln_factorial\nn\tSum\t\t\tError\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%.15f\t%.15f\n", i, data_ln_factorial.sum[i],
           data_ln_factorial.err[i]);
  }

  free_memory(&data_ln_factorial);

  struct xn data_sin_recurrence;

  init(&data_sin_recurrence, n);
  init_station(&data_sin_recurrence, math_sin_recurrence, x);
  fill(&data_sin_recurrence, math_sin_recurrence, x);

  printf("sin_recurrence\nn\tSum\t\t\tError\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%.15f\t%.15f\n", i, data_sin_recurrence.sum[i],
           data_sin_recurrence.err[i]);
  }

  free_memory(&data_sin_recurrence);

  struct xn data_cos_recurrence;

  init(&data_cos_recurrence, n);
  init_station(&data_cos_recurrence, math_cos_recurrence, x);
  fill(&data_cos_recurrence, math_cos_recurrence, x);

  printf("cos_recurrence\nn\tSum\t\t\tError\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%.15f\t%.15f\n", i, data_cos_recurrence.sum[i],
           data_cos_recurrence.err[i]);
  }

  free_memory(&data_cos_recurrence);

  struct xn data_exp_recurrence;

  init(&data_exp_recurrence, n);
  init_station(&data_exp_recurrence, math_exp_recurrence, x);
  fill(&data_exp_recurrence, math_exp_recurrence, x);

  printf("exp_recurrence\nn\tSum\t\t\tError\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%.15f\t%.15f\n", i, data_exp_recurrence.sum[i],
           data_exp_recurrence.err[i]);
  }

  free_memory(&data_exp_recurrence);

  struct xn data_ln_recurrence;

  init(&data_ln_recurrence, n);
  init_station(&data_ln_recurrence, math_ln_recurrence, x);
  fill(&data_ln_recurrence, math_ln_recurrence, x);

  printf("ln_recurrence\nn\tSum\t\t\tError\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%.15f\t%.15f\n", i, data_ln_recurrence.sum[i],
           data_ln_recurrence.err[i]);
  }

  free_memory(&data_ln_recurrence);

  return 0;
}
