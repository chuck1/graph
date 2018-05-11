import pbs

e = pbs.Executable(self, "test_graph_0", __file__)

e.add_dep("graph")

self.parts.append(e)

