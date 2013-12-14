class Tree:
    def __init__(self, alist):
        if alist == []:
            return None
        else:
            self.alist = alist

t = Tree([1])
a = Tree([])
print type(t) == type(a)
print a
