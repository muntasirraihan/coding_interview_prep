class Solution {
    int binarySearch(int low, int high, int x) {
        int mid = (low + high) / 2;
        if (mid == 0) return 1;
        int s = x / mid;
        if (s == mid || low == mid) {
            return mid;
        } else if (s < mid) {
            return bisect(low, mid, x);
        } else {
            return bisect(mid, high, x);
        }
    }
public:
    int sqrt(int x) {
        if (x == 0) return 0;
        return binarySearch(0, x, x);
    }
};