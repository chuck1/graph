import pbs2

e = pbs2.Executable(self, "test_lp", __file__)

e.add_dep("graph")

self.parts.append(e)

