def qsort(data):
	n = len(data)
	if n == 0:
		return data
	if n == 1:
		return data
	pivot = data[n/2]
	data.pop(n/2)
	left = [x for x in data if x<=pivot]
	right = [x for x in data if x>pivot]
	return qsort(left) + [pivot] + qsort(right)

unsorted = [5, 2, 1, 6]
print qsort(unsorted)

unsorted = [5, 2, 2, 2, 1, 6]
print qsort(unsorted)

unsorted = [2, 1, 6]
print qsort(unsorted)

unsorted = [7, 3, 2, 1, 6]
print qsort(unsorted)

unsorted = [0]
print qsort(unsorted)