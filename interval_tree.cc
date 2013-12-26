#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

struct interval {
	int low;
	int high;
	interval (int l, int h): low(l), high(h) {}
};

bool compareIntervalByIncLow(interval i1, interval i2) {
	return (i1.low < i2.low);
}

bool compareIntervalByDecHigh(interval i1, interval i2) {
	return (i1.high > i2.high);
}

class interval_tree {
// fully closed intervals
private:
	int find_median(vector<int> &A) {
		// for interval tree; find approximate median
		int size = A.size();
		// if (size % 2 == 1) {
		// 	// odd
		// 	return nth_element(A.begin(), A.begin() + size / 2, A.end());
		// } else {
		// 	// even
		// 	int a = nth_element(A.begin(), A.begin() + size / 2 - 1, A.end());
		// 	int b = nth_element(A.begin(), A.begin() + size / 2, A.end());
		// 	return (1.0*a + b) / 2.0;
		// }
		nth_element(A.begin(), A.begin() + size / 2, A.end());
		return A[size/2];
	}

	int find_x_center(vector<interval> &intervals) {
		vector<int> A;
		for (int i = 0; i < intervals.size(); ++i) {
			A.push_back(intervals[i].low);
			A.push_back(intervals[i].high);
		}
		return find_median(A);
	}

public:
	int x_center;
	vector<interval> S_center_l;
	vector<interval> S_center_h;

	interval_tree *T_left;
	interval_tree *T_right;

	// construct interval tree from a set of intervals
	interval_tree(vector<interval> &intervals) {
		if (intervals.size() == 0) return;

		// determine x_center = median of all endpoints
		x_center = find_x_center(intervals);

		// determine S_left, S_right and S_center
		vector<interval> S_left;
		vector<interval> S_right;
		for (int i = 0; i < intervals.size(); ++i) {
			interval intv = intervals[i];
			if (intv.high < x_center) {
				S_left.push_back(intv);
			} else if (intv.low > x_center) {
				S_right.push_back(intv);
			} else {
				S_center_l.push_back(intv);
				S_center_h.push_back(intv);
			}
		}

		// sort S_center_l by increasing low endpoints
		if (S_center_l.size() > 0) {
			sort(S_center_l.begin(), S_center_l.end(), compareIntervalByIncLow);
		}	
		// sort S_center_h by decreasing high endpoints
		if (S_center_h.size() > 0) {
			sort(S_center_h.begin(), S_center_h.end(), compareIntervalByDecHigh);
		}

		// construct left and right interval trees
		if (S_left.size() > 0) {
			T_left = new interval_tree(S_left);
		} else {
			T_left = NULL;
		}

		if (S_right.size() > 0) {
			T_right = new interval_tree(S_right);
		} else {
			T_right = NULL;
		}
	}

	vector<interval> query_point(int q) {
		if (q == x_center) return S_center_l;

		vector<interval> results;
		vector<interval> extra;
		if (q < x_center) {
			for (int i = 0; i < S_center_l.size(); ++i) {
				interval intv = S_center_l[i];
				if (intv.low <= q) {
					results.push_back(intv);
				} else {
					break;
				}
			}
			if (T_left != NULL) {
				extra = T_left->query_point(q);
			}			
		} else {
			for (int i = 0; i < S_center_h.size(); ++i) {
				interval intv = S_center_h[i];
				if (intv.high >= q) {
					results.push_back(intv);
				} else {
					break;
				}
			}
			if (T_right != NULL) {
				extra = T_right->query_point(q);
			}	
		}

		for (int j = 0; j < extra.size(); ++j) {
			results.push_back(extra[j]);
		}

		return results;
	}
};

int main() {
	vector<interval> v;
	interval i1 = interval(0, 4);
	interval i2 = interval(2, 6);
	interval i3 = interval(1, 3);
	v.push_back(i1);
	v.push_back(i2);
	v.push_back(i3);
	interval_tree *t = new interval_tree(v);

	vector<interval> results = t->query_point(2);
	for (interval intv : results) {
		cout << intv.low << " " << intv.high << endl;
	}
}
