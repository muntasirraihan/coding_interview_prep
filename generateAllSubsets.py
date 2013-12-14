import copy

universe = [1, 2, 3]

def backtrack(selector, nstage):
	# filled out a full subset
	if nstage == len(universe):
		print_subset(selector)
		return

	selector_true = copy.deepcopy(selector)
	selector_true.append(True)

	selector_false = copy.deepcopy(selector)
	selector_false.append(False)

	backtrack(selector_true, nstage+1)
	backtrack(selector_false, nstage+1)

def print_subset(selector):
	subset = []
	for i in xrange(len(selector)):
		if selector[i]:
			subset.append(universe[i])
	print subset



# initialize selector to be all false
a_selector = []

backtrack(a_selector, 0)

