# hashtable using
# separate chaining (closed addressing) with linked list

class hashtable():
	def __init__(self, hash_func=hash, table_size = 100):
		self.hash_func = hash_func
		self.table_size = table_size
		self.data_store = []
		for i in xrange(table_size):
			self.data_store.append([])

	def put(self, k, v):
		entry = self.data_store[self.hash_func(k) % self.table_size]
		entry.append((k, v))

	def get(self, k):
		entry = self.data_store[self.hash_func(k) % self.table_size]
		for (key, val) in entry:
			if key == k:
				return val

	def delete(self, k):
		entry = self.data_store[self.hash_func(k) % self.table_size]
		new_entry = [item for item in entry if item[0]!=k]
		self.data_store[self.hash_func(k) % self.table_size] = new_entry

	def exists(self, k):
		entry = self.data_store[self.hash_func(k) % self.table_size]
		for (key, val) in entry:
			if key == k:
				return True
		return False

	

ht = hashtable()
ht.put(1, 'A')
ht.put(2, 'B')
ht.put(3, 'C')
ht.put(4, 'D')


print ht.get(1)
print ht.get(2)
print ht.get(3)


print ht.exists(1)
ht.delete(1)
ht.delete(6)
print ht.exists(1)