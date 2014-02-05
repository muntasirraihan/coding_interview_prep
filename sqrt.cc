int sqrt(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;

    int low = 0;
    int high = x / 2 + 1;

    while (low < high) {
        int mid = (low + high) / 2;
        int t = x / mid;
        
        // found solution
        if (t == mid) return mid;

        // adjust
        if (t > mid) {
            if (x / (mid + 1) < mid + 1) return mid;
            low = mid;
        }
        if (t < mid) high = mid;
    }
}