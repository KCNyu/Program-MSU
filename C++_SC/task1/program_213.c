for(i = 2; i <= n+1; ++i){
   for(j = 2; j <= m+1; ++j){
      C[i][j] = C[i][j + 1] + D[i][j];  
   }
}

for(i = 2; i <= n+1; ++i){
#pragma omp parallel for
   for(j = 2; j <= m+1; ++j){
      B[i][j] = B[i - 1][j] + C[2][2];
   }
}
#pragma omp parallel for
for(i = 2; i <= n+1; ++i){
   for(j = 2; j <= m+1; ++j){
#pragma omp parallel for
      for(k = 1; k <= n; ++k){
         A[i][j][k] = A[i][j][k] + A[i][j - 1][1] + C[i][m + 1];
      }
   }
}
