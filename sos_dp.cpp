for(ll i = 0; i < (1<<N); i++) F[i] = A[i];
for(ll i = 0; i < N; i++) for(ll mask = 0; mask < (1<<N); mask++){
    if(mask & (1<<i)) F[mask] += F[mask^(1<<i)];
}