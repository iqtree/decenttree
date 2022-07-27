import numpy;
import pydecenttree;

#Todo: Each of these generate different error messages

#pydecenttree.constructTree()
#should complain, no algorithm

#pydecenttree.constructTree('wrong')
#should complain no list of sequences
#(should it also complain, invalid algorithm name?)

#pydecenttree.constructTree('wrong', ['cat','dog'])
#should complain, only two sequences
#(should it also complain, invalid algorithm name?)

#pydecenttree.constructTree('wrong', ['cat','dog', 'rat'], [0,1,1,0], 0)
#Should return an error saying distance matrix is wrong size.

#pydecenttree.constructTree('NJ-R', ['cat','dog', 'rat'], [0,1,1,1,0,1,1,1,0], 0, -2)
#Should say negative precision is nonsensical

#s = pydecenttree.constructTree('NJ-R', ['cat','dog', 'rat'], [0,1,1,1,0,1,1,1,0], -1, 6, 2)
# print (s)
#should work and output (cat:0.5,dog:0.5,rat:0.5).

# s = pydecenttree.constructTree('NJ-R', ['cat','dog', 'rat'], [[0,1,1] ,[1,0,1] ,[2,2]], -1, 6, 2)
# should fail, because third row only has two items

#s = pydecenttree.constructTree('NJ-R', ['cat','dog', 'rat'], [[0,1,1] ,[1,0,1] ,[1,1,0]], -1, 6, 2)
#print (s)
#should work and output (cat:0.5,dog:0.5,rat:0.5).

dm = numpy.array([[0,2,2], [2,0,2], [2,2,0]], dtype=numpy.double)
s = pydecenttree.constructTree('NJ-R', ['cat','dog', 'rat'], dm, -1, 6, 2)
print (s)


