class Tree:
	def __init__(self, value, ltree, rtree):
		self.value = value
		self.ltree = ltree
		self.rtree = rtree

def DFS(tree_node, visited):

	# pre-order
	if visited.has_key(tree_node) and visited[tree_node]:	
		return
	print tree_node.value #visit function is print
	visited[tree_node] = True

	if tree_node.ltree != None:
		DFS(tree_node.ltree, visited)
	if tree_node.rtree != None:
		DFS(tree_node.rtree, visited)


new_tree = Tree('A', Tree('B', Tree('D', None, None), Tree('E', None, None)), Tree('C', Tree('F', None, None), None))
DFS(new_tree, {})

print '----------------	'

def DFS_iterative(tree_node):
	visited = {}
	stack = []

	# pre-order
	stack.append(tree_node)
	while not len(stack) == 0:
		node = stack.pop()
		if visited.has_key(node) and visited[node]:
			continue
		print node.value
		visited[node] = True

		if node.rtree != None:
			stack.append(node.rtree)
		if node.ltree != None:
			stack.append(node.ltree)


new_tree = Tree('A', Tree('B', Tree('D', None, None), Tree('E', None, None)), Tree('C', Tree('F', None, None), None))

DFS_iterative(new_tree)