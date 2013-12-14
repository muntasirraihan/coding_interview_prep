class intervalTree:

    @staticmethod
    def findMedian(aList):
        sortedList = sorted(aList)
        if len(aList) % 2 == 0:
            return (sortedList[len(aList)/2-1] + sortedList[len(aList)/2])/2.0
        return sortedList[len(aList)/2]
    
    def __init__(self, listOfIntervals):
        # each interval is a tuple

        setOfEndpoints = []
        for interval in listOfIntervals:
            setOfEndpoints.append(interval[0])
            setOfEndpoints.append(interval[1])

        self.x_median = self.findMedian(setOfEndpoints)
        S_left = []
        S_right = []
        S_center = []

        for interval in listOfIntervals:
            if interval[1] < self.x_median:
                S_left.append(interval)
            elif interval[0] > self.x_median:
                S_right.append(interval)
            else:
                S_center.append(interval)
        
        # construct left and right subtrees
        if S_left == []:
            self.left_tree = None
        else:
            self.left_tree = intervalTree(S_left)

        if S_right == []:
            self.right_tree = None
        else:
            self.right_tree = intervalTree(S_right)

        # maintain two sorted lists of intervals for S_center
        self.S_center_by_increasing_left = sorted(S_center, 
                                                key = lambda interval: interval[0])
        self.S_center_by_decreasing_right = sorted(S_center, 
                                                key = lambda interval: interval[1], 
                                                reverse = True)
    
    def find_all_overlapping_intervals(self, point):
        # base case
        if self == None:
            return []

        # normal case
        overlapping_intervals = []
        if point < self.x_median:
            # add all center intervals that start before point
            for interval in self.S_center_by_increasing_left:
                if interval[0] <= point:
                    overlapping_intervals.append(interval)
            # add all overlapping intervals from left_tree
            if self.left_tree:
                overlapping_intervals.extend(self.left_tree.find_all_overlapping_intervals(point))
        elif point > self.x_median:
            # add all center intervals that end after point
            for interval in self.S_center_by_decreasing_right:
                if interval[1] >= point:
                    overlapping_intervals.append(interval)
            # add all overlapping intervals from left_tree
            if self.right_tree:
                overlapping_intervals.extend(self.right_tree.find_all_overlapping_intervals(point))
        else:
            # if point == x_median, then only add all center intervals
            overlapping_intervals = self.S_center_by_increasing_left

        return overlapping_intervals
            
if __name__ == "__main__":
    listOfIntervals = [(0, 2), (1, 4), (2, 5), (3, 5)]
    iTree = intervalTree(listOfIntervals)
    overlap = iTree.find_all_overlapping_intervals(3.1)
    print overlap
