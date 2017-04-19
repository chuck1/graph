import pbs2

e = pbs2.Executable(self, "test_cycles", __file__)

e.add_dep("graph")

self.parts.append(e)

