class BST:
	def __init__(self, value, ltree, rtree):
		self.value = value
		self.ltree = ltree
		self.rtree = rtree

	def insert(val):
		if val < self.value:
			if self.ltree == None:
				self.ltree = BST(val, None, None)
			else:
				self.ltree.insert(value)
		else:
			if self.rtree == None:
				self.rtree = BST(val, None, None)
			else:
				self.rtree.insert(val)

	def find(val):
		if val == self.value:
			return self
		if val < self.value:
			if self.ltree == None:
				return None
			else:
				self.ltree.find(val)
		else:
			if self.rtree == None:
				return None
			else:
				self.rtree.find(val)