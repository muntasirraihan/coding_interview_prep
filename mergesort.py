# Nov 18, 2013

# assume data can be modified
def mergesort(data, n):
	if n == 1:
		return data
	return merge(mergesort(data[0:n/2], n/2),
			mergesort(data[n/2:], n-n/2),
			n/2,
			n-n/2)

def merge(left, right, nLeft, nRight):
	sortedData = []
	iLeft = 0
	iRight = 0
	while (iLeft < nLeft) and (iRight < nRight):
		if left[iLeft] < right[iRight]:
			sortedData.append(left[iLeft])
			iLeft += 1
		else:
			sortedData.append(right[iRight])
			iRight += 1
	if iLeft < nLeft:
		sortedData.extend(left[iLeft:])
	elif iRight < nRight:
		sortedData.extend(right[iRight:])
		
	return sortedData

unsorted = [5, 2, 1, 6]
print mergesort(unsorted, len(unsorted))

unsorted = [2, 1, 6]
print mergesort(unsorted, len(unsorted))

unsorted = [7, 3, 2, 1, 6]
print mergesort(unsorted, len(unsorted))

unsorted = [0]
print mergesort(unsorted, len(unsorted))