
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int num_past_diag;
int num_attr;

int *past_diag_class;
double **past_diag_attr;

double eu_dist(double *X, double *Y, int n) {
  double ret = 0.0;

  for(int i=0; i<n; i++) {
    ret += (X[i] - Y[i])*(X[i] - Y[i]);
  }

  return sqrt(ret);
}

int vote(int *X, int n) {
  int votes[2];

  for(int i=0; i<n; i++) {
    votes[X[i]]++;
  }

  return votes[0] > votes[1] ? 0 : 1;
}

void sort_by(double *X, int *Y, int n) {
  for(int i=0; i<n-1; i++) {
    int minimum_idx = i;

    for(int j=i+1; j<n; j++) {
      if(X[minimum_idx] > X[j]) minimum_idx = j;
    }

    // Swap the values.
    double tmp_X;
    int tmp_Y;
    tmp_X = X[i];
    tmp_Y = Y[i];
    X[i] = X[minimum_idx];
    Y[i] = Y[minimum_idx];
    X[minimum_idx] = tmp_X;
    Y[minimum_idx] = tmp_Y;
  }
}

int knn_diag(double *P, int k) {
  int *votes_class = malloc(sizeof(int) * num_past_diag);
  double *votes_dist = malloc(sizeof(double) * num_past_diag);

  for(int i=0; i<num_past_diag; i++) {
    votes_class[i] = past_diag_class[i];
    votes_dist[i] = eu_dist(past_diag_attr[i], P, num_attr);
  }

  sort_by(votes_dist, votes_class, num_past_diag);

  for(int i=0; i<k; i++) {
    printf("%lf %d\n", votes_dist[i], votes_class[i]);
  }

  int c = vote(votes_class, k);

  free(votes_class);
  free(votes_dist);

  return c;
}

int main() {
  scanf("%d", &num_past_diag);
  scanf("%d", &num_attr);

  // Read the past diagnosis data.
  past_diag_class = malloc(sizeof(int) * num_past_diag);
  past_diag_attr  = malloc(sizeof(double*) * num_past_diag);

  for(int i=0; i<num_past_diag; i++) {
    past_diag_attr[i] = malloc(sizeof(double) * num_attr);

    for(int j=0; j<num_attr; j++) {
      scanf("%lf", &past_diag_attr[i][j]);
    }

    scanf("%d", &past_diag_class[i]);
  }

  // Read testing data.
  double *test_diag_attr;

  test_diag_attr = malloc(sizeof(double) * num_attr);

  for(int j=0; j<num_attr; j++) {
    scanf("%lf", &test_diag_attr[j]);
  }

  int c = knn_diag(test_diag_attr, 3);

  if(c == 0) printf("You are healthy!\n");
  else       printf("You have a heart disease!\n");

  // Release the array.
  free(past_diag_class);

  for(int i=0; i<num_past_diag; i++) {
    free(past_diag_attr[i]);
  }

  free(past_diag_attr);
  free(test_diag_attr);
}
