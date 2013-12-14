s = '{}[(])'

# use stack to store forward braces
# that remains to be matched
braces_stack = []

for brace in s:
    # push new forward brace seen onto stack
    if brace in ['[', '{', '(']:
        braces_stack.append(brace)
    else:
        # if backward braces comes up next
        # and all forward braces seen so far have been matched
        if braces_stack == []:
            print 'ERROR: backward brace comes up first'
            exit(0)
        # if backward brace comes up next
        # check if it matches with the most recently seen forward brace
        else:
            old_brace = braces_stack.pop()
            if brace == ']' and old_brace != '[' \
                or brace == '}' and old_brace != '{' \
                    or brace == ')' and old_brace != '(':
                        print 'ERROR: backward brace not matched'
                        exit(0)

# if all backward braces have been matched
# check if there are remaining forward braces to be matched
if braces_stack != []:
    print 'ERROR: extra braces found'
    exit(0)

print 'all braces matched'
            
