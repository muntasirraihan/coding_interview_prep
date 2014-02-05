

// <hash, vector<filenames>>
unordered_map<int, vector<string> > visited;

struct TreeNode {
	bool isDir;
	string filename;
	long file_size;
	vector<TreeNode *> children;
};

#define CHUNK_SIZE 1024

int hash(string filename) {
	// read file content
	int file_size = get_file_size(filename);
	int bytes_read = 0;
	int fd = open(filename);
	int hash_val = 0;
	int bytes_to_read;
	while (bytes_read <= file_size) {
		if (bytes_read + CHUNK_SIZE > file_size) {
			bytes_to_read = file_size - bytes_read;
		} else {
			bytes_to_read = CHUNK_SIZE;	
		}
		void *mem_start = mmap(fd, start, bytes_to_read);
		bytes_read += CHUNK_SIZE;
		
		if (hash_val == 0) {
			hash_val = hash_digest(mem_start);
		} else {
			hash_val = hash_update(hash_val, mem_start);
		}
		free(mem_start);
	}

	close(fd);
	// return hash
	return hash_val;
}

void DFS(TreeNode *root) {
	if (root == NULL) return;

	// mark visited
	visited(hash(root->filename)).push_back(root->filename);

	// visited children if directory
	if (root->isDir) {
		for (int i = 0; i < root->children.size(); ++i) {
			DFS(root->children[i]);
		}
	}

	return;
}

void dupes(TreeNode *root) {
	vector<vector<string> > dups;
	DFS(root);

	for (unordered_map<int, vector<string> >::iterator iter = visited.begin();
		iter != visited.end(); ++iter) {

		if (iter->second.size() > 1) {
			dups.push_back(iter->second);
		}
	}
	return dups;
}

unordered_map<int, vector<string> > file_size_map;
unordered_map<int, vector<string> > visited;

for (unordered_map<int, vector<string> >::iterator iter = file_size_map.begin();
	iter != file_size_map.end(); ++iter) {

	for (int i = 0; i < iter->second.size(); ++i) {
		if (visited.find(hash(iter->second[i])) != visited.end()) {
			visited[hash(iter->second[i])].push_back(iter->second[i]);
		} else {
			
		}
	}
}



