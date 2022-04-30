import tsplib95
problem = tsplilb95.load("path")
print("{} {}".format(problem.capacity, problem.capacity*(problem.capacity-1)))
lista = list(problem.get_edges())
for edge in lista:
     peso = problem.get_weight(edge)
     print("{} {} {}".format(edge[0], edge[1], peso))